#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodesc {
    struct elemento *topo;
    int tamanho;
};

typedef struct nodesc Pilha;

Pilha* criar();

int push(Pilha *);

int pop(Pilha *);

int vazia(Pilha *);

int tamanhoP(Pilha *);