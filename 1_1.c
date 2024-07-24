#include<stdio.h>

//Write a C program to swap the contents of two variables enterd through the command line using function and pointers

#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y){
    *x=*x+*y;
    *y=*x-*y;
    *x=*x-*y;
}

int main(int argc, char *argv[]) {
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    printf("Before swapping:\n");
    printf("num1 = %d\n", num1);
    printf("num2 = %d\n", num2);

    swap(&num1, &num2);

    printf("After swapping:\n");
    printf("num1 = %d\n", num1);
    printf("num2 = %d\n", num2);

    return 0;
}