%{
#include <string>
#include "parser.tab.h"
using namespace std;
%}

%%

[ \t\n\r]
"//.*"

"programa" { return PROGRAMA; }
"inicio" { return INICIO; }
"fin" { return FIN; }
"vars" { return VARS; }
"entero" { return ENTERO; }
"flotante" { return FLOTANTE; }
"nula" { return NULA; }
"si" { return SI; }
"sino" { return SINO; }
"mientras" { return MIENTRAS; }
"haz" { return HAZ; }
"escribe" { return ESCRIBE; }

[0-9]+\.[0-9]+  { yylval.fval = atof(yytext); return CTE_FLOT; }
[0-9]+          { yylval.ival = atoi(yytext); return CTE_ENT; }
\"[^\"]*\"      { yylval.sval = strdup(yytext); return LETRERO; }
[a-zA-Z][a-zA-Z0-9]*  { yylval.sval = strdup(yytext); return ID; }

"=="    { return EQ; }
"!="    { return NEQ; }
"="     { return ASSIGN; }
"<"     { return LT; }
">"     { return GT; }
"+"     { return PLUS; }
"-"     { return MINUS; }
"*"     { return TIMES; }
"/"     { return DIVIDE; }
";"     { return SEMICOLON; }
":"     { return COLON; }
","     { return COMMA; }
"("     { return LPAREN; }
")"     { return RPAREN; }
"{"     { return LBRACE; }
"}"     { return RBRACE; }
"["     { return LBRACKET; }
"]"     { return RBRACKET; }

.       { printf("Error léxico: %s\n", yytext); }

%%

int yywrap() { return 1; }