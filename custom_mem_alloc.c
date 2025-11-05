#include "my_malloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdbool.h>



//Structure that holds metadata about each provided memory chunk. Data structure used is basically Linked List
typedef struct BLOCK
{
   size_t size;
   bool is_free;
   struct BLOCK *next;
   struct BLOCK *prev; 
}BLOCK;


#define BLOCK_SIZE sizeof(BLOCK) //Macro for holding info about size of struct
#define ALIGNMENT 16
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

static BLOCK *head = NULL; //Initiation of structure that will hold info about blocks of memory requested from system


 void *custom_malloc(size_t size);
 static BLOCK *request_memory(BLOCK *chunk, size_t size);
 static BLOCK *find_chunk(BLOCK **chunk, size_t size);
 void custom_free(void *ptr);
 void print_blocks(void);




  

BLOCK *request_memory(BLOCK *chunk, size_t size)  //Function that makes request memory from operating system
{
   size_t total_chunk_size = size + sizeof(BLOCK);
   BLOCK *ptr = mmap(NULL, total_chunk_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
   
   if(ptr == MAP_FAILED)
   {

      return NULL;

   }

   ptr->is_free = false;
   ptr->size = size;
   ptr->next = NULL;
   ptr->prev = chunk;

   if(chunk)
   {
      chunk->next = ptr;
   }

   return (void *)ptr;

}

BLOCK *find_chunk(BLOCK **chunk, size_t size)
{
  
   BLOCK *block = head;

   while(block && !(block->is_free && block->size >= size))
   {
      *chunk = block;
      block = block->next;
   }
   return block;
}


void custom_free(void *ptr) // Marked block as available
{
   BLOCK *block;
   if(ptr == NULL)
   {
      return;
   }

   block = (BLOCK*)ptr - 1;

   block->is_free = true;


}


void print_blocks(void)
{
   BLOCK *ptr;
   ptr = head;

   if(!ptr)
   {
      printf("No allocated blocks\n");
      return;
   }

   while(ptr != NULL)
   {
      printf("Size of block: %ld\n", ptr->size);
      printf("Block is avaliable: %d\n", ptr->is_free);
      ptr = ptr->next;
   }
}


void *custom_malloc(size_t size) //Allocates memory on the heap and manage memory blocks
{
   size_t aligned_size = ALIGN(size);
   if(aligned_size <= 0)
   {
      return NULL;
   }

   BLOCK *block;

   if(!head)
   {
      block = request_memory(NULL, aligned_size);       
      if(!block)
      {
         return NULL;                             
      }

      head = block;
   }
   else
   {
      BLOCK *last = head;
      block = find_chunk(&last, aligned_size);
      if(!block)
      {
         block = request_memory(last, aligned_size);
      }
      else
      {
         block->is_free = 0;
      }
      
   }
   


   return (void *)(block + 1);
}