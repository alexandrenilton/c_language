#include <stdio.h>
#include <conio.c>
void mostra(int );
int main(int argc, char *argv[])
{
    int *p;
    int numero;
    numero=10;
    p=&numero;
    //printf ("%d",(*p));
    mostra(p);
    getch();
}
void mostra(int f)
{
    printf ("%d",f);
}
