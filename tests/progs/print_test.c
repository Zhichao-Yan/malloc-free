/*
 * @Author       : chao
 * @Date         : 2024-01-01 15:25:47 +0800
 * @LastEditors  : yan yzc53@icloud.com
 * @LastEditTime : 2024-01-03 20:38:53 +0800
 * @FilePath     : /malloc/tests/progs/print-test.c
 * @Description  : 
 * @QQ           : 1594047159@qq.com
 * Copyright (c) 2024,All Rights Reserved. 
 */

#include "allocator.h"

int main(void)
{
    void *a = malloc(4000);
    void *b = malloc(4000);
    void *c = malloc(4000);

    print_memory();

    return 0;
}