/*
Escreva um programa que declare uma matriz 100x100 
de inteiros. Voc� deve inicializar a matriz com zeros 
usando ponteiros para endere�ar seus elementos. Preencha 
depois a matriz com os n�meros de 1 a 10000, tamb�m usando 
ponteiros. 
*/

#include <stdio.h>
#include <conio.c>
#include <string.h>
int main (int argc, char *argv[])
{
    int *ptr;
    int i;
    int str[100][100];
    ptr=str[0];
    for ( int a=0; a <= 10000 ; a++)
    {
        *ptr=0;
        printf("%d\n",*ptr);
        *ptr++;
    }
    ptr=str[0];
    for ( int a=0; a<=10000 ; a++)
    {
        *ptr=a;
        printf("%d\n",*ptr);
        *ptr++;
    }
    getch();
}
