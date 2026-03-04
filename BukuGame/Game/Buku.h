#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pilha.h"

typedef Pilha** Tabuleiro;

Tabuleiro *criarTabuleiro(int );

int tomarColuna(Tabuleiro *, int, int);

int tomarLinha(Tabuleiro *, int, int);

void printTabuleiroBasico(Tabuleiro *, int);

Pilha *criarPilhaPont();

int pontuacaoVerificacao(Tabuleiro *, int, Pilha *, Pilha *);

int checarVitoria(Tabuleiro *, int);

int pingar(Tabuleiro *, int, Pilha *, Pilha *);

int desistencia(Tabuleiro *, int, Pilha *);