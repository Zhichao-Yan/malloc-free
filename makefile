dir := ./build
lib := $(dir)/liballocator.so
DEBUG ?= 0
CC := gcc
CFLAGS := -Wall -g -pthread -fPIC -shared

# generate allocator.so
$(lib): allocator.c allocator.h
	@$(CC) $(CFLAGS) -DDEBUG=$(DEBUG) allocator.c -o $(lib)

clean:
	@rm -rf $(dir)/*

test: $(lib)
	@cd ./tests; ./test.sh $(run)


