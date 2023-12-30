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


