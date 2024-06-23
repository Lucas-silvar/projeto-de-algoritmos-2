#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Definição da struct Posicao para armazenar os valores iniciais e finais do cavalo
typedef struct
{
    int x, y;
} Posicao;

typedef struct no
{
    Posicao pos;
    int numeroDePassos;
    struct no *parent;
} no;

int **criarTabuleiro(int **tabuleiro, int tamanhoDoTabuleiro)
{
    // cria a matriz "tabuleiro" e define todos os valores para "-1"
    tabuleiro = (int **)malloc(tamanhoDoTabuleiro * sizeof(int *));
    for (int i = 0; i < tamanhoDoTabuleiro; i++)
    {
        tabuleiro[i] = (int *)malloc(tamanhoDoTabuleiro * sizeof(int));
        for (int j = 0; j < tamanhoDoTabuleiro; j++)
        {
            tabuleiro[i][j] = -1;
        }
    }

    return tabuleiro;
}
// Cria um novo nó
// Recebe como parâmetros a coordenada do cavalo no tabuleiro, o numeroDePassos para
// realizar o próximo passo e o que será um nó pai
no *criarNo(int x, int y, int numeroDePassos, no *parent)
{
    no *tree = (no *)malloc(sizeof(no));
    tree->pos.x = x;
    tree->pos.y = y;
    tree->numeroDePassos = numeroDePassos;
    tree->parent = parent;
    return tree;
}

// Função recursiva para mostrar o caminho percorrido pelo cavalo no tabuleiro
// como sendo passo 0, 1, 2, 3, ..., tamanhoDoTabuleiro
// Recebe como parâmetro uma árvore e uma matriz quadrada tamanhoDoTabuleiro
void imprimirCaminho(no *node, int **tabuleiro)
{
    if (node == NULL) // critério de parada
        return;

    imprimirCaminho(node->parent, tabuleiro); // percorre a árvore inteira

    if (tabuleiro[node->pos.x][node->pos.y] == -1)
    {
        static int passo = 0;                          // os valores da variável passo serão mantidos independentes das funções chamadas
                                                       // para marcar o trajeto do cavalo
        tabuleiro[node->pos.x][node->pos.y] = passo++; // posição atual agora é o próximo passo, então incrementa passo
    }
}

// Verifica se uma posição é válida dentro do tabuleiro tamanhoDoTabuleiro x tamanhoDoTabuleiro
int ehValida(int x, int y, int tamanhoDoTabuleiro)
{
    return (x >= 0 && x < tamanhoDoTabuleiro && y >= 0 && y < tamanhoDoTabuleiro);
}

// Movimentos possíveis do cavalo em relação à sua posição atual [x, y]
int movimentos[8][2] = {
    {2, 1}, // 2 em x + 1 em y = nova posição
    {2, -1},
    {-2, 1},
    {-2, -1},
    {1, 2},
    {1, -2},
    {-1, 2},
    {-1, -2}};

// Encontra o menor caminho do cavalo saindo de uma posição incial [x0, y0] até uma posição final [x, y]
// Parâmetros de posição de início [x, y], fim [x, y] e uma matriz quadrada de tamanho tamanhoDoTabuleiro
int menorCaminho(Posicao inicio, Posicao fim, int **tabuleiro, int tamanhoDoTabuleiro)
{
    if (!ehValida(inicio.x, inicio.y, tamanhoDoTabuleiro) || !ehValida(fim.x, fim.y, tamanhoDoTabuleiro))
    {
        return -1;
    }

    // Inicializa a variável "visitado", que guarda as casas que o cavalo já percorreu
    int **visitado = (int **)malloc(tamanhoDoTabuleiro * sizeof(int *));
    for (int i = 0; i < tamanhoDoTabuleiro; i++)
    {
        visitado[i] = (int *)malloc(tamanhoDoTabuleiro * sizeof(int));
        for (int j = 0; j < tamanhoDoTabuleiro; j++)
            visitado[i][j] = 0; // inicializa todas as posições como não visitada
    }
    // Criação do nó raiz representando a posição inicial do cavalo
    no *raiz = criarNo(inicio.x, inicio.y, 0, 0);

    // Fila para armazenar os nós a serem explorados (fila prioritária)
    no **fila = (no **)malloc(tamanhoDoTabuleiro * tamanhoDoTabuleiro * sizeof(no *));
    int frente = 0, tras = 0;

    // Adiciona a raiz na fila e marca a posição inicial do cavalo
    fila[tras++] = raiz;
    visitado[inicio.x][inicio.y] = 1;

    int limitanteSuperior = INT_MAX; // Inicializa o limitante superior

    // Loop que explora os nós da fila
    while (frente < tras)
    {
        no *atual = fila[frente++];
        int x = atual->pos.x;
        int y = atual->pos.y;
        int numeroDePassos = atual->numeroDePassos;
        // Verifica se a posição atual é a posição desejada (posição final)
        if (x == fim.x && y == fim.y)
        {
            imprimirCaminho(atual, tabuleiro); // Se sim, imprime o caminho percorrido
            for (int i = 0; i < tamanhoDoTabuleiro; i++)
            {
                free(visitado[i]);
            }
            free(visitado);
            free(fila);
            return numeroDePassos;
        }
        // Explora todos os movimentos possíveis do cavalo a partir da posição atual
        for (int i = 0; i < 8; i++)
        {
            int novoX = x + movimentos[i][0];
            int novoY = y + movimentos[i][1];

            if (ehValida(novoX, novoY, tamanhoDoTabuleiro) && !visitado[novoX][novoY]) // Verifica se a nova posição é válida e ainda
            {
                int limitanteInferior = abs(fim.x - novoX) + abs(fim.y - novoY); // define limite inferior

                if (numeroDePassos + 1 + limitanteInferior < limitanteSuperior)
                {
                    visitado[novoX][novoY] = 1;
                    fila[tras++] = criarNo(novoX, novoY, numeroDePassos + 1, atual); // Marca a nova posição como visitada e adiciona o novo nó na fila
                }
            }
        }
    }
    // Libera a memória caso nenhum caminho seja encontrado
    for (int i = 0; i < tamanhoDoTabuleiro; i++)
    {
        free(visitado[i]);
    }
    free(visitado);
    free(fila);
    return (limitanteSuperior == INT_MAX) ? -1 : limitanteSuperior;
}

// Mostra o tabuleiro com os passos dados do cavalo
// Recebe uma matriz quadrada de tamanho tamanhoDoTabuleiro
void imprimirTabuleiro(int **tabuleiro, int tamanhoDoTabuleiro)
{
    printf("Tabuleiro:\n");
    for (int i = 0; i < tamanhoDoTabuleiro; i++)
    { // linhas do tabuleiro
        for (int j = 0; j < tamanhoDoTabuleiro; j++)
        { // colunas
            if (tabuleiro[i][j] == -1)
                printf(". ");
            else
                printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int lerDadosDoArquivo(const char *caminho, int *tamanhoDoTabuleiro, Posicao *inicio, Posicao *fim)
{
    FILE *dadosDoArquivo;

    // abrindo o arquivo no modo leitura
    dadosDoArquivo = fopen(caminho, "r");

    if (dadosDoArquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    // lê o valor de tamanhoDoTabuleiro
    if (fscanf(dadosDoArquivo, "%d\n", tamanhoDoTabuleiro) != 1)
    {
        printf("Erro ao ler tamanhoDoTabuleiro!\n");
        fclose(dadosDoArquivo);
        return 1;
    }

    // lê a posição inicial
    if (fscanf(dadosDoArquivo, "%d %d\n", &inicio->x, &inicio->y) != 2)
    {
        printf("Erro ao ler as coordenadas de início!\n");
        fclose(dadosDoArquivo);
        return 1;
    }

    // lê a posição final
    if (fscanf(dadosDoArquivo, "%d %d\n", &fim->x, &fim->y) != 2)
    {
        printf("Erro ao ler as coordenadas de fim!\n");
        fclose(dadosDoArquivo);
        return 1;
    }
    printf("Tamanho do tabuleiro: %d\n", *tamanhoDoTabuleiro);
    printf("Cordenada inicial: %d %d\n", inicio->x, inicio->y);
    printf("Coordenada final: %d %d\n", fim->x, fim->y);

    // Fechando o arquivo
    fclose(dadosDoArquivo);

    return 0;
}

void liberarTabuleiro(int **tabuleiro, int tamanhoDoTabuleiro)
{
    for (int i = 0; i < tamanhoDoTabuleiro; i++)
    { // percorre linha a linha, liberando espaço de memoria dos elementos da matriz
        free(tabuleiro[i]);
    }

    free(tabuleiro); // libera espaço de memoria do "tabuleiro"
}

void imprimirResposta(int resultado, int **tabuleiro, int tamanhoDoTabuleiro)
{
    if (resultado != -1)
    {
        printf("Caminho encontrado com %d passos:\n", resultado); // imprime o numero de passos que o cavalo deu para chegar ao ponto final, junto com a matriz embaixo
        imprimirTabuleiro(tabuleiro, tamanhoDoTabuleiro);         // mostrando qual foi o caminho que o cavalo percorreu
    }
    else
        printf("Nao foi possivel encontrar um caminho.\n"); // uma vez que todos os valores da matriz foram inicializados com o valor "-1", caso o valor encontrado para
                                                            //  "resultado" ainda seja "-1", nao foi encontrado um caminho, já que nao foi alterado o valor
}

int main()
{
    const char *caminhoArquivo = "../../data/tab2.txt";

    int tamanhoDoTabuleiro;
    Posicao inicio, fim;

    // Ler os dados do arquivo
    if (lerDadosDoArquivo(caminhoArquivo, &tamanhoDoTabuleiro, &inicio, &fim) != 0)
    {
        // Tratar erro de leitura do arquivo
        fprintf(stderr, "Erro ao ler o arquivo: %s\n", caminhoArquivo);
        return 1;
    }

    int **tabuleiro = NULL;
    tabuleiro = criarTabuleiro(tabuleiro, tamanhoDoTabuleiro);

    int resultado = menorCaminho(inicio, fim, tabuleiro, tamanhoDoTabuleiro);

    imprimirResposta(resultado, tabuleiro, tamanhoDoTabuleiro);

    // Liberar memória alocada para o tabuleiro, se necessário
    for (int i = 0; i < tamanhoDoTabuleiro; i++)
    {
        free(tabuleiro[i]);
    }
    free(tabuleiro);

    return 0;
}
