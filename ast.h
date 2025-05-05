#ifndef AST_H
#define AST_H

typedef enum {
    AST_VAR_DECL,
    AST_ASSIGN,
    AST_LITERAL,
    AST_BINARY_EXPR,
    AST_IDENTIFIER,
    AST_PRINT_STMT,
    AST_IF_STMT
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    union {
        struct {
            char* id;
            char* type_name;
        } var_decl;

        struct {
            char* id;
            struct ASTNode* value;
        } assignment;

        struct {
            int value;
        } literal;

        struct {
            struct ASTNode* left;
            char op;  // '+', '-', etc.
            struct ASTNode* right;
        } binary_expr;

        struct {
            char* name;
        } identifier;

        struct {
            struct ASTNode* expr;
        } print_stmt;

        struct {
            struct ASTNode* condition;
            struct ASTNode* then_branch;
            struct ASTNode* else_branch;
        } if_stmt;
    };
} ASTNode;

// AST constructors
ASTNode* create_var_decl(char* id, char* type_name);
ASTNode* create_assignment(char* id, ASTNode* value);
ASTNode* create_literal(int value);
ASTNode* create_binary_expr(ASTNode* left, char op, ASTNode* right);
ASTNode* create_identifier(char* name);
ASTNode* create_print_stmt(ASTNode* expr);
ASTNode* create_if_stmt(ASTNode* cond, ASTNode* then_b, ASTNode* else_b);

void print_ast(ASTNode* root, int indent);

#endif
