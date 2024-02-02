#include <stdio.h>
#include <stdlib.h>

#define MAX_EXPR_SIZE 100

// Structure to represent a temporary variable
typedef struct {
    char name;
    int count;
} TempVariable;

TempVariable tempVar[MAX_EXPR_SIZE]; // Array to store temporary variables
int tempVarCount = 0; // Counter to track the number of temporary variables used

// Function prototypes
char getNextTempVar();
void generateThreeAddressCode(char *expression);

int main() {
    char expression[MAX_EXPR_SIZE];

    // Input the arithmetic expression
    printf("Enter the arithmetic expression: ");
    fgets(expression, MAX_EXPR_SIZE, stdin);

    // Remove the newline character from the input
    if (expression[strlen(expression) - 1] == '\n') {
        expression[strlen(expression) - 1] = '\0';
    }

    // Generate and print the three-address code
    generateThreeAddressCode(expression);

    return 0;
}

// Function to get the next temporary variable
char getNextTempVar() {
    char temp = 'T' + tempVarCount;
    tempVar[tempVarCount].name = temp;
    tempVar[tempVarCount].count = 0;
    tempVarCount++;
    return temp;
}

// Function to generate three-address code
void generateThreeAddressCode(char *expression) {
    printf("Three Address Code:\n");

    char resultVar;
    char operand1, operand2;
    char operator;
    int i = 0;

    while (expression[i] != '\0') {
        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            operator = expression[i];
            operand1 = getNextTempVar();
            operand2 = expression[i + 1];
            resultVar = getNextTempVar();

            printf("%c := %c %c %c\n", resultVar, operand1, operator, operand2);

            tempVar[tempVarCount - 2].count++;
            tempVar[tempVarCount - 1].count++;
            i += 2;
        } else {
            operand1 = expression[i];
            operand2 = expression[i + 1];
            resultVar = getNextTempVar();

            printf("%c := %c\n", resultVar, operand1);

            tempVar[tempVarCount - 1].count++;
            i += 1;
        }
    }

    // Print the final assignment
    printf("Final Result: %c\n", resultVar);
}
