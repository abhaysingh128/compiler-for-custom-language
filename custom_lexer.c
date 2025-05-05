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
// AST AND PARSER

extern int yylex();
extern int line;
extern char *yytext;

int lookahead;

// AST node types
typedef enum {
    AST_VAR_DECL,
    AST_ASSIGN,
    AST_LITERAL,
    AST_BINARY_OP,
    AST_IDENTIFIER,
    AST_IF_STATEMENT
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    union {
        // Variable declaration
        struct {
            char *id;
            char *typeStr;
        } varDecl;

        // Assignment
        struct {
            char *id;
            struct ASTNode *expr;
        } assign;

        // Literal
        char *literal;

        // Binary expression
        struct {
            char *op;
            struct ASTNode *left;
            struct ASTNode *right;
        } binary;

        // Identifier
        char *id;

        // If statement
        struct {
            struct ASTNode *condition;
            struct ASTNode *thenBranch;
            struct ASTNode *elseBranch;
        } ifStmt;
    };
} ASTNode;

void syntax_error(const char *msg) {
    fprintf(stderr, "Syntax Error at line %d: %s (token '%s')\n", line, msg, yytext);
    exit(EXIT_FAILURE);
}

ASTNode* parse_expression();  // Forward declaration

void match(int expected) {
    if (lookahead == expected) {
        lookahead = yylex();
    } else {
        char errorMsg[100];
        sprintf(errorMsg, "Expected token %s", tokenNames[expected]);
        syntax_error(errorMsg);
    }
}

ASTNode* new_var_decl(char *id, char *typeStr) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_VAR_DECL;
    node->varDecl.id = strdup(id);
    node->varDecl.typeStr = strdup(typeStr);
    return node;
}

ASTNode* new_assign(char *id, ASTNode *expr) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_ASSIGN;
    node->assign.id = strdup(id);
    node->assign.expr = expr;
    return node;
}

ASTNode* new_literal(char *val) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_LITERAL;
    node->literal = strdup(val);
    return node;
}

ASTNode* new_identifier(char *name) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_IDENTIFIER;
    node->id = strdup(name);
    return node;
}

ASTNode* new_binary_op(char *op, ASTNode *left, ASTNode *right) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_BINARY_OP;
    node->binary.op = strdup(op);
    node->binary.left = left;
    node->binary.right = right;
    return node;
}

ASTNode* parse_primary() {
    ASTNode *node = NULL;
    if (lookahead == T_NUM || lookahead == T_RNUM || lookahead == T_STRING || lookahead == T_TRUE || lookahead == T_FALSE) {
        node = new_literal(yytext);
        match(lookahead);
    } else if (lookahead == T_ID) {
        node = new_identifier(yytext);
        match(T_ID);
    } else {
        syntax_error("Expected a primary expression");
    }
    return node;
}

ASTNode* parse_expression() {
    ASTNode *left = parse_primary();
    while (lookahead == T_PLUS || lookahead == T_MINUS || lookahead == T_MUL || lookahead == T_DIV) {
        char op[2] = {yytext[0], '\0'};
        int currentOp = lookahead;
        match(currentOp);
        ASTNode *right = parse_primary();
        left = new_binary_op(op, left, right);
    }
    return left;
}

ASTNode* parse_var_decl() {
    match(T_LET);
    if (lookahead != T_ID) syntax_error("Expected identifier after 'let'");
    char *id = strdup(yytext);
    match(T_ID);
    match(T_BE);
    if (lookahead != T_TYPE_NUM && lookahead != T_TYPE_TEXT && lookahead != T_TYPE_BOOL)
        syntax_error("Expected type after 'be'");
    char *typeStr = strdup(tokenNames[lookahead]);
    match(lookahead);
    match(T_SEMI);
    return new_var_decl(id, typeStr);
}

ASTNode* parse_assignment() {
    match(T_SET);
    if (lookahead != T_ID) syntax_error("Expected identifier after 'set'");
    char *id = strdup(yytext);
    match(T_ID);
    match(T_IS);
    ASTNode *expr = parse_expression();
    match(T_SEMI);
    return new_assign(id, expr);
}
ASTNode* new_if_statement(ASTNode *condition, ASTNode *thenBranch, ASTNode *elseBranch) {
    ASTNode *node = malloc(sizeof(ASTNode));
    node->type = AST_IF_STATEMENT;
    node->ifStmt.condition = condition;
    node->ifStmt.thenBranch = thenBranch;
    node->ifStmt.elseBranch = elseBranch;
    return node;
}

ASTNode* parse_if_statement() {
    match(T_IF);
    ASTNode *condition = parse_expression();
    match(T_THEN);
    ASTNode *thenBranch = parse_assignment();  // You can later expand this to support blocks
    ASTNode *elseBranch = NULL;
    if (lookahead == T_ELSE) {
        match(T_ELSE);
        elseBranch = parse_assignment();
    }
    return new_if_statement(condition, thenBranch, elseBranch);
}


void print_ast(ASTNode *node, int indent) {
    if (!node) return;
    for (int i = 0; i < indent; i++) printf("  ");
    switch (node->type) {
        case AST_VAR_DECL:
            printf("VarDecl: %s : %s\n", node->varDecl.id, node->varDecl.typeStr);
            break;
        case AST_ASSIGN:
            printf("Assign: %s = \n", node->assign.id);
            print_ast(node->assign.expr, indent + 1);
            break;
        case AST_LITERAL:
            printf("Literal: %s\n", node->literal);
            break;
        case AST_IDENTIFIER:
            printf("Identifier: %s\n", node->id);
            break;
        case AST_BINARY_OP:
            printf("BinaryOp: %s\n", node->binary.op);
            print_ast(node->binary.left, indent + 1);
            print_ast(node->binary.right, indent + 1);
            break;
        case AST_IF_STATEMENT:
            printf("IfStatement:\n");
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Condition:\n");
            print_ast(node->ifStmt.condition, indent + 2);
            for (int i = 0; i < indent + 1; i++) printf("  ");
            printf("Then:\n");
            print_ast(node->ifStmt.thenBranch, indent + 2);
            if (node->ifStmt.elseBranch) {
                for (int i = 0; i < indent + 1; i++) printf("  ");
                printf("Else:\n");
                print_ast(node->ifStmt.elseBranch, indent + 2);
            }
            break;

        default:
            printf("Unknown AST Node\n");
    }
}

extern FILE *yyin;
extern int yylex();
extern char *yytext;
extern int lookahead;

void syntax_error(const char *msg);
ASTNode* parse_var_decl();
ASTNode* parse_assignment();
ASTNode* parse_if_statement();
void print_ast(ASTNode *node, int indent);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: ./custom_parser <source_file>\n");
        return 1;
    }

    FILE* source = fopen(argv[1], "r");
    if (!source) {
        perror("File open failed");
        return 1;
    }

    yyin = source;               // Direct Flex lexer to read from file
    lookahead = yylex();         // Start lexing

    while (lookahead != 0) {
        ASTNode *stmt = NULL;
        if (lookahead == T_LET) {
            stmt = parse_var_decl();
        } else if (lookahead == T_SET) {
            stmt = parse_assignment();
        } else if (lookahead == T_IF) {
            stmt = parse_if_statement();
        } else {
            syntax_error("Unknown statement type");
        }
        print_ast(stmt, 0);
        // Free memory if needed
    }

    fclose(source);
    return 0;
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
