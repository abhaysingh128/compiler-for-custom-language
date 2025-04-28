#ifndef TOKENS_H
#define TOKENS_H

// All token types for your custom human-readable language
typedef enum {
    T_LET, T_BE, T_SET, T_IS, T_NULL,
    T_IF, T_THEN, T_ELSE, T_RETURN,
    T_WHILE, T_REPEAT, T_UNTIL, T_DO,
    T_BREAK, T_CONTINUE,
    T_DEFINE, T_FUNCTION, T_END, T_WITH, T_RETURNS,

    T_AND, T_OR, T_NOT,
    T_TRUE, T_FALSE,

    T_EQ, T_NEQ, T_GT, T_LT,

    T_ASK, T_PRINT, T_RUN,

    T_MATCH, T_CASE, T_END_MATCH,
    T_TRY, T_CATCH, T_END_TRY,

    T_INTO,

    T_TYPE_NUM, T_TYPE_TEXT, T_TYPE_BOOL,

    T_PLUS, T_MINUS, T_MUL, T_DIV,
    T_LPAREN, T_RPAREN, T_SEMI, T_COMMA,
    T_LBRACE, T_RBRACE, T_LBRACKET, T_RBRACKET,
    T_COLON,

    T_STRING, T_NUM, T_RNUM, T_ID,

    T_UNKNOWN
} TokenType;

// Optional: Names for printing
static const char* tokenNames[] = {
    "LET", "BE", "SET", "IS", "NULL",
    "IF", "THEN", "ELSE", "RETURN",
    "WHILE", "REPEAT", "UNTIL", "DO",
    "BREAK", "CONTINUE",
    "DEFINE", "FUNCTION", "END", "WITH", "RETURNS",
    "AND", "OR", "NOT",
    "TRUE", "FALSE",
    "EQ", "NEQ", "GT", "LT",
    "ASK", "PRINT", "RUN",
    "MATCH", "CASE", "END_MATCH",
    "TRY", "CATCH", "END_TRY",
    "INTO",
    "TYPE_NUM", "TYPE_TEXT", "TYPE_BOOL",
    "PLUS", "MINUS", "MUL", "DIV",
    "LPAREN", "RPAREN", "SEMI", "COMMA",
    "LBRACE", "RBRACE", "LBRACKET", "RBRACKET",
    "COLON",
    "STRING", "NUM", "RNUM", "ID",
    "UNKNOWN"
};

#endif // TOKENS_H
