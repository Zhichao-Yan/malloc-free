
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
    int *ptr2 = malloc(2);
    int *ptr3 = malloc(45);
    int *ptr4 = malloc(200);
}