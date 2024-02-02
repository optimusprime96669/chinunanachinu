#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_RULES 10
#define MAX_SYMBOLS 10

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
void eliminateLeftRecursion(Rule *rules, int *numRules);
void eliminateLeftFactoring(Rule *rules, int *numRules);
void printRules(Rule *rules, int numRules);

// Function to add a symbol to a set
void addToSet(SymbolSet *set, char symbol) {
    if (set->count < MAX_SYMBOLS) {
        set->symbols[set->count++] = symbol;
    }
}

// Function to merge two sets
void mergeSets(SymbolSet *destination, SymbolSet *source) {
    for (int i = 0; i < source->count; i++) {
        addToSet(destination, source->symbols[i]);
    }
}

// Function to print a set
void printSet(SymbolSet *set) {
    printf("{ ");
    for (int i = 0; i < set->count; i++) {
        printf("%c ", set->symbols[i]);
    }
    printf("}");
}

// Function to print production rule
void printRule(Rule *rule) {
    printf("%c -> ", rule->nonTerminal);
    for (int i = 0; i < rule->production.count; i++) {
        printf("%c", rule->production.symbols[i]);
    }
    printf("\n");
}



// Function to eliminate left recursion
void eliminateLeftRecursion(Rule *rules, int *numRules) {
    for (int i = 0; i < *numRules; i++) {
        char A = rules[i].nonTerminal;

        for (int j = 0; j < i; j++) {
            char B = rules[j].nonTerminal;

            // Check for left recursion: A -> Aα
            if (A == rules[j].production.symbols[0]) {
                // Remove left recursion by creating new non-terminal A' and updating rules
                char A_prime = A + 1;

                // Replace A -> Aα with A -> βA' and A' -> αA' | ε
                SymbolSet beta;
                beta.count = 0;
                for (int k = 1; k < rules[i].production.count; k++) {
                    addToSet(&beta, rules[i].production.symbols[k]);
                }

                rules[i].production.count = 1;
                rules[i].production.symbols[0] = A_prime;

                rules[*numRules].nonTerminal = A_prime;
                rules[*numRules].production = beta;
                (*numRules)++;

                // Add A' -> ε
                rules[*numRules].nonTerminal = A_prime;
                rules[*numRules].production.count = 0;
                (*numRules)++;
            }
        }
    }
}

// Function to eliminate left factoring
void eliminateLeftFactoring(Rule *rules, int *numRules) {
    for (int i = 0; i < *numRules; i++) {
        char A = rules[i].nonTerminal;

        // Find common prefixes in the production
        for (int j = 0; j < rules[i].production.count - 1; j++) {
            char X = rules[i].production.symbols[j];

            for (int k = j + 1; k < rules[i].production.count; k++) {
                char Y = rules[i].production.symbols[k];

                if (X == Y) {
                    // Common prefix found: A -> Xα | Xβ
                    // Create new non-terminal A' and update rules
                    char A_prime = A + 1;

                    // Replace A -> Xα | Xβ with A -> XA' and A' -> α | β
                    rules[i].production.count = j + 1;
                    rules[i].production.symbols[j + 1] = A_prime;

                    rules[*numRules].nonTerminal = A_prime;
                    rules[*numRules].production.count = rules[i].production.count - (j + 1);
                    for (int l = 0; l < rules[i].production.count - (j + 1); l++) {
                        rules[*numRules].production.symbols[l] = rules[i].production.symbols[j + 1 + l];
                    }
                    (*numRules)++;
                }
            }
        }
    }
}

// Function to print rules
void printRules(Rule *rules, int numRules) {
    for (int i = 0; i < numRules; i++) {
        printRule(&rules[i]);
    }
}
int main() {
    int numRules;

    // Input grammar rules from the user
    printf("Enter the number of rules: ");
    scanf("%d", &numRules);

    Rule rules[MAX_RULES];

    printf("Enter the grammar rules:\n");
    for (int i = 0; i < numRules; i++) {
        scanf(" %c -> %s", &rules[i].nonTerminal, rules[i].production.symbols);
        rules[i].production.count = strlen(rules[i].production.symbols);
    }

    // Eliminate left recursion
    eliminateLeftRecursion(rules, &numRules);

    // Eliminate left factoring
    // eliminateLeftFactoring(rules, &numRules);

    // Display modified rules
    printf("\nModified Rules:\n");
    printRules(rules, numRules);

    return 0;
}
