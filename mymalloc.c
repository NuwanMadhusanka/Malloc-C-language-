#include<stdio.h>
#include<sys/types.h>
#include<string.h>

typedef unsigned int size_t;

struct header
{
    char detail;//memory block allocate or not
    int size;//size of the memory block
    struct header *next;//header to next memory block
    struct header *pre;//header to previous memory block
};
typedef struct header block;

static char malloc_array[25000];//Initialize the memory size as 25000
static char *base=malloc_array;//Get first address of the array
static char free_flag='f';//Determine which memory blocks are free
char allocate_flag='a';//Determine which memory blocks are allocate_flag
block *pre=NULL;

void *mymalloc(size_t);
void myfree(void *);
block *find_block(size_t);
void split_block(block *block,size_t size);
void display(void *);


block* find_block(size_t size)
{
     block *ip=(block*)base;
     int num=0;

     while(ip)
     {
         num=(ip->size);//get the memory block size


        if(ip->detail==free_flag && num>=size)
        {
            return(ip);
            break;
        }
        else
        {
            pre=ip;
            ip=ip->next;
        }
     }
     if(!ip)
     {
         return NULL;
     }

}


void split_block(block *m_block,size_t size)
{

    size_t curr_block_size=m_block->size;


    if(((char*)m_block+size+sizeof(block))==(base+24999))
    {
        m_block->detail=allocate_flag;
        m_block->next=NULL;
    }
    else if(curr_block_size==size)
    {
       m_block->detail=allocate_flag;
    }
    else
    {
        m_block->detail=allocate_flag;//fill meta data
        m_block->size=size;//fill meta data
        m_block->next=(block*)((char*)m_block+sizeof(block)+size);
        m_block->next->detail=free_flag;//remain of the block
        m_block->next->size=curr_block_size-(size+sizeof(block));
    }
}


void *mymalloc(size_t size)//malloc funtion implement
{

    if(size<=0 || size>(24999-sizeof(block)))//if size is negative value or zero
    {
       return NULL;
    }

    if(!*base)//if whole memory is free
    {
        block *start=(block*)base;
        start->detail='f';
        start->size=24999-sizeof(block);
        start->next=NULL;
        start->pre=NULL;
    }

    block* m_block=find_block(size);//find free memory block

    if(m_block)//if we have free memory block
    {
        if(m_block->size >= size)//if free memory block size is greter than needed memory size
        {
            split_block(m_block,size);
            m_block->pre=pre;
            char* ip=(char*)m_block+sizeof(block);
            return((void*)ip);
        }
    }
    else
    {
        return NULL;
    }

}

void display(void *ip)
{
    char* block_d=(char*)ip-sizeof(block);
    block* m_block=(block*)block_d;
    if(m_block)
    {
        if((char*)m_block==base)
        {
            printf("\n=====Details about memory block=====\n");
            printf("Block size:%d\n",m_block->size);
            printf("Block free or allocate:%c\n",m_block->detail);
            if(m_block->next!=NULL)
            {
                printf("Next block size:%d\n",m_block->next->size);
                printf("Next block free or not:%c\n",m_block->next->detail);
            }

        }
        else if(((char*)m_block+m_block->size+sizeof(block))==base+24999)
        {
            printf("\n=====Details about memory block=====\n");
            printf("Block size:%d\n",m_block->size);
            printf("Block free or allocate:%c\n",m_block->detail);
            printf("previous block size:%d\n",m_block->pre->size);
            printf("previous block free or not:%c\n",m_block->pre->detail);
        }
        else
        {
            printf("\n=====Details about memory block=====\n");
            printf("Block size:%d\n",m_block->size);
            printf("Block free or allocate:%c\n",m_block->detail);
            printf("Next block size:%d\n",m_block->next->size);
            printf("Next block free or not:%c\n",m_block->next->detail);
            printf("previous block size:%d\n",m_block->pre->size);
            printf("previous block free or not:%c\n",m_block->pre->detail);
        }


    }
    else
    {
        printf("\n=====Details about memory block====\n");
        printf("Error,Couldn't allocate");
    }

}

void myfree(void *ip)
{
    char *ptr=(char*)ip-sizeof(block);
    block *m_block=(block*)ptr;

    int block_s=m_block->size;
    block *next_m_block=m_block->next;

    if(m_block)
    {
        m_block->detail=free_flag;

        if(m_block->next != NULL)//right side block also free then combine both block
        {
            char next_f=m_block->next->detail;
            int next_s=m_block->next->size;

            if(next_f==free_flag)
            {
                m_block->size=block_s+next_s+sizeof(block);
                block_s=m_block->size;
                if(m_block->next->next != NULL)
                {
                    m_block->next=m_block->next->next;
                    m_block->next->pre=m_block;
                }
                else
                {
                    m_block->next=NULL;
                }

            }

        }

        if(m_block->pre!=NULL)
        {


            char pre_f=m_block->pre->detail;
            char pre_s=m_block->pre->size;

            if(pre_f==free_flag)
            {

                block* pre=m_block->pre;
                pre->size=block_s+sizeof(block)+pre->size;
                if(m_block->next!=NULL)
                {
                    pre->next=m_block->next;
                    m_block->next->pre=m_block->pre;
                }
                else
                {
                    pre->next=NULL;
                }

            }
        }


    }
}

