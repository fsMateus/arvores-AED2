#include <stdlib.h>
#include <stdio.h>

#include "arvAvl.h"

int altura (tno *node){
	int esq, dir;

	if(node == NULL) return -1;

	esq = altura(node->esq);
	dir = altura(node->dir);

	if(esq > dir)
		return esq+1;
	else
		return dir+1;
}

int fatorBalanciamento (tno *no){
	return labs(altura(no->esq) - altura(no->dir));
}

tno* buscaMenor (tno *no){
	tno *ant = no;
	tno *aux = no->esq;
	while(aux != NULL){
		ant = aux;
		aux = aux->esq;
	}
	return ant;
}

void rotDir (tno **raiz){
	tno *aux;

	aux = (*raiz)->esq;
	(*raiz)->esq =  aux->dir;
	aux->dir = *raiz;

	aux->fb = altura(aux->dir)-altura(aux->esq);
	(*raiz)->fb = altura((*raiz)->dir)-altura((*raiz)->esq);

    *raiz = aux;
}

void rotEsq (tno **raiz){
	tno *aux;

	aux = (*raiz)->dir;
	(*raiz)->dir = aux->esq;
	aux->esq = *raiz;

	aux->fb = altura(aux->dir) - altura(aux->esq);
	(*raiz)->fb = altura((*raiz)->dir) - altura((*raiz)->esq);

	*raiz = aux;
}

void rotLR (tno **raiz){
	rotEsq(&(*raiz)->esq);
	rotDir(raiz);
}

void rotRL (tno **raiz){
	rotDir(&(*raiz)->dir);
	rotEsq(raiz);
}

void inserirAvl(tno **raiz, int valor){
	if(*raiz == NULL){

		tno *novo = (tno*)malloc(sizeof(tno));
		if(novo == NULL)
			printf("erro em alocar\n");

		novo->info = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		novo->fb = 0;

		*raiz = novo;
	}
	else{
		tno *atual;
		atual = *raiz;
		if(valor == atual->info)
			printf("valor ja existe na arvore!\n");
		else if(valor < atual->info){
			inserirAvl(&(atual->esq),valor);
			int r = fatorBalanciamento(atual);
			if(r >= 2){
				if(valor < (*raiz)->esq->info)
					rotDir(raiz);
				else
					rotLR(raiz);
			}
		}
		else{
			inserirAvl(&(atual->dir),valor);
			int r = fatorBalanciamento(atual);
			if(r >= 2){
				if(valor > ((*raiz)->dir->info))
					rotEsq(raiz);
				else
					rotRL(raiz);
			}
		}
		atual->fb = altura(atual);
	}
}

void removerAvl (tno **raiz,int valor){
	if(*raiz == NULL){
		printf("valor não existe\n");
	}
	if(valor < (*raiz)->info){
		removerAvl(&(*raiz)->esq,valor);
		int r = fatorBalanciamento(*raiz);
		if(r >= 2){
			if(altura((*raiz)->dir->esq) <= altura((*raiz)->dir->dir))
				rotEsq(raiz);
			else
				rotRL(raiz);
		}

	}
	else if(valor > (*raiz)->info){
		removerAvl(&(*raiz)->dir,valor);
		int r = fatorBalanciamento(*raiz);
		if(r >= 2){
			if(altura((*raiz)->esq->dir) <= altura((*raiz)->esq->esq))
				rotDir(raiz);
			else
				rotLR(raiz);
		}
	}
	else{
		if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
			tno *aux = *raiz;
			if((*raiz)->esq != NULL)
				*raiz = (*raiz)->esq;
			else
				*raiz = (*raiz)->dir;
			free(aux);
		}
		else{
			tno *temp = buscaMenor((*raiz)->dir);
			(*raiz)->info = temp->info;
			removerAvl(&(*raiz)->dir,(*raiz)->info);
			int r = fatorBalanciamento(*raiz);
			if(r >= 2){
				if(altura((*raiz)->esq->dir) <= altura((*raiz)->esq->esq))
					rotDir(raiz);
				else
					rotLR(raiz);
			}

		}
	}
}

void imprimeAvl(tno *raiz){

	if(raiz != NULL){

		printf("%d-> ",raiz->info);
		imprimeAvl(raiz->esq);
		imprimeAvl(raiz->dir);

	}
	//printf("\n");
}

int main(int argc, char const *argv[])
{
	tno *arvore = NULL;

	inserirAvl(&arvore,9);
	inserirAvl(&arvore,6);
	inserirAvl(&arvore,12);
	inserirAvl(&arvore,10);
	inserirAvl(&arvore,7);
	inserirAvl(&arvore,5);
	inserirAvl(&arvore,8);
	inserirAvl(&arvore,13);
	inserirAvl(&arvore,17);
	inserirAvl(&arvore,15);
	inserirAvl(&arvore,18);
	//inserirAvl(&arvore,12);

	imprimeAvl(arvore);

	removerAvl(&arvore,12);
	removerAvl(&arvore,7);

	imprimeAvl(arvore);
	return 0;
}
