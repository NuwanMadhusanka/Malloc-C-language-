#include<stdio.h>
#include<string.h>
#include"mymalloc.h"

struct Student
{
    char ar[20];
    int age;
};
typedef struct Student node;

int main()
{
    //This is a testing code
   int *a=(int*)mymalloc(20000);
    int *b=(int*)mymalloc(3000);
    char *c=(char*)mymalloc(1951);


    myfree(c);
    myfree(b);
    myfree(a);

    display(a);
    display(b);


    printf("%d\n",sizeof(node));
    node *saman=(node*)mymalloc(sizeof(node));
    printf("Enter your name:");
    gets(saman->ar);
    printf("Enter your age:");
    scanf("%d",&saman->age);
    printf("%s is %d years old",saman->ar,saman->age);
    display(saman);
    myfree(saman);

    /*int* a=(int*)mymalloc(100);
    display(a);

    int a[10];
    int* s=(int*)mymalloc(12);
    *(s)=12;
    printf("%d",*s);*/







    return 0;

}
