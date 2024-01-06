# memory-allocator
------------------
### What is it


------------------
### What is in it
* `myallocator.h` header file
* `myallocator.c` source file
* `main.c` test file

------------------
### What does it implement
* `void *mymalloc(size_t size)`
* `void myfree(void *block)`
* `void *mycalloc(size_t num, size_t nsize)`
* `void *myrealloc(void *block, size_t size)`

------------------
### How to use the shared library


------------------
### how to test it
```shell
# Run all test cases:
make test

# Run a specific test case:
make test run=4

# Run a few specific test cases (4, 8, and 12 in this case):
make test run='4 8 12'
```

------------------
### Reference Links
1. [memory-allocator](https://github.com/rtmacaibay/memory-allocator/tree/master)
------------------


