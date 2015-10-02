#include <stdio.h>
#include <conio.c>
#include <string.h>

int main (int argc, char *argv[])
{
    int vetor[5]={1,2,3,4,5};
    int *p,t;
    p=vetor;
    for ( t=0 ; t<5 ; t++){ 
		printf ("%d    ",(*p[t])); 
    }
    getch( ); 

}
