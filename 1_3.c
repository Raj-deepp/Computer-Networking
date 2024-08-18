//Write a C program to extract each byte from a given number and store them in separate character variables and print the content of those variables.

#include <stdio.h>

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    
    unsigned char b1 = (num & 255);
    unsigned char b2 = (num >> 8) & 255;
    unsigned char b3 = (num >> 16) & 255;
    unsigned char b4 = (num >> 24) & 255;

    printf("B1: %u\n", b1);
    printf("B2: %u\n", b2);
    printf("B3: %u\n", b3);
    printf("B4: %u\n", b4);
    return 0;
}