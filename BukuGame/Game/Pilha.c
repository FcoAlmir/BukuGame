#include "Pilha.h"

struct elemento {
    struct elemento *prox;
    int x, y;
};

struct nodesc {
    struct elemento *topo;
    int tamanho;
};


typedef struct elemento Elemento;

int push(Pilha *p) {
    if(p == NULL) return 0;

    else {
        Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
        if(novo != NULL) {
            novo->prox = p->topo;
            novo->x = 0;
            novo->y = 0;
            p->topo = novo;
            p->tamanho++;
            return 1;
        }
    }
    return 0;
}

int pushCoordenadas(Pilha *p, int a, int b) {
    if(p == NULL) return 0;

    else {
        Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
        if(novo != NULL) {
            novo->prox = p->topo;
            novo->x = a;
            novo->y = b;
            p->topo = novo;
            p->tamanho++;
            return 1;
        }
    }
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

int acessar(Pilha *p, int *a, int *b) {
    if(p == NULL || vazia(p)) return 0;
    else {
        Elemento *no = p->topo;
        *a = no->x;
        *b = no->y;
        pop(p);
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

int popAteN(Pilha *p) {
    if(p == NULL) return -1;
    else {
        int qtd = 0;
        while(p->topo != NULL) {
            pop(p);
            qtd++;
        }

        return qtd;
    }
}

int comparaValor(int l, int c, Pilha *jogadas) {
    Elemento* aux = jogadas->topo;
    while(aux != NULL) {
        if(aux->x == l && aux->y == c) {
            return 1;
        }
        else aux = aux->prox;
    }

    return 0;
}