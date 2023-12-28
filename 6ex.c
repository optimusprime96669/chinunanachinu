#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define MAX_RULES 10
#define MAX_FIRST 10
#define MAX_FOLLOW 10

typedef struct {
    char lhs;
    char rhs[10];
} ProductionRule;

ProductionRule rules[MAX_RULES];
int numRules = 0;

char firstSets[MAX_FIRST][MAX_FIRST];
char followSets[MAX_FOLLOW][MAX_FIRST];

void addRule(char lhs, const char* rhs) {
    rules[numRules].lhs = lhs;
    strcpy(rules[numRules].rhs, rhs);
    numRules++;
}

bool isTerminal(char symbol) {
    return islower(symbol) || symbol == '$'; // Assuming '$' represents epsilon
}

void computeFirstSet(char nonTerminal) {
    for (int i = 0; i < numRules; ++i) {
        if (rules[i].lhs == nonTerminal) {
            if (isTerminal(rules[i].rhs[0])) {
                firstSets[nonTerminal - 'A'][rules[i].rhs[0] - 'a'] = 1;
            } else {
                computeFirstSet(rules[i].rhs[0]);
            }
        }
    }
}

void computeFollowSet(char nonTerminal) {
    for (int i = 0; i < numRules; ++i) {
        int len = strlen(rules[i].rhs);
        for (int j = 0; j < len; ++j) {
            if (rules[i].rhs[j] == nonTerminal) {
                if (j < len - 1 && isTerminal(rules[i].rhs[j + 1])) {
                    followSets[nonTerminal - 'A'][rules[i].rhs[j + 1] - 'a'] = 1;
                } else if (j == len - 1) {
                    computeFollowSet(rules[i].lhs);
                } else {
                    int k = j + 1;
                    while (k < len && !isTerminal(rules[i].rhs[k])) {
                        computeFirstSet(rules[i].rhs[k]);
                        k++;
                    }
                }
            }
        }
    }
}

int main() {
    addRule('S', "AB");
    addRule('A', "aB");
    addRule('A', "");
    addRule('B', "b");

    computeFirstSet('A');
    computeFirstSet('B');
    computeFollowSet('S');
    computeFollowSet('A');
    computeFollowSet('B');

    // Displaying the First and Follow sets
    printf("First Sets:\n");
    for (int i = 0; i < 2; ++i) {
        printf("First(%c) = { ", 'A' + i);
        for (int j = 0; j < 26; ++j) {
            if (firstSets[i][j]) {
                printf("%c ", 'a' + j);
            }
        }
        printf("}\n");
    }

    printf("\nFollow Sets:\n");
    printf("Follow(S) = { $ ");
    for (int j = 0; j < 26; ++j) {
        if (followSets[0][j]) {
            printf("%c ", 'a' + j);
        }
    }
    printf("}\n");

    printf("Follow(A) = { $ ");
    for (int j = 0; j < 26; ++j) {
        if (followSets[1][j]) {
            printf("%c ", 'a' + j);
        }
    }
    printf("}\n");

    return 0;
}
