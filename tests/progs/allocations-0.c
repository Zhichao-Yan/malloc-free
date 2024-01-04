
#include "allocator.h"
#define ALLOCATOR_LEAK_CHECK 1

void __attribute__((destructor)) shutdown()
{
    if(ALLOCATOR_LEAK_CHECK)
    {
        leak_check();
    }
    return;
}
int main()
{

    int *ptr1 = malloc(120);
    print_blocklist();
    int *ptr2 = malloc(2);
    print_blocklist();
    int *ptr3 = malloc(45);
    print_blocklist();
    int *ptr4 = malloc(200);
    print_blocklist();
    print_freelist();
    free(ptr1);
    print_memory();
    free(ptr3);
    print_memory();
    free(ptr2);
    print_memory();
    free(ptr4);
    print_memory();
}