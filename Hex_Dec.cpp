/************************************************************************
 *  Descricao: Algoritmo que converte um valor hexadecimal para o       *
 *  correspondente decimal.                                             *
 *  Compilador Utilizado: Borland C++ 3.1                               *
 *  Este codigo foi desenvolvido pelo Fundao da Computacao - UFMS       *
 *  www.fundao.pro.br     &&   fundao@fundao.pro.br                     *
 ************************************************************************/
#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

//Prototipo
int Converte(char);


//Implementacao
void main()
{
  char hex[20];
  int  aux=0,tam,exp=0,dec=0;

  clrscr();
  cout<<"\nEntre com um n£mero em hexadecimal: ";
  gets(hex);

  tam = strlen(hex);        //Pega o quantidade de digitos entrada

  while(tam)                //Enquanto o tamanho for diferente de zero
  {
	  aux = Converte(hex[--tam]);   //Passa para Converte o ultimo digito
					//Como em C um vetor comeca na posicao zero
					//se um vetor tem 3 elementos --tam passa
					//a posicao 2 (terceiro elemento)

	  dec += aux*pow(16,exp++); //Soma a dec o valor retornado por Converte
                                    //multiplicado pela potencia de 16
  }

  cout<<endl<<"Numero decimal: "<<dec;
  getch();
}

/**************************************************************************
 *  Funcao Converte                                                       *
 *  Entrada: Recebe um char em a que representa um digito em hexadecimal  *
 *  Retorna: Um valor decimal correspondente ao digito em hexa entrado    *
 *           ou -1 se o valor entrado nao for um digito valido (Ex.: 't') *
 **************************************************************************/
int Converte(char a)
{
	int ret;

	if (a>47  && a<58)
		return a-'0';
	if (a>64 && a<71)
		return a-55;
	else if (a>96 && a<103)
		return a-87;
	return -1;      //Nao eh hexadecimal
}