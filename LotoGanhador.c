#ifdef _MSC_VER
#pragma warning ( disable: 4996 )
#endif


/*******************************************************************************************
* Nome do grupo:
* Integrantes:
* Descrição: Implementação de um sistema em linguagem C para o controle de apostas de uma loteria. 
* Curso: Tecnologia em Análise e Desenvolvimento de Sistemas
* Data: 19/02/2010
*******************************************************************************************/


/******************************************Bibliotecas*************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*****************************************Definições***************************************/
#define TAM_STRING 100
#define SEMENTE 500

#define SENA 0.62
#define QUINA 0.19
#define QUADRA 0.19

#define QTD_SENA 2
#define QTD_QUINA 1
#define QTD_QUADRA 10
/*****************************************Estruturas***************************************/
//Estrutura utilizada para armazenaros dados de uma aposta
typedef struct Aposta
{
	int iCodigoAposta;
	char strEstado[3];
	char strCidade[50];
	int vetNumeros[6];
	struct Aposta* ptProxima;
}stAposta;

//Estrutura utizada para definir uma lista de apostas
typedef struct Lista
{
	stAposta* ptInicio;
	stAposta* ptFim;
	int iTotal;
}stLista;

/*Criado*/
//Estrutura utilizada para definir os dados dos ganhadores da sena por regiao;
typedef struct ListaGanhadores{
	int qtdGanhadores;
	char strEstado[3];
	char strCidade[50];
	struct ListaGanhadores *ptProxima;
}stGanhadores;


/****************************************Protótipos das funções****************************/
void mostraMenu(void);
void sorteiaNumeros(int*);
int jaSorteado(int*, int);
void leArquivo(stLista*);
stAposta* criaAposta(char *);
void insereApostaLista(stLista*, stAposta*);
void geraRelatorio(stLista*, int*);
void liberaMemoria(stLista*);

/*Criado*/
int verificaQuantidadeAcertos(int [], int [] );
stGanhadores *search(stLista *ptLista, stAposta *ptAposta, int ptVetor[] );


/*------------------------------------------------------------------------------------------
* Nome da função: main
* Descrição: Função principal de um programa em C
* Parâmetros: int, char**
* Retorno: int
------------------------------------------------------------------------------------------*/
int main(int argc, char* argv[])
{
	//Declaração das variáveis utilizadas
	stLista listaApostas;
	int iOpcao = 0;
	int vtNumerosSorteados[6];

	//Inicializando variáveis ponteiros da lista
	listaApostas.ptInicio = NULL;
	listaApostas.ptFim = NULL;
	listaApostas.iTotal = 0;
	
	//Configuração da semente utilizada no sorteio dos números
	srand(SEMENTE);

	//Loop do Menu
	while(iOpcao!=4)
	{
		//Mosta o menu principal
		mostraMenu();

		//Le a opcao
		scanf("%d",&iOpcao);

		//Chama as funções correspondentes
		if (iOpcao == 1)
		{
			//Chama a função para a leitura do arquivo e criação da lista de apostas
			leArquivo(&listaApostas);
		}
		else if (iOpcao == 2)
		{
			//Chama a função que realiza o sorteio dos números
			sorteiaNumeros(vtNumerosSorteados);
		}
		else if (iOpcao == 3)
		{
			//Chama a função que gera o arquivo de resultados
			geraRelatorio(&listaApostas, vtNumerosSorteados);
		}
	}

	//Chama a função que Libera a memória alocada dinamicamente
	liberaMemoria(&listaApostas);

	return 0;
}


/**************************************Implementação das funções****************************/
/*------------------------------------------------------------------------------------------
* Nome da função: mostraMenu()
* Descrição: esta função imprime o menu na tela
* Parâmetros: Nenhum
* Retorno: Nenhum
------------------------------------------------------------------------------------------*/
void mostraMenu(void)
{
    printf("\n  |------------------------------------------------|\n");
    printf("  |                                                |\n");    
    printf("  |            LOTERIAS TADS                       |\n");
    printf("  |                                                |\n");
    printf("  |------------------------------------------------|\n");
    printf("  |                                                |\n");
    printf("  |    <1> Ler Apostas                             |\n");    
    printf("  |    <2> Sortear numeros                         |\n");    
    printf("  |    <3> Gerar relatorio do sorteio              |\n");    
    printf("  |    <4> Sair                                    |\n");    
    printf("  |                                                |\n");    
    printf("  |------------------------------------------------|\n\n");    
    printf("\t\tOpcao: ");    
}

/*------------------------------------------------------------------------------------------
* Nome da função: leArquivo()
* Descrição: esta função realiza a leitura das apostas no arquivo e cria a lista de apostas
* Parâmetros: stLista*
* Retorno: Nenhum
------------------------------------------------------------------------------------------*/
void leArquivo(stLista* ptLista)
{
	//Declara a string responsável pelo armazenamento da linha lida do arquivo
	char strLinha[TAM_STRING];

	//Variável temporária para uma aposta
	stAposta* ptTmpAposta = NULL;

	//Realiza a abertura do arquivo
	FILE* ptArquivo = fopen("D:\\apostas.txt","rt");

	//Testa se o arquivo foi aberto com sucesso
	if (!ptArquivo)
	{
		printf("Arquivo de entrada nao pode ser aberto\n");
		return;
	}

	//Enquanto não for final de arquivo
	while(!feof(ptArquivo))
	{
		//Realiza a leitura de uma linha do arquivo
		fgets(strLinha,TAM_STRING,ptArquivo);

		//Extrai os dados da String lida do arquivo e preenche a estrutura da aposta
		ptTmpAposta = criaAposta(strLinha);

		//Insere uma aposta na lista dinâmica
		insereApostaLista(ptLista, ptTmpAposta);

		//Incrementa o total da apostas da lista
		ptLista->iTotal++;
	}

	//Fecha o arquivo
	fclose(ptArquivo);

	//Anula ponteiroS locais
	ptTmpAposta = NULL;
	ptArquivo = NULL;
}

/*------------------------------------------------------------------------------------------
* Nome da função: criaAposta()
* Descrição: esta função retira os dados de uma linha do arquivo e cria uma aposta
* Parâmetros: char*
* Retorno: stAposta*
------------------------------------------------------------------------------------------*/
stAposta* criaAposta(char* strLinha)
{
	//Declara um ponteiro para stAposta e variável auxiliar
	stAposta* ptTempAposta = NULL;
	int iIndice = 0;

	//Aloca memória para a estrutura  e inicializa o ponteiro
	ptTempAposta = (stAposta*)malloc(sizeof(stAposta));

	//Testa se a memória foi alocada
	if (!ptTempAposta)
	{
		printf("Nao foi possivel alocar a memoria");
		exit(1);
	}

	//Anula o ponteiro da estrutura
	ptTempAposta->ptProxima = NULL;

	//Quebra a string em tokens e atribui os valores para a estrutura
	ptTempAposta->iCodigoAposta = atoi(strtok(strLinha,";,/"));
	strcpy(ptTempAposta->strEstado,strtok(NULL,";,/"));
	strcpy(ptTempAposta->strCidade,strtok(NULL,";,/"));
	
	//Preenche o vetor de números
	for (iIndice=0; iIndice<6; iIndice++)
	{
		ptTempAposta->vetNumeros[iIndice] = atoi(strtok(NULL,";,/"));
	}
	
	//Retorna a estrutura preenchida
	return ptTempAposta;
}

/*------------------------------------------------------------------------------------------
* Nome da função: insereApostaLista()
* Descrição: esta função insere uma nova aposta na lista
* Parâmetros: stLista*, stAposta*
* Retorno: Nenhum
------------------------------------------------------------------------------------------*/
void insereApostaLista(stLista* ptLista, stAposta* ptAposta)
{
	stAposta *ptApostaTmp;
	stAposta *aux=ptAposta;

	int qtdTotal = 0;

	int i=0;

	//primeiro elemento
	if ( ptLista->ptInicio == NULL  && ptLista->ptFim == NULL )
	{
		printf("Primeiro Elemento\n");
		ptAposta->ptProxima = NULL;
		ptLista->ptInicio = ptAposta;
		ptLista->ptFim = ptAposta;
		return;
	}

	//caso 2 elemento eh menor que o anterior
	if ( strcmp(ptAposta->strEstado, ptLista->ptInicio->strEstado) < 0 )
	{
		printf ("%s e menor que %s\n", ptAposta->strEstado,ptLista->ptInicio->strEstado);
		ptAposta->ptProxima = ptLista->ptInicio;
		ptLista->ptInicio = ptAposta;
		return;
	}

	//
	if ( strcmp(ptAposta->strEstado, ptLista->ptInicio->strEstado) == 0 )
	{
		if ( strcmp(ptAposta->strCidade, ptLista->ptInicio->strCidade) <= 0 )
		{
			printf("%s e menor que %s\n", ptAposta->strCidade, ptLista->ptInicio->strCidade);
			ptAposta->ptProxima = ptLista->ptInicio;
			ptLista->ptInicio = ptAposta;
			return;
		}
	}

	//caso 3
	aux = ptLista->ptInicio;
	while( aux->ptProxima != NULL )
	{
		if ( strcmp(aux->ptProxima->strEstado, ptAposta->strEstado) > 0 )
		{
			ptAposta->ptProxima = aux->ptProxima;
			aux->ptProxima = ptAposta;
			return;
		}

		if ( strcmp(aux->ptProxima->strEstado, ptAposta->strEstado) == 0 )
		{
			if ( strcmp(aux->ptProxima->strCidade, ptAposta->strCidade) >= 0 ) {
				ptAposta->ptProxima = aux->ptProxima;
				aux->ptProxima = ptAposta;
				return;
			}
		}
		aux = aux->ptProxima;
	}
	
	//caso 4 - elemento é maior que o ultimo
	aux = ptLista->ptFim;

	//se estado é maior, insere no final
	if ( strcmp(ptAposta->strEstado, aux->strEstado) > 0 )
	{
		printf("ATUAL: %s eh MAIOR que FIM: %s\n", ptAposta->strEstado, aux->strEstado);
			ptAposta->ptProxima = NULL;
			
		ptLista->ptFim = ptAposta;
		aux->ptProxima = ptAposta;
	}
	if ( strcmp(ptAposta->strEstado, aux->strEstado) >= 0 )
	{
		printf("ATUAL: %s eh MAIOR que FIM: %s\n", ptAposta->strEstado, aux->strEstado);
		if ( strcmp(ptAposta->strCidade, aux->strCidade) > 0 )
		{
			ptAposta->ptProxima = NULL;
			
			ptLista->ptFim = ptAposta;
			aux->ptProxima = ptAposta;
		}
	}
	
	printf("\t======== DADOS DA APOSTA ===========\n" );
	printf("\tCodigo: %d\n", ptAposta->iCodigoAposta );
	printf("\tEstado: %s\n", ptAposta->strEstado);
	printf("\tCidade: %s\n", ptAposta->strCidade);
	printf("\tNumeros: ");
	for(i=0; i< 6; i++)
		printf(" %d", ptAposta->vetNumeros[i] );

	printf("\n\n");
	
	qtdTotal++;
	
	printf("Total atual: %d\n", qtdTotal);
}

/*------------------------------------------------------------------------------------------
* Nome da função: sorteiaNumeros()
* Descrição: esta função sorteia 6 numeros entre 1 e 20
* Parâmetros: int*
* Retorno: Nenhum
------------------------------------------------------------------------------------------*/
void sorteiaNumeros(int* ptVetor)
{
	//Variaveis locais
	int iIndice = 0, iPosicao = 0, iAux = 0;

	//Realiza o sorteio
	for (iIndice=0; iIndice<6; iIndice++)
	{
		iAux = 1+rand()%20;

		//Numero sorteado já existe no vetor?
		while(jaSorteado(ptVetor,iAux))
		{
			iAux = 1+rand()%20;
		}

		//Atribui o valor sorteado
		ptVetor[iIndice] = iAux;
	}

	//Ordena os números do vetor (Bubble sort)
	for (iIndice=0; iIndice<6; iIndice++)
	{
		for (iPosicao=0; iPosicao<5-iIndice; iPosicao++)
		{
			if (ptVetor[iPosicao]>ptVetor[iPosicao+1])
			{
				iAux = ptVetor[iPosicao];
				ptVetor[iPosicao] = ptVetor[iPosicao+1];
				ptVetor[iPosicao+1] = iAux;
			}
		}
	}

	//Imprime numeros na tela
	for (iIndice=0; iIndice<6; iIndice++)
	{
		printf("%d ",ptVetor[iIndice]);
	}
}

/*------------------------------------------------------------------------------------------
* Nome da função: jaSorteado()
* Descrição: verifica se um número já está contido no vetor de números sorteados ou não
* Parâmetros: int*, int
* Retorno: int
------------------------------------------------------------------------------------------*/
int jaSorteado(int* ptVetor, int iNumero)
{
	//Variáveis locais
	int iIndice=0;

	//Passa pelo vetor verificando
	for (iIndice=0; iIndice<6; iIndice++)
	{
		if (ptVetor[iIndice] == iNumero)
		{
			return 1;
		}
	}

	return 0;
}

/*------------------------------------------------------------------------------------------
* Nome da função: geraRelatorio()
* Descrição: esta função cria um arquivo contendo um relatorio com os resultado obtidos
* Parâmetros: stLista*, int*
* Retorno: Nenhum
------------------------------------------------------------------------------------------*/
void geraRelatorio(stLista* ptLista, int* ptVetor)
{
	stAposta *aposta = NULL;
	stGanhadores *ganhadores;
	stGanhadores *auxGanhadores = NULL;

	char tmpEstado[3];
	char tmpCidade[50];
	
	float percSena = SENA;
	float percQuina = QUINA;
	float percQuadra = QUADRA;
	float valorPremioCada;
	
	int iIndice, 
		qtdAcertos, 
		qtdGanhadoresSena = 0, 
		qtdGanhadoresQuina = 0, 
		qtdGanhadoresQuadra = 0, 
		count;
	
	float qtdTotal = (ptLista->iTotal * 2.00);
	
	FILE *arquivoSaida;
	
	//Deleta arquivo de relatorio anterior;
	unlink("D:\\relatorio_pre.txt");

	arquivoSaida = fopen("D:\\relatorio_pre.txt", "wt");

	if (ptVetor == NULL ){
		printf("Ainda nao houve sorteio\n");
		return;
	}

	aposta = ptLista->ptInicio;
	
	//Limpa as variaveis.
	memset(tmpEstado, 0, sizeof(tmpEstado));
	memset(tmpCidade, 0, sizeof(tmpCidade));
	
	ganhadores = NULL;

	//Verifica quantidade de ganhadores da sena, quina e quadra
	for(iIndice=0; iIndice < ptLista->iTotal; iIndice++)
	{
		//Forca parada 
		if (aposta == NULL ){
			break;
		}

		qtdAcertos = verificaQuantidadeAcertos(ptVetor, aposta->vetNumeros );
		
		if ( qtdAcertos == QTD_SENA )
		{
			/*procura quantas vezes uma determinada cidade, 
			  estado aparee na lista e traz o total na struct. */
			if ( strcmp(aposta->strEstado, tmpEstado) == 0 &&
				strcmp(aposta->strCidade, tmpCidade) == 0 )
			{
				printf("Cidade %s PESQUISADA\n", aposta->strCidade);
			}else{
				printf("Cidade %s NAO PESQUISADA\n", aposta->strCidade);
				
				auxGanhadores = search(ptLista, aposta, ptVetor);
				strcpy(tmpEstado, aposta->strEstado);
				strcpy(tmpCidade, aposta->strCidade);
					
				if ( ganhadores == NULL )
				{
					ganhadores = auxGanhadores;
					ganhadores->ptProxima=NULL;
				}else{
					auxGanhadores->ptProxima=NULL;
					ganhadores->ptProxima = auxGanhadores;	
				}
			}
			qtdGanhadoresSena++;
		}else if ( qtdAcertos == QTD_QUINA ){
			qtdGanhadoresQuina++;
		}else if ( qtdAcertos == QTD_QUADRA ){
			qtdGanhadoresQuadra++;
		}
		aposta = aposta->ptProxima;
	}

	if ( ptLista->ptInicio != NULL ) 
	{
		fprintf(arquivoSaida, "============================================================\n");
		fprintf(arquivoSaida, "                   Sistema Loto TAD$\n");
		fprintf(arquivoSaida, "                    Resultado final\n\n");

		fprintf(arquivoSaida, "Total de apostas: %d\n", ptLista->iTotal);
		fprintf(arquivoSaida, "Total arrecadado: R$ %d\n", (ptLista->iTotal * 2) );
		fprintf(arquivoSaida, "Numeros sorteados:" );
		
		for (iIndice=0; iIndice<6; iIndice++) 
			fprintf(arquivoSaida, " %i", ptVetor[iIndice]);
		
		fprintf(arquivoSaida, " \n\n");
		fprintf(arquivoSaida, "Premiação:\n");
		fprintf(arquivoSaida, "Faixa de premiação\t|\tNº de ganhadores\t|\t Valor do Prêmio (R$)\n");
		
		//Inserir calculos para ganhos..
		if ( qtdGanhadoresSena > 0 )
		{
			valorPremioCada = (qtdTotal*percSena)/qtdGanhadoresSena;
			fprintf(arquivoSaida, "Sena\t\t\t|\t\t%d\t\t|\t\t%.2f\n", qtdGanhadoresSena, valorPremioCada ); 
		}
		if ( qtdGanhadoresQuina > 0)
		{
			valorPremioCada = (qtdTotal*percQuina)/qtdGanhadoresQuina;
			fprintf(arquivoSaida, "Quina\t\t\t|\t\t%d\t\t|\t\t%.2f\n", qtdGanhadoresQuina, valorPremioCada );
		}
		
		if (qtdGanhadoresQuadra > 0)
		{
			valorPremioCada = (qtdTotal*percQuadra)/qtdGanhadoresQuadra;
			fprintf(arquivoSaida, "Quadra\t\t\t|\t\t%d\t\t|\t\t%.2f\n", qtdGanhadoresQuadra, valorPremioCada );
		}

		fprintf(arquivoSaida, "\n" );

		fprintf(arquivoSaida, "GANHADORES SENA POR ESTADO/MUNICIPIO\n" );
		fprintf(arquivoSaida, "ESTADO/MUNICIPIO\t|\tNº DE GANHADORES\n");

		if ( ganhadores != NULL )
		{
			while(ganhadores)
			{
				fprintf(arquivoSaida, "%s/%s\t\t|\t\t%d\n", ganhadores->strEstado, 
					ganhadores->strCidade, ganhadores->qtdGanhadores );
				ganhadores = ganhadores->ptProxima;
			}
		}else{
			printf("Ganhadores esta vazio!\n");
		}


		aposta = ptLista->ptInicio;
	}else{
		printf("Lista vazia\n");
	}

	fclose(arquivoSaida);

}
/*------------------------------------------------------------------------------------------
* Nome da função: liberaMemoria()
* Descrição: esta função libera a memória alocada dinamicamente para as apostas da lista
* Parâmetros: stLista*
* Retorno: Nenhum
------------------------------------------------------------------------------------------*/
void liberaMemoria(stLista* ptLista)
{
	//Variável temporária
	stAposta* ptTemp = NULL;

	//Verifica se a lista está vazia
	if (!ptLista || !ptLista->ptInicio)
	{
		return;
	}
	
	//Desaloca todos os nós da lista
	while (ptLista->ptInicio != NULL)
	{
		ptTemp = ptLista->ptInicio;
		ptLista->ptInicio = ptLista->ptInicio->ptProxima;
		free(ptTemp);
	}

	//Anula ponteiros
	ptLista->ptInicio = NULL;
	ptLista->ptFim = NULL;
	ptTemp = NULL;
}
int verificaQuantidadeAcertos(int sortiados[], int jogados[] )
{
	int i;
	int j;
	int qtdAcertos = 0;

	for(i=0; i<6; i++)
	{
		for(j=0; j<6; j++) {
			if ( sortiados[i] == jogados[j])
			{
				qtdAcertos++;
				break;
			}
		}
	}

	return qtdAcertos;
}
stGanhadores *search(stLista *ptLista, stAposta *ptAposta, int ptVetor[] )
{
	int indice = 0;
	int i = 0;
	int qtdTotal = 0;

	stGanhadores *ptGanhadores;
	stAposta *aposta;
	aposta = ptLista->ptInicio;

	
	for (indice=0; indice < (ptLista->iTotal); indice++)
	{
		
		if ( aposta == NULL )
			break;
		
		if ( strcmp(ptAposta->strEstado, aposta->strEstado) == 0 
		     && strcmp(ptAposta->strCidade, aposta->strCidade) == 0 ) 
		{
			
			i = verificaQuantidadeAcertos(aposta->vetNumeros, ptVetor);	
			
			if ( i == QTD_SENA ){
				qtdTotal++;
			}
		}
		aposta = aposta->ptProxima;
	}

	if ( qtdTotal > 1 ) {
		if ( ptGanhadores = (stGanhadores *)malloc(sizeof(stGanhadores) ) )
		{
			strcpy(ptGanhadores->strEstado, ptAposta->strEstado);
			strcpy(ptGanhadores->strCidade, ptAposta->strCidade);
			ptGanhadores->qtdGanhadores = qtdTotal;
			return ptGanhadores;
		}else{
			printf("Estouro de memoria\n");
		}
	}
}
