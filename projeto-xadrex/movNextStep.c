/*Esse codigo foi feito no chat gpt ao ser fornecido o codigo mainMov.c use apenas para esclarecer a l�gica de  como dar o proximo passo com o cavalo no tabuleiro*/

#include <stdio.h>
#include <stdlib.h>

#define N 8 // Tamanho do tabuleiro

// Estrutura para representar uma posi��o no tabuleiro
typedef struct {
    int x, y;
} Posicao;

// Fun��o para verificar se uma posi��o est� dentro do tabuleiro
int ehValida(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Fun��o para calcular os pr�ximos movimentos poss�veis do cavalo
Posicao* movimentosPossiveis(Posicao posAtual) {
    // Array com as posi��es poss�veis para o movimento do cavalo
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

    // Alocando mem�ria para armazenar os movimentos poss�veis
    Posicao* possiveisMovimentos = (Posicao*)malloc(8 * sizeof(Posicao));
    if (possiveisMovimentos == NULL) {
        printf("Erro de aloca��o de mem�ria.\n");
        exit(1);
    }

    // Calculando as pr�ximas posi��es poss�veis para o cavalo
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

    // Marcando o final da lista com uma posi��o inv�lida (-1, -1)
    possiveisMovimentos[contador].x = -1;
    possiveisMovimentos[contador].y = -1;

    return possiveisMovimentos;
}

// Fun��o para imprimir o tabuleiro de xadrez com as posi��es poss�veis para o cavalo
void imprimirTabuleiroComMovimentos(Posicao posAtual, Posicao* possiveisMovimentos) {
    printf("Tabuleiro de Xadrez com movimentos poss�veis:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (posAtual.x == i && posAtual.y == j) {
                printf("X "); // Marca a posi��o inicial com um "X"
            } else {
                int k;
                int encontrou = 0;
                for (k = 0; possiveisMovimentos[k].x != -1 && k < 8; k++) {
                    if (possiveisMovimentos[k].x == i && possiveisMovimentos[k].y == j) {
                        printf("1 "); // Se a posi��o estiver nos movimentos poss�veis, marca como "C"
                        encontrou = 1;
                        break;
                    }
                }
                if (!encontrou) {
                    printf(". "); // Caso contr�rio, marca como "."
                }
            }
        }
        printf("\n");
    }
}

// Fun��o para escolher uma nova posi��o para o cavalo
Posicao escolherNovaPosicao(Posicao* possiveisMovimentos) {
    int escolha;
    printf("Escolha uma nova posi��o (0 a 7):\n");
    for (int i = 0; possiveisMovimentos[i].x != -1 && i < 8; i++) {
        printf("%d: (%d, %d)\n", i, possiveisMovimentos[i].x, possiveisMovimentos[i].y);
    }
    scanf("%d", &escolha);
    return possiveisMovimentos[escolha];
}

// Fun��o principal
int main() {
    Posicao posAtual = {0, 0}; // Posi��o inicial do cavalo
    Posicao posAntiga = posAtual; // Posi��o antiga do cavalo

    // Loop para mover o cavalo e atualizar a posi��o antiga
    while (1) {
        // Obtendo os movimentos poss�veis para a posi��o atual
        Posicao* possiveisMovimentos = movimentosPossiveis(posAtual);

        // Imprimindo o tabuleiro de xadrez com os movimentos poss�veis
        imprimirTabuleiroComMovimentos(posAtual, possiveisMovimentos);

        // Escolhendo uma nova posi��o para o cavalo
        posAntiga = posAtual;
        posAtual = escolherNovaPosicao(possiveisMovimentos);

        // Liberando a mem�ria alocada
        free(possiveisMovimentos);

        // Imprimindo a posi��o antiga e a nova posi��o do cavalo
        printf("Posi��o antiga: (%d, %d)\n", posAntiga.x, posAntiga.y);
        printf("Nova posi��o: (%d, %d)\n", posAtual.x, posAtual.y);
    }

    return 0;
}
