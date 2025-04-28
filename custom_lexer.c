#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokens.h"

#define MAX_TOKEN_LEN 256

int line = 1;

// Helper to print tokens
void printToken(TokenType type, const char* lexeme) {
    printf("Line %-3d %-20s => %s\n", line, lexeme, tokenNames[type]);
}

// Keyword matcher
int isKeyword(const char* word, TokenType* type) {
    if (strcmp(word, "let") == 0) { *type = T_LET; return 1; }
    if (strcmp(word, "be") == 0) { *type = T_BE; return 1; }
    if (strcmp(word, "set") == 0) { *type = T_SET; return 1; }
    if (strcmp(word, "is") == 0) { *type = T_IS; return 1; }
    if (strcmp(word, "null") == 0) { *type = T_NULL; return 1; }
    if (strcmp(word, "if") == 0) { *type = T_IF; return 1; }
    if (strcmp(word, "then") == 0) { *type = T_THEN; return 1; }
    if (strcmp(word, "else") == 0) { *type = T_ELSE; return 1; }
    if (strcmp(word, "return") == 0 || strcmp(word, "give") == 0) { *type = T_RETURN; return 1; }
    if (strcmp(word, "while") == 0) { *type = T_WHILE; return 1; }
    if (strcmp(word, "repeat") == 0) { *type = T_REPEAT; return 1; }
    if (strcmp(word, "until") == 0) { *type = T_UNTIL; return 1; }
    if (strcmp(word, "do") == 0) { *type = T_DO; return 1; }
    if (strcmp(word, "break") == 0) { *type = T_BREAK; return 1; }
    if (strcmp(word, "continue") == 0) { *type = T_CONTINUE; return 1; }
    if (strcmp(word, "define") == 0) { *type = T_DEFINE; return 1; }
    if (strcmp(word, "function") == 0) { *type = T_FUNCTION; return 1; }
    if (strcmp(word, "end") == 0) { *type = T_END; return 1; }
    if (strcmp(word, "with") == 0) { *type = T_WITH; return 1; }
    if (strcmp(word, "returns") == 0) { *type = T_RETURNS; return 1; }
    if (strcmp(word, "and") == 0) { *type = T_AND; return 1; }
    if (strcmp(word, "or") == 0) { *type = T_OR; return 1; }
    if (strcmp(word, "not") == 0) { *type = T_NOT; return 1; }
    if (strcmp(word, "true") == 0) { *type = T_TRUE; return 1; }
    if (strcmp(word, "false") == 0) { *type = T_FALSE; return 1; }
    if (strcmp(word, "ask") == 0) { *type = T_ASK; return 1; }
    if (strcmp(word, "print") == 0) { *type = T_PRINT; return 1; }
    if (strcmp(word, "run") == 0) { *type = T_RUN; return 1; }
    if (strcmp(word, "match") == 0) { *type = T_MATCH; return 1; }
    if (strcmp(word, "case") == 0) { *type = T_CASE; return 1; }
    if (strcmp(word, "endmatch") == 0 || strcmp(word, "end_match") == 0) { *type = T_END_MATCH; return 1; }
    if (strcmp(word, "try") == 0) { *type = T_TRY; return 1; }
    if (strcmp(word, "catch") == 0) { *type = T_CATCH; return 1; }
    if (strcmp(word, "endtry") == 0 || strcmp(word, "end_try") == 0) { *type = T_END_TRY; return 1; }
    if (strcmp(word, "into") == 0) { *type = T_INTO; return 1; }
    if (strcmp(word, "number") == 0) { *type = T_TYPE_NUM; return 1; }
    if (strcmp(word, "text") == 0) { *type = T_TYPE_TEXT; return 1; }
    if (strcmp(word, "boolean") == 0) { *type = T_TYPE_BOOL; return 1; }
    return 0;
}

// Main tokenizer
void tokenize(FILE* source) {
    char ch;
    while ((ch = fgetc(source)) != EOF) {
        if (isspace(ch)) {
            if (ch == '\n') line++;
            continue;
        }

        if (ch == '#') {
            while ((ch = fgetc(source)) != EOF && ch != '\n');
            line++;
            continue;
        }

        if (isalpha(ch) || ch == '_') {
            char buffer[MAX_TOKEN_LEN];
            int i = 0;
            buffer[i++] = ch;
            while (isalnum(ch = fgetc(source)) || ch == '_') {
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            ungetc(ch, source);

            TokenType type;
            if (isKeyword(buffer, &type)) {
                printToken(type, buffer);
            } else {
                printToken(T_ID, buffer);
            }
        }

        else if (isdigit(ch)) {
            char buffer[MAX_TOKEN_LEN];
            int i = 0;
            int hasDot = 0;
            buffer[i++] = ch;
            while (isdigit(ch = fgetc(source)) || (ch == '.' && !hasDot)) {
                if (ch == '.') hasDot = 1;
                buffer[i++] = ch;
            }
            buffer[i] = '\0';
            ungetc(ch, source);

            printToken(hasDot ? T_RNUM : T_NUM, buffer);
        }

        else if (ch == '"') {
            char buffer[MAX_TOKEN_LEN];
            int i = 0;
            buffer[i++] = ch;
            while ((ch = fgetc(source)) != EOF && ch != '"') {
                buffer[i++] = ch;
            }
            buffer[i++] = '"';
            buffer[i] = '\0';

            printToken(T_STRING, buffer);
        }

        else {
            switch (ch) {
                case '+': printToken(T_PLUS, "+"); break;
                case '-': printToken(T_MINUS, "-"); break;
                case '*': printToken(T_MUL, "*"); break;
                case '/': printToken(T_DIV, "/"); break;
                case ';': printToken(T_SEMI, ";"); break;
                case ',': printToken(T_COMMA, ","); break;
                case '(': printToken(T_LPAREN, "("); break;
                case ')': printToken(T_RPAREN, ")"); break;
                case '{': printToken(T_LBRACE, "{"); break;
                case '}': printToken(T_RBRACE, "}"); break;
                case '[': printToken(T_LBRACKET, "["); break;
                case ']': printToken(T_RBRACKET, "]"); break;
                case ':': printToken(T_COLON, ":"); break;
                default: {
                    char unknown[2] = {ch, '\0'};
                    printToken(T_UNKNOWN, unknown);
                    break;
                }
            }
        }
    }
}

// Entry Point
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: ./custom_lexer <source_file>\n");
        return 1;
    }

    FILE* source = fopen(argv[1], "r");
    if (!source) {
        perror("File open failed");
        return 1;
    }

    tokenize(source);
    fclose(source);
    return 0;
}
