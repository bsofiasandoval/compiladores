%{
#include <iostream>
#include <string>
using namespace std;

void yyerror(const char* s) {
    cerr << "Error sintáctico: " << s << endl;
}
int yylex();
%}

%union {
    int ival;
    float fval;
    char* sval;
}

/* tokens simples */
%token PROGRAMA INICIO FIN VARS NULA ENTERO FLOTANTE
%token SI SINO MIENTRAS HAZ ESCRIBE
%token ASSIGN SEMICOLON COLON COMMA
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token EQ NEQ LT GT
%token PLUS MINUS TIMES DIVIDE

%token <ival> CTE_ENT
%token <fval> CTE_FLOT
%token <sval> ID LETRERO

/* precedencia */
%left PLUS MINUS
%left TIMES DIVIDE

%%

programa:
    PROGRAMA ID SEMICOLON programa_p programa_pp INICIO cuerpo FIN
    { cout << "Programa válido!" << endl; }
;

programa_p:
    vars
    |
;

programa_pp:
    funcs programa_pp
    |
;

vars:
    VARS vars_p
;

vars_p:
    ID vars_pp COLON tipo SEMICOLON vars_p
    |
;

vars_pp:
    COMMA ID vars_pp
    |
;

tipo:
    ENTERO 
    | FLOTANTE
;

funcs:
    NULA ID LPAREN funcs_p RPAREN LBRACE funcs_pp cuerpo RBRACE SEMICOLON
    | tipo ID LPAREN funcs_p RPAREN LBRACE funcs_pp cuerpo RBRACE SEMICOLON
;

funcs_p:
    ID COLON tipo funcs_ppp
    |
;

funcs_pp:
    vars
    |
;

funcs_ppp:
    COMMA ID COLON tipo funcs_ppp
    |
;

cuerpo:
    LBRACE cuerpo_p RBRACE
;

cuerpo_p:
    estatuto cuerpo_p
    |
;

estatuto:
    asigna
    | condicion
    | ciclo
    | llamada SEMICOLON
    | imprime
    | LBRACKET estatuto_p RBRACKET
;

estatuto_p:
    estatuto estatuto_p
    |
;

asigna:
    ID ASSIGN expresion SEMICOLON
;

llamada:
    ID LPAREN llamada_p RPAREN
;

llamada_p:
    expresion llamada_pp
    |
;

llamada_pp:
    COMMA llamada_p
;

imprime:
    ESCRIBE LPAREN imprime_p RPAREN SEMICOLON
;

imprime_p:
    expresion imprime_pp
    | LETRERO imprime_pp
;

imprime_pp:
    COMMA imprime_p
    |
;

condicion:
    SI LPAREN expresion RPAREN cuerpo condicion_p SEMICOLON
;

condicion_p:
    SINO cuerpo
    |
;

ciclo:
    MIENTRAS LPAREN expresion RPAREN HAZ cuerpo SEMICOLON
;

expresion:
    exp expresion_p
;

expresion_p:
    GT exp
    | LT exp
    | NEQ exp
    | EQ exp
    |
;

exp:
    termino exp_p
;

exp_p:
    PLUS termino exp_p
    | MINUS termino exp_p
    |
;

termino:
    factor termino_p
;

termino_p:
    TIMES factor termino_p
    | DIVIDE factor termino_p
    |
;

factor:
    LPAREN expresion RPAREN
    | llamada
    | ID
    | cte
    | PLUS factor_p
    | MINUS factor_p
;

factor_p:
    ID
    | cte
;

cte:
    CTE_ENT
    | CTE_FLOT
;
%%

int main() {
    { cout << "Ingresa tu programa:" << endl; }
    yyparse();
    return 0;
}