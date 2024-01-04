/*
 * @Author       : chao
 * @Date         : 2024-01-01 15:22:29 +0800
 * @LastEditors  : yan yzc53@icloud.com
 * @LastEditTime : 2024-01-03 15:52:24 +0800
 * @FilePath     : /malloc/tests/progs/allocations-2.c
 * @Description  : 
 * @QQ           : 1594047159@qq.com
 * Copyright (c) 2024,All Rights Reserved. 
 */
#include <stdio.h>
#include "allocator.h"

size_t vmsize();
int main(void)
{
    size_t vm_start = vmsize();

    void *a = malloc(500);
    void *b = malloc(1000);
    void *c = malloc(250);
    void *d = malloc(250);
    void *e = malloc(500);

    free(b);
    free(d);

    void *f = malloc(600);
    void *g = malloc(150);
    void *h = malloc(50);

    size_t vm_end = vmsize();

    printf("Pages at start = %zd\n",vm_start);
    printf("pages at end   = %zd\n",vm_end);
    printf("Allocated total %zd pages!\n",vm_start - vm_end);
    return 0;
}