#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

/* Push */
void push(char ch)
{
    if (top == MAX - 1)
        printf("Stack Overflow\n");
    else
        stack[++top] = ch;
}

/* Pop */
char pop()
{
    if (top == -1)
        return '\0';

    return stack[top--];
}

/* Peek */
char peek()
{
    if (top == -1)
        return '\0';

    return stack[top];
}

/* Precedence */
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;

    if (op == '*' || op == '/')
        return 2;

    if (op == '^')
        return 3;

    return 0;
}

/* Infix to Postfix */
void infixToPostfix(char infix[], char postfix[])
{
    int i, j = 0;
    char ch;

    top = -1;

    for (i = 0; infix[i] != '\0'; i++)
    {
        ch = infix[i];

        /* Operand */
        if (isalnum(ch))
        {
            postfix[j++] = ch;
        }

        /* Opening bracket */
        else if (ch == '(')
        {
            push(ch);
        }

        /* Closing bracket */
        else if (ch == ')')
        {
            while (top != -1 && peek() != '(')
                postfix[j++] = pop();

            pop(); // Remove '('
        }

        /* Operator */
        else
        {
            while (top != -1 &&
                   precedence(peek()) >= precedence(ch))
            {
                postfix[j++] = pop();
            }

            push(ch);
        }
    }

    /* Pop remaining operators */
    while (top != -1)
        postfix[j++] = pop();

    postfix[j] = '\0';
}

/* Main */
int main()
{
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}