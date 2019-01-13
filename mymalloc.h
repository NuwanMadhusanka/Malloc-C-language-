#include<stdio.h>
#include "mymalloc.c"

void *mymalloc(size_t);
void myfree(void *);
block *find_block(size_t );
void split_block(block *block,size_t size);
void display(void *);

