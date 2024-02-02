#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include<stdbool.h>



#define MAX_RULES 10
#define MAX_SYMBOLS 10
#define MAX_STACK 100

// Structure to represent a set of symbols
typedef struct {
    char symbols[MAX_SYMBOLS];
    int count;
} SymbolSet;

// Structure to represent a production rule
typedef struct {
    char nonTerminal;
    SymbolSet production;
} Rule;

// Function prototypes
void initializeGrammar(Rule *rules, int *numRules);
void printRules(Rule *rules, int numRules);
bool shiftReduceParse(char *input, Rule *rules, int numRules);

int main() {
    int numRules;
    Rule rules[MAX_RULES];
    initializeGrammar(rules, &numRules);

    char input[100];
    printf("Enter the input string: ");
    scanf("%s", input);

    if (shiftReduceParse(input, rules, numRules)) {
        printf("Accepted\n");
    } else {
        printf("Rejected\n");
    }

    return 0;
}

// Function to initialize grammar rules
void initializeGrammar(Rule *rules, int *numRules) {
    printf("Enter the number of rules: ");
    scanf("%d", numRules);

    printf("Enter the grammar rules:\n");
    for (int i = 0; i < *numRules; i++) {
        scanf(" %c -> %s", &rules[i].nonTerminal, rules[i].production.symbols);
        rules[i].production.count = strlen(rules[i].production.symbols);
    }
}

// Function to print grammar rules
void printRules(Rule *rules, int numRules) {
    for (int i = 0; i < numRules; i++) {
        printf("%c -> %s\n", rules[i].nonTerminal, rules[i].production.symbols);
    }
}

// Function to perform Shift-Reduce parsing
bool shiftReduceParse(char *input, Rule *rules, int numRules) {
    char stack[MAX_STACK];
    int top = -1;
    int inputIndex = 0;

    // Push the start symbol onto the stack
    stack[++top] = 'S'; // Assuming 'S' is the start symbol

    while (top >= 0) {
        // Print the current stack and input
        printf("Stack: %s\tInput: %s\n", stack, &input[inputIndex]);

        // Pop the top of the stack
        char currentSymbol = stack[top--];

        // If the current symbol is a terminal or matches the input, perform a shift
        if (!isupper(currentSymbol) || currentSymbol == input[inputIndex]) {
            if (currentSymbol == '\0') {
                // Accept condition
                return true;
            }

            // Move to the next input symbol
            inputIndex++;
        } else {
            // If the current symbol is a non-terminal, find a matching production rule
            int ruleIndex = -1;
            for (int i = 0; i < numRules; i++) {
                if (rules[i].nonTerminal == currentSymbol) {
                    ruleIndex = i;
                    break;
                }
            }

            if (ruleIndex == -1) {
                // No matching rule found, reject
                return false;
            }

            // Reduce by replacing the non-terminal with its production in reverse order
            for (int i = rules[ruleIndex].production.count - 1; i >= 0; i--) {
                stack[++top] = rules[ruleIndex].production.symbols[i];
            }
        }
    }

    // If the stack is empty and the input is fully processed, accept
    return (stack[0] == '\0' && input[inputIndex] == '\0');
}
