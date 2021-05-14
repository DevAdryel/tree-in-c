#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryNode//ESSE PRIMEIRO TYPEDEF SERVE COMO SE FOSSE UMA CAIXA DE MODELAR UMA MASSA
{
	   int dado;
	   struct BinaryNode *esq;
	   struct BinaryNode *dir;	
}BNode;

typedef struct BinaryTree//ESSe SEGUNDO TYPEDEF SERVE PARA AMAZENAR OS DADOS DA RAIZ
{
	BNode *raiz;//AQUI PODEMOS ENTEDER QUE A RAIZ TEM UMA DIREITA E UMA ESQUERDA
	int quant;// ESSE QUANT SERVE PARA QUE SEJA AMAZENADO Nó
}BTree;

BNode* inicilizarNO(int num){//ESSSA FUNÇÃO É O PRIMEIRO PASSO PARA CRIAR UM NÓ
	BNode *node = (BNode*) malloc (sizeof (BNode));// AQUI VOCÊ ESTÁ DIZENDO: "COMPUDADOR ME DAR UM PEDAÇO DE SUA MEMORIA" PARA CRIAR UM NÓ
	
	node->dado = num;//AQUI É COMO SE FOSSE O DNA DO NÓ, QUE SERVE PARA AMAZENAR SEU CONTEUDO GENETICO
	node->esq = NULL;// NO PRINCIPIO ELE NÃO TEM FILHOS, POR ISSO SUA ESQUERDA E DIREITA É VAZIA
	node->dir = NULL;
	return node;
}

BTree* inicializarTree(int num){//AQUI VOCÊ ESTÁ DANDO O PRIMEIRO PASSO PARA CRIAR UMA ARVORE
	
	printf("O numero %d sera adicionado na arvore", num);
	
	BNode *node = inicilizarNO(num);//AQUI ESTÁ ADRIBUINDO UM NÓ QUE TAMBEM SERÁ UMA RAIZ
	BTree *arv = (BTree*) malloc (sizeof (BTree));// AQUI VOCÊ ESTÁ DIZENDO: "COMPUDADOR ME DAR UM PEDAÇO DE SUA MEMORIA" PARA CRIAR UMA ARVORE
	arv->raiz = node;//ATRIBUINDO À RAIZ O NÓ CRIADO ANTES
	arv->quant=0;
	return arv;	
}

void inserir (BTree *arv, BNode *node){
	printf("Inserindo no com valor: %d\n", node->dado);
	BNode *tmp = arv->raiz;//ESSE AQUI SERVE PARA PECORER O WHILE, ONDE O TMP VAI RECEBER A CABEÇA
	
	while(tmp!= NULL){//ESSE WHILE SERVE PARA PERCORER A ARVORE
		if(node->dado > tmp->dado){//AQUI ACONTECE UMA COMPARAÇÃO: O QUE EU QUERO INSERIR É MAIOR QUE O NÓ ATUAL? 
			if(tmp->dir==NULL){//SENDO MAIOR IRÁ PARA A DIREITA E SE A DIREITA ESTIVER VAZIA IRÁ ADICIONAR
				tmp->dir = node;
				arv->quant++;
				return;//CASO SEJA VERDADE, ENTÃO A FUNÇÃO INSERIR TERMINA AQUI
			}
			else{
				tmp=tmp->dir;//NA PRIMEIRA TENTATIVA IRÁ COMPARA COM A RAIZ, CASO SEJA MAIOR IRÁ PARA DIREITA DELA E SE NÃO ESTIVER VAZIA
							 // ELE IRA FAZER A COMPARAÇÃO AGORA COM O PROXIMO, PARA VERIFICAR SE ADICIONA NA SUA DIREITA OU NA ESQUERDA
			}
		}
		else{// CASO A COMPAÇÃO DIGA QUE O QUE VOCÊ QUER INSERIR É UM NUMERO MENOR..
			if(tmp->esq == NULL){// ELE IRA VERIFICAR SE ESTÁ VAZIA E SE PODE ADICIONAR AQUI
				tmp->esq = node;
				arv->quant++;
				return;
			}
			else{
				tmp = tmp->esq;// CASO NÃO ESTEJA VAZIA ELE IRA PARA A ESQUERDA PARA FAZER OUTRA COMPARAÇÃO PARA VERIFICAR SE ADICIONA NA SUA DIREITA 
																																		// OU ESQUERDA
			}
		}
	}	
	
}

void imprimirDecrecente (BNode *tmp){
	if(tmp!=NULL){
		imprimirDecrecente (tmp->dir);
		printf("%d      ", tmp->dado);
		imprimirDecrecente(tmp->esq);
	}
}
void imprimir(BNode *tmp){
	if(tmp!=NULL){
		imprimir(tmp->esq);
		printf("%d      ", tmp->dado);
		imprimir (tmp->dir);
		
		
	}
}


int folha(BNode *arv){
	if (arv==NULL){
		return 0;
	}
	if(arv->dir==NULL && arv->esq == NULL){
		return 1;
	}
	else{
		return folha(arv->dir) + folha (arv->esq);
	}
	
}



int main(int argc, char** argv)
{
	BTree *arv= inicializarTree(5);
	inserir(arv, inicilizarNO(6));
	inserir (arv, inicilizarNO(7));
	inserir (arv, inicilizarNO(4));
	inserir (arv, inicilizarNO(3));
//	inserir (arv, inicilizarNO(11));
	imprimir (arv->raiz); 
	printf("\n");
	
	imprimirDecrecente(arv->raiz);
	int x;
	x = folha(arv->raiz); printf ("\n\n%d", x);
	
	printf ("\nA altura e %d", arv->quant);
	return 0;
}