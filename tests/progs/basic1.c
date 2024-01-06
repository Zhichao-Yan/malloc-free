/*
 * @Author       : chao
 * @Date         : 2024-01-01 15:24:46 +0800
 * @LastEditors  : yan yzc53@icloud.com
 * @LastEditTime : 2024-01-02 00:28:01 +0800
 * @FilePath     : /malloc/tests/progs/allocations-3.c
 * @Description  : 
 * @QQ           : 1594047159@qq.com
 * Copyright (c) 2024,All Rights Reserved. 
 */

#include "allocator.h"

int main(void)
{
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

    print_memory();

    return 0;
}