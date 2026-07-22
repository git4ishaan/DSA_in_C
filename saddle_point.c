#include <stdio.h>

int main()
{
    int mat[10][10];
    int m, n;
    int found = 0;

    printf("Enter number of rows: ");
    scanf("%d", &m);

    printf("Enter number of columns: ");
    scanf("%d", &n);

    printf("\nEnter Matrix Elements:\n");

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("Enter element[%d][%d]: ", i, j);
            scanf("%d", &mat[i][j]);
        }
    }

    printf("\nMatrix:\n");

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < m; i++)
    {
        int min = mat[i][0];
        int col = 0;

        for (int j = 1; j < n; j++)
        {
            if (mat[i][j] < min)
            {
                min = mat[i][j];
                col = j;
            }
        }

        int k;
        for (k = 0; k < m; k++)
        {
            if (mat[k][col] > min)
            {
                break;
            }
        }

        if (k == m)
        {
            printf("\nSaddle Point = %d", min);
            printf("\nPosition = (%d,%d)", i, col);
            found = 1;
        }
    }

    if (found == 0)
    {
        printf("\nNo Saddle Point Found.");
    }

    return 0;
}