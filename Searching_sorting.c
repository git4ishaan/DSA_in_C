#include <stdio.h>
#define MAX 100

struct Student
{
    int roll;
    char name[50];
    float marks;
};

void display(struct Student s[], int n)
{
    int i;

    printf("\nRoll\tName\tMarks\n");

    for (i = 0; i < n; i++)
        printf("%d\t%s\t%.2f\n", s[i].roll, s[i].name, s[i].marks);
}

int linearSearch(struct Student s[], int n, int key)
{
    int i;

    for (i = 0; i < n; i++)
        if (s[i].roll == key)
            return i;

    return -1;
}

int binarySearch(struct Student s[], int n, int key)
{
    int low = 0, high = n - 1, mid;

    while (low <= high)
    {
        mid = (low + high) / 2;

        if (s[mid].roll == key)
            return mid;
        else if (s[mid].roll < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

void insertionSort(struct Student s[], int n)
{
    int i, j;
    struct Student temp;

    for (i = 1; i < n; i++)
    {
        temp = s[i];
        j = i - 1;

        while (j >= 0 && s[j].roll > temp.roll)
        {
            s[j + 1] = s[j];
            j--;
        }

        s[j + 1] = temp;
    }
}

void selectionSort(struct Student s[], int n)
{
    int i, j, min;
    struct Student temp;

    for (i = 0; i < n - 1; i++)
    {
        min = i;

        for (j = i + 1; j < n; j++)
            if (s[j].roll < s[min].roll)
                min = j;

        temp = s[i];
        s[i] = s[min];
        s[min] = temp;
    }
}

void shellSort(struct Student s[], int n)
{
    int gap, i, j;
    struct Student temp;

    for (gap = n / 2; gap > 0; gap = gap / 2)
    {
        for (i = gap; i < n; i++)
        {
            temp = s[i];
            j = i;

            while (j >= gap && s[j - gap].roll > temp.roll)
            {
                s[j] = s[j - gap];
                j = j - gap;
            }

            s[j] = temp;
        }
    }
}

int main()
{
    struct Student s[MAX];
    int n, i, choice, key, pos;

    printf("Enter number of students: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX)
    {
        printf("Invalid number of students.\n");
        return 0;
    }

    for (i = 0; i < n; i++)
    {
        printf("\nEnter roll number, name and marks:\n");
        scanf("%d %49s %f", &s[i].roll, s[i].name, &s[i].marks);
    }

    do
    {
        printf("\n1. Display");
        printf("\n2. Linear Search");
        printf("\n3. Insertion Sort");
        printf("\n4. Selection Sort");
        printf("\n5. Shell Sort");
        printf("\n6. Binary Search");
        printf("\n7. Exit");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                display(s, n);
                break;

            case 2:
                printf("Enter roll number: ");
                scanf("%d", &key);

                pos = linearSearch(s, n, key);

                if (pos == -1)
                    printf("Student not found.\n");
                else
                    printf("Student found at position %d.\n", pos + 1);
                break;

            case 3:
                insertionSort(s, n);
                display(s, n);
                break;

            case 4:
                selectionSort(s, n);
                display(s, n);
                break;

            case 5:
                shellSort(s, n);
                display(s, n);
                break;

            case 6:
                insertionSort(s, n);
                printf("Enter roll number: ");
                scanf("%d", &key);

                pos = binarySearch(s, n, key);

                if (pos == -1)
                    printf("Student not found.\n");
                else
                    printf("Student found at position %d.\n", pos + 1);
                break;

            case 7:
                printf("Program terminated.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 7);

    return 0;
}