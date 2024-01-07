#include "allocator.h"
int main()
{
    printf("sizeof(struct block) is %ld bytes\n",sizeof(struct block));
    char *p = malloc(sizeof(char) * 5001);
    print_memory();
    /* the request memory increased, but the block 
     * already has some extra space because of its alignment 
     * so, no changes are needed(actual blocksize is 5056)
    */
    p = realloc(p,5010);
    print_memory();
    /* the block is being shrunk,
     * splitting off a new block 
     * from the extra free space that was made
     * If the free space created by shrinking a block 
     * is located next to another free block, 
     * they should be merged.*/
    p = realloc(p,2000);
    print_memory();
    /* try to expand the request memory from 2000 to 4000
     * if there is a neighboring free block 
     * we expand current block into neighboring free block 
     * If the entire free block is not consumed by the expansion, 
     * then the remaining free space 
     * should be split off into a new free block */
    p = realloc(p,4000);
    print_memory();
    strcpy(p,"hello,world!!");
    printf("content of char *p before realloc : %s\n" , p);
    /* If none of the situations above are possible 
     * (e.g., the block is too large to resize in place), 
     * simply malloc a new, appropriately sized block, 
     * copy the data there, and then free the old block. */
    p = realloc(p,20000);
    printf("content of char *p after realloc : %s\n" , p);
    print_memory();
    free(p);
}