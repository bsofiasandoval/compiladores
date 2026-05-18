%{
#include <iostream>
#include <string>
#include <vector>
#include "funcDir.h"
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

%token PROGRAMA INICIO FIN VARS NULA ENTERO FLOTANTE
%token SI SINO MIENTRAS HAZ ESCRIBE
%token ASIGNACION PUNTOYCOMA DOSPUNTOS COMA
%token PARENIZQ PARENDER LLAVEIZQ LLAVEDER CORCHETEIZQ CORCHETEDER
%token IGUAL DIFERENTE MENORQUE MAYORQUE
%token MAS MENOS POR ENTRE

%token <ival> CTE_ENT
%token <fval> CTE_FLOT
%token <sval> ID LETRERO
%type <sval> tipo

%left MAS MENOS
%left POR ENTRE

%%

programa:
    PROGRAMA ID PUNTOYCOMA
    {
        dirFunc.insert("global", FuncEntry("nula"));
        scopeActual = "global";
    }
    programa_p programa_pp INICIO cuerpo FIN
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
    ID
    {
        idStack.push_back($1);
    }
    vars_pp DOSPUNTOS tipo PUNTOYCOMA
    {
        cerr << "Insertando variables con tipo: " << $5 << endl;
        for (auto& id : idStack) {
            cerr << "  Insertando: " << id << endl;
            try {
                dirFunc.get(scopeActual).varTable.vars.insert(id, $5);
            } catch (runtime_error&) {
                yyerror("Variable doblemente declarada");
                YYABORT;
            }
        }
        idStack.clear();
    }
    vars_p
    |
;

vars_pp:
    COMA ID
    {
        idStack.push_back($2);
    }
    vars_pp
    |
;

tipo:
    ENTERO   { $$ = strdup("entero"); }
    | FLOTANTE { $$ = strdup("flotante"); }
;

funcs:
    NULA ID
    {
        try {
            dirFunc.insert($2, FuncEntry("nula"));
        } catch (runtime_error&) {
            yyerror("Función doblemente declarada");
            YYABORT;
        }
        scopeActual = $2;
    }
    PARENIZQ funcs_p PARENDER LLAVEIZQ funcs_pp cuerpo LLAVEDER PUNTOYCOMA
    { scopeActual = "global"; }

    | tipo ID
    {
        try {
            dirFunc.insert($2, FuncEntry($1));
        } catch (runtime_error&) {
            yyerror("Función doblemente declarada");
            YYABORT;
        }
        scopeActual = $2;
    }
    PARENIZQ funcs_p PARENDER LLAVEIZQ funcs_pp cuerpo LLAVEDER PUNTOYCOMA
    { scopeActual = "global"; }
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
    cout << "Ingresa tu programa:" << endl;
    yyparse();
    return 0;
}