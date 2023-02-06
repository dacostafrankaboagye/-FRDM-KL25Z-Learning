//header======file1.h====

/** this is a collection of functions for demo 
 */ 
#ifndef FILE1_H
#define FILE1_H

extern int add(int a, int b);  //function prototype
extern int sub(int a, int b);
extern void doubleParams(int* a, int *b);
extern void specialAdd();
extern int demo(int *a);
#endif


//C file1.c========

#include <stdio.h>
#include "file1.h"

/**
 * adds two numbers
 * @param a first parameter
 * @param b second param
 * @return the sum
 */ 
int add(int a, int b){  //function implementation
    int c;
    c=a+b;
    return c;
}

int sub(int a, int b){
    return a-b;
}

void doubleParams(int *a, int *b){
    *a= *a * 2;
    printf("in the fxn: a=%d", *a);
    *b*=2;       //b=b*2;
    printf("in the fxn: b=%d", *b);
}

void specialAdd(){
    static int a=5;
    a=5;
    a++;
    printf("\na=%d\n", a);
    
}

  int demo(int *a){
    *a=*a*2;
    return *a; 
}

//====main.c
#include <stdio.h>
#include "file1.h"

extern void sillyFxn();

int main()
{
int x=4, y=5;
int z;
z= add(x,y);  //pass by value
printf("z is %d\n", z);

z=sub(x,y);
printf("z is %d\n", z);

x=4, y=5;
printf("value x=%d, y=%d", x,y);
doubleParams(&x,&y);  //pass by reference
printf("value x=%d, y=%d", x,y);

specialAdd();
specialAdd();
specialAdd();

sillyFxn();

 x=5;
z=demo(&x);
printf("z=%d\t  x=%d\n",z,x);
return 0;
}



//========silly.c
 void sillyFxn()
{
}
