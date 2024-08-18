// Write a C program to check whether the Host machine is in Little Endian or Big Endian. Enter a number, print the content of each byte location and Convert the Endianness of the same i.e. Little to Big Endian and vice-versa.

#include <stdio.h>

void print(int num) {
    unsigned char byte1 = (num & 255);
    unsigned char byte2 = (num >> 8) & 255;
    unsigned char byte3 = (num >> 16) & 255;
    unsigned char byte4 = (num >> 24) & 255;

    printf("Number in Hexal: %X\n", num);
    printf("B1: %02X\n", byte1);
    printf("B2: %02X\n", byte2);
    printf("B3: %02X\n", byte3);
    printf("B4: %02X\n", byte4);
}

int convert(int num) {
    int new = 0;
    new |= (num & 0xFF000000) >> 24;
    new |= (num & 0x00FF0000) >> 8;
    new |= (num & 0x0000FF00) << 8;
    new |= (num & 0x000000FF) << 24;
    return new;
}

int main() {
    int num;

    printf("Enter a number: ");
    scanf("%d", &num);
	
	printf("Little Endian: \n");
    print(num);

    int num2 = convert(num);
	
	printf("Big Endian: \n");
    print(num2);

    return 0;
}