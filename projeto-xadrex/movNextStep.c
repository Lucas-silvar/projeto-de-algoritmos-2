/*Esse codigo foi feito no chat gpt ao ser fornecido o codigo mainMov.c use apenas para esclarecer a lógica de  como dar o proximo passo com o cavalo no tabuleiro*/

#include <stdio.h>
#include <stdlib.h>

#define N 8 // Tamanho do tabuleiro

// Estrutura para representar uma posição no tabuleiro
typedef struct {
    int x, y;
} Posicao;

// Função para verificar se uma posição está dentro do tabuleiro
int ehValida(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Função para calcular os próximos movimentos possíveis do cavalo
Posicao* movimentosPossiveis(Posicao posAtual) {
    // Array com as posições possíveis para o movimento do cavalo
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

    // Alocando memória para armazenar os movimentos possíveis
    Posicao* possiveisMovimentos = (Posicao*)malloc(8 * sizeof(Posicao));
    if (possiveisMovimentos == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }

    // Calculando as próximas posições possíveis para o cavalo
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

    // Marcando o final da lista com uma posição inválida (-1, -1)
    possiveisMovimentos[contador].x = -1;
    possiveisMovimentos[contador].y = -1;

    return possiveisMovimentos;
}

// Função para imprimir o tabuleiro de xadrez com as posições possíveis para o cavalo
void imprimirTabuleiroComMovimentos(Posicao posAtual, Posicao* possiveisMovimentos) {
    printf("Tabuleiro de Xadrez com movimentos possíveis:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (posAtual.x == i && posAtual.y == j) {
                printf("X "); // Marca a posição inicial com um "X"
            } else {
                int k;
                int encontrou = 0;
                for (k = 0; possiveisMovimentos[k].x != -1 && k < 8; k++) {
                    if (possiveisMovimentos[k].x == i && possiveisMovimentos[k].y == j) {
                        printf("1 "); // Se a posição estiver nos movimentos possíveis, marca como "C"
                        encontrou = 1;
                        break;
                    }
                }
                if (!encontrou) {
                    printf(". "); // Caso contrário, marca como "."
                }
            }
        }
        printf("\n");
    }
}

// Função para escolher uma nova posição para o cavalo
Posicao escolherNovaPosicao(Posicao* possiveisMovimentos) {
    int escolha;
    printf("Escolha uma nova posição (0 a 7):\n");
    for (int i = 0; possiveisMovimentos[i].x != -1 && i < 8; i++) {
        printf("%d: (%d, %d)\n", i, possiveisMovimentos[i].x, possiveisMovimentos[i].y);
    }
    scanf("%d", &escolha);
    return possiveisMovimentos[escolha];
}

// Função principal
int main() {
    Posicao posAtual = {0, 0}; // Posição inicial do cavalo
    Posicao posAntiga = posAtual; // Posição antiga do cavalo

    // Loop para mover o cavalo e atualizar a posição antiga
    while (1) {
        // Obtendo os movimentos possíveis para a posição atual
        Posicao* possiveisMovimentos = movimentosPossiveis(posAtual);

        // Imprimindo o tabuleiro de xadrez com os movimentos possíveis
        imprimirTabuleiroComMovimentos(posAtual, possiveisMovimentos);

        // Escolhendo uma nova posição para o cavalo
        posAntiga = posAtual;
        posAtual = escolherNovaPosicao(possiveisMovimentos);

        // Liberando a memória alocada
        free(possiveisMovimentos);

        // Imprimindo a posição antiga e a nova posição do cavalo
        printf("Posição antiga: (%d, %d)\n", posAntiga.x, posAntiga.y);
        printf("Nova posição: (%d, %d)\n", posAtual.x, posAtual.y);
    }

    return 0;
}
