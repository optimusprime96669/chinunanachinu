#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Token types enumeration
enum TokenType {
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    LITERAL,
    PUNCTUATOR,
    COMMENT,
    UNKNOWN
};

// Function to identify the token type
enum TokenType identifyToken(char *token) {
    // Keywords
    char *keywords[] = {"int", "float", "char", "if", "else", "while", "for", "return"};
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return KEYWORD;
        }
    }

    // Operators
    char *operators[] = {"+", "-", "*", "/", "=", "==", "!=", "<", ">", "<=", ">="};
    for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); i++) {
        if (strcmp(token, operators[i]) == 0) {
            return OPERATOR;
        }
    }

    // Punctuators
    char *punctuators[] = {";", ",", "(", ")", "{", "}"};
    for (int i = 0; i < sizeof(punctuators) / sizeof(punctuators[0]); i++) {
        if (strcmp(token, punctuators[i]) == 0) {
            return PUNCTUATOR;
        }
    }

    // Identifiers
    if (isalpha(token[0]) || token[0] == '_') {
        return IDENTIFIER;
    }

    // Literals
    if (isdigit(token[0])) {
        return LITERAL;
    }

    // Comments
    if (token[0] == '/' && token[1] == '/') {
        return COMMENT;
    }

    // Unknown
    return UNKNOWN;
}

int main() {
    char program[1000];
    printf("Enter the C program:\n");
    fgets(program, sizeof(program), stdin);

    char *token = strtok(program, " \t\n");
    while (token != NULL) {
        enum TokenType type = identifyToken(token);

        printf("Token: %-20s Type: ", token);

        switch (type) {
            case KEYWORD:
                printf("Keyword\n");
                break;
            case IDENTIFIER:
                printf("Identifier\n");
                break;
            case OPERATOR:
                printf("Operator\n");
                break;
            case LITERAL:
                printf("Literal\n");
                break;
            case PUNCTUATOR:
                printf("Punctuator\n");
                break;
            case COMMENT:
                printf("Comment\n");
                break;
            case UNKNOWN:
                printf("Unknown\n");
                break;
        }

        token = strtok(NULL, " \t\n");
    }

    return 0;
}
