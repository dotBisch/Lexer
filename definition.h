#ifndef DEFINITION_H
#define DEFINITION_H

#include <stdio.h>

#define MAX_TOKEN_LENGTH 100
#define MAX_TOKENS 1000
#define MAX_STACK_SIZE 100

// Token types
typedef enum {
    IDENTIFIER, KEYWORD, RESERVED_WORD, NOISE_WORD, 
    INTEGER_LITERAL, FLOAT_LITERAL, STRING_LITERAL, CHAR_LITERAL,
    ARITHMETIC_OP, BOOLEAN_OP, ASSIGNMENT_OP, RELATIONAL_OP,
    PUNCTUATOR, LP_BRACKET, RP_BRACKET, LS_BRACKET, RS_BRACKET, LC_BRACKET, RC_BRACKET,
    COMMENT, INVALID
} TokenType; 

// Token type names
const char *tokenTypeNames[] = {
    "IDENTIFIER", "KEYWORD", "RESERVED_WORD", "NOISE_WORD", 
    "INTEGER_LITERAL", "FLOAT_LITERAL", "STRING_LITERAL","CHAR_LITERAL", 
    "ARITHMETIC_OP", "BOOLEAN_OP", "ASSIGNMENT_OP", "RELATIONAL_OP",
    "PUNCTUATOR", "LP_BRACKET", "RP_BRACKET", "LS_BRACKET", "RS_BRACKET", "LC_BRACKET", "RC_BRACKET",
    "COMMENT", "INVALID"
}; 
// Operators categorized
const char *numericChars[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", NULL };
const char *arithmeticOperators[] = { "+", "-", "*", "/", "%", "++", "--", NULL };
const char *booleanOperators[] = { "&&", "||", "!", NULL };
const char *relationalOperators[] = { "==", "!=", "<", ">", "<=", ">=", NULL };
const char *assignmentOperators[] = { "=",  "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", ">>=", "<<=", NULL };
const char *punctuatorChar[] = { ";", ",", ".", NULL };
const char *brackets[] = { "(", ")", "[", "]", "{", "}", NULL };
const char *keywords[] = {  "char", "const", "constant", "cont", "continue", "def", "default", "do", "double", "else", "enum", "float", "for", 
                            "if", "int", "life", "print", "return", "scan", "test", "test_state", "void", "while", "NULL", NULL };
const char *reservedWords[] = { "ms", "sec", "after", "every", "timeout", "freeze", "true", "false", NULL };
const char *noiseWords[] = { "ant", "inue", "ault", NULL };
const char *whitespaceChars[] = { " ", "\t", "\n", "\v", "\f", "\r", NULL };
const char *alphabetChars[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", 
                                "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
                                "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
                                "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", NULL };
const char *invalidChars[] = { "#", "$", "~", "`", ":", "@","\"", NULL};

// Token structure
typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LENGTH];
    int lineNumber;
} Token;

// Stack structure for delimiter matching
typedef struct {
    char items[MAX_STACK_SIZE];
    int top;
} Stack;

#endif 