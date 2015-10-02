#include <stdio.h>
#include <stdlib.h>

struct Lista{
    char nome[51];
    char Tcomida[31];
    float nota;
    char endereco[61];
    struct Lista *proxLista;
}typedef Item;

int main() {
  int i, qtd;
  
  Item item;
  
  printf ("\t\tCADASTRO DE RESTAURANTES\n\n");

  printf ("Entre com a quantidade de restaurantes que deseja cadastrar: ");
  scanf ("%d", &qtd);
  printf ("\n");

  for (i = 0; i < qtd; i++){
    printf ("Entre com o nome do Restaurante %d: ", i+1);
    fgets (item.nome,51,stdin);

    printf ("\nEntre com o Endereco: ");
    fgets (item.endereco,61,stdin);

    printf ("Entre com o tipo de comida que deseja: ");
    fgets (item.Tcomida,31,stdin);

    do{
       printf ("Entre com uma nota de avaliacao para a cozinha [0,5]: ");
       scanf ("%f",&item.nota);
     } while (item.nota<0||item.nota>5);
      printf ("\n");
  }

  system ("PAUSE");

  return (0);
}

//FUNÇÃO CRIA LISTA VAZIA
Item* lst_cria (void){
  return NULL;
}
