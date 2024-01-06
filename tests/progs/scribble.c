/*
 * @Author       : chao
 * @Date         : 2024-01-01 15:26:20 +0800
 * @LastEditors  : yan yzc53@icloud.com
 * @LastEditTime : 2024-01-04 01:20:11 +0800
 * @FilePath     : /malloc/tests/progs/scribble.c
 * @Description  : 
 * @QQ           : 1594047159@qq.com
 * Copyright (c) 2024,All Rights Reserved. 
 */

#include <stdio.h>
#include "allocator.h"

int main(void)
{
    puts("Printing uninitialized variables:");
    int *x = malloc(sizeof(int));
    printf("%d\n", *x);
    *x = 42;
    free(x);
    int *y = malloc(sizeof(int));
    printf("%d\n", *y);

    int *i = malloc(sizeof(int));
    unsigned long *ul = malloc(sizeof(unsigned long));
    printf("%d\n", *i);
    printf("%lu\n", *ul);
    printf("%x\n", *i);
    printf("%lx\n", *ul);

    unsigned char *arr = malloc(sizeof(unsigned char) * 5000);

    puts("Suming up uninitialized arrays:");
    int l;
    unsigned long total = 0;
    for (l = 0; l < 5000; ++l) {
        total += arr[l];
    }
    printf("%lu\n", total);

    puts("calloc should still zero out the memory:");
    int *cleared = calloc(sizeof(int), 450);
    total = 0;
    for (l = 0; l < 450; ++l) {
        total += cleared[l];
    }
    printf("%lu\n", total);

    return 0;
}