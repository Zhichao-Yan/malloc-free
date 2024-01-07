# Malloc
------------------
### What is it


------------------
### What is in it
* `malloc/tests/script`  test script files
* `malloc/tests/progs` test source file
* `malloc/allocator.c` source file
* `malloc/allocator.h` head file
* `malloc/makefile` makefile for liballocator.so

------------------
### What functions does it implement
* void *malloc(size_t size);
* void free(void *ptr);
* void *calloc(size_t nmemb, size_t size);
* void *realloc(void *ptr, size_t size);
* void print_memory();
* void print_freelist();
* void print_blocklist();
* void leak_check();
* size_t vmsize();

------------------
### How to use the shared library


------------------
### how to test it
```shell
# Run all test cases:
make test

# Run a few specific test cases (4, 8, and 12 in this case):
make test run='4 8 12'
```

------------------
### Reference Links
1. [memory-allocator](https://github.com/rtmacaibay/memory-allocator/tree/master)
------------------


