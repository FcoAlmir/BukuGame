#include "Pilha.h"
#include "Buku.h"
#include <time.h>
#include <ctype.h>

int main() {
    Tabuleiro *tab = NULL;
    Pilha *pontBrancas = criarPilhaPont();
    Pilha *pontPretas = criarPilhaPont();
    Pilha *mao = criar();
    Pilha *jogadas = criar();
    int tam = 0, jogador = 0;
    srand(time(NULL));

    printf("Digite o tamanho do tabuleiro: ");

    while(scanf("%d", &tam) != 1 || tam < 2) {
        printf("Tamanho invalido, por favor, digite um tamanho maior ou igual a 2: ");
        while(getchar() != '\n');
    }

    tab = criarTabuleiro(tam);

    int num_aleatorio1 = (rand() % tam);
    int num_aleatorio2 = (rand() % tam);
    push(tab[num_aleatorio1][num_aleatorio2]);

    while(checarVitoria(tab, tam) != 1) {
        if((jogador % 2) == 0) {
            printf("--------------------\n\n");
            printTabuleiroBasico(tab, tam);
            printf("--------------------\n");
            int escolhaLinha = -1;
            printf("Brancas escolhem uma linha para ser removida(de 1 a %d): ", tam);
            while(scanf("%d", &escolhaLinha) != 1 || escolhaLinha < 1 || escolhaLinha > tam) {
                printf("Linha invalida, por favor, digite novamente: ");
                while(getchar() != '\n');
            }

            int qtdPecas = tomarLinha(tab, tam, escolhaLinha);
            for(int i = 0 ; i < qtdPecas ; i++) {
                push(mao);
            }
            printf("--------------------\n\n");
            printTabuleiroBasico(tab, tam);
            printf("--------------------\n");
            printf("Voce tem %d pecas na mao\n", tamanhoP(mao));
            int flag = pingar(tab, tam, jogadas, mao);

            if(flag == 0) {
                desistencia(tab, tam, pontPretas);
            }
            else if(flag == 1) {
                pontuacaoVerificacao(tab, tam, pontBrancas, pontPretas);
            }
            else { //REFAZ O PINGO
                for(int j = 0 ; j < flag ; j++) {
                    push(mao);
                }
            }

            jogador++;
        }

        else {
            printf("--------------------\n\n");
            printTabuleiroBasico(tab, tam);
            printf("--------------------\n");
            int escolhaColuna = -1;
            printf("Pretas escolhem uma coluna para ser removida(de 1 a %d): ", tam);
            while(scanf("%d", &escolhaColuna) != 1 || escolhaColuna < 1 || escolhaColuna > tam) {
                printf("Coluna invalida, por favor, digite novamente: ");
                while(getchar() != '\n');
            }

            int qtdPecas = tomarColuna(tab, tam, escolhaColuna);
            for(int i = 0 ; i < qtdPecas ; i++) {
                push(mao);
            }
            printf("--------------------\n\n");
            printTabuleiroBasico(tab, tam);
            printf("--------------------\n");
            printf("Voce tem %d pecas na mao\n", tamanhoP(mao));
            int flag = pingar(tab, tam, jogadas, mao);

            if(flag == 0) {
                desistencia(tab, tam, pontBrancas);
            }
            else if(flag == 1) {
                pontuacaoVerificacao(tab, tam, pontBrancas, pontPretas);
            }
            else { //REFAZ O PINGO
                for(int j = 0 ; j < flag ; j++) {
                    push(mao);
                }
            }

            jogador++;
        }
    }

    printf("\nJogo Terminado!\n");
    
    if(tamanhoP(pontBrancas) > tamanhoP(pontPretas)) {
        printf("As Brancas venceram com %d pontos!\n", tamanhoP(pontBrancas));
        printf("As Pretas ficaram com %d pontos!\n", tamanhoP(pontPretas));
    }

    else if(tamanhoP(pontBrancas) < tamanhoP(pontPretas)) {
        printf("As Pretas venceram com %d pontos!\n", tamanhoP(pontPretas));
        printf("As Brancas ficaram com %d pontos!\n", tamanhoP(pontBrancas));
    }

    else {
        printf("Empatou bixo\n");
    }

    return 0;
}
