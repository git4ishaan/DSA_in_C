#include <stdio.h>

void accept(int a[10][10], int m, int n)
{
    int i, j;

    printf("Enter Matrix Elements:\n");

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("Enter element[%d][%d]: ", i, j);
            scanf("%d", &a[i][j]);
        }
    }
}

void display(int a[10][10], int m, int n)
{
    int i, j;

    printf("\nMatrix:\n");

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void sparse(int a[10][10], int b[20][3], int m, int n)
{
    int i, j;
    int k = 1;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (a[i][j] != 0)
            {
                b[k][0] = i;
                b[k][1] = j;
                b[k][2] = a[i][j];
                k++;
            }
        }
    }

    b[0][0] = m;
    b[0][1] = n;
    b[0][2] = k - 1;

    printf("\nCompact (Triplet) Matrix:\n");

    for (i = 0; i < k; i++)
    {
        printf("%d\t%d\t%d\n", b[i][0], b[i][1], b[i][2]);
    }
}

int main()
{
    int a[10][10];
    int b[20][3];
    int m, n;

    printf("Enter number of rows: ");
    scanf("%d", &m);

    printf("Enter number of columns: ");
    scanf("%d", &n);

    accept(a, m, n);

    display(a, m, n);

    sparse(a, b, m, n);

    return 0;
}