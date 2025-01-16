#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "definition.h"
#include "functions.h"

// Lexer function
void tokenize(const char *input) {
    int i = 0, invalidTokens = 0;
    int length = strlen(input);
    Token tokens[MAX_TOKENS];
    int tokenCount = 0;
    int lineNumber = 1; // Track line numbers
    Stack delimiterStack = { .top = -1 };

    FILE *outputFile = fopen("tokens.txt", "w");
    if (!outputFile) {
    perror("Error opening output file");
    return;
    }

    while (i < length) {
        if (isSpace(input[i])) {
            if (input[i] == '\n') {
                lineNumber++; // Increment line number on newline
            }
            i++;
            continue;
        }
        
        Token token;
        token.lineNumber = lineNumber; // Assign current line number

        // Handle identifiers, keywords, and reserved words
        if (isAlpha(input[i]) || input[i] == '_') {
            int start = i;
            while (isAlnum(input[i]) || input[i] == '_') {
                i++;
            }
            strncpy(token.value, &input[start], i - start);
            token.value[i - start] = '\0';
        
            // Check if the identifier contains any special characters
            int isValid = 1;
            for (int j = 0; token.value[j] != '\0'; j++) { 
                if (!isAlnum(token.value[j]) && token.value[j] != '_') {
                    isValid = 0;
                    break;
                }
            }
        
            if (!isValid) {
                fprintf(stderr, "Error: Invalid identifier '%s' at line %d\n", token.value, lineNumber);
                token.type = INVALID;
                invalidTokens++;
            } else if (isKeyword(token.value)) {
                // Check for noise words within the keyword
                for (int j = 0; noiseWords[j] != NULL; j++) {
                    char *noisePos = strstr(token.value, noiseWords[j]);
                    if (noisePos != NULL) {
                        // Remove the noise word from the original string
                        size_t noiseLen = strlen(noiseWords[j]);
                        memmove(noisePos, noisePos + noiseLen, strlen(noisePos + noiseLen) + 1);
                    }
                } 
                token.type = KEYWORD;
            }else if (isReservedWord(token.value)) {
                token.type = RESERVED_WORD;
            } else {
                token.type = IDENTIFIER;
            }
        } 
        else if (isDigit(input[i])) { // Handle numbers
            int start = i;
            while (isDigit(input[i])) { // Scan numeric characters
                i++;
            }
            int isFloat = 0;
        
            if (input[i] == '.' && isDigit(input[i + 1])) { // Detect floats
                isFloat = 1;
                i++;
                while (isDigit(input[i])) {
                    i++;
                }
            }
        
            // Copy the numeric part of the token value
            int end = i;
            strncpy(token.value, &input[start], end - start);
            token.value[end - start] = '\0';
        
            // Set the token type
            token.type = isFloat ? FLOAT_LITERAL : INTEGER_LITERAL;
            token.lineNumber = lineNumber; // Assign current line number
        }
        else if (input[i] == '"') { // String literals
            int start = i++;
            while (input[i] != '"' && input[i] != '\0') {
                if (input[i] == '\n') lineNumber++; // Count newlines inside strings
                i++;
            }
            if (input[i] == '"') {
                i++;
                strncpy(token.value, &input[start], i - start);
                token.value[i - start] = '\0';
                token.type = STRING_LITERAL;
            } else {
                fprintf(stderr, "Error: Unterminated string literal at line %d\n", lineNumber);
                token.type = INVALID;
                invalidTokens++;
                strncpy(token.value, &input[start], i - start);
                token.value[i - start] = '\0';
            }

        } else if (input[i] == '\'' && input[i + 1] == '\\' && input[i + 2] == '0' && input[i + 3] == '\'') {
            
            strncpy(token.value, &input[i], 4); 
            token.value[4] = '\0';
            token.type = CHAR_LITERAL;
            i += 4; 

        } else if (input[i] == '\'' && isprint(input[i + 1]) && input[i + 2] == '\'') { 
            int start = i;
            strncpy(token.value, &input[start], 3); 
            token.value[3] = '\0';
            token.type = CHAR_LITERAL;
            i += 3; 

        } else if (input[i] == '/' && input[i + 1] == '/') { 
            int start = i;
            while (input[i] != '\n' && input[i] != '\0') {
                i++;
            }
            strncpy(token.value, &input[start], i - start);
            token.value[i - start] = '\0';
            token.type = COMMENT;

        } else if (input[i] == '/' && input[i + 1] == '*') { 
            int start = i;
            i += 2;
            while (!(input[i] == '*' && input[i + 1] == '/') && input[i] != '\0') {
                if (input[i] == '\n') lineNumber++;
                i++;
            }
            if (input[i] == '*' && input[i + 1] == '/') {
                i += 2;
                strncpy(token.value, &input[start], i - start);
                token.value[i - start] = '\0';
                token.type = COMMENT;
            } else {
                fprintf(stderr, "Error: Unterminated comment starting at line %d\n", lineNumber);
                token.type = INVALID;
                invalidTokens++;
                strncpy(token.value, &input[start], i - start);
                token.value[i - start] = '\0';
            }
        } else { // Handle operators, punctuators, and invalid tokens
            int start = i;

            // Check for delimiters
            if (input[i] == '(') {
                token.value[0] = input[i];
                token.value[1] = '\0';
                token.type = LP_BRACKET;
                push(&delimiterStack, input[i]);
                i++;
            } else if (input[i] == ')') {
                token.value[0] = input[i];
                token.value[1] = '\0';
                token.type = RP_BRACKET;
                i++;
            } else if (input[i] == '{') {
                token.value[0] = input[i];
                token.value[1] = '\0';
                token.type = LC_BRACKET;
                push(&delimiterStack, input[i]);
                i++;
            } else if (input[i] == '}') {
                token.value[0] = input[i];
                token.value[1] = '\0';
                token.type = RC_BRACKET;
                i++;
            } else if (input[i] == '[') {
                token.value[0] = input[i];
                token.value[1] = '\0';
                token.type = LS_BRACKET;
                push(&delimiterStack, input[i]);
                i++;
            } else if (input[i] == ']') {
                token.value[0] = input[i];
                token.value[1] = '\0';
                token.type = RS_BRACKET;
                i++;
            } else {
                if (isPunctuator(input[i])) {
                    token.value[0] = input[i];
                    token.value[1] = '\0'; 
                    token.type = PUNCTUATOR;
                    i++;
                } else if (isOperator((char[]){input[i], '\0'})) {
                    char temp[3]; 
                    temp[0] = input[i];
                    temp[1] = input[i + 1]; 
                    temp[2] = '\0'; 

                    if (isOperator(temp)) { 
                        strncpy(token.value, temp, 2); 
                        token.value[2] = '\0';         
                        i += 2;                       
                    } else { 
                        temp[1] = '\0'; 
                        strncpy(token.value, temp, 1); 
                        token.value[1] = '\0';         
                        i++;                          
                    }

                    // Classify the operator
                    if (isArithmeticOperator(token.value)) {
                        token.type = ARITHMETIC_OP;
                    } else if (isBooleanOperator(token.value)) {
                        token.type = BOOLEAN_OP;
                    } else if (isAssignmentOperator(token.value)) {
                        token.type = ASSIGNMENT_OP;
                    } else if (isRelationalOperator(token.value)) {
                        token.type = RELATIONAL_OP;
                    } 
                }
                else { 
                    if (isInvalidChar(input[i])) {
                        while (isInvalidChar(input[i])) {
                            i++;
                        }
                        strncpy(token.value, &input[start], i - start);
                        token.value[i - start] = '\0';
                        token.type = INVALID;
                        invalidTokens++;
                        fprintf(stderr, "Error: Invalid token '%s' at line %d\n", token.value, lineNumber);
                    }
                }
            } 
        }

        if (tokenCount < MAX_TOKENS) {
            tokens[tokenCount++] = token;
        } else {
            fprintf(stderr, "Error: Token limit exceeded.\n");
            break;
        }
    } 

    fprintf(outputFile, "Token Table:\n");
    fprintf(outputFile, "Invalid Tokens: %d\n", invalidTokens);
    
    for (int j = 0; j < tokenCount; j++) {
        fprintf(outputFile, "%-20s %-15s %-5d \n",
                tokenTypeNames[tokens[j].type], tokens[j].value, tokens[j].lineNumber);
    }

    // Close the output file
    fclose(outputFile);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename.cig>\n", argv[0]);
        return 1;
    }

    // Check if the file has the ".cig" extension
    const char *filename = argv[1];
    const char *extension = strrchr(filename, '.'); // Get the file extension
    if (!extension || strcmp(extension, ".cig") != 0) {
        fprintf(stderr, "Error: Only '.cig' files are allowed.\n");
        return 1;
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *code = (char *)malloc(fileSize + 1);
    if (!code) {
        perror("Memory allocation failed");
        fclose(file);
        return 1;
    }

    fread(code, 1, fileSize, file);
    code[fileSize] = '\0';
    fclose(file);

    tokenize(code);
    free(code); 
    return 0; 
}

