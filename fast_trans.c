#include <stdio.h>

void fastTranspose(int a[20][3], int b[20][3])
{
    int rowTerms[20], startPos[20];
    int i, j;

    // Copy header information
    b[0][0] = a[0][1];
    b[0][1] = a[0][0];
    b[0][2] = a[0][2];

    // Initialize rowTerms
    for(i = 0; i < a[0][1]; i++)
        rowTerms[i] = 0;

    // Count the number of elements in each column
    for(i = 1; i <= a[0][2]; i++)
        rowTerms[a[i][1]]++;

    // Calculate starting position of each row
    startPos[0] = 1;

    for(i = 1; i < a[0][1]; i++)
        startPos[i] = startPos[i - 1] + rowTerms[i - 1];

    // Perform fast transpose
    for(i = 1; i <= a[0][2]; i++)
    {
        j = startPos[a[i][1]];

        b[j][0] = a[i][1];
        b[j][1] = a[i][0];
        b[j][2] = a[i][2];

        startPos[a[i][1]]++;
    }
}

void display(int a[20][3])
{
    int i;

    printf("\nRow\tCol\tValue\n");

    for(i = 0; i <= a[0][2]; i++)
    {
        printf("%d\t%d\t%d\n", a[i][0], a[i][1], a[i][2]);
    }
}

int main()
{
    int a[20][3], b[20][3];
    int i;

    printf("Enter number of rows, columns and non-zero elements: ");
    scanf("%d%d%d", &a[0][0], &a[0][1], &a[0][2]);

    printf("\nEnter Row Column Value:\n");

    for(i = 1; i <= a[0][2]; i++)
    {
        scanf("%d%d%d", &a[i][0], &a[i][1], &a[i][2]);
    }

    printf("\nOriginal Sparse Matrix:\n");
    display(a);

    fastTranspose(a, b);

    printf("\nFast Transpose:\n");
    display(b);

    return 0;
}