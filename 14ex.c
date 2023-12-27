#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>


#define MAX_SIZE 100

// Stack implementation
typedef struct
{
    int top;
    int items[MAX_SIZE];
} Stack;

void initialize(Stack *s)
{
    s->top = -1;
}

int isEmpty(Stack *s)
{
    return s->top == -1;
}

void push(Stack *s, int val)
{
    if (s->top == MAX_SIZE - 1)
    {
        printf("Stack Overflow\n");
        return;
    }
    s->items[++(s->top)] = val;
}

int pop(Stack *s)
{
    if (isEmpty(s))
    {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
    return s->items[(s->top)--];
}

// Function to evaluate the postfix expression
int evaluatePostfix(char *exp)
{
    Stack stack;
    initialize(&stack);

    for (int i = 0; exp[i]; ++i)
    {
        if (isdigit(exp[i]))
        {
            push(&stack, exp[i] - '0');
        }
        else
        {
            int val1 = pop(&stack);
            int val2 = pop(&stack);
            switch (exp[i])
            {
            case '+':
                push(&stack, val2 + val1);
                break;
            case '-':
                push(&stack, val2 - val1);
                break;
            case '*':
                push(&stack, val2 * val1);
                break;
            case '/':
                push(&stack, val2 / val1);
                break;
            }
        }
    }
    return pop(&stack);
}

int main()
{
    char exp[MAX_SIZE];
    printf("Enter the postfix expression: ");
    fgets(exp, sizeof(exp), stdin);
    exp[strcspn(exp, "\n")] = '\0'; // Remove trailing newline

    int result = evaluatePostfix(exp);
    printf("Result: %d\n", result);

    return 0;
}
