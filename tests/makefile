CC := gcc
CFLAGS += -Wall -Wno-unused-variable -g -pthread -I../ 
LDLIBS += -lallocator -L/Users/Yan/Project/just-do-it/Finished/malloc/build 
DIR1 := ./build
DIR2 := ./progs

objects := allocations-0 allocations-1 allocations-2 allocations-3 allocations-4 allocations-5
all: $(objects)

$(objects): %: $(DIR2)/%.c
	$(CC) $(CFLAGS) $^ -o $(DIR1)/$@ $(LDLIBS)
clean:
	rm -rf $(DIR1)/* 



