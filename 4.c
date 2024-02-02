#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100
#define MAX_PRODUCTIONS 10

// Function to match a non-terminal symbol
int match(char *input, char *symbol);

// Function to parse the input string
int parse(char *input, char productions[MAX_PRODUCTIONS][MAX_LEN], int numProductions, int *index);

int main() {
    char input[MAX_LEN];
    char productions[MAX_PRODUCTIONS][MAX_LEN];
    int numProductions;

    printf("Enter the input string: ");
    scanf("%s", input);

    printf("Enter the number of production rules: ");
    scanf("%d", &numProductions);

    printf("Enter the production rules:\n");
    for (int i = 0; i < numProductions; i++) {
        scanf("%s", productions[i]);
    }

    int index = 0;

    if (parse(input, productions, numProductions, &index)) {
        printf("Parsing successful!\n");
    } else {
        printf("Parsing failed!\n");
    }

    return 0;
}

int match(char *input, char *symbol) {
    int len = strlen(symbol);
    if (strncmp(input, symbol, len) == 0) {
        return len;
    }
    return 0;
}

int parse(char *input, char productions[MAX_PRODUCTIONS][MAX_LEN], int numProductions, int *index) {
    for (int i = 0; i < numProductions; i++) {
        int originalIndex = *index;
        int consumed = match(input + *index, productions[i]);
        if (consumed > 0) {
            *index += consumed;
            return 1;
        } else {
            *index = originalIndex;
        }
    }
    return 0;
}
