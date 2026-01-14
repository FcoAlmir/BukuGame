#include <SDL2/SDL.h>
#include <stdio.h>

const int TAMANHO_TABULEIRO = 8;
const int TAMANHO_CASA = 60; // 60 pixels por quadrado

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Tabuleiro de Xadrez", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        TAMANHO_TABULEIRO * TAMANHO_CASA, TAMANHO_TABULEIRO * TAMANHO_CASA, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    int rodando = 1;
    SDL_Event evento;

    while (rodando) {
        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) rodando = 0;
        }

        // Limpar fundo
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Desenhar Tabuleiro
        for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
            for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
                if ((i + j) % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 235, 235, 208, 255); // Cor clara
                } else {
                    SDL_SetRenderDrawColor(renderer, 119, 149, 86, 255);  // Cor escura
                }
                
                SDL_Rect retangulo = { j * TAMANHO_CASA, i * TAMANHO_CASA, TAMANHO_CASA, TAMANHO_CASA };
                SDL_RenderFillRect(renderer, &retangulo);
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}