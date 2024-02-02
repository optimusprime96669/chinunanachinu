#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void computeFirstSets(Rule *rules, int numRules, SymbolSet *firstSets);
void computeFollowSets(Rule *rules, int numRules, SymbolSet *firstSets, SymbolSet *followSets);

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
    printf("}\n");
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

    // Compute First sets
    SymbolSet firstSets[MAX_RULES];
    computeFirstSets(rules, numRules, firstSets);

    // Compute Follow sets
    SymbolSet followSets[MAX_RULES];
    computeFollowSets(rules, numRules, firstSets, followSets);

    // Display First and Follow sets
    printf("\nFirst Sets:\n");
    for (int i = 0; i < numRules; i++) {
        printf("First(%c): ", rules[i].nonTerminal);
        printSet(&firstSets[i]);
    }

    printf("\nFollow Sets:\n");
    for (int i = 0; i < numRules; i++) {
        printf("Follow(%c): ", rules[i].nonTerminal);
        printSet(&followSets[i]);
    }

    return 0;
}

// Function to compute First sets
void computeFirstSets(Rule *rules, int numRules, SymbolSet *firstSets) {
    for (int i = 0; i < numRules; i++) {
        firstSets[i].count = 0;
    }

    // Repeat until no changes are made to any First set
    int changes;
    do {
        changes = 0;

        // Iterate through each rule
        for (int i = 0; i < numRules; i++) {
            char nonTerminal = rules[i].nonTerminal;
            SymbolSet *currentSet = &firstSets[i];

            // Iterate through each symbol in the production
            for (int j = 0; j < rules[i].production.count; j++) {
                char symbol = rules[i].production.symbols[j];

                // If the symbol is a terminal, add it to the First set
                if (isupper(symbol) || symbol == '\0') {
                    addToSet(currentSet, symbol);
                    break; // Stop processing the rest of the production
                }

                // If the symbol is a non-terminal, add its First set to the current set
                SymbolSet *nextSet = &firstSets[nonTerminal - 'A'];
                mergeSets(currentSet, nextSet);

                // If epsilon is not in the First set of the non-terminal, stop processing
                if (!strchr(nextSet->symbols, '\0')) {
                    break;
                }
            }

            // Check if the First set has changed
            if (currentSet->count > firstSets[i].count) {
                changes = 1;
            }
        }
    } while (changes);
}

// Function to compute Follow sets
void computeFollowSets(Rule *rules, int numRules, SymbolSet *firstSets, SymbolSet *followSets) {
    for (int i = 0; i < numRules; i++) {
        followSets[i].count = 0;
    }

    // Add $ (end marker) to the Follow set of the start symbol
    addToSet(&followSets[0], '$');

    // Repeat until no changes are made to any Follow set
    int changes;
    do {
        changes = 0;

        // Iterate through each rule
        for (int i = 0; i < numRules; i++) {
            char nonTerminal = rules[i].nonTerminal;

            // Iterate through each symbol in the production
            for (int j = 0; j < rules[i].production.count; j++) {
                char symbol = rules[i].production.symbols[j];

                // If the symbol is a non-terminal, add the First set of the next symbol
                if (isupper(symbol) && j < rules[i].production.count - 1) {
                    SymbolSet *nextSet = &firstSets[rules[i].production.symbols[j + 1] - 'A'];

                    // Exclude epsilon from the First set
                    for (int k = 0; k < nextSet->count; k++) {
                        if (nextSet->symbols[k] != '\0') {
                            addToSet(&followSets[symbol - 'A'], nextSet->symbols[k]);
                        }
                    }

                    // If epsilon is in the First set of the next symbol, add the Follow set of the non-terminal
                    if (strchr(nextSet->symbols, '\0')) {
                        mergeSets(&followSets[symbol - 'A'], &followSets[nonTerminal - 'A']);
                    }
                }

                // If the symbol is the last in the production, add the Follow set of the non-terminal
                if (j == rules[i].production.count - 1) {
                    mergeSets(&followSets[symbol - 'A'], &followSets[nonTerminal - 'A']);
                }
            }
        }
    } while (changes);
}
