#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodesc Pilha;

Pilha* criar();

int push(Pilha *);

int pushCoordenadas(Pilha *, int, int);

int pop(Pilha *);

int vazia(Pilha *);

int tamanhoP(Pilha *);

int popAteN(Pilha *);

int comparaValor(int, int, Pilha *);

int acessar(Pilha *, int *, int *);