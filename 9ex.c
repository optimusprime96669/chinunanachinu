#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include<ctype.h>

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

// Structure to represent items in LR(0) parsing
typedef struct {
    int ruleIndex;
    int dotPosition;
} LR0Item;

// Function prototypes
void initializeGrammar(Rule *rules, int *numRules);
void printRules(Rule *rules, int numRules);
void closure(Rule *rules, int numRules, SymbolSet *itemSet);
void gotoLR0(Rule *rules, int numRules, SymbolSet *itemSet, char symbol, SymbolSet *result);
void buildParsingTable(Rule *rules, int numRules, char **actionTable, int **gotoTable);
bool parseLRString(char *input, Rule *rules, int numRules, char **actionTable, int **gotoTable);


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

// Function to compute closure of an LR(0) item set
void closure(Rule *rules, int numRules, SymbolSet *itemSet) {
    int originalCount;

    do {
        originalCount = itemSet->count;

        for (int i = 0; i < itemSet->count; i++) {
            int ruleIndex = itemSet->symbols[i];
            int dotPosition = 0;

            for (int j = 0; j < itemSet->count; j++) {
                if (rules[ruleIndex].production.symbols[dotPosition] == itemSet->symbols[j]) {
                    dotPosition++;
                }
            }

            if (dotPosition < rules[ruleIndex].production.count) {
                addToSet(itemSet, rules[ruleIndex].production.symbols[dotPosition]);
            }
        }

    } while (originalCount < itemSet->count);
}

// Function to compute Goto operation for an LR(0) item set
void gotoLR0(Rule *rules, int numRules, SymbolSet *itemSet, char symbol, SymbolSet *result) {
    result->count = 0;

    for (int i = 0; i < itemSet->count; i++) {
        int ruleIndex = itemSet->symbols[i];

        if (rules[ruleIndex].production.symbols[0] == symbol) {
            addToSet(result, ruleIndex);
        }
    }

    closure(rules, numRules, result);
}

// Function to build LR(0) parsing table
void buildParsingTable(Rule *rules, int numRules, char **actionTable, int **gotoTable) {
    SymbolSet canonicalSet[MAX_STACK];
    int canonicalSetCount = 0;

    for (int i = 0; i < numRules; i++) {
        SymbolSet itemSet;
        itemSet.count = 0;
        addToSet(&itemSet, i);
        closure(rules, numRules, &itemSet);
        canonicalSet[canonicalSetCount++] = itemSet;
    }

    actionTable = (char **)malloc(canonicalSetCount * sizeof(char *));
    gotoTable = (int **)malloc(canonicalSetCount * sizeof(int *));
    for (int i = 0; i < canonicalSetCount; i++) {
        actionTable[i] = (char *)malloc(256 * sizeof(char));
        gotoTable[i] = (int *)malloc(numRules * sizeof(int));
        for (int j = 0; j < 256; j++) {
            actionTable[i][j] = ' ';
        }
    }

    for (int i = 0; i < canonicalSetCount; i++) {
        SymbolSet itemSet = canonicalSet[i];

        for (int j = 0; j < itemSet.count; j++) {
            int ruleIndex = itemSet.symbols[j];

            if (rules[ruleIndex].production.symbols[rules[ruleIndex].production.count - 1] == '.') {
                // Reduce action
                for (int k = 0; k < 256; k++) {
                    if (actionTable[i][k] == ' ') {
                        actionTable[i][k] = 'r';
                        sprintf(&actionTable[i][k + 1], "%d", ruleIndex);
                        break;
                    }
                }
            } else {
                // Shift or goto action
                SymbolSet nextSet;
                char nextSymbol = rules[ruleIndex].production.symbols[rules[ruleIndex].production.count - 1];

                if (j + 1 < itemSet.count) {
                    nextSymbol = itemSet.symbols[j + 1];
                }

                if (isupper(nextSymbol)) {
                    gotoLR0(rules, numRules, &itemSet, nextSymbol, &nextSet);

                    for (int k = 0; k < canonicalSetCount; k++) {
                        if (nextSet.count > 0 && nextSet.symbols[0] == k) {
                            gotoTable[i][k] = 1;
                        }
                    }
                } else {
                    for (int k = 0; k < 256; k++) {
                        if (actionTable[i][k] == ' ') {
                            actionTable[i][k] = 's';
                            sprintf(&actionTable[i][k + 1], "%d", nextSymbol);
                            break;
                        }
                    }
                }
            }
        }
    }
}

// Function to parse an input string using LR(0) parsing table
bool parseLRString(char *input, Rule *rules, int numRules, char **actionTable, int **gotoTable) {
    int stack[MAX_STACK];
    int top = -1;
    int currentState = 0;

    for (int i = 0; i < strlen(input); i++) {
        char symbol = input[i];

        int actionIndex = symbol;
        if (actionTable[currentState][actionIndex] == 's') {
            // Shift
            int nextState = atoi(&actionTable[currentState][actionIndex + 1]);
            stack[++top] = currentState;
            currentState = nextState;
        } else if (actionTable[currentState][actionIndex] == 'r') {
            // Reduce
            int ruleIndex = atoi(&actionTable[currentState][actionIndex + 1]);
            SymbolSet production = rules[ruleIndex].production;
            currentState = stack[top--];

            for (int j = 0; j < production.count; j++) {
                if (production.symbols[j] != '.') {
                    stack[++top] = production.symbols[j];
                }
            }
        } else {
            // Error
            return false;
        }
    }

    // Accept if the last action is a reduction to the start symbol
    return actionTable[currentState][0] == 'r' && atoi(&actionTable[currentState][1]) == 0;
}
int main() {
    int numRules;
    Rule rules[MAX_RULES];
    initializeGrammar(rules, &numRules);

    char **actionTable;
    int **gotoTable;
    buildParsingTable(rules, numRules, actionTable, gotoTable);

    char input[100];
    printf("Enter the input string: ");
    scanf("%s", input);

    if (parseLRString(input, rules, numRules, actionTable, gotoTable)) {
        printf("Accepted\n");
    } else {
        printf("Rejected\n");
    }

    return 0;
}
