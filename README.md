# Malloc-Free
------------------
### What's it?
a malloc/free implementation
------------------
### Features
* explicit double-linked list for free blocks
* doubly-linked list for used blocks
* first-fit/worst-fit/best-fit algorithms
* use only `mmap()` instead of `sbrk()`
* `print_memory()`current state of memory 
* memory leak check when program quits(C destructor)

------------------
### What's in it?
* `malloc/tests/script`  test script files
* `malloc/tests/progs` test source file
* `malloc/tests/tesh.sh` start-up script file
* `malloc/tests/makefile` makefile for building test source files
* `malloc/allocator.c` source file
* `malloc/allocator.h` head file
* `malloc/makefile` makefile generates liballocator.so

------------------
### What functions does it implement?
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
### How do you build it?
`mkdir build && make`

------------------
### How to use it?
```shell
make
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:./build
LD_PRELOAD=./build/liballocator.so ls /
```
------------------
### How to test it?
```shell
# Run all test cases:
make test

# Run a few specific test cases (4, 8, and 12 in this case):
make test run='1 2 3'
```

------------------
### Reference Links
* [task specification](https://www.cs.usfca.edu/~mmalensek/cs326/assignments/project-3.html)
* [memory-allocator](https://github.com/rtmacaibay/memory-allocator/tree/master)
------------------


