#include <stdio.h>
#include <conio.c>
#include <string.h>
void show(char *);
int main(int argc, char *argv[])
{
    char str[80],*p;
    str[0]='c';
    p=str;
    show(p);
    getch();
}
void show(char *ptr)
{
    printf ("%c",*ptr);
}
