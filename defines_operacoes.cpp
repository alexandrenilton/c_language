#include "stdio.h"
#include "conio.c"

#define MAM 0
#define MAX 100
#define UM 1
#define DOIS UM+UM
#define TRES DOIS+UM
#define NOVO TRES+TRES+TRES

#define LEN 100
#define WIDTH 100

#define MSG_ERRO "\nErro ao abrir arquivo\n"

#define MOD(a)  (a) < 0 ? -(a) : (a)
int main(int argc, char *argv[])
{
    int array[LEN][WIDTH];
    //#undef LEN
    if ( LEN != 100 )
        printf("LEN esvaziado\n");
    return 0;
    printf("Teste\n");
    if ( UM == 1 )
        printf("UM = 1\n");
    if ( DOIS == 2 )
        printf("DOIS = 2\n");
    
  
    /*Ele so entra aqui, porque MAM ta defenido, independente do valor*/
    #ifdef MAM
        #ifndef SET
    /*Se eu mudar o valor de MAX para sastifazer a condicao abaixo,
    a parte descrita entre #if e #endif sera compilada*/
          #if MAX == 100
             if ( TRES == 3 )
               printf("\n\nMAXXXXXX -- > TRES = 3\n\n\n");
    
          #endif
        #endif
    #endif
    
    if ( NOVO == 9 )
        printf("MACRO eh igual a 9\n");
    printf("%d,%d,%d",UM,DOIS,TRES);
    printf(MSG_ERRO);
    printf("modulo de -1 e 1 eh..: %d e %d",MOD(-1),MOD(1));
    
    getch();
    
}
