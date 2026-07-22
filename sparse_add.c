#include <stdio.h>

void addSparse(int a[20][3], int b[20][3], int c[40][3])
{
    int i = 1, j = 1, k = 1;

    // Check dimensions
    if (a[0][0] != b[0][0] || a[0][1] != b[0][1])
    {
        printf("Addition not possible!\n");
        return;
    }

    // Store header information
    c[0][0] = a[0][0];
    c[0][1] = a[0][1];

    while (i <= a[0][2] && j <= b[0][2])
    {
        // Same position
        if (a[i][0] == b[j][0] && a[i][1] == b[j][1])
        {
            c[k][0] = a[i][0];
            c[k][1] = a[i][1];
            c[k][2] = a[i][2] + b[j][2];

            i++;
            j++;
            k++;
        }

        // A comes first
        else if (a[i][0] < b[j][0] ||
                 (a[i][0] == b[j][0] && a[i][1] < b[j][1]))
        {
            c[k][0] = a[i][0];
            c[k][1] = a[i][1];
            c[k][2] = a[i][2];

            i++;
            k++;
        }

        // B comes first
        else
        {
            c[k][0] = b[j][0];
            c[k][1] = b[j][1];
            c[k][2] = b[j][2];

            j++;
            k++;
        }
    }

    // Copy remaining elements of A
    while (i <= a[0][2])
    {
        c[k][0] = a[i][0];
        c[k][1] = a[i][1];
        c[k][2] = a[i][2];

        i++;
        k++;
    }

    // Copy remaining elements of B
    while (j <= b[0][2])
    {
        c[k][0] = b[j][0];
        c[k][1] = b[j][1];
        c[k][2] = b[j][2];

        j++;
        k++;
    }

    c[0][2] = k - 1;
}

void display(int a[20][3])
{
    int i;

    printf("\nRow\tCol\tValue\n");

    for (i = 0; i <= a[0][2]; i++)
    {
        printf("%d\t%d\t%d\n", a[i][0], a[i][1], a[i][2]);
    }
}

int main()
{
    int a[20][3], b[20][3], c[40][3];
    int i;

    printf("Enter rows, columns and non-zero elements of Matrix A: ");
    scanf("%d%d%d", &a[0][0], &a[0][1], &a[0][2]);

    printf("Enter triplets of Matrix A:\n");
    for (i = 1; i <= a[0][2]; i++)
    {
        scanf("%d%d%d", &a[i][0], &a[i][1], &a[i][2]);
    }

    printf("Enter rows, columns and non-zero elements of Matrix B: ");
    scanf("%d%d%d", &b[0][0], &b[0][1], &b[0][2]);

    printf("Enter triplets of Matrix B:\n");
    for (i = 1; i <= b[0][2]; i++)
    {
        scanf("%d%d%d", &b[i][0], &b[i][1], &b[i][2]);
    }

    addSparse(a, b, c);

    printf("\nResultant Sparse Matrix:\n");
    display(c);

    return 0;
}