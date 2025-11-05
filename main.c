#include <stdio.h>
#include "my_malloc.h"

int main(void)
{
    int *ptr = custom_malloc(500);
    
    print_blocks();
    custom_free(ptr);
}
