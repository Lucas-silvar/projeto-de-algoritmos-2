#include <stdio.h>
#include <stdlib.h>

// Definição da struct Posicao para armazenar os valores iniciais e finais do cavalo
typedef struct{
    int x, y;
} Posicao;

typedef struct Node{
    Posicao pos;
    int custo;
    struct Node* parent;
} Node;

// Verifica se uma posição é válida dentro do tabuleiro N x N
int ehValida(int x, int y, int N) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Movimentos possíveis do cavalo em relação à sua posição atual [x, y]
int movimentos[8][2] = {
    {2, 1},  //2 em x + 1 em y = nova posição
    {2, -1}, 
    {-2, 1}, 
    {-2, -1},
    {1, 2}, 
    {1, -2}, 
    {-1, 2}, 
    {-1, -2}
};

// Cria um novo nó
// Recebe como parêmetros a coordenada do cavalo no tabuleiro, o custo para
// realizar o próximo passo e o que será um nó pai
Node* criarNo(int x, int y, int custo, Node* parent) {
    Node* tree = (Node*)malloc(sizeof(Node));
    tree->pos.x = x;
    tree->pos.y = y;
    tree->custo = custo;
    tree->parent = parent;
    return tree;
}

// Função recursiva para mostrar o caminho percorrido pelo cavalo no tabuleiro
// como sendo passo 0, 1, 2, 3, ..., N
// Recebe como parâmetro uma árvore e uma matriz quadrada N
void imprimirCaminho(Node* node, int** tabuleiro) {
    if (node == NULL) // critério de parada
        return;

    imprimirCaminho(node->parent, tabuleiro); // percorre a árvore inteira

    if (tabuleiro[node->pos.x][node->pos.y] == -1) {
        static int passo = 0; // os valores da variável passo serão mantidos independentes das funções chamadas
                              // para marcar o trajeto do cavalo
        tabuleiro[node->pos.x][node->pos.y] = passo++; // posição atual agora é o próximo passo, então incrementa passo
    }
}

// Mostra o tabuleiro com os passos dados do cavalo
// Recebe uma matriz quadrada de tamanho N
void imprimirTabuleiro(int** tabuleiro, int N) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < N; i++){ //linhas do tabuleiro
        for (int j = 0; j < N; j++) { //colunas
            if (tabuleiro[i][j] == -1)
                printf(". ");
            else
                printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Encontra o menor caminho do cavalo saindo de uma posição incial [x0, y0] até uma posição final [x, y]
// Parâmetros de posição de início [x, y], fim [x, y] e uma matriz quadrada de tamanho N
int menorCaminho(Posicao inicio, Posicao fim, int** tabuleiro, int N) {
    if (!ehValida(inicio.x, inicio.y, N) || !ehValida(fim.x, fim.y, N)) {
        return -1;
    }

    // Inicializa a variável "visitado", que guarda as casas que o cavalo já percorreu
    int** visitado = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        visitado[i] = (int*)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++)
            visitado[i][j] = 0; //inicializa todas as posições como não visitada
    }
    // Criação do nó raiz representando a posição inicial do cavalo
    Node* raiz = criarNo(inicio.x, inicio.y, 0, 0);
    
    // Fila para armazenar os nós a serem explorados ( fila prioritária )
    Node** fila = (Node**)malloc(N * N * sizeof(Node*));
    int frente = 0, tras = 0;
    
    // Adiciona a raiz na fila e marca a posição inicial do cavalo
    fila[tras++] = raiz;
    visitado[inicio.x][inicio.y] = 1;
    
    // Loop que explora os nós da fila 
    while (frente < tras) {
        Node* atual = fila[frente++];
        int x = atual->pos.x;
        int y = atual->pos.y;
        int custo = atual->custo;
    // Verifica se a posição atual é a posição desejada(posição final)
        if (x == fim.x && y == fim.y) {
            imprimirCaminho(atual, tabuleiro); // Se sim, imprime o caminho percorrido
            for (int i = 0; i < N; i++) {
                free(visitado[i]);
            }
            free(visitado);
            free(fila);
            return custo;
        }
        // Explora todos os movimentos possíveis do cavalo a partir da posição atual 
        for (int i = 0; i < 8; i++) {
            int novoX = x + movimentos[i][0];
            int novoY = y + movimentos[i][1];

            if (ehValida(novoX, novoY, N) && !visitado[novoX][novoY]) { // Verifica se a nova posição é válida e ainda
                visitado[novoX][novoY] = 1;                             // não foi visitada
        // Marca a nova posição como visitada e adiciona o novo nó na fila       
                fila[tras++] = criarNo(novoX, novoY, custo + 1, atual);
            }
        }
    }
    // Libera a memória caso nenhum caminho seja encontrado 
    for (int i = 0; i < N; i++) {
        free(visitado[i]);
    }
    free(visitado);
    free(fila);
    return -1;
}

int main() {

    int N;

    Posicao inicio, fim;

    FILE *pont_arq;

    //abrindo o arquivo no modo leitura
    pont_arq = fopen("data/tab3.txt", "r");

    //verifica se foi aberto com sucesso 
    if (pont_arq == NULL) {
        printf("Erro ao abrir o arquivo!");
        return 1;
    }

    //le o valor de N
    if (fscanf(pont_arq, "%d\n", &N) != 1) {
        printf("Erro ao ler N!\n");
        fclose(pont_arq);
        return 1;
    }

    //le a pos inicial
    if (fscanf(pont_arq, "%d %d\n", &inicio.x, &inicio.y) != 2) {
        printf("Erro ao ler as coordenadas de inicio!\n");
        fclose(pont_arq);
        return 1;
    }

    //le a pos final
    if (fscanf(pont_arq, "%d %d\n", &fim.x, &fim.y) != 2) {
        printf("Erro ao ler as coordenadas de fim!\n");
        fclose(pont_arq);
        return 1;
    }

    // Fechando o arquivo
    fclose(pont_arq);


    int** tabuleiro = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        tabuleiro[i] = (int*)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            tabuleiro[i][j] = -1;
        }
    }

    int resultado = menorCaminho(inicio, fim, tabuleiro, N);
    if (resultado != -1) {
        printf("caminho encontrado com %d passos:\n", resultado);
        imprimirTabuleiro(tabuleiro, N);
    } else
        printf("Nao foi possivel encontrar um caminho.\n");

    for (int i = 0; i < N; i++)
        free(tabuleiro[i]);

    free(tabuleiro);

    return 0;
}