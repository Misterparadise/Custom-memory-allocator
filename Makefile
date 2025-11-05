

CC = gcc
CFLAGS = -Wall -Wextra -g 
EXECUTABLE = malloc
LIBRARY = libmy_malloc.a 
ALLOC_OBJ = custom_mem_alloc.o
TEST_OBJ = main.o 

all: $(EXECUTABLE)


$(EXECUTABLE):  $(TEST_OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) $(TEST_OBJ) -L. -lmy_malloc -o $(EXECUTABLE)

$(LIBRARY): $(ALLOC_OBJ)
	ar rcs $(LIBRARY) $(ALLOC_OBJ)

$(ALLOC_OBJ): custom_mem_alloc.c my_malloc.h
	$(CC) $(CFLAGS) -c custom_mem_alloc.c -o $(ALLOC_OBJ)

$(TEST_OBJ): main.c my_malloc.h
	$(CC) $(CFLAGS) -c main.c -o $(TEST_OBJ)			


clean: 
	rm -f $(ALLOC_OBJ) $(TEST_OBJ) $(LIBRARY) $(EXECUTABLE)

.PHONY: all clean	
