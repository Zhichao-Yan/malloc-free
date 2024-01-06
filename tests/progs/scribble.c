/*
 * @Author       : chao
 * @Date         : 2024-01-01 15:26:20 +0800
 * @LastEditors  : yan yzc53@icloud.com
 * @LastEditTime : 2024-01-07 01:19:21 +0800
 * @FilePath     : /malloc/tests/progs/scribble.c
 * @Description  : 
 * @QQ           : 1594047159@qq.com
 * Copyright (c) 2024,All Rights Reserved. 
 */

#include <stdio.h>
#include "allocator.h"
/* In the macOS system, all uninitialized allocated memory would be zero automatically */
int main(void)
{
    printf("Printing uninitialized variables:");
    int *x = malloc(sizeof(int));
    printf("%d\n", *x);     // 0
    *x = 42;
    free(x);
    int *y = malloc(sizeof(int));
    printf("%d\n", *y);     // 0

    int *i = malloc(sizeof(int));
    unsigned long *ul = malloc(sizeof(unsigned long));
    printf("%d\n", *i);     // 0
    printf("%lu\n", *ul);   // 0
    printf("%x\n", *i);     // 0
    printf("%lx\n", *ul);   // 0

    unsigned char *arr = malloc(sizeof(unsigned char) * 5000);
    printf("Suming up uninitialized arrays:");
    int l;
    unsigned long total = 0;
    for (l = 0; l < 5000; ++l) {
        total += arr[l];
    }
    printf("%lu\n", total); // 0

    printf("calloc should zero out the memory:");
    int *cleared = calloc(sizeof(int), 450);
    total = 0;
    for (l = 0; l < 450; ++l) {
        total += cleared[l];
    }
    printf("%lu\n", total); // 0

    return 0;
}