CC := gcc
CFLAGS += -Wall -Wno-unused-variable -g -pthread -I../ 
LDLIBS += -lallocator -L/Users/Yan/Project/just-do-it/Finished/malloc/build 
DIR1 := /Users/Yan/Project/just-do-it/Finished/malloc/tests/build
DIR2 := /Users/Yan/Project/just-do-it/Finished/malloc/tests/progs

objects := print_test scribble free thread_safe total_pages_allocated leak_check basic0 basic1
all: $(objects)

$(objects): %: $(DIR2)/%.c
	$(CC) $(CFLAGS) $^ -o $(DIR1)/$@ $(LDLIBS)
clean:
	rm -rf $(DIR1)/* 



