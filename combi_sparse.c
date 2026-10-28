#include <stdio.h>
void accept(int a[10][10], int rows, int coln);
void declare(int a[10][10], int rows, int coln);
void compact(int a[10][10], int rows, int coln, int s[20][3]);
void simpletranspose(int nz, int s[20][3]);
void fasttranspose(int nz, int s[20][3]);

void accept(int a[10][10], int rows, int coln)
{
    int i, j;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < coln; j++)
        {
            printf("Enter a no:");
            scanf("%d", &a[i][j]);
        }
    }
}
void declare(int a[10][10], int rows, int coln)
{
    int i, j;
    printf("The matrix is:\n");
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < coln; j++)
        {
            printf("\t%d", a[i][j]);
        }
        printf("\n");
    }
}
void compact(int a[10][10], int rows, int coln, int s[20][3])
{
    int i, j, z = 0, nz = 0;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < coln; j++)
        {
            if (a[i][j] == 0)
                z++;
            else
                nz++;
        }
    }
    if (nz > z)
    {
        printf("It is not a sparse matrix\n");
    }
    else
    {
        s[0][0] = rows;
        s[0][1] = coln;
        s[0][2] = nz;
        int k = 1;
        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < coln; j++)
            {
                if (a[i][j] != 0)
                {
                    s[k][0] = i;
                    s[k][1] = j;
                    s[k][2] = a[i][j];
                    k++;
                }
            }
        }
        printf("\nThe sparse matrix is:\n");
        printf("row\tcol\tvalue\n");
        for (i = 0; i < nz + 1; i++)
        {
            for (j = 0; j < 3; j++)
            {
                printf("%d\t", s[i][j]);
            }
            printf("\n");
        }
    }
}
void simpletranspose(int nz, int s[20][3])
{
    int t[20][3];
    int i, j, k = 1;
    t[0][0] = s[0][1];
    t[0][1] = s[0][0];
    t[0][2] = s[0][2];

    for (i = 0; i < s[0][1]; i++)
    {
        for (j = 1; j <= nz; j++)
        {
            if (s[j][1] == i)
            {
                t[k][0] = s[j][1];
                t[k][1] = s[j][0];
                t[k][2] = s[j][2];
                k++;
            }
        }
    }
    printf("\nThe Simple transpose is :\n");
    printf("row\tcol\tvalue\n");
    for (i = 0; i < nz + 1; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%d\t", t[i][j]);
        }
        printf("\n");
    }
}
void fasttranspose(int nz, int s[20][3])
{
    int t[20][3];
    int S[20] = {0}, T[20] = {0};
    int i, j;
    t[0][0] = s[0][1];
    t[0][1] = s[0][0];
    t[0][2] = s[0][2];
    if (nz == 0)
    {
        printf("\nFast transpose is:\n");
        printf("%d\t%d\t%d\n", t[0][0], t[0][1], t[0][2]);
        return;
    }
    for (i = 0; i < s[0][1]; i++)
        S[i] = 0;
    for (i = 1; i <= nz; i++)
        S[s[i][1]]++;
    T[0] = 1;
    for (i = 1; i < s[0][1]; i++)
        T[i] = T[i - 1] + S[i - 1];
    for (i = 1; i <= nz; i++)
    {
        j = T[s[i][1]];
        t[j][0] = s[i][1];
        t[j][1] = s[i][0];
        t[j][2] = s[i][2];
        T[s[i][1]]++;
    }
    printf("\nThe Fast Transpose is:\n");
    printf("Row\tCol\tValue\n");

    for (i = 0; i <= nz; i++)
    {
        printf("%d\t%d\t%d\n", t[i][0], t[i][1], t[i][2]);
    }
}
int main()
{
    int a[10][10], rows, coln, i, j;
    int s[20][3];
    int nz;
    printf("Enter no of rows and columns:");
    scanf("%d%d", &rows, &coln);
    accept(a, rows, coln);
    declare(a, rows, coln);
    compact(a, rows, coln, s);
    nz = s[0][2];
    simpletranspose(nz, s);
    fasttranspose(nz, s);
    return 0;
}