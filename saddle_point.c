#include <stdio.h>
#include <stdlib.h>

int main()
{

    int mat[10][10];
    int m, n;

    printf("Enter The elements of The Matrix:\n");

    for (int i = 0; i < n; i++){

        for (int j = 0; j < m; j++){

            printf("Enter element[%d][%d]: ", i, j);
            scanf("%d", &mat[i][j]);
        }
    }

        

        return 0;
}