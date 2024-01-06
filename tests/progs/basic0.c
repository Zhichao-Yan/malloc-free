/*
 * @Author       : chao
 * @Date         : 2024-01-01 14:57:56 +0800
 * @LastEditors  : yan yzc53@icloud.com
 * @LastEditTime : 2024-01-01 15:21:20 +0800
 * @FilePath     : /malloc/tests/progs/allocations-1.c
 * @Description  : 
 * @QQ           : 1594047159@qq.com
 * Copyright (c) 2024,All Rights Reserved. 
 */

#include "allocator.h"

int main(void)
{
    void *a = malloc(100);
    void *b = malloc(100); /* Will be deleted */
    void *c = malloc(100);
    void *d = malloc(10);  /* Will be deleted */
    void *e = malloc(100);
    void *f = malloc(100);

    free(b);
    free(d);

    /* This will split:
     * - b with first fit
     * - d with best fit
     * - f with worst fit
     */
    void *g = malloc(10);

    print_memory();

    return 0;
}