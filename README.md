# Deslocamento do Cavalo no Xadrez

*Este é um projeto desenvolvido como parte da disciplina de Algoritmos e Estrutura de Dados 2 do curso de Engenharia de Computação, pelos alunos: .*
  - Allef Fernandes Santos;
  - Lucas Arruda Silva;
  - Lucas Tarcisio Morais Pies;
  - Guilherme Macedo Baggio;
  - Yuri Gabriel dos Reis Souza.

## Objetivo:
  - Resolver o problema do deslocamento do cavalo em um tabuleiro de xadrez NxN.

## Descrição do Problema:
 - Dado um tabuleiro de xadrez de tamanho NxN, uma posição inicial (x0, y0) e uma posição final (xf, yf), o algoritmo deve encontrar um percurso mínimo que leve a peça da posição inicial à posição final, seguindo as regras de movimento do cavalo no xadrez.

## Funcionalidades:
 - Encontrar o caminho mínimo de passos para o deslocamento do cavalo;
 - Deve ser destacado que o a posição linha 1, coluna 1, é representado por (0,0), ou seja o valor local na matriz pode ser determinado por (x-1, y-1);
 - O ponto (0,0) está no canto superior esquerdo.

## Modo de uso:
 - Selecionar um dos arquivos txt, sendo eles tab1, tab2 ou tab3, mudando no código como nos exemplos abaixo (de acordo com o seu diretório):

  1. **tab1:** dadosDoArquivo = fopen("data/tab1.txt", "r");
  2. **tab2:** dadosDoArquivo = fopen("data/tab2.txt", "r");
  3. **tab3:** dadosDoArquivo = fopen("data/tab3.txt", "r");

 - Algo que deve ser levado em consideração, é que o "data/tab1.txt", obtido para "tab1", foi copiado o diretório onde estava o arquivo. 

***Vale lembrar que no windows é utilizado "\" para separar entre os diretorios, já no linux é utilizado o "/".***

  ### Editar o .txt da seguinte forma:
10    // A primeira linha representa o tamanho do tabuleiro, neste caso N = 10, onde o tamanho do tabuleiro é definido por NxN;
1 1   // Define x0 e y0, ou seja, a posição inicial do cavalo (colocar um espaço entre o valor x0 e o valor y0);
7 9   // Define xf e yf, ou seja, a posição final que o cavalo deve chegar (colocar um espaço entre o valor xf e o valor yf);

