/*
 * @Author       : chao
 * @Date         : 2023-11-10 16:12:17 +0800
 * @LastEditors  : yan yzc53@icloud.com
 * @LastEditTime : 2024-01-06 08:57:20 +0800
 * @FilePath     : /malloc/allocator.c
 * @Description  :
 * @QQ           : 1594047159@qq.com
 * Copyright (c) 2023,All Rights Reserved.
 */

#include "allocator.h"

/* aligned the size to 16 bytes */
#define ALIGNED(size) ((((size) + 15) / 16) * 16)
/* define the minimium size of block: 16 bytes of data portion and the head size*/
#define MIN_BLOCK_SIZE (ALIGNED(sizeof(struct block) + 16))
/* according to the requested size, return the block size  */
#define BLOCK_SIZE(size) (ALIGNED(sizeof(struct block) + (size)))

/* free the block */
#define FREE(bp) ((bp->size) = (bp->size) & (~(0x1)))
/* set the block */
#define SET(bp) ((bp->size) = (bp->size) | (0x1))

/* get pointer of next free block from current free block */
#define NEXT_FREE_BLOCK(ptr) (((struct link *)(ptr + 1))->succ)
/* get pointer of previous free block from current free block */
#define PREV_FREE_BLOCK(ptr) (((struct link *)(ptr + 1))->pred)
/* acquire the allocate state  */
#define GET_ALLOC(bp) (bp->size & (0x1))
#define GET_SIZE(bp) (bp->size & (~0x7))

struct block *head = NULL, *tail = NULL;
struct block *freed = NULL;

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mach/mach.h>

#ifdef __APPLE__
    #define OS "macOS"
#elif __linux__
    #define OS "linux"
#else
    #define OS "unknown"
#endif

size_t vmsize()
{
    size_t num;
    if(strcmp(OS,"macOS") == 0)
    {
        // 获取当前进程的任务端口
        task_t task = mach_task_self();
        // 定义一个结构来保存任务信息
        task_basic_info_data_t info;
        mach_msg_type_number_t count = TASK_BASIC_INFO_COUNT;
        kern_return_t result = task_info(task, TASK_BASIC_INFO, (task_info_t)&info, &count);
        if (result == KERN_SUCCESS) {
            // 虚拟字节数量/虚拟页面大小 
            num =  info.virtual_size / sysconf(_SC_PAGESIZE);
            // 虚拟页面数量，以页面为单位
            return num;
        } else {
            fprintf(stderr, "Failed to get task info\n");
            return 0;
        }

    }else if(strcmp(OS,"linux") == 0)
    {
        pid_t pid = getpid();
        char path[4096] = {0};
        /* read the info of process according to its pid from its file located at /proc/pid/statm */
        sprintf(path,"/proc/%d/statm",pid);
        FILE *p = fopen(path,"r");
        /* the first data in /proc/%d/statm represents its virtual memory pages */
        fscanf(p,"%zu",&num);
        return num;
    }
    return 0;
}

static void add_to_freelist(struct block *ptr)
{
    NEXT_FREE_BLOCK(ptr) = freed;
    PREV_FREE_BLOCK(freed) = ptr;
    PREV_FREE_BLOCK(ptr) = NULL;
    freed = ptr;
}

static void remove_from_freelist(struct block *ptr)
{
    struct block *pred = PREV_FREE_BLOCK(ptr);
    struct block *succ = NEXT_FREE_BLOCK(ptr);
    if(pred)
    {
        NEXT_FREE_BLOCK(pred) = succ;
    }
    if(succ)
    {
        PREV_FREE_BLOCK(succ) = pred;
    }
    /* ptr is the first block in the free list */
    if(ptr == freed)
    {
        freed = succ;
    }
}

static void merge_block(struct block *ptr1, struct block *ptr2)
{
    ptr1->size += ptr2->size;
    if(ptr2 != tail)
    {
        ptr2->next->prev = ptr1;
        ptr1->next = ptr2->next;
    }else
    {
        tail = ptr1;
        ptr1->next = NULL;
    }
}

static struct block *split_off(struct block *bp, size_t size)
{
    struct block *fbp = (struct block *)((char *)bp + size);
    
    /* link up */
    fbp->next = bp->next;
    fbp->prev = bp;
    bp->next = fbp;
    /* strech the tail */
    if (bp == tail)
        tail = fbp;
    
    /* size info */
    fbp->size = bp->size - size;
    bp->size = size;

    /* Region this block is a part of,This should point to the first block in the region */
    fbp->region = bp->region;
    fbp->rsize = 0;
    return fbp;
}

void *search(size_t size)
{
    struct block *ptr = freed;
    char *algo = getenv("ALLOCATOR_ALGORITHM");
    if (algo == NULL)
    {
        algo = "first_fit";
    }
    if (strcmp(algo, "first_fit") == 0)
    {
        while (ptr)
        {
            if (ptr->size >= size)
            {
                break;
            }
            else
            {
                /* move forward */
                ptr = NEXT_FREE_BLOCK(ptr);
            }
        }
        if(ptr == NULL)
            return NULL;
    }
    else if (strcmp(algo, "best_fit") == 0)
    {
        struct block *mark = NULL;
        while(ptr)
        {
            if (ptr->size >= size)
            {
                if(!mark || ptr->size < mark->size)
                {
                    mark = ptr;
                }
            }
            ptr = NEXT_FREE_BLOCK(ptr);
        }
        /* if mark == NULL, whether the freed list is empty or we don't find the suitable block */
        if(mark == NULL)
            return NULL;
        else
            /* we find the best fit */
            ptr = mark;
    }
    else if (strcmp(algo, "worst_fit") == 0)
    {
        struct block *mark = NULL;
        while(ptr)
        {
            if (ptr->size >= size)
            {
                if(!mark || ptr->size > mark->size)
                {
                    mark = ptr;
                }
            }
            ptr = NEXT_FREE_BLOCK(ptr);
        }
        /* we find the worst fit */
        if(mark == NULL)
            return NULL;
        else
            ptr = mark;
    }

    remove_from_freelist(ptr);
    /* set the next free block point and previous free block point as NULL  */
    NEXT_FREE_BLOCK(ptr) = NULL;
    PREV_FREE_BLOCK(ptr) = NULL;
    return (void *)ptr;
}

static void place(void *ptr, size_t block_size)
{
    struct block *bp = (struct block *)ptr;
    if (bp->size - block_size >= MIN_BLOCK_SIZE)
    {
        /* split a new block from bp */
        struct block *fbp = split_off(bp,block_size);
        /* Insert fbp into free block list */
        NEXT_FREE_BLOCK(fbp) = freed;
        PREV_FREE_BLOCK(fbp) = NULL;
        freed = fbp;
    }
}



void *malloc(size_t request_size)
{
    /* If size
     * is 0, then malloc() returns a unique pointer value that can later
     * be successfully passed to free()
     */
    if (request_size == 0)
        return NULL;

    /* returned ptr of data portion */
    void *rptr = NULL;


    /* caclulate the blocksize according to request_size */
    size_t block_size = BLOCK_SIZE(request_size);

    /* block_size must be larger than the MIN_BLOCK_SIZE */
    if(block_size < MIN_BLOCK_SIZE)
        block_size = MIN_BLOCK_SIZE;
    /* search the list of only free block  */
    void *ptr = search(block_size);
    
    if (ptr == NULL)
    {
        /* acquire the page size of system */
        size_t page_size = sysconf(_SC_PAGESIZE);

        /* calculate how many pages we need*/
        size_t page_num = (block_size / page_size + 1);

        /* calculate the total bytes of memory we need  */
        size_t region_size = page_num * page_size;

        /* virtual memory map */
        // ptr = mmap(NULL, region_size, PROT_WRITE | PROT_READ | PROT_EXEC, MAP_ANON | MAP_PRIVATE, 0, 0);
        ptr = mmap(
            NULL, /* Address (we use NULL to let the kernel decide) */
            region_size, /* Size of memory block to allocate */
            PROT_READ | PROT_WRITE, /* Memory protection flags */
            MAP_PRIVATE | MAP_ANON, /* Type of mapping */
            -1, /* file descriptor */
            0 /* offset to start at within the file */);

        /* assertation whether map is successful */
        assert(ptr != MAP_FAILED);

        struct block *bk = (struct block *)ptr;
        /*
         * region_size is the sizeof the mapped region whihc is a multiple of pages(one page is 16348 bytes),which can be devided evenly by 16
         * so the 0th bit of (bk->size) is automatically 0,meaning it's now free.
         */
        bk->size = region_size;
        /* point to the first block in the region */
        bk->region = bk;
        
        if (head == NULL && tail == NULL)
        {
            head = bk;
            tail = bk;
            bk->next = NULL;
            bk->prev = NULL;
        }
        else
        {
            tail->next = bk;
            bk->prev = tail;
            bk->next = NULL;
            tail = bk;
        }
    }
    place(ptr,block_size);
    struct block *bk1 = (struct block *)ptr;
    bk1->rsize = request_size;
    SET(bk1);    // the whole block as allocated
    rptr = (void *)(bk1 + 1);
    return rptr;
}



void free(void *ptr)
{
    /* 
     * If ptr is NULL, no operation is
     * performed.
     */
    if(ptr == NULL)
        return;

    struct block *bp = (((struct block *)ptr) - 1);

    /* if bp block is already freed, then abort the process */
    /* if ptr has already been freed, undefined behavior occurs */
    assert(GET_ALLOC(bp) != 0);
    
    /* free the block */
    FREE(bp);
    
    /* the neigboring block of bp */
    struct block *bp_next = bp->next;
    struct block *bp_prev = bp->prev;
    
    /*  check neighboring blocks to determine whether you can merge with them or not. */
    bool  prev_mergeable = false,next_mergeable = false;
    if( bp_next && bp_next->region == bp->region && GET_ALLOC(bp_next) == 0 )
    {
        next_mergeable = true;
    }
    if( bp_prev && bp_prev->region == bp->region && GET_ALLOC(bp_prev) == 0 )
    {
        prev_mergeable = true;
    } 
    /* case 1: both bp_next and bp_prev are not mergeable */
    if (prev_mergeable == false && next_mergeable == false) 
    {
        add_to_freelist(bp);
    }
    /* case 2: bp_next is mergeable */
    if (prev_mergeable == false && next_mergeable == true) 
    {
        merge_block(bp, bp_next);
        remove_from_freelist(bp_next);
        add_to_freelist(bp);
    }
    /* case 3: only prev block is mergeable */
    if (prev_mergeable == true && next_mergeable == false)
    {
        merge_block(bp_prev, bp);
        /* bp move forwards */
        bp = bp_prev;
    }
    /* case 4: both prev block and next block are  mergeable */
    if (prev_mergeable == true && next_mergeable == true) 
    {
        merge_block(bp_prev,bp);
        merge_block(bp_prev,bp_next);
        remove_from_freelist(bp_next);
        /* bp move forwards */
        bp = bp_prev;
    }
    bp->rsize = 0;
    /* use flag1 and flag2 to judge whether we should munmap bp block */
    bool flag1 = false,flag2 = false;
    if(!bp->prev)
    {
        flag1 = true;
    }else{
        if(bp->prev->region != bp->region)
        {
            flag1 = true;
        }
    }
    if(!bp->next)
    {
        flag2 = true;
    }else{
        if(bp->next->region != bp->region)
        {
            flag2 = true;
        }
    }
    /* only if both flag1 and flag2 are true that we can munmap bp block  */
    if(flag1 == true && flag2 == true)
    {
        if(bp == head && bp == tail)
        {
            head = NULL;
            tail = NULL;
        }else if(bp == head)
        {
            head = bp->next;
            head->prev = NULL;
        }else if(bp == tail)
        {
            tail = bp->prev;
            tail->next = NULL;
        }else{
            bp->next->prev = bp->prev;
            bp->prev->next = bp->next;
        }
        bp->next = NULL;
        bp->prev = NULL;
        remove_from_freelist(bp);
        assert(munmap(bp,bp->size) == 0);
    }
    return;
}



void *realloc(void *ptr, size_t size)
{
    if(ptr == NULL)
    {
        return malloc(size);
    }
    if(ptr != NULL && size == 0)
    {
        free(ptr);
        return NULL;
    }
    struct block *bp = (((struct block*)ptr) - 1);
    /* The block already has some extra space
     * no changes need to be made
     * block can be resized in place.
     */
    if(bp->size - sizeof(struct block) >= size)
    {
        if(size >= bp->rsize)
        {
            bp->rsize = size;
            return ptr;
        }else
        {
            /* shrunk_size is the block size when request for size bytes */
            size_t shrunk_size = BLOCK_SIZE(size);
            if(bp->size - shrunk_size >= MIN_BLOCK_SIZE)
            {
                /* split off (bp->size - shrunk_size) free space from bp to form fbp */
                struct block *fbp = split_off(bp,shrunk_size);
                /*  if fbp is located next to another free block, they should be merged. */
                struct block *btk = fbp->next;
                /* if btk block is in the free list and mergeable */
                if( btk && btk->region == fbp->region && GET_ALLOC(btk) == 0)
                {
                    merge_block(fbp,btk);
                    remove_from_freelist(btk);
                    add_to_freelist(fbp);
                }
            }          
            bp->rsize = size;
            return ptr;
        }
    }else{
        struct block *fbp = bp->next;
        if(fbp && fbp->region == bp->region && GET_ALLOC(fbp) == 0)
        {
            /* calculate neighboring block size + bp's data portion*/
            /* check whether the block can expand into a neighboring free block. */
            if(fbp->size + (bp->size - sizeof(struct block)) >= size)
            {
                merge_block(bp,fbp);
                remove_from_freelist(fbp);
                place(bp,BLOCK_SIZE(size));
                bp->rsize = size;
                return ptr;
            }
        }
    } 
    void *rptr = malloc(size);
    memcpy(rptr,ptr,bp->rsize);
    free(ptr);
    return rptr;
}

static bool no_overflow(size_t x, size_t y) {
    size_t p = x * y;
    return !x || p / x == y;
}

void *calloc(size_t nmemb, size_t size)
{
    if( nmemb == 0 || size == 0 )
        return NULL;
    if( no_overflow(nmemb, size) == false)
    {
        errno = EOVERFLOW;
        return (void*)-1;
    }
    void *ptr = malloc(nmemb * size);
    memset(ptr,0,nmemb * size);
    return ptr;
}


void print_memory()
{
    print_blocklist();
    print_freelist();
}

void print_blocklist()
{
    printf("-- Current Memory State --\n");
    struct block *ptr = head;
    struct block *region = NULL;
    while(ptr)
    {
        if(ptr->region != region)
        {
            printf("[REGION %p]\n",ptr->region);
            region = ptr->region;
        }
        printf("\t[BLOCK %p-%p]\t%8zd(%zd)",ptr,(char*)ptr + GET_SIZE(ptr),GET_SIZE(ptr),ptr->rsize);
        if(GET_ALLOC(ptr) == 1)
            printf("\t\t[USED]\n");
        else
            printf("\t\t[FREE]\n");
        ptr = ptr->next;
    }
}

void print_freelist()
{
    printf("-- Free List --\n");
    struct block *ptr = freed;
    while(ptr)
    {
        printf("[%p] -> ",ptr);
        ptr = NEXT_FREE_BLOCK(ptr);
    }
    printf("NULL\n");
}

void leak_check()
{
    printf("-- Leak Check --\n");
    struct block *ptr = head;
    size_t cnt = 0;
    size_t sum = 0;
    while(ptr)
    {
        printf("[BLOCK %p]\t%zd\n",ptr,ptr->size);
        cnt += 1;
        sum += ptr->size;
        ptr = ptr->next;
    }
    printf("-- Summary --\n");
    printf("%zd blocks lost (%zd bytes)\n",cnt,sum);
}