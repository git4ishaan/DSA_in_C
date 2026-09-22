#include <stdio.h>
#include <stdlib.h>

void accept(int a[10][10], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("Enter element[%d][%d]: ", i, j);
            scanf("%d", &a[i][j]);
        }
    }
}

void display(int a[10][10], int m, int n)
{
    printf("\nMatrix:\n");

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void add(int a[10][10], int b[10][10], int c[10][10], int m, int n)
{
    printf("\nEnter elements of Second Matrix:\n");
    accept(b, m, n);

    printf("\nAddition of Matrices:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = a[i][j] + b[i][j];
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
}

void subtract(int a[10][10], int b[10][10], int c[10][10], int m, int n)
{
    printf("\nEnter elements of Second Matrix:\n");
    accept(b, m, n);

    printf("\nSubtraction of Matrices:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = a[i][j] - b[i][j];
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
}

void mul(int a[10][10], int b[10][10], int c[10][10], int m, int n)
{
    printf("\nEnter elements of Second Matrix:\n");
    accept(b, m, n);

    printf("\nElement-wise Multiplication:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = a[i][j] * b[i][j];
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
}

void trans(int a[10][10], int m, int n)
{
    int temp[10][10];

    printf("\nTranspose of Matrix:\n");

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp[j][i] = a[i][j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", temp[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int a[10][10], b[10][10], c[10][10];
    int m = 3, n = 3;
    int choice;

    printf("Enter elements of First Matrix:\n");
    accept(a, m, n);

    display(a, m, n);

    printf("\nChoose Function to Perform:\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Transpose\n");
    printf("5. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        add(a, b, c, m, n);
        break;

    case 2:
        subtract(a, b, c, m, n);
        break;

    case 3:
        mul(a, b, c, m, n);
        break;

    case 4:
        trans(a, m, n);
        break;

    case 5:
        exit(0);

    default:
        printf("Invalid Choice!");
    }

    return 0;
}