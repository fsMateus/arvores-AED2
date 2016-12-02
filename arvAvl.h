#include <stdlib.h>
#include <stdio.h>

typedef struct no
{
	int info;
	struct no *esq;
	struct no *dir;
	int fb;
}tno;

//calcula altura da subarvore do no corrente
int altura (tno *node);

int fatorBalanciamento (tno *no);
tno* buscaMenor (tno *no);

//faz rotação para direita
void rotDir (tno **raiz);

//faz rotação para esquerda
void rotEsq (tno **raiz);

void rotLR (tno **raiz);
void rotRL (tno **raiz);

void inserirAvl (tno **raiz, int valor);
void removerAvl (tno **raiz, int valor);
void imprimeAvl (tno *raiz);