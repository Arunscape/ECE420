#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


int var = 9;

int * b_;


void * addOne(void * i){
    int * a=(int*) i;
    *a += 1;
    
    int b = 10;
    b_ = &b;
    
    printf("AddOne: b = %d\n", *b_);
    
    while(1){};
    return NULL;
}

int main()
{
    //Method 1
    //int number = 0;
    //int * a = &number;
    
    //Method 2 (recommended)
    int* a = malloc(sizeof(int));
    *a = 0;
    
    //Method 3
    //int * a;
    //*a = 0;
    
    //Method 4
    //int a[1] = {0};
    
    
    printf("number = %d\n", *a);

    pthread_t * handle = malloc(sizeof(pthread_t));
    
    pthread_create(handle, NULL, addOne, (void*)a);
    
    sleep(1);
    printf("Main: b = %d\n", *b_);


    pthread_join(*handle, NULL);


    printf("number = %d\n", *a);

    
    return 0;
}