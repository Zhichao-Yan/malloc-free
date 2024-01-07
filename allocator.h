/*
 * @Author       : chao
 * @Date         : 2023-11-10 16:12:21 +0800
 * @LastEditors  : yan yzc53@icloud.com
 * @LastEditTime : 2024-01-07 23:44:48 +0800
 * @FilePath     : /malloc/allocator.h
 * @Description  : 
 * @QQ           : 1594047159@qq.com
 * Copyright (c) 2023,All Rights Reserved. 
 */

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>



struct block {
    struct block *region;
    // char name[32];
    size_t size;
    size_t rsize;       // user-requested size
    struct block *next;
    struct block *prev; 
}__attribute__((packed));

struct link{
    struct block *pred;
    struct block *succ; 
}__attribute__((packed));

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void print_memory();
void print_freelist();
void print_blocklist();
void leak_check();
size_t vmsize();

#endif 