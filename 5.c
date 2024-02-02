#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


#define MAX_RULES 10

// Function prototypes for non-terminal symbols
bool parseRule(char *input);
bool parseExpr(char *input);
bool parseTerm(char *input);
bool parseFactor(char *input);
bool  parseTermRest(char *input);
bool parseExprRest(char *input);

// Function to match a terminal symbol
bool match(char *input, char *symbol) {
    if (strncmp(input, symbol, strlen(symbol)) == 0) {
        return true;
    }
    return false;
}

// Function to parse a rule
bool parseRule(char *input) {
    return parseExpr(input) && match(input, ";");
}

// Function to parse an expression
bool parseExpr(char *input) {
    return parseTerm(input) && parseExprRest(input);
}

// Function to parse the rest of an expression
bool parseExprRest(char *input) {
    if (match(input, "+")) {
        return match(input, "+") && parseTerm(input) && parseExprRest(input);
    } else {
        return true; // epsilon (empty string)
    }
}

// Function to parse a term
bool parseTerm(char *input) {
    return parseFactor(input) && parseTermRest(input);
}

// Function to parse the rest of a term
bool parseTermRest(char *input) {
    if (match(input, "*")) {
        return match(input, "*") && parseFactor(input) && parseTermRest(input);
    } else {
        return true; // epsilon (empty string)
    }
}

// Function to parse a factor
bool parseFactor(char *input) {
    if (match(input, "(")) {
        return match(input, "(") && parseExpr(input) && match(input, ")");
    } else if (isalpha(input[0])) {
        return match(input, "id");
    } else {
        return false;
    }
}

int main() {
    char grammar[MAX_RULES][50];
    int numRules;

    // Input grammar rules from the user
    printf("Enter the number of rules: ");
    scanf("%d", &numRules);

    printf("Enter the grammar rules:\n");
    for (int i = 0; i < numRules; i++) {
        scanf("%s", grammar[i]);
    }

    // Parse each rule
    for (int i = 0; i < numRules; i++) {
        if (parseRule(grammar[i])) {
            printf("Rule %d: Accepted\n", i + 1);
        } else {
            printf("Rule %d: Rejected\n", i + 1);
        }
    }

    return 0;
}
