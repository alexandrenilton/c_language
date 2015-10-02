#include "stdio.h"
#include "conio.c"
#define UM 1
#define DOIS UM+UM
#define TRES DOIS+UM
int main(int argc, char *argv[])
{
    printf("Teste\n");
    if ( UM == 1 )
        printf("1 = 1\n");
    if ( DOIS == 2 )
        printf("DOIS = 2\n");
    if ( TRES == 3 )
        printf("TRES = 3\n");
    getch();
}
