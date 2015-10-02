#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 20

typedef struct no{
    char conteudo[MAX];
    struct no *proximo;
}no;


//Prototipos de Funcoes
no *insere(no *, char *);
void imprimirLista(no *);
int find(no *,char *);

int main()
{
    no *lista=NULL;
    /*
    lista=insere(lista, "Belem" ); //1 Caso
    lista=insere(lista, "Alexandre"); //2 Caso
    lista=insere(lista, "Aalexandre");
    lista=insere(lista, "Nilton");
    lista=insere(lista, "Matos");
    lista=insere(lista, "Six");
    */
    lista=insere(lista,"Marco Feliciano"); //caso 1
    lista=insere(lista,"Alexandre"); //caso 2
    lista=insere(lista,"Yzaac"); //caso 4
    lista=insere(lista,"Carlos"); //caso 3
    
    imprimirLista(lista);    

    if ( find(lista, "Alexandre") ) { //retorna 1 se encontra, 1 no C eh verdadeiro
       printf("Alexandre existe na lista ordenada\n");
    }

    system("PAUSE");
}

no *insere(no *lista, char *elemento)
{
     no *novo;
     no *aux=lista;
    
    //Caso 1 - Fila esta vazia
    if (lista == NULL ){
        if (lista=(no*)malloc(sizeof(no)))
        {
           strcpy(lista->conteudo, elemento);
           lista->proximo=NULL;
           return lista;
        }else{
            printf("Erro ao alocar novo no.\n");
        }    
    }

    if (novo=(no *)malloc(sizeof(no)) ) {
        strcpy(novo->conteudo, elemento);
        //Caso 2
        if ( strcmp(elemento, lista->conteudo) < 0 ){
           novo->proximo=lista;
           lista=novo;
           return lista;
        }
        
        //Caso 3
        while (aux->proximo!=NULL) {
            if (strcmp(aux->proximo->conteudo,elemento)>0)
            {
                novo->proximo=aux->proximo;
                aux->proximo=novo;
                return lista;
            }
            aux=aux->proximo;
        }

        //Caso 4
        novo->proximo=NULL;
        aux->proximo=novo;
        return lista;
    }else{
        printf("Estouro de memoria!\n");
    }
}

void imprimirLista(no *lista)
{
    no *aux;
    if ( lista == NULL ) {
       printf("Lista esta vazia\n");
    }else{
        aux = lista;
        while(aux) {
            printf("Valor: %s\n", aux->conteudo);
            aux = aux->proximo;
        }
    }
}


int find(no *lista,char *elemento)
{
    no *aux=lista;
    while (aux!=NULL)
    {
        if (strcmp(aux->conteudo,elemento)==0)
            return 1;
        aux=aux->proximo;
    }
    return 0;
}
