#include "Pilha.h"

struct elemento {
    struct elemento *prox;
};


typedef struct elemento Elemento;

int push(Pilha *p) {
    if(p == NULL) return 0;

    else {
        Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
        if(novo != NULL) {
            novo->prox = p->topo;
            p->topo = novo;
            p->tamanho++;
            return 1;
        }
    }
    return 0;
}

int pop(Pilha *p) {
    if(p == NULL || vazia(p)) return 0;
    else {
        Elemento *adeus = p->topo;
        p->topo = adeus->prox;
        adeus->prox = NULL;
        p->tamanho--;
        free(adeus);
        return 1;
    }
}

Pilha *criar() {
    Pilha *p = NULL;
    p = (Pilha *)malloc(sizeof(Pilha));
    if (p != NULL) {
        p->topo = NULL;
        p->tamanho = 0;
    }

    return p;
}

int vazia(Pilha *p) {
    if(p->tamanho == 0) return 1;
    else return 0;
}

int tamanhoP(Pilha *p) {
    if(p == NULL) return -1;
    else if(vazia(p)) return 0;
    else return p->tamanho;
}