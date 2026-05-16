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
%token ASIGNACION PUNTOYCOMA DOSPUNTOS COMA
%token PARENIZQ PARENDER LLAVEIZQ LLAVEDER CORCHETEIZQ CORCHETEDER
%token IGUAL DIFERENTE MENORQUE MAYORQUE
%token MAS MENOS POR ENTRE

%token <ival> CTE_ENT
%token <fval> CTE_FLOT
%token <sval> ID LETRERO

/* precedencia */
%left MAS MENOS
%left POR ENTRE

%%

programa:
    PROGRAMA ID PUNTOYCOMA programa_p programa_pp INICIO cuerpo FIN
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
    ID vars_pp DOSPUNTOS tipo PUNTOYCOMA vars_p
    |
;

vars_pp:
    COMA ID vars_pp
    |
;

tipo:
    ENTERO 
    | FLOTANTE
;

funcs:
    NULA ID PARENIZQ funcs_p PARENDER LLAVEIZQ funcs_pp cuerpo LLAVEDER PUNTOYCOMA
    | tipo ID PARENIZQ funcs_p PARENDER LLAVEIZQ funcs_pp cuerpo LLAVEDER PUNTOYCOMA
;

funcs_p:
    ID DOSPUNTOS tipo funcs_ppp
    |
;

funcs_pp:
    vars
    |
;

funcs_ppp:
    COMA ID DOSPUNTOS tipo funcs_ppp
    |
;

cuerpo:
    LLAVEIZQ cuerpo_p LLAVEDER
;

cuerpo_p:
    estatuto cuerpo_p
    |
;

estatuto:
    asigna
    | condicion
    | ciclo
    | llamada PUNTOYCOMA
    | imprime
    | CORCHETEIZQ estatuto_p CORCHETEDER
;

estatuto_p:
    estatuto estatuto_p
    |
;

asigna:
    ID ASIGNACION expresion PUNTOYCOMA
;

llamada:
    ID PARENIZQ llamada_p PARENDER
;

llamada_p:
    expresion llamada_pp
    |
;

llamada_pp:
    COMA llamada_p
;

imprime:
    ESCRIBE PARENIZQ imprime_p PARENDER PUNTOYCOMA
;

imprime_p:
    expresion imprime_pp
    | LETRERO imprime_pp
;

imprime_pp:
    COMA imprime_p
    |
;

condicion:
    SI PARENIZQ expresion PARENDER cuerpo condicion_p PUNTOYCOMA
;

condicion_p:
    SINO cuerpo
    |
;

ciclo:
    MIENTRAS PARENIZQ expresion PARENDER HAZ cuerpo PUNTOYCOMA
;

expresion:
    exp expresion_p
;

expresion_p:
    MAYORQUE exp
    | MENORQUE exp
    | DIFERENTE exp
    | IGUAL exp
    |
;

exp:
    termino exp_p
;

exp_p:
    MAS termino exp_p
    | MENOS termino exp_p
    |
;

termino:
    factor termino_p
;

termino_p:
    POR factor termino_p
    | ENTRE factor termino_p
    |
;

factor:
    PARENIZQ expresion PARENDER
    | llamada
    | ID
    | cte
    | MAS factor_p
    | MENOS factor_p
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