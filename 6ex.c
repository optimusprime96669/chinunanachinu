#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_RULES 10
#define MAX_SYMBOLS 10

struct Rule {
    char nonTerminal;
    char production[10];
};

struct Rule rules[MAX_RULES];
int numRules;

struct Symbol {
    char symbol;
    bool isTerminal;
};

struct Symbol firstSets[MAX_SYMBOLS][MAX_SYMBOLS];
struct Symbol followSets[MAX_SYMBOLS][MAX_SYMBOLS];

int numFirstSets[MAX_SYMBOLS];
int numFollowSets[MAX_SYMBOLS];

int findIndex(char c) {
    for (int i = 0; i < numRules; ++i) {
        if (rules[i].nonTerminal == c) {
            return i;
        }
    }
    return -1;
}

void addToFirstSet(char nonTerminal, char terminal) {
    int index = findIndex(nonTerminal);
    int i;
    for (i = 0; i < numFirstSets[index]; ++i) {
        if (firstSets[index][i].symbol == terminal) {
            break;
        }
    }
    if (i == numFirstSets[index]) {
        firstSets[index][i].symbol = terminal;
        firstSets[index][i].isTerminal = true;
        numFirstSets[index]++;
    }
}

void addToFollowSet(char nonTerminal, char terminal) {
    int index = findIndex(nonTerminal);
    int i;
    for (i = 0; i < numFollowSets[index]; ++i) {
        if (followSets[index][i].symbol == terminal) {
            break;
        }
    }
    if (i == numFollowSets[index]) {
        followSets[index][i].symbol = terminal;
        followSets[index][i].isTerminal = true;
        numFollowSets[index]++;
    }
}

void computeFirstSet() {
    // Your logic to compute First sets goes here
    // Iterate through the grammar rules and compute First sets for each non-terminal symbol
    // Update the firstSets array accordingly
}

void computeFollowSet() {
    // Your logic to compute Follow sets goes here
    // Iterate through the grammar rules and compute Follow sets for each non-terminal symbol
    // Update the followSets array accordingly
}

int main() {
    printf("Enter the number of rules: ");
    scanf("%d", &numRules);

    printf("Enter the grammar rules (format: S->abc): \n");
    for (int i = 0; i < numRules; ++i) {
        scanf(" %c->%s", &rules[i].nonTerminal, rules[i].production);
    }

    // Initialize First and Follow sets
    memset(numFirstSets, 0, sizeof(numFirstSets));
    memset(numFollowSets, 0, sizeof(numFollowSets));

    computeFirstSet();
    computeFollowSet();

    // Display First and Follow sets
    // Display logic goes here

    return 0;
}
