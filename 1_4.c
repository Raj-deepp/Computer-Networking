// Write a C Program to enter a number and store the number across the following structure and print the content of each member of the structure. Then aggregate each member of the structure to form the original number and print the same.
// struct pkt {
// char ch1;
// char ch2[2];
// char ch3;
// };

#include <stdio.h>

struct pkt {
    char ch1;
    char ch2[2];
    char ch3;
};

int main() {
    struct pkt data;
    int num;
    
    printf("Enter a number: ");
    scanf("%d", &num);
    
    if (num < 0 || num > 9999) {
        printf("The number can't be above 9999. Error!");
        return 1;
    }
    
    char n[5];
    int i = 0;
    while(i <= 3){
    	n[i++] = num%10 + '0';
    	num /= 10;
    }
    n[i] = '\0';
    
    for(int j = 0 ; j < i/2 ; j++){
    	char temp = n[j];
        n[j] = n[i - j - 1];
        n[i - j - 1] = temp;
    }
	
    data.ch1 = n[0];
    data.ch2[0] = n[1];
    data.ch2[1] = n[2];
    data.ch3 = n[3];
    
    printf("\nch1: %c\n", data.ch1);
    printf("ch2[0]: %c\n", data.ch2[0]);
    printf("ch2[1]: %c\n", data.ch2[1]);
    printf("ch3: %c\n", data.ch3);
    
    int nums = (data.ch1 - '0') * 1000 + (data.ch2[0] - '0') * 100 + (data.ch2[1] - '0') * 10 + (data.ch3 - '0');

    printf("\nAggregated Number: %d\n\n", nums);

    return 0;
}
