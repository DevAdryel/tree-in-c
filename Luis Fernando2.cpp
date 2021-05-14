#include <stdlib.h>
#include <stdio.h>

typedef struct BinaryNode {
	int dado;
	struct BinaryNode *esq;
	struct BinaryNode *dir;

} BNode;

typedef struct {
	BNode *raiz;
	int quant;
} BTree;

#define MAX(a,b) (((a)>(b))?(a):(b))

BNode* inicializaNo(int valor) {
	BNode* node = (BNode*) malloc(sizeof(BNode));
	node->dado = valor;
	node->esq = NULL;
	node->dir = NULL;

	return node;
}

BTree* inicializaArvore(int valor) {

	printf("Inicializando arvore. Raiz com valor: %d\n", valor);

	BNode* node = inicializaNo(valor);

	BTree* arv = (BTree*) malloc(sizeof(BTree));
	arv->raiz = node;
	arv->quant = 1;

	return arv;
}

void inserir(BTree *tree, BNode *node) {
	printf("Inserindo no com valor: %d\n", node->dado);
	BNode *aux = tree->raiz;
	while (aux != NULL) {
		if (node->dado < aux->dado) {
			if (aux->esq == NULL) {
				aux->esq = node;
				tree->quant++;
				return;
			} else {
				aux = aux->esq;
			}
		} else {
			if (aux->dir == NULL) {
				aux->dir = node;
				tree->quant++;
				return;
			} else {
				aux = aux->dir;
			}
		}
	}
}

BNode* buscar(BTree *tree, int valor) {
	BNode *aux = tree->raiz;
	while (aux != NULL) {
		if (aux->dado == valor) {
			return aux;
		}
		if (valor < aux->dado) {
			if (aux->esq == NULL) {
				return NULL;
			} else {
				aux = aux->esq;
			}
		} else {
			if (aux->dir == NULL) {
				return NULL;
			} else {
				aux = aux->dir;
			}
		}
	}
	return 0;
}

void imprimirTab(int n) {
	for (int i = 0; i < n; i++) {
		printf("\t");
	}
}

void imprimir(BNode *aux, int nivel) {
	if (aux != NULL) {
		imprimir(aux->dir, nivel + 1);
		imprimirTab(nivel);
		printf("%d\n", aux->dado);
		imprimir(aux->esq, nivel + 1);
	}
}

int contaFolhas(BNode *node) {
	if (node == NULL) {
		return 0;
	}

	if ((node->esq == NULL) && (node->dir == NULL)) {
		return 1;
	}

	return contaFolhas(node->esq) + contaFolhas(node->dir);
}

int folhas(BTree *tree) {
	if (tree == NULL) {
		return 0;
	} else {
		return contaFolhas(tree->raiz);
	}
}

void imprimeDecr(BNode *aux) {
	if (aux != NULL) {
		imprimeDecr(aux->dir);
		printf("%d   ", aux->dado);
		imprimeDecr(aux->esq);
	}
}

void imprimeDecrescente(BTree *tree) {
	if (tree == NULL) {
		printf("arvore vazia");
	} else {
		imprimeDecr(tree->raiz);
	}
}

int alturaNode(BNode *node) {
	if ((node == NULL) || ((node->esq == NULL) && (node->dir == NULL))) {
		return 0;
	}
	return 1 + MAX(alturaNode(node->esq), alturaNode(node->dir));
}

int altura(BTree *tree) {
	if (tree == NULL) {
		return 0;
	} else {
		return alturaNode(tree->raiz);
	}
}

int ordemNode(BNode *node) {
	if ((node == NULL) || ((node->esq == NULL) && (node->dir == NULL))) {
		return 1;
	}

	if ((node->esq != NULL) && (node->dado < node->esq->dado)) {
		return 0;
	}

	if ((node->dir != NULL) && (node->dado > node->dir->dado)) {
		return 0;
	}

	return ordemNode(node->esq) && ordemNode(node->dir);
}

int verificaOrdenacao(BTree *tree) {
	if (tree == NULL) {
		return 0;
	} else {
		return ordemNode(tree->raiz);
	}
}

int igualNode(BNode *node1, BNode *node2) {

	if ((node1 == NULL) && (node2 == NULL)) {
		return 1; //São iguais
	}

	if (((node1 == NULL) && (node2 != NULL))
			|| ((node2 == NULL) && (node1 != NULL))) {
		return 0; //São diferentes
	}

	if (node1->dado != node2->dado) {
		return 0; //São diferentes
	} else {
		if (igualNode(node1->esq, node2->esq)
				&& igualNode(node1->dir, node2->dir)) {
			return 1; //São iguais
		} else {
			return 0; //São diferentes
		}
	}
}

int igual(BTree *tree1, BTree *tree2) {
	return igualNode(tree1->raiz, tree2->raiz);
}

int main(int argc, char **argv) {
	printf("Arvore 1\n");
	BTree *tree = inicializaArvore(6);
	inserir(tree, inicializaNo(4));
	inserir(tree, inicializaNo(9));
	inserir(tree, inicializaNo(3));
	inserir(tree, inicializaNo(8));
	inserir(tree, inicializaNo(11));

	printf("\nImprimindo arvore:\n");
	imprimir(tree->raiz, 0);

	printf("\nFolhas: %d\n", folhas(tree));

	printf("\nImprimindo arvore em ordem decrescente\n");
	imprimeDecrescente(tree);

	printf("\n\nAltura: %d\n", altura(tree));

	printf("\nVerifica ordenacao: %d\n", verificaOrdenacao(tree));

	printf("\nArvore 2\n");
	BTree *tree2 = inicializaArvore(3);
	inserir(tree2, inicializaNo(2));
	inserir(tree2, inicializaNo(4));
	printf("\nImprimindo arvore:\n");
	imprimir(tree2->raiz, 0);

	printf("\nVerifica se arvores 1 e 2 sao iguais: %d\n", igual(tree, tree2));

}
