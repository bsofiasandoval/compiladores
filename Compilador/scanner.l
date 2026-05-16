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

"=="    { return IGUAL; }
"!="    { return DIFERENTE; }
"="     { return ASIGNACION; }
"<"     { return MENORQUE; }
">"     { return MAYORQUE; }
"+"     { return MAS; }
"-"     { return MENOS; }
"*"     { return POR; }
"/"     { return ENTRE; }
";"     { return PUNTOYCOMA; }
":"     { return DOSPUNTOS; }
","     { return COMA; }
"("     { return PARENIZQ; }
")"     { return PARENDER; }
"{"     { return LLAVEIZQ; }
"}"     { return LLAVEDER; }
"["     { return CORCHETEIZQ; }
"]"     { return CORCHETEDER; }

.       { printf("Error léxico: %s\n", yytext); }

%%

int yywrap() { return 1; }