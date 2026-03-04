#include "Buku.h"
#include "Pilha.h"

Tabuleiro *criarTabuleiro(int tam) { //cria uma matriz dinamica de ponteiro de pilha, retorna o ponteiro da matriz
    if(tam <= 1) return NULL;
    else {
        Tabuleiro *tab = (Tabuleiro *)malloc(sizeof(Tabuleiro) * tam);
        if(tab == NULL) return NULL;
        for(int i = 0 ; i < tam ; i++) {
            tab[i] = (Tabuleiro)malloc(sizeof(Pilha *) * tam);
            if(tab[i] == NULL) return NULL;
            for(int j = 0 ; j < tam ; j++) {
                tab[i][j] = criar();
                push(tab[i][j]);
            }
        }

        if(tab != NULL) return tab;
        else return NULL;
    }
}

Pilha *criarPilhaPont() { //cria uma pilha comum, usada para a pontuação dos jogadores;
    Pilha *pp = criar();
    if(pp != NULL) return pp;
    else return NULL;
}

int tomarLinha(Tabuleiro *tab, int tam, int linha) { //jogada das Brancas, toma todas as peças de uma linha escolhida; Retorna a quantidade de peças tomadas;
    if(tab == NULL) return -1;
    else {
        int qtdPeças = 0;
        linha--;
        for(int j = 0 ; j < tam ; j++) {
            qtdPeças = qtdPeças + popAteN(tab[linha][j]);
        }
        return qtdPeças;
    }
}

int tomarColuna(Tabuleiro *tab, int tam, int coluna) { //jogada das Pretas, toma todas as peças da coluna escolhida; Retorna a quantidade de peças tomadas;
    if(tab == NULL) return -1;
    else {
        int qtdPeças = 0;
        coluna--;
        for(int i = 0 ; i < tam ; i++) {
            qtdPeças = qtdPeças + popAteN(tab[i][coluna]);
        }
        return qtdPeças;
    }
}

int pontuacaoVerificacao(Tabuleiro *tab, int tam, Pilha *pontBranco, Pilha *pontPreto) { //Verifica se tem 3 ou mais peças empilhadas e adiciona na pilha de pontuação
    int pont = 0;
    for(int i = 0 ; i < tam ; i++) {
        for(int j = 0 ; j < tam ; j++) {
            if(tamanhoP(tab[i][j]) >= 3) {
                pont = popAteN(tab[i][j]);
                if((i + j) % 2 == 0) {
                    while(pont > 0) { //coloca a pontuacao no branco
                        push(pontBranco);
                        pont--;
                    }
                }

                else { //coloca a pontuaçao no preto
                    while(pont > 0) {
                        push(pontPreto);
                        pont--;
                    }
                }

                pont = 0; // garantia
            }
        }
    }
}

void printTabuleiroBasico(Tabuleiro *tab, int tam) { //print basico do tabuleiro
    if(tab == NULL) return;
    else {
        for(int i = 0 ; i < tam ; i++) {
            for(int j = 0 ; j < tam ; j++) {
                printf("%d  ", tamanhoP(tab[i][j]));
            }
            printf("\n");
        }
        printf("\n");
    }
}

int checarVitoria(Tabuleiro *tab, int tam) { //se todas as posições tiverem 1 ou nenhuma peça, retorna a flag como 1, indicando q acabou o jogo;
    int flag = 1;
    for(int i = 0 ; i < tam ; i++) {
        for(int j = 0 ; j < tam ; j++) {
            if(tamanhoP(tab[i][j]) >= 2) {
                flag = 0;
                return flag;
            }
        }
    }

    return flag;
}

int desfazJogada(Tabuleiro *tab, int tam, Pilha *jogadas) {
    int a, b;
    while(tamanhoP(jogadas) > 0) {
        acessar(jogadas, &a, &b);
        pop(tab[a][b]);
    }
}

int pingar(Tabuleiro *tab, int tam, Pilha *jogadas, Pilha *mao) {
    //escolhe uma posição do tabuleiro
    if(tamanhoP(mao) == 0) return 0;
    int l = 0, c = 0;
    char caminho;
    printf("Escolha a posicao inicial que voce quer pingar (x y): ");
    scanf("%d %d", &l, &c);
    printf("\n");

    while(l <= 0 || c <= 0 || l > tam || c > tam) {
        printf("Digite uma posicao valida: \n");
        scanf("%d", &l);
        scanf("%d", &c);    
    }

    l--; c--;

    //da push nessa posição
    push(tab[l][c]);
    pop(mao);
    printTabuleiroBasico(tab, tam);

    //da push das coordenadas na pilha de jogadas
    pushCoordenadas(jogadas, l, c);
    
    while(tamanhoP(mao) > 0) {
        printf("\nQuantidade da mao: %d\n", tamanhoP(mao));
        //checagem das proximas jogadas
        int Norte = comparaValor(l-1, c, jogadas);
        int Oeste = comparaValor(l, c-1, jogadas);
        int Sul = comparaValor(l+1, c, jogadas);
        int Leste = comparaValor(l, c+1, jogadas);

        printf("Voce pode pingar nas direcoes: ");
        if(l > 0 && l < tam) {
            if(Norte == 0) {
                printf(" W (Norte) ");
            }
        }
        else Norte = 1;

        if(c > 0 && c < tam) {
            if(Oeste == 0) {
                printf(" A (Oeste) ");
            }
        }
        else Oeste = 1;

        if(l >= 0 && l < tam-1) {
            if(Sul == 0) {
                printf(" S (Sul) ");
            }
        }
        else Sul = 1;

        if(c >= 0 && c < tam-1) {
            if(Leste == 0) {
                printf(" D (Leste) ");
            }
        }
        else Leste = 1;

        if(Norte == 1 && Sul == 1 && Oeste == 1 && Leste == 1) {
            printf("Voce chegou num beco sem saida, refaca suas jogadas do começo!\n");
            int save = tamanhoP(mao) + tamanhoP(jogadas);
            desfazJogada(tab, tam, jogadas);
            return save;
        }

        if(Norte == 1 && Oeste == 1 && l+1 == tam && c+1 == tam) {
            printf("Voce chegou num beco sem saida, refaca suas jogadas do começo!\n");
            int save = tamanhoP(mao) + tamanhoP(jogadas);
            desfazJogada(tab, tam, jogadas);
            return save;
        }

        if(Norte == 1 && Leste == 1 && l+1 == tam && c-1 == -1) {
            printf("Voce chegou num beco sem saida, refaca suas jogadas do começo!\n");
            int save = tamanhoP(mao) + tamanhoP(jogadas);
            desfazJogada(tab, tam, jogadas);
            return save;
        }

        if(Sul == 1 && Leste == 1 && l-1 == -1 && c-1 == -1) {
            printf("Voce chegou num beco sem saida, refaca suas jogadas do começo!\n");
            int save = tamanhoP(mao) + tamanhoP(jogadas);
            desfazJogada(tab, tam, jogadas);
            return save;
        }

        if(Sul == 1 && Oeste == 1 && l-1 == -1 && c+1 == tam) {
            printf("Voce chegou num beco sem saida, refaca suas jogadas do começo!\n");
            int save = tamanhoP(mao) + tamanhoP(jogadas);
            desfazJogada(tab, tam, jogadas);
            return save;
        }

        else {
            printf("Digite o caminho no qual voce quer seguir: ");
            scanf(" %c", &caminho);
        }

        int teste = 0;
        while(teste != 1) {

            switch(caminho) {
                case 'W': if(Norte == 1) {
                            printf("Nao pode, jogue novamente\n");
                            scanf(" %c", &caminho);
                            break;
                } 
                        l--;
                        pushCoordenadas(jogadas, l, c);
                        pop(mao);
                        push(tab[l][c]);
                        teste = 1;
                        break;
                case 'w': if(Norte == 1) {
                            printf("Nao pode, jogue novamente\n");
                            scanf(" %c", &caminho);
                            break;
                }  
                        l--;
                        pushCoordenadas(jogadas, l, c);
                        pop(mao);
                        push(tab[l][c]);
                        teste = 1;
                        break;
                case 'A': if(Oeste == 1) {
                            printf("Nao pode, jogue novamente\n");
                            scanf(" %c", &caminho);
                            break;
                }  
                        c--;
                        pushCoordenadas(jogadas, l, c);
                        pop(mao);
                        push(tab[l][c]);
                        teste = 1;
                        break;
                case 'a': if(Oeste == 1) {
                            printf("Nao pode, jogue novamente\n");
                            scanf(" %c", &caminho);
                            break;
                }   
                        c--;
                        pushCoordenadas(jogadas, l, c);
                        pop(mao);
                        push(tab[l][c]);
                        teste = 1;
                        break;
                case 'S': if(Sul == 1) {
                            printf("Nao pode, jogue novamente\n");
                            scanf(" %c", &caminho);
                            break;
                }   
                        l++;
                        pushCoordenadas(jogadas, l, c);
                        pop(mao);
                        push(tab[l][c]);
                        teste = 1;
                        break;
                case 's': if(Sul == 1) {
                            printf("Nao pode, jogue novamente\n");
                            scanf(" %c", &caminho);
                            break;
                }  
                        l++;
                        pushCoordenadas(jogadas, l, c);
                        pop(mao);
                        push(tab[l][c]);
                        teste = 1;
                        break;
                case 'D': if(Leste == 1) {
                            printf("Nao pode, jogue novamente\n");
                            scanf(" %c", &caminho);
                            break;
                }   
                        c++;
                        pushCoordenadas(jogadas, l, c);
                        pop(mao);
                        push(tab[l][c]);
                        teste = 1;
                        break;
                case 'd': if(Leste == 1) {
                            printf("Nao pode, jogue novamente\n");
                            scanf(" %c", &caminho);
                            break;
                }   
                        c++;
                        pushCoordenadas(jogadas, l, c);
                        pop(mao);
                        push(tab[l][c]);
                        teste = 1;
                        break;

                default: printf("Direcao nao encontrada\n");
                        scanf(" %c", &caminho);
                        teste = 0;
                        break;
            }
    }
        printf("\n");
        printTabuleiroBasico(tab, tam);
    }
    popAteN(jogadas);
    return 1;

    //se sim, repete o loop
    //senão da pop em todas as posições da pilha jogadas e volta pro começo
}

int desistencia(Tabuleiro *tab, int tam, Pilha *pont) {
    for(int i = 0 ; i < tam ; i++) {
        for(int j = 0 ; j < tam ; j++) {
            while(tamanhoP(tab[i][j]) > 0) {
                push(pont);
                pop(tab[i][j]);
            }
        }
    }

    return 1;
}