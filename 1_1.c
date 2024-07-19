#include<stdio.h>

//Write a C program to swap the contents of two variables enterd through the command line using function and pointers
void swap(int *x, int *y){
    *x=*x+*y;
    *y=*x-*y;
    *x=*x-*y;
}

int main(){
    int a, b;
    printf("Enter two numbers: ");
    scanf("%d %d",&a,&b);
    printf("Before Swapping: %d %d\n",a,b);

    swap(&a,&b);
    printf("After Swapping: %d %d",a,b);
    return 0;
}