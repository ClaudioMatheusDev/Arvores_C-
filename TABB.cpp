#include "TABB.h"
#include <iostream>

#include <math.h>

// necess�rios para gotoxy
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>


using namespace std; 

// CLASSE �RVORE BIN�RIA DE BUSCA - ABB --------------------------------------------

//----------------------------------------------------------------------------------
void TABB::InserirNo(TNo *&No, TInfo valor)
{
	if( No != NULL )
	{
		if( valor < No->dado )
		{
			InserirNo( No->esq, valor);
		}
		else
		{
			InserirNo( No->dir, valor);
		}
	}
	else
	{
		No = new TNo;
		No->dado = valor;
		No->esq = NULL;
		No->dir = NULL;
	}
		
} // InserirNo(TNo *No, TInfo valor)

//----------------------------------------------------------------------------------
TABB::TNo* TABB::LocalizarNo(TNo *No, TInfo valor)
{
	if( No != NULL )
	{
		if( valor == No->dado )
		{
			return No;
		}		
		else
		if( valor < No->dado )
		{
			return LocalizarNo( No->esq, valor);
		}
		else
		{
			return LocalizarNo( No->dir, valor);
		}
	}
	else
	{
		return NULL;
	}
		
} // TABB::TNo* TABB::LocalizarNo(TNo *No, TInfo valor)

//----------------------------------------------------------------------------------
void TABB::Init()
{
	Raiz = NULL;	
	
} // void TABB::Init()

//----------------------------------------------------------------------------------
bool TABB::IsEmpty()
{
	return Raiz == NULL;	
	
} // void TABB::IsEmpty()


//----------------------------------------------------------------------------------

TABB::TNo* TABB::GetRaiz()
{
	return Raiz;
	
} // TNo TABB::GetRaiz()

//--- CONSTRUTOR -------------------------------------------------------------------------------
TABB::TABB()
{
	Init();
	
	// propriedades para a impress�o da �rvore
	width = 80;	
	linha_inicial = 7;	
	linhas_entre_niveis = 2;
	
} // TABB()

//--- DESTRUTOR --------------------------------------------------------------------------------
TABB::~TABB()
{
	Destruir_Arvore();
	
} // ~TABB()

//----------------------------------------------------------------------------------
void TABB::Destruir_Arvore()
{
	while( Raiz != NULL ) Remover(Raiz->dado);
	
} // Destruir_Arvore()

//----------------------------------------------------------------------------------
void TABB::print_caminhamento_em_pre_ordem(TNo *no)
{
	if( no != NULL )
	{
		printf("%d ", no->dado);
		print_caminhamento_em_pre_ordem(no->esq);
		print_caminhamento_em_pre_ordem(no->dir);
	}	
	
} // print_caminhamento_em_pre_ordem

//----------------------------------------------------------------------------------
void TABB::print_caminhamento_em_in_ordem(TNo *no)
{
	if( no != NULL )
	{
		print_caminhamento_em_in_ordem(no->esq);
		printf("%d ", no->dado);
		print_caminhamento_em_in_ordem(no->dir);
	}	
	
} // print_caminhamento_em_in_ordem

//----------------------------------------------------------------------------------
void TABB::print_caminhamento_em_pos_ordem(TNo *no)
{
	if( no != NULL )
	{
		print_caminhamento_em_pos_ordem(no->esq);
		print_caminhamento_em_pos_ordem(no->dir);
		printf("%d ", no->dado);
	}	
	
} // print_caminhamento_em_pos_ordem

//----------------------------------------------------------------------------------
bool TABB::Remover(TInfo Elemento)
{
	TNo* aux;
	
	aux = LocalizarNo(Raiz, Elemento);
	
	if( aux != NULL )
	{
		// Caso 1 : N� n�o possui filho
		if( aux->esq == NULL && aux->dir == NULL ) 
		{
			RemoverCaso1(aux);
			return true;
		}
		else
		// Caso 2 : N� possui apenas um filho
		if( (aux->esq == NULL && aux->dir != NULL) || (aux->esq != NULL && aux->dir == NULL) )
		{
			RemoverCaso2(aux);
			return true;
		}
		else
		// Caso 2 : N� possui apenas um filho
		{
			RemoverCaso3(aux);
			return true;
		}		
	}
	else
	{
		cout << "\n\nO elemento " << Elemento << " nao esta cadastrado na arvore !!!\n\n";
		return false;
	}

} // bool TABB::Remover(TInfo Elemento)


//----------------------------------------------------------------------------------
void TABB::RemoverCaso1(TNo *&no)
{		
	if( no != Raiz )
	{
		TNo* pai;

		// obtendo o Pai do n� a ser excluido
		pai = Pai(Raiz, no->dado);

		// retirando o v�nculo do pai com o filho
		if( pai->esq == no )
		{
			pai->esq = NULL;
		}
		else
		{
			pai->dir = NULL;
		}

		// eliminando o n�
		delete(no);	
		no = NULL;
	}
	else
	{
		// eliminando o n� Raiz
		delete(Raiz);	
		Raiz = NULL;
	}	
} // void TABB::RemoverCaso1(TNo* no)

//----------------------------------------------------------------------------------
void TABB::RemoverCaso3(TNo *no)
{		
	TInfo aux;
	TNo *no_maior;
	
	no_maior = Maior( no->esq->dado );
	
	aux = no_maior->dado;
	
	Remover(no_maior->dado);
	
	no->dado = aux;	
	
} // void TABB::RemoverCaso3(TNo *no)


//----------------------------------------------------------------------------------
void TABB::RemoverCaso2(TNo *&no)
{	
	TNo *filho;
	
	// obtendo o filho do n� a ser excluido
	if( no->esq != NULL ) filho = no->esq;
	if( no->dir != NULL ) filho = no->dir;

	// se o n� a ser excluido n�o for a raiz
	if( no != Raiz ) 
	{
		TNo *pai;
	
		// obtendo o Pai do n� a ser excluido
		pai = Pai(Raiz, no->dado);
		
		// fazendo com que o n� filho do n� a ser excluido ocupe o lugar do n� a ser removido
		if( pai->esq == no )
		{
			pai->esq = filho;
		}
		else
		{
			pai->dir = filho;
		}
		
	} // no != Raiz
	else
	{
		Raiz = filho;
	}
	
	// eliminando o no
	delete(no);
	no = NULL;
	
} // void TABB::RemoverCaso2(TNo* no)

//----------------------------------------------------------------------------------
TABB::TNo* TABB::Pai(TNo *no, TInfo Elemento)
{
	TNo* aux;
	
	if( IsEmpty() ) return NULL;
	
	if( no == NULL ) return NULL;
	
	// o Pai da Raiz � a pr�pria Raiz ---------
	if( Raiz->dado == Elemento ) return Raiz;	
	
	if( Elemento > no->dado )
	{
		if( no->dir != NULL ) 
		{
			if( no->dir->dado == Elemento )
				return no;
			else
				return Pai(no->dir, Elemento);
		}
	}
	else
	{
		if( no->esq != NULL ) 
		{
			if( no->esq->dado == Elemento )
				return no;
			else
				return Pai(no->esq, Elemento);
		}
	}

	return NULL;
	
} // Pai(TNo *no, TInfo Elemento)

//----------------------------------------------------------------------------------
TABB::TNo* TABB::Maior(TInfo elemento)
{
	if( IsEmpty() ) 
	{
		cout << "\n\nArvore vazia !!!\n\n";
		return NULL;
	}
	
	TNo *no;
	
	no = LocalizarNo(Raiz, elemento);
	
	if( no == NULL  ) 
	{
		cout << "\n\nNo nao encontrado !!!\n\n";
		return NULL;
	}
	
	while( no->dir != NULL )
	{
		no = no->dir;
	}
	
	return no;	
	
} // Maior(TInfo elemento)

//----------------------------------------------------------------------------------
TABB::TNo* TABB::Menor(TInfo elemento)
{
	if( IsEmpty() ) 
	{
		cout << "\n\nArvore vazia !!!\n\n";
		return NULL;
	}
	
	TNo *no;
	
	no = LocalizarNo(Raiz, elemento);
	
	if( no == NULL  ) 
	{
		cout << "\n\nNo nao encontrado !!!\n\n";
		return NULL;
	}

	while( no->esq != NULL )
	{
		no = no->esq;
	}
	
	return no;	
	
} // Maior(TInfo elemento)

//--- Obtem o N�vel de um N� utilizando O M�todo Pai -------------------------------
int TABB::Nivel(TInfo Elemento)
{
	
	TNo *n = LocalizarNo(GetRaiz(), Elemento);
	
	int nivel;
	
	if( n != NULL )
	{
		nivel = 0;
		while( n != GetRaiz() )
		{
			n = Pai(GetRaiz(), n->dado);
			nivel++;
		}
		
		return nivel;
	}
	else
	{
		return -1;
	}
	 
} // int TABB::Nivel(TInfo Elemento)

//----------------------------------------------------------------------------------
int TABB::TotalNos(TNo *no) 
{
    if (no == NULL) return 0;
    
    return TotalNos(no->esq) + TotalNos(no->dir) + 1;
    
} // TotalNos()

//--- Altura da �rvore = Maior N�vel -----------------------------------------------
int TABB::Altura(TNo *no)
{
    int i, j, retorno;
    
    if (no == NULL) 
	{
		return -1;
	}
	
    i = Altura(no->esq);
    j = Altura(no->dir);    
    
    if (i > j) 
    {
    	retorno = i+1;
	}
	else
	{
		retorno = j+1;	
	}
	
	return retorno;
	 
} // Altura()

//----------------------------------------------------------------------------------
bool TABB::Alterar(TInfo Elemento_origem, TInfo Elemento_novo)
{		
	if( LocalizarNo(Raiz, Elemento_origem) != NULL && LocalizarNo(Raiz, Elemento_novo) == NULL )
	{
		Remover(Elemento_origem);
		
		InserirNo(Raiz, Elemento_novo);
		
		return true;
	}
	else
	{
		return false;
	}
	
} // Alterar()

//---------------------------------------------------------------------------------
void gotoxy(int x, int y)
{
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

//----------------------------------------------------------------------------------
void TABB::imprimir_arvore()
{
	/*
	system("cls");
	printf("\n\n=================================================================");
	printf("\nARVORE BINARIA DE BUSCA (ABB)");
	printf("\n=================================================================");
	*/

	imprimir_arvore(Raiz, width/2, linha_inicial);
		
	for(int i=1; i<= Altura(Raiz)+2; i++) printf("\n");
	
} // imprimir_arvore()
//----------------------------------------------------------------------------------
void TABB::imprimir_arvore(TNo *no, int x, int y)
{
	if( no != NULL )
	{
	    gotoxy(x, y);
	    printf("%d", no->dado);	
	    
	    if( no->esq != NULL )
	    {
		    gotoxy(x-1, y+1);
		    printf("%s", "/");
		}
	    
	    if( no->dir != NULL )
	    {
		    gotoxy(x+1, y+1);
		    printf("%s", "\\");
		}
	    
	    int nivel = Nivel(no->dado) + 1;
	    
	    imprimir_arvore(no->esq, x - width/pow(2,nivel+1) , y+linhas_entre_niveis);
	    imprimir_arvore(no->dir, x + width/pow(2,nivel+1) , y+linhas_entre_niveis);

	} // se no != NULL
	
	

	/*
	for(int c=1; c<=100; c++)
	{
		int linha=7;
		if( c % 10 == 0 )
		{
		    gotoxy(c,linha);
		    printf("%d", c);	
		}
	}
	*/
	
	
} // imprimir_arvore(TNo *no)
//----------------------------------------------------------------------------------

void TABB::Negativar_H(TNo* no, TInfo valor)
{
	if(no == NULL) return;
	
	no->h = -1;
	
	if(valor == no-> dado) return;
	
	if(valor < no->dado){
		Negativar_H(no->esq, valor);
	}
	else
	{
		Negativar_H(no->dir, valor);
	}
	
	return;
}// VOID TABB::Negativar_H(TNo* no, TInfo valor)

//----------------------------------------------------------------------------------
int TABB::GetFB(TNo* no){
	int hE, hD;
	
	if(no == NULL) return 0;
	 
	if(no->esq == NULL)
		hE = 0;
	else
		hE = no->esq->h;
	
	if(no->dir == NULL)
		hD = 0;
	else
		hD = no->dir->h;
	
return hE - hD;
}// int GetFB(TNo* no);

//----------------------------------------------------------------------------------

int TABB::Altura(TNo *no){
	int i, j, retorno;
	
	if(no == NULL){
		return 0;
	}
	
	i = Altura(no->esq);
	j = Altura(no->dir);
	
	if(i > j){
		retorno = i+1;
	}
	else{
		retorno = j+1;
	}
	return retorno;
} //Altura()

//----------------------------------------------------------------------------------

int TABB::Recalcular_Altura(TNo* no){
	int hOir; //Altura da sub-�rvore da direita do n�
	int hEsq; //Altura da sub-�rvore da esquerda do n�
}













