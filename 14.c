#include <stdio.h>
#include <stdlib.h>
#include<string.h>


// Structure to represent a node in the abstract syntax tree (AST)
typedef struct Node {
    char data;
    struct Node *left;
    struct Node *right;
} Node;

// Function prototypes
Node *createNode(char data);
Node *buildExpressionTree(char *expression, int *index);
void generateCode(Node *root,int n);

int main() {
    char expression[100];

    // Input the arithmetic expression
    printf("Enter the arithmetic expression: ");
    fgets(expression, sizeof(expression), stdin);

    int index = 0;
    Node *root = buildExpressionTree(expression, &index);

    // Generate code for the expression
    generateCode(root,strlen(expression));

    return 0;
}

// Function to create a new node in the AST
Node *createNode(char data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to build the expression tree from the input expression
Node *buildExpressionTree(char *expression, int *index) {
    if (expression[*index] == '\0' || expression[*index] == '\n') {
        return NULL;
    }

    Node *node = createNode(expression[*index]);
    (*index)++;

    if (expression[*index] == '+' || expression[*index] == '-' ||
        expression[*index] == '*' || expression[*index] == '/') {
        (*index)++;
        node->left = buildExpressionTree(expression, index);
        (*index)++;
        node->right = buildExpressionTree(expression, index);
    }

    return node;
}

// Function to generate x86 assembly code for a given AST
void generateCode(Node *root,int n) {
    if (root == NULL) {
        return;
    }
for(i=0;i<n;i++){
    if (root->data == '+' || root->data == '-' || root->data == '*' || root->data == '/') {
        generateCode(root->left,n);
        generateCode(root->right,n);

        if (root->left->data != root->data) {
            printf("MOV AX, %c\n", root->left->data);
        }

        printf("MOV BX, %c\n", root->right->data);

        switch (root->data) {
            case '+':
                printf("ADD AX, BX\n");
                break;
            case '-':
                printf("SUB AX, BX\n");
                break;
            case '*':
                printf("IMUL BX\n");
                break;
            case '/':
                printf("XOR DX, DX\n");
                printf("DIV BX\n");
                break;
            default:
                break;
        }

        printf("MOV %c, AX\n", root->data);
    } else {
        printf("MOV %c, %c\n", root->data, root->data);
    }
}
}
