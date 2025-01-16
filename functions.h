#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "definition.h"
#include <stdio.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100
#define MAX_TOKENS 1000
#define MAX_STACK_SIZE 100

// Stack operations
void push(Stack *stack, char c) {
    if (stack->top < MAX_STACK_SIZE - 1) {
        stack->items[++(stack->top)] = c;
    } else {
        fprintf(stderr, "Error: Stack overflow while pushing '%c'\n", c);
    }
}

char pop(Stack *stack) {
    if (stack->top >= 0) {
        return stack->items[(stack->top)--];
    } else {
        fprintf(stderr, "Error: Stack underflow while popping\n");
        return '\0';
    }
}

char peek(const Stack *stack) {
    if (stack->top >= 0) {
        return stack->items[stack->top];
    } else {
        return '\0';
    }
}

// Utility function to check if a string is an arithmetic operator
int isArithmeticOperator(const char *word) {
    for (int i = 0; arithmeticOperators[i] != NULL; i++) {
        if (strcmp(word, arithmeticOperators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Utility function to check if a string is a boolean operator
int isBooleanOperator(const char *word) {
    for (int i = 0; booleanOperators[i] != NULL; i++) {
        if (strcmp(word, booleanOperators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Utility function to check if a string is an assignment operator
int isAssignmentOperator(const char *word) {
    for (int i = 0; assignmentOperators[i] != NULL; i++) {
        if (strcmp(word, assignmentOperators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Utility function to check if a string is an assignment operator
int isRelationalOperator(const char *word) {
    for (int i = 0; relationalOperators[i] != NULL; i++) {
        if (strcmp(word, relationalOperators[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a word is a keyword
int isKeyword(const char *word) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a word is a reserved word
int isReservedWord(const char *word) {
    for (int i = 0; reservedWords[i] != NULL; i++) {
        if (strcmp(word, reservedWords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a word is a punctuator
int isPunctuator(const char c) {
    for (int i = 0; punctuatorChar[i] != NULL; i++) {
        if (c == punctuatorChar[i][0]) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a word is a bracket
int isBracket(const char c) {
    for (int i = 0; brackets[i] != NULL; i++) {
        if (c == brackets[i][0]) {
            return 1;
        }
    }
    return 0;
}

int isSpace(char c) {
    for (int i = 0; whitespaceChars[i] != NULL; i++) {
        if (c == whitespaceChars[i][0]) {
            return 1;
        }
    }
    return 0;
}

int isAlpha(char c) {
    for (int i = 0; alphabetChars[i] != NULL; i++) {
        if (c == alphabetChars[i][0]) {
            return 1;
        }
    }
    return 0;
}

int isDigit(char c) {
    for (int i = 0; numericChars[i] != NULL; i++) {
        if (c == numericChars[i][0]) {
            return 1;
        }
    }
    return 0;
}

int isInvalidChar(char c) {
    for (int i = 0; invalidChars[i] != NULL; i++) {
        if (c == invalidChars[i][0]) {
            return 1;
        }
    }
    return 0;
}

int isAlnum(char c) {
    return isAlpha(c) || isDigit(c);
}

// Function to check if a word is a delimiter
int isOperator(const char *word) {

    return
    isArithmeticOperator(word) || isBooleanOperator(word) || 
    isAssignmentOperator(word) || isRelationalOperator(word);
}

#endif 