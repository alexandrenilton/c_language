#include <stdio.h>
#include <conio.c>
#include <string.h>
int main(int argc, char *argv[])
{
    int matrix[50][50];
    int *ptr;
    int count;
    ptr=matrix[0];
    for ( count=0 ; count<=2500/*50 x 50*/ ; count++)
    {
        *ptr=0;
         printf("%d\n",*ptr);
         ptr++;
    }
    getch();
}
