#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "allocator.h"

#define NUM_ROUNDS 50
#define NUM_ALLOCATIONS 10
#define ALLOC_SZ 50000


int main()
{
    size_t vm_limit = 512;
    srand(time(0));
    for( int i = 0; i < NUM_ROUNDS; ++i)
    {
        size_t vm_start = vmsize();
        printf("[%d]th rounds: Virtual Memory Size at start (pages): %zu\n" , i , vm_start);
        int *alloc[NUM_ALLOCATIONS];
        for(int j = 0; j < NUM_ALLOCATIONS; j++)
        {
            size_t cnt = rand() % ALLOC_SZ;
            int *ptr = malloc(cnt * sizeof(int));
            if(ptr == NULL)
            {
                exit(1);
            }
            memset(ptr,0,cnt * sizeof(int));
            alloc[j] = ptr;
        }
        print_memory();
        for (int j = 0; j < NUM_ALLOCATIONS; ++j) {
            free(alloc[j]);
        }
        /* currrent virtual memory(pages) */
        size_t vm_end = vmsize();
        printf("[%d]th rounds: Virtual Memory Size at end(pages): %zu\n\n", i, vm_end);
        if (vm_end - vm_start > vm_limit) {
            printf("free() is not functioning correctly,\
                    it is unable to free all the allocations.\n");
            exit(1);
        }
    }
    printf("free() is functioning correctly,\
        it is able to free all the allocations.\n");
    return 0;
}