/*
 * @Author       : chao
 * @Date         : 2024-01-01 15:27:46 +0800
 * @LastEditors  : yan yzc53@icloud.com
 * @LastEditTime : 2024-01-04 01:50:53 +0800
 * @FilePath     : /malloc/tests/progs/thread-safety.c
 * @Description  : 
 * @QQ           : 1594047159@qq.com
 * Copyright (c) 2024,All Rights Reserved. 
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "allocator.h"

#define THREADS_PER_ROUND 2500
#define NUM_ROUNDS 10
#define MAX_ALLOC 2050

void *thread_proc(void *arg)
{
    int i, r;

    r = rand() % MAX_ALLOC;
    int *mem = malloc(sizeof(int) * r);
    for (i = 0; i < r; ++i) {
        mem[i] = (long) arg;
    }

    unsigned long total = 0;
    for (i = 0; i < r; ++i) {
        total += mem[i];
    }

    if (total != ((long) arg) * r) {
        printf("Mismatch of array total! Memory corruption?\n");
    }

    free(mem);
    return 0;
}


int main(void)
{
    //srand(time(0));
    srand(time(0));
    clock_t t1 = clock();

    pthread_t threads[THREADS_PER_ROUND];
    int i, j;

    for (i = 0; i < NUM_ROUNDS; ++i) {
        for (j = 0; j < THREADS_PER_ROUND; ++j) {
            pthread_create(&threads[j], NULL, thread_proc, (void *) (long) j);
        }

        for (j = 0; j < THREADS_PER_ROUND; ++j) {
            pthread_join(threads[j], NULL);
        }
    }
    clock_t t2 = clock();
    printf("Performed %d rounds of %d multi-threaded allocations in %.2fs\n",
            NUM_ROUNDS,THREADS_PER_ROUND, ((float)(t2 - t1))/CLOCKS_PER_SEC);

    return 0;
}