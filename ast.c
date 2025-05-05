#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ASTNode* create_var_decl(char* id, char* type_name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_VAR_DECL;
    node->var_decl.id = strdup(id);
    node->var_decl.type_name = strdup(type_name);
    return node;
}

ASTNode* create_assignment(char* id, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_ASSIGN;
    node->assignment.id = strdup(id);
    node->assignment.value = value;
    return node;
}

ASTNode* create_literal(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_LITERAL;
    node->literal.value = value;
    return node;
}

ASTNode* create_binary_expr(ASTNode* left, char op, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_BINARY_EXPR;
    node->binary_expr.left = left;
    node->binary_expr.op = op;
    node->binary_expr.right = right;
    return node;
}

ASTNode* create_identifier(char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_IDENTIFIER;
    node->identifier.name = strdup(name);
    return node;
}

ASTNode* create_print_stmt(ASTNode* expr) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_PRINT_STMT;
    node->print_stmt.expr = expr;
    return node;
}

ASTNode* create_if_stmt(ASTNode* cond, ASTNode* then_b, ASTNode* else_b) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_IF_STMT;
    node->if_stmt.condition = cond;
    node->if_stmt.then_branch = then_b;
    node->if_stmt.else_branch = else_b;
    return node;
}

void print_indent(int indent) {
    for (int i = 0; i < indent; ++i) printf("  ");
}

void print_ast(ASTNode* root, int indent) {
    if (!root) return;

    switch (root->type) {
        case AST_VAR_DECL:
            print_indent(indent);
            printf("VarDecl: %s : %s\n", root->var_decl.id, root->var_decl.type_name);
            break;
        case AST_ASSIGN:
            print_indent(indent);
            printf("Assignment: %s = \n", root->assignment.id);
            print_ast(root->assignment.value, indent + 1);
            break;
        case AST_LITERAL:
            print_indent(indent);
            printf("Literal: %d\n", root->literal.value);
            break;
        case AST_BINARY_EXPR:
            print_indent(indent);
            printf("BinaryExpr: %c\n", root->binary_expr.op);
            print_ast(root->binary_expr.left, indent + 1);
            print_ast(root->binary_expr.right, indent + 1);
            break;
        case AST_IDENTIFIER:
            print_indent(indent);
            printf("Identifier: %s\n", root->identifier.name);
            break;
        case AST_PRINT_STMT:
            print_indent(indent);
            printf("Print:\n");
            print_ast(root->print_stmt.expr, indent + 1);
            break;
        case AST_IF_STMT:
            print_indent(indent);
            printf("IfStmt:\n");
            print_indent(indent + 1); printf("Condition:\n");
            print_ast(root->if_stmt.condition, indent + 2);
            print_indent(indent + 1); printf("Then:\n");
            print_ast(root->if_stmt.then_branch, indent + 2);
            print_indent(indent + 1); printf("Else:\n");
            print_ast(root->if_stmt.else_branch, indent + 2);
            break;
    }
}
