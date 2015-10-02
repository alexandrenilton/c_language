/************************************************************************
 *  Descricao: Algoritmo que converte um valor binario para o           *
 *  correspondente decimal.                                             *
 *  Compilador Utilizado: Borland C++ 3.1                               *
 *  Este codigo foi desenvolvido pelo Fundao da Computacao - UFMS       *
 *  www.fundao.pro.br     &&   fundao@fundao.pro.br                     *
 *  Obs.: Por nao utilizarmos alocacao dinamica  o tamanho do numero    *
 *  que pode ser entrado pelo usuario deve ser menor que 20             *
 *  Para simplificar o codigo pode-se retirar a funcao Converte e       *
 *  'fundi-la' 'a main.                                                 *
 ************************************************************************/
//#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

//Prototipo
int Converte(char);


//Implementacao
int main()
{
  char hex[20];
  int  aux=0,tam,exp=0,dec=0;

  clrscr();
  printf("\nEntre com um n£mero em binario: ");
  gets(hex);

  tam = strlen(hex);        //Pega o quantidade de digitos entrada

  while(tam && aux!=-1)                //Enquanto o tamanho for diferente de zero
  {
	  //Passa para Converte o ultimo digito
	  //Como em C um vetor comeca na posicao zero
	  //se um vetor tem 3 elementos --tam passa
	  //a posicao 2 (terceiro elemento)
	  if( (aux = Converte(hex[--tam]))==-1 )
	      break;

	  dec += aux*pow(2,exp++);  //Soma a dec o valor retornado por Converte
				    //multiplicado pela potencia de 2
  }

  if ( aux!=-1 )
     cout<<endl<<"Numero decimal: "<<dec;
  else
     cout<<endl<<"O Numero Entrado Nao eh Binario!";
  getch();
}

/**************************************************************************
 *  Funcao Converte                                                       *
 *  Entrada: Recebe um char em a que representa um digito em binario      *
 *  Retorna: Um valor decimal correspondente ao digito em binario entrado *
 *           ou -1 se o valor entrado nao for um digito valido (Ex.: '3') *
 **************************************************************************/
int Converte(char a)
{
	int ret;

	if (a>47  && a<50)
		return a-'0';
	return -1;      //Nao eh binario
}
