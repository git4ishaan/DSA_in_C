#include <stdio.h>
#include <string.h>

#define MAX 100

struct Student
{
    int roll;
    char name[50];
    float marks;
};

/* Display students */
void display(struct Student s[], int n)
{
    printf("\n%-10s %-20s %-10s\n", "Roll No", "Name", "Marks");
    printf("---------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("%-10d %-20s %-10.2f\n",
               s[i].roll, s[i].name, s[i].marks);
    }
}

/* Linear Search */
int linearSearch(struct Student s[], int n, int key)
{
    for (int i = 0; i < n; i++)
    {
        if (s[i].roll == key)
            return i;
    }
    return -1;
}

/* Binary Search */
int binarySearch(struct Student s[], int n, int key)
{
    int low = 0, high = n - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (s[mid].roll == key)
            return mid;
        else if (s[mid].roll < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

/* Insertion Sort */
void insertionSort(struct Student s[], int n)
{
    for (int i = 1; i < n; i++)
    {
        struct Student temp = s[i];
        int j = i - 1;

        while (j >= 0 && s[j].roll > temp.roll)
        {
            s[j + 1] = s[j];
            j--;
        }

        s[j + 1] = temp;
    }
}

/* Selection Sort */
void selectionSort(struct Student s[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;

        for (int j = i + 1; j < n; j++)
        {
            if (s[j].roll < s[min].roll)
                min = j;
        }

        if (min != i)
        {
            struct Student temp = s[i];
            s[i] = s[min];
            s[min] = temp;
        }
    }
}

/* Shell Sort */
void shellSort(struct Student s[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {

        for (int i = gap; i < n; i++)
        {
            struct Student temp = s[i];
            int j = i;

            while (j >= gap &&
                   s[j - gap].roll > temp.roll)
            {
                s[j] = s[j - gap];
                j -= gap;
            }

            s[j] = temp;
        }
    }
}

int main()
{
    struct Student s[MAX];
    int n, choice, key, pos;

    printf("Enter number of students: ");
    scanf("%d", &n);

    printf("\nEnter student details:\n");

    for (int i = 0; i < n; i++)
    {
        printf("\nStudent %d\n", i + 1);

        printf("Roll No: ");
        scanf("%d", &s[i].roll);

        printf("Name: ");
        scanf("%s", s[i].name);

        printf("Marks: ");
        scanf("%f", &s[i].marks);
    }

    do
    {
        printf("\n===== MENU =====\n");
        printf("1. Display Records\n");
        printf("2. Linear Search\n");
        printf("3. Insertion Sort\n");
        printf("4. Selection Sort\n");
        printf("5. Shell Sort\n");
        printf("6. Binary Search\n");
        printf("7. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:
            display(s, n);
            break;

        case 2:
            printf("Enter roll number to search: ");
            scanf("%d", &key);

            pos = linearSearch(s, n, key);

            if (pos != -1)
                printf("Student found at position %d.\n", pos + 1);
            else
                printf("Student not found.\n");

            break;

        case 3:
            insertionSort(s, n);
            printf("\nRecords sorted using Insertion Sort:\n");
            display(s, n);
            break;

        case 4:
            selectionSort(s, n);
            printf("\nRecords sorted using Selection Sort:\n");
            display(s, n);
            break;

        case 5:
            shellSort(s, n);
            printf("\nRecords sorted using Shell Sort:\n");
            display(s, n);
            break;

        case 6:
            printf("Enter roll number to search: ");
            scanf("%d", &key);

            pos = binarySearch(s, n, key);

            if (pos != -1)
                printf("Student found at position %d.\n", pos + 1);
            else
                printf("Student not found.\n");

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