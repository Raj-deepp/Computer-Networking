//Write a C program to extract each byte from a given number and store them in separate character variables and print the content of those variables.

#include <stdio.h>

int main() {
    int number;
    char byte1, byte2, byte3, byte4;

    // Prompt user for input
    printf("Enter a number: ");
    scanf("%u", &number);

    // Extract each byte
    byte1 = (number >> 24) & 0xFF;
    byte2 = (number >> 16) & 0xFF;
    byte3 = (number >> 8) & 0xFF;
    byte4 = number & 0xFF;

    // Print the content of each byte
    printf("Byte 1: 0x%02X\n", byte1);
    printf("Byte 2: 0x%02X\n", byte2);
    printf("Byte 3: 0x%02X\n", byte3);
    printf("Byte 4: 0x%02X\n", byte4);
    return 0;
}