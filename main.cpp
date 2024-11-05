#include <iostream>
#include <conio.h>
#include "TABB.h"

using namespace std;

//---------------------------------------------------------------------------------
// Variáveis e objetos públicos
TABB arvore;


//---------------------------------------------------------------------------------
int main(int argc, char** argv) {
	
	/* Inserir elementos para testes --------------------------------------------------------------- */
	arvore.InserirNo( arvore.Raiz, 15);

	arvore.InserirNo( arvore.Raiz, 10);
	arvore.InserirNo( arvore.Raiz, 6);
	arvore.InserirNo( arvore.Raiz, 5);
	arvore.InserirNo( arvore.Raiz, 12);
	arvore.InserirNo( arvore.Raiz, 9);
	arvore.InserirNo( arvore.Raiz, 8);

	arvore.InserirNo( arvore.Raiz, 20);
	arvore.InserirNo( arvore.Raiz, 18);
	arvore.InserirNo( arvore.Raiz, 16);
	arvore.InserirNo( arvore.Raiz, 19);
	arvore.InserirNo( arvore.Raiz, 17);
	arvore.InserirNo( arvore.Raiz, 25);
	arvore.InserirNo( arvore.Raiz, 30);
	arvore.InserirNo( arvore.Raiz, 27);
	
	/* --------------------------------------------------------------------------------------------- */
	arvore.imprimir_arvore();
	


	cout << "\n\n";
	
	return 0;
	
} // main()
