#include <stdio.h>
#include <stdlib.h>

int **create_matrix(int l, int c)
{

    int **mat = (int **)malloc(sizeof(int *) * l);
    if (mat != NULL)
    {
        int i, j;
        for (i = 0; i < l; i++)
        {
            mat[i] = (int *)malloc(sizeof(int) * c);
        }

        for (i = 0; i < l; i++)
            for (j = 0; j < c; j++)
                mat[i][j] = -1;
    }

    return mat;
}
void print_matrix(int **mat, int l, int c)
{
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (mat[i][j] == -1)
                printf(". ");
            else
            {
                printf("%d ", mat[i][j]);
            }
        }

        printf("\n");
    }
}

void free_matrix(int **mat, int l, int c)
{
    if (mat != NULL)
    {
        int i, j;

        for (i = 0; i < l; i++)
            for (j = 0; j < c; j++)
                free(mat[i][j]);
    }
}
int knight_move(int **mat, int x, int y, int *count)
{

    mat[x][y] = *count;
    (*count)++;

    return *count;
}

int main()
{
    int n = 8;
    int *count = 0;
    int **mat = create_matrix(n, n);
    print_matrix(mat, n, n);

    printf("\n");
    knight_move(mat, 0, 0, &count);
    knight_move(mat, 0, 1, &count);
    knight_move(mat, 0, 2, &count);

    print_matrix(mat, n, n);

    free_matrix(mat, n, n);

    return 0;
}