#include <stdio.h>
#include <ctype.h>

#define MAX 100

int stack[MAX];
int top = -1;

/* Push */
void push(int value)
{
    if (top == MAX - 1)
        printf("Stack Overflow\n");
    else
        stack[++top] = value;
}

/* Pop */
int pop()
{
    if (top == -1)
    {
        printf("Stack Underflow\n");
        return -1;
    }

    return stack[top--];
}

/* Evaluate Postfix Expression */
int evaluatePostfix(char expression[])
{
    int i;
    int operand1, operand2, result;

    for (i = 0; expression[i] != '\0'; i++)
    {
        /* Ignore spaces */
        if (expression[i] == ' ')
            continue;

        /* If operand, push it */
        if (isdigit(expression[i]))
        {
            push(expression[i] - '0');
        }

        /* If operator */
        else
        {
            operand2 = pop();
            operand1 = pop();

            switch (expression[i])
            {
            case '+':
                result = operand1 + operand2;
                break;

            case '-':
                result = operand1 - operand2;
                break;

            case '*':
                result = operand1 * operand2;
                break;

            case '/':
                result = operand1 / operand2;
                break;

            default:
                printf("Invalid operator\n");
                return -1;
            }

            push(result);
        }
    }

    return pop();
}

int main()
{
    char expression[MAX];
    int result;

    printf("Enter postfix expression: ");
    fgets(expression, MAX, stdin);

    result = evaluatePostfix(expression);

    printf("Result = %d\n", result);

    return 0;
}