dir := ./build
lib := $(dir)/allocator.so
obj := $(dir)/main
DEBUG ?= 0

CFLAGS := -Wall -g -pthread -fPIC -shared

$(obj): $(lib)
	gcc -o $(obj) main.c $(lib)

$(lib): allocator.c 
	gcc $(CFLAGS) -DDEBUG=$(DEBUG) allocator.c -o $(lib)

clean:
	rm -rf $(dir)/*


# set DEBUG=1 means we need debug infos when testing
# this is target-specific variable
test: DEBUG=1
test: $(lib) ./tests/run_tests
	./tests/run_tests $(run)

# do test clean
testclean:
	rm -rf tests/*

# do testupdate will fist finish testclean and then do new test
testupdate: testclean test

./tests/run_tests:
	git submodule update --init --remote

