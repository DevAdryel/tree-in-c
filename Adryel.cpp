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
	int quant;// ESSE QUANT SERVE PARA QUE SEJA AMAZENADO N�
}BTree;

BNode* inicilizarNO(int num){//ESSSA FUN��O � O PRIMEIRO PASSO PARA CRIAR UM N�
	BNode *node = (BNode*) malloc (sizeof (BNode));// AQUI VOC� EST� DIZENDO: "COMPUDADOR ME DAR UM PEDA�O DE SUA MEMORIA" PARA CRIAR UM N�
	
	node->dado = num;//AQUI � COMO SE FOSSE O DNA DO N�, QUE SERVE PARA AMAZENAR SEU CONTEUDO GENETICO
	node->esq = NULL;// NO PRINCIPIO ELE N�O TEM FILHOS, POR ISSO SUA ESQUERDA E DIREITA � VAZIA
	node->dir = NULL;
	return node;
}

BTree* inicializarTree(int num){//AQUI VOC� EST� DANDO O PRIMEIRO PASSO PARA CRIAR UMA ARVORE
	
	printf("O numero %d sera adicionado na arvore", num);
	
	BNode *node = inicilizarNO(num);//AQUI EST� ADRIBUINDO UM N� QUE TAMBEM SER� UMA RAIZ
	BTree *arv = (BTree*) malloc (sizeof (BTree));// AQUI VOC� EST� DIZENDO: "COMPUDADOR ME DAR UM PEDA�O DE SUA MEMORIA" PARA CRIAR UMA ARVORE
	arv->raiz = node;//ATRIBUINDO � RAIZ O N� CRIADO ANTES
	arv->quant=0;
	return arv;	
}

void inserir (BTree *arv, BNode *node){
	printf("Inserindo no com valor: %d\n", node->dado);
	BNode *tmp = arv->raiz;//ESSE AQUI SERVE PARA PECORER O WHILE, ONDE O TMP VAI RECEBER A CABE�A
	
	while(tmp!= NULL){//ESSE WHILE SERVE PARA PERCORER A ARVORE
		if(node->dado > tmp->dado){//AQUI ACONTECE UMA COMPARA��O: O QUE EU QUERO INSERIR � MAIOR QUE O N� ATUAL? 
			if(tmp->dir==NULL){//SENDO MAIOR IR� PARA A DIREITA E SE A DIREITA ESTIVER VAZIA IR� ADICIONAR
				tmp->dir = node;
				arv->quant++;
				return;//CASO SEJA VERDADE, ENT�O A FUN��O INSERIR TERMINA AQUI
			}
			else{
				tmp=tmp->dir;//NA PRIMEIRA TENTATIVA IR� COMPARA COM A RAIZ, CASO SEJA MAIOR IR� PARA DIREITA DELA E SE N�O ESTIVER VAZIA
							 // ELE IRA FAZER A COMPARA��O AGORA COM O PROXIMO, PARA VERIFICAR SE ADICIONA NA SUA DIREITA OU NA ESQUERDA
			}
		}
		else{// CASO A COMPA��O DIGA QUE O QUE VOC� QUER INSERIR � UM NUMERO MENOR..
			if(tmp->esq == NULL){// ELE IRA VERIFICAR SE EST� VAZIA E SE PODE ADICIONAR AQUI
				tmp->esq = node;
				arv->quant++;
				return;
			}
			else{
				tmp = tmp->esq;// CASO N�O ESTEJA VAZIA ELE IRA PARA A ESQUERDA PARA FAZER OUTRA COMPARA��O PARA VERIFICAR SE ADICIONA NA SUA DIREITA 
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