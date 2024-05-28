#include <stdio.h>
#include <stdlib.h>

#define N 8

typedef struct {
    int x, y;
} Posicao;

int ehValida(int x, int y) {
    return ((x >= 0 && x < N) && (y >= 0 && y < N));
}

Posicao* movimentosPossiveis(Posicao posAtual) {
    if (!ehValida(posAtual.x, posAtual.y)) {
        Posicao* movimentosInvalidos = (Posicao*)malloc(sizeof(Posicao));
        movimentosInvalidos[0].x = -1;
        movimentosInvalidos[0].y = -1;
        return movimentosInvalidos;
    }

    int mov_poss[8][2] = {
        {2, 1},
        {2, -1},
        {-2, 1},
        {-2, -1},
        {1, 2},
        {1, -2},
        {-1, 2},
        {-1, -2}
    };

    Posicao* possiveisMovimentos = (Posicao*)malloc(8 * sizeof(Posicao));
    if (possiveisMovimentos == NULL) {
        exit(1);
    }

    int contador = 0;
    for (int i = 0; i < 8; i++) {
        int newX = posAtual.x + mov_poss[i][0];
        int newY = posAtual.y + mov_poss[i][1];
        if (ehValida(newX, newY)) {
            possiveisMovimentos[contador].x = newX;
            possiveisMovimentos[contador].y = newY;
            contador++;
        }
    }

    possiveisMovimentos[contador].x = -1;
    possiveisMovimentos[contador].y = -1;

    return possiveisMovimentos;
}

void imprimirTabuleiroComMovimentos(Posicao posAtual, Posicao* possiveisMovimentos) {
    if (possiveisMovimentos[0].x == -1 && possiveisMovimentos[0].y == -1) {
        printf("Posicao inicial invalida\n");
        return;
    }

    printf("movimentos poss:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (posAtual.x == i && posAtual.y == j) {
                printf("X ");
            } else {
                int k;
                int encontrou = 0;
                for (k = 0; possiveisMovimentos[k].x != -1 && k < 8; k++) {
                    if (possiveisMovimentos[k].x == i && possiveisMovimentos[k].y == j) {
                        printf("1 ");
                        encontrou = 1;
                        break;
                    }
                }
                if (!encontrou) {
                    printf(". ");
                }
            }
        }
        printf("\n");
    }
}

int main() {
    Posicao posAtual = {7, 7};

    Posicao* possiveisMovimentos = movimentosPossiveis(posAtual);

    imprimirTabuleiroComMovimentos(posAtual, possiveisMovimentos);

    free(possiveisMovimentos);

    return 0;
}
