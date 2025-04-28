%{
#include <stdio.h>
#include <string.h>
#include "tokens.h"

int line = 1; 
extern FILE *yyin; 
%}
%option noyywrap

DIGIT     [0-9]
ID        [a-zA-Z_][a-zA-Z0-9_]*
STRING    \"([^\n\"]|\\.)*\"
WHITESPACE [ \t]+
NEWLINE   \n
%%

#.*                             {/*skip comment*/}
{NEWLINE}                       { line++; }
{WHITESPACE}                    { /*skip whitespace*/}


"is equal to"                   { printf("Found token: T_EQ\n"); return T_EQ; }
"is not"                        { printf("Found token: T_NEQ\n"); return T_NEQ; }
"is greater than"               { printf("Found token: T_GT\n"); return T_GT; }
"is less than"                  { printf("Found token: T_LT\n"); return T_LT; }


"let"                           { printf("Found token: T_LET\n"); return T_LET; }
"be"                            { printf("Found token: T_BE\n"); return T_BE; }
"set"                           { printf("Found token: T_SET\n"); return T_SET; }
"is"                            { printf("Found token: T_IS\n");return T_IS; }
"null"                          { printf("Found token: T_NULL\n");return T_NULL; }

"if"                            { printf("Found token: T_IF\n"); return T_IF; }
"then"                          { printf("Found token: T_THEN\n"); return T_THEN; }
"else"                          { printf("Found token: T_ELSE\n"); return T_ELSE; }
"return"|"give"                 { printf("Found token: T_RETURN\n"); return T_RETURN; }

"while"                         { printf("Found token: T_WHILE\n"); return T_WHILE; }
"repeat"                        { printf("Found token: T_REPEAT\n"); return T_REPEAT; }
"until"                         { printf("Found token: T_UNTIL\n"); return T_UNTIL; }
"do"                            { printf("Found token: T_DO\n"); return T_DO; }
"break"                         { printf("Found token: T_BREAK\n"); return T_BREAK; }
"continue"                      { printf("Found token: T_CONTINUE\n"); return T_CONTINUE; }

"define"                        { printf("Found token: T_DEFINE\n"); return T_DEFINE; }
"function"                      { printf("Found token: T_FUNCTION\n"); return T_FUNCTION; }
"end"                           { printf("Found token: T_END\n"); return T_END; }
"with"                          { printf("Found token: T_WITH\n"); return T_WITH; }
"returns"                       { printf("Found token: T_RETURNS\n"); return T_RETURNS; }

"and"                           { printf("Found token: T_AND\n"); return T_AND; }
"or"                            { printf("Found token: T_OR\n"); return T_OR; }
"not"                           { printf("Found token: T_NOT\n"); return T_NOT; }

"true"                          { printf("Found token: T_TRUE\n"); return T_TRUE; }
"false"                         { printf("Found token: T_FALSE\n"); return T_FALSE; }

"ask"                           { printf("Found token: T_ASK\n"); return T_ASK; }
"print"                         { printf("Found token: T_PRINT\n"); return T_PRINT; }
"run"                           { printf("Found token: T_RUN\n"); return T_RUN; }

"match"                         { printf("Found token: T_MATCH\n"); return T_MATCH; }
"case"                          { printf("Found token: T_CASE\n"); return T_CASE; }
"endmatch"|"end_match"          { printf("Found token: T_END_MATCH\n"); return T_END_MATCH; }

"try"                           { printf("Found token: T_TRY\n"); return T_TRY; }
"catch"                         { printf("Found token: T_CATCH\n"); return T_CATCH; }
"endtry"|"end_try"              { printf("Found token: T_END_TRY\n"); return T_END_TRY; }

"into"                          { printf("Found token: T_INTO\n"); return T_INTO; }

"number"                        { printf("Found token: T_TYPE_NUM\n"); return T_TYPE_NUM; }
"text"                          { printf("Found token: T_TYPE_TEXT\n"); return T_TYPE_TEXT; }
"boolean"                       { printf("Found token: T_TYPE_BOOL\n"); return T_TYPE_BOOL; }


"+"                             { printf("Found token: T_PLUS\n"); return T_PLUS; }
"-"                             { printf("Found token: T_MINUS\n"); return T_MINUS; }
"*"                             { printf("Found token: T_MUL\n"); return T_MUL; }
"/"                             { printf("Found token: T_DIV\n"); return T_DIV; }
"("                             { printf("Found token: T_LPAREN\n"); return T_LPAREN; }
")"                             { printf("Found token: T_RPAREN\n"); return T_RPAREN; }
";"                             { printf("Found token: T_SEMI\n"); return T_SEMI; }
","                             { printf("Found token: T_COMMA\n"); return T_COMMA; }
"["                             { printf("Found token: T_LBRACKET\n"); return T_LBRACKET; }
"]"                             { printf("Found token: T_RBRACKET\n"); return T_RBRACKET; }
"{"                             { printf("Found token: T_LBRACE\n"); return T_LBRACE; }
"}"                             { printf("Found token: T_RBRACE\n"); return T_RBRACE; }
":"                             { printf("Found token: T_COLON\n"); return T_COLON; }


{STRING}                        { printf("Found token: T_STRING (%s)\n", yytext); return T_STRING; }
{DIGIT}+"."{DIGIT}+             { printf("Found token: T_RNUM (%s)\n", yytext); return T_RNUM; }
{DIGIT}+                        { printf("Found token: T_NUM (%s)\n", yytext); return T_NUM; }
{ID}                            { printf("Found token: T_ID (%s)\n", yytext); return T_ID; }

.                               { printf("Line %d: Unknown token '%s'\n", line, yytext); return T_UNKNOWN; }

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");  // Open the file for reading
        if (!yyin) {
            fprintf(stderr, "Could not open input file: %s\n", argv[1]);
            return 1;
        }
    }
    int token;
    while(token)
    {
    yylex();  // Start lexical analysis
    }
    return 0;
}


