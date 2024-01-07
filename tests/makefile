CC := gcc
CFLAGS += -Wall -Wno-unused-variable -g -pthread -I../ 
LDLIBS += -lallocator -L../build 
DIR1 := ./build
DIR2 := ./progs

objects := print_test scribble free total_pages_allocated leak_check basic0 basic1 realloc
all: $(objects)

$(objects): %: $(DIR2)/%.c
	@$(CC) $(CFLAGS) $^ -o $(DIR1)/$@ $(LDLIBS)
clean:
	rm -rf $(DIR1)/* 



