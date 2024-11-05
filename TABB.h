#ifndef TABB_H
#define TABB_H

// CLASSE ÁRVORE BINÁRIA DE BUSCA - ABB ---------------------------------------------

class TABB
{
	//-----------------------------------------------
	public:		
		typedef int TInfo;
		
		struct TNo {	
			TInfo dado;	
			TNo *esq, *dir;
			int h; //Altura do nó(subárvore)
		};
		
		TNo *Raiz;

		bool IsEmpty();
		TNo* GetRaiz();		

		void InserirNo(TNo *&No, TInfo valor);
		TNo* LocalizarNo(TNo *No, TInfo valor);
		
	
		bool Alterar(TInfo Elemento_origem, TInfo Elemento_novo);
		
		void imprimir_arvore();
		
		void print_caminhamento_em_pre_ordem(TNo *no);
		void print_caminhamento_em_pos_ordem(TNo *no);
		
		TNo* Pai(TNo *no, TInfo Elemento);
		
		int Nivel(TInfo Elemento);
		int TotalNos(TNo *no); 
		int Altura(TNo *no);
		int Altura2(TNo *no);


		void Destruir_Arvore();
			
		TABB();  // construtor
		~TABB(); // destrutor
		
		// Métodos solicitados na prova -------------------
		void print_caminhamento_em_in_ordem(TNo *no);

		TNo* Maior(TInfo elemento);
		TNo* Menor(TInfo elemento);

		bool Remover(TInfo Elemento);
		
		//ADD
		void Negativar_H(TNo* no, TInfo valor);
		
		void RSE(TNo* no1, TNo* no2);
		void RSD(TNo* no1, TNo* no2);
		void RDE(TNo* no1, TNo* no2);
		void RDD(TNo* no1, TNo* no2);
		
	//-----------------------------------------------
	protected:
		
		// propriedades para a impressão da árvore
		int width; // largura da tela em caracteres
		int linha_inicial; // linha inicial (y) da impressão
		int linhas_entre_niveis;

		void Init();

		void imprimir_arvore(TNo *no, int x, int y);

		// Métodos solicitados na prova -------------------
		void RemoverCaso1(TNo *&no);
		void RemoverCaso2(TNo *&no);
		void RemoverCaso3(TNo *no);
		
		int GetFB(TNo* no);
		
		int Recalcular_Altura(TNo* no);
		
		void Rotacionar();
	//-----------------------------------------------
	private:
		
}; // TABB

#endif
