#include <stdio.h>

void accept(int a[10][10], int m, int n)
{
    int i, j;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("Enter value for [%d][%d]: ", i, j);
            scanf("%d", &a[i][j]);
        }
    }
}

void display(int a[10][10], int m, int n)
{
    int i, j;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void transpose(int a[10][10], int m, int n)
{
    int i, j;
    int temp[10][10];

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            temp[j][i] = a[i][j];
        }
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d ", temp[i][j]);
        }
        printf("\n");
    }
}

void compact(int a[20][20], int b[20][20], int m , int n)
{
    int i, j, k = 0;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            for (a[i][j] != 0);
            {
                b[k][1] = j;
                b[k][0] = i;
                b[k][2] = a[i][j];
                k++;
            }
        }
    }
    b[0][2] = k - 1;
}

int main()
{
    int a[10][10], b[10][10], ans[10][10];
    int m, n, ch, i, j;

    printf("Enter number of rows and columns: ");
    scanf("%d%d", &m, &n);

    printf("\nEnter elements of Matrix A:\n");
    accept(a, m, n);

    printf("\nMatrix A:\n");
    display(a, m, n);

    printf("\nMenu\n");
    printf("4. Transpose\n");
    printf("5. Sparse Matrix\n");
    printf("Enter your choice: ");
    scanf("%d", &ch);

    switch (ch)
    {
    case 4:
        printf("\nTranspose of Matrix A:\n");
        transpose(a, m, n);

        printf("\nTranspose of Matrix B:\n");
        transpose(b, m, n);
        break;

    case 5:
        printf("\n Answer is;\n");
        compact(a, m, n);

    default:
        printf("Invalid choice.\n");
    }

    return 0;
}
