dir := ./build
lib := $(dir)/liballocator.so
DEBUG ?= 0
CC := gcc
CFLAGS := -Wall -g -pthread -fPIC -shared

# generate allocator.so
$(lib): clean allocator.c 
	@$(CC) $(CFLAGS) -DDEBUG=$(DEBUG) allocator.c -o $(lib)

clean:
	@rm -rf $(dir)/*

test: $(lib)
	@echo "Building test programs...."
	@echo "Start testing....."
	@cd ./tests; make; ./test.sh $(run)


