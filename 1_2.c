/*Write a C program to assign values to each member of the following structure. 
Pass the populated structure to a function Using call-by-value and another function using call-by-address and print the value of each member of the structure.
struct student_info{
int roll_no;
char name [50];
float CGPA;
struct dob age;
};*/

#include<stdio.h>

struct dob{
    int dd;
    int mm;
    int year;
};

struct student_info{
    int roll_no;
    char name[50];
    float CGPA;
    struct dob d;
};

void callByValue(struct student_info s){
    printf("CALL BY VALUE\n");
    printf("Roll No.: %d\n",s.roll_no);
    printf("Name: %s\n",s.name);
    printf("CGPA: %f\n",s.CGPA);
    printf("DOB: %d-%d-%d\n",s.d.dd,s.d.mm,s.d.year);
}

void callByRefernce(struct student_info *s){
    printf("CALL BY REFERENCE\n");
    printf("Roll No.: %d\n",s->roll_no);
    printf("Name: %s\n",s->name);
    printf("CGPA: %f\n",s->CGPA);
    printf("DOB: %d-%d-%d\n",s->d.dd,s->d.mm,s->d.year);
}

int main(){
    struct student_info s;
    printf("Enter Roll No.: ");
    scanf("%d",&s.roll_no);
    printf("Enter name: ");
    scanf("%s",s.name);
    printf("Enter CGPA: ");
    scanf("%f",&s.CGPA);
    printf("Enter DOB: ");
    scanf("%d%d%d",&s.d.dd,&s.d.mm,&s.d.year);

    callByValue(s);
    callByRefernce(&s);
}