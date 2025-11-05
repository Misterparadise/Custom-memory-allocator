#ifndef MY_MALLOC_H
#define MY_MALLOC_H

#include <stddef.h>



void *custom_malloc(size_t size);
void custom_free(void *ptr);
void print_blocks(void);

#endif