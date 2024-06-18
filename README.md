# Deslocamento do Cavalo no Xadrez

Este é um projeto desenvolvido como parte da disciplina de Algoritmos e Estrutura de Dados 2. 

Objetivo:

Resolver o problema do deslocamento do cavalo em um tabuleiro de xadrez NxN.

Descrição do Problema:

Dado um tabuleiro de xadrez de tamanho NxN, uma posição inicial (x0, y0) e uma posição final (xf, yf), o objetivo é encontrar um passeio mínimo de cavalo que leve da posição inicial à posição final, seguindo as regras de movimento do cavalo no xadrez.

Funcionalidades:

Encontrar o caminho mínimo de passos para o deslocamento do cavalo.

Modo de uso:
Selecionar um dos arquivos txt, sendo eles tab1, tab2 ou tab3, mudando no código como nos exemplos abaixo (de acordo com o seu diretório):
tab1:
dadosDoArquivo = fopen("data/tab1.txt", "r");

tab2:
dadosDoArquivo = fopen("data/tab2.txt", "r");

tab3:
dadosDoArquivo = fopen("data/tab3.txt", "r");

editar o .txt da seguinte forma:
10    //onde a primeira linha representara o tamanho do tabuleiro, nesse caso N = 10, onde o tamanho do tabuleiro é definido por NxN
1 1   //Define x0 e y0, ou seja, a posição inicial do cavalo (colocar um espaço entre o valor x0 e o valor y0)
7 9   //Define xf e yf, ou seja, a posição final que o cavalo deve chegar (colocar um espaço entre o valor xf e o valor yf)






