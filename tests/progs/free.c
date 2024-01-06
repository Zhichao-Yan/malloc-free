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
    srand(time(0));
    size_t vm_start = vmsize();
    printf("Virtual Memory Size at startup (pages): %zu\n", vm_start);
    for( int i = 0; i < NUM_ROUNDS; ++i)
    {
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
        for (int j = 0; j < NUM_ALLOCATIONS; ++j) {
            free(alloc[j]);
        }
        /* currrent virtual memory(pages) */
        size_t vm = vmsize();
        printf("Virtual Memory Size at [%d]rounds (pages): %zu\n", i, vm);
        if (vm != 0) {
            printf("free() is not functioning correctly,\
                    it is unable to free all the allocations.\n");
            exit(1);
        }
    }
    return 0;
}