#include <stdio.h>

void accept(int a[10][10], int m, int n);
void displayMatrix(int a[10][10], int m, int n);
void sparse(int a[10][10], int b[20][3], int m, int n);
void displayTriplet(int b[20][3]);
void simpleTranspose(int a[20][3], int b[20][3]);
void fastTranspose(int a[20][3], int b[20][3]);

int main()
{
    int matrix[10][10];
    int sparseMatrix[20][3];
    int simple[20][3];
    int fast[20][3];
    int rows, cols;

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter number of columns: ");
    scanf("%d", &cols);

    accept(matrix, rows, cols);

    printf("\nOriginal Matrix:\n");
    displayMatrix(matrix, rows, cols);

    sparse(matrix, sparseMatrix, rows, cols);

    printf("\nSparse (Triplet) Matrix:\n");
    displayTriplet(sparseMatrix);

    simpleTranspose(sparseMatrix, simple);

    printf("\nSimple Transpose:\n");
    displayTriplet(simple);

    fastTranspose(sparseMatrix, fast);

    printf("\nFast Transpose:\n");
    displayTriplet(fast);

    return 0;
}

// Accept Matrix
void accept(int a[10][10], int m, int n)
{
    int i, j;

    printf("\nEnter Matrix Elements:\n");

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("Element[%d][%d]: ", i, j);
            scanf("%d", &a[i][j]);
        }
    }
}

// Display Original Matrix
void displayMatrix(int a[10][10], int m, int n)
{
    int i, j;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d\t", a[i][j]);
        }
        printf("\n");
    }
}

// Convert Matrix to Sparse Triplet
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
}

// Display Triplet Matrix
void displayTriplet(int b[20][3])
{
    int i;

    printf("Row\tCol\tValue\n");

    for (i = 0; i <= b[0][2]; i++)
    {
        printf("%d\t%d\t%d\n", b[i][0], b[i][1], b[i][2]);
    }
}

// Simple Transpose
void simpleTranspose(int a[20][3], int b[20][3])
{
    int i, j, k = 1;

    b[0][0] = a[0][1];
    b[0][1] = a[0][0];
    b[0][2] = a[0][2];

    for (i = 0; i < a[0][1]; i++)
    {
        for (j = 1; j <= a[0][2]; j++)
        {
            if (a[j][1] == i)
            {
                b[k][0] = a[j][1];
                b[k][1] = a[j][0];
                b[k][2] = a[j][2];
                k++;
            }
        }
    }
}

// Fast Transpose
void fastTranspose(int a[20][3], int b[20][3])
{
    int rowTerms[20], startPos[20];
    int i, j;

    b[0][0] = a[0][1];
    b[0][1] = a[0][0];
    b[0][2] = a[0][2];

    for (i = 0; i < a[0][1]; i++)
        rowTerms[i] = 0;

    for (i = 1; i <= a[0][2]; i++)
        rowTerms[a[i][1]]++;

    startPos[0] = 1;

    for (i = 1; i < a[0][1]; i++)
        startPos[i] = startPos[i - 1] + rowTerms[i - 1];

    for (i = 1; i <= a[0][2]; i++)
    {
        j = startPos[a[i][1]];

        b[j][0] = a[i][1];
        b[j][1] = a[i][0];
        b[j][2] = a[i][2];

        startPos[a[i][1]]++;
    }
}