%{
#include <iostream>
#include <string>
#include <vector>
#include "FuncDir.h"
#include "SemanticCube.h"
#include "QuadrupleBuilder.h"
#include "Stack.h"
using namespace std;

void yyerror(const char* s) {
    cerr << "Error sintáctico: " << s << endl;
}
int yylex();

SemanticCube cube;

Stack<string> operators;
Stack<string> vars;
Stack<string> types;
QuadrupleBuilder quadruples;

void makeQuadruple() {
    string op = operators.getTop(); operators.pop();
    string varDer = vars.getTop(); vars.pop();
    string tipoDer = types.getTop(); types.pop();
    string varIzq = vars.getTop(); vars.pop();
    string tipoIzq = types.getTop(); types.pop();

   

    if(op == "="){
        quadruples.add(op, varDer, "_", varIzq);
    } 
    else {
        string tipoRes = cube.validate(tipoIzq, tipoDer, op);
        string tempNum = quadruples.newTemp(); // numero de temporal "t1, t2, etc."
        quadruples.add(op,varIzq, varDer, tempNum);
        vars.push(tempNum);
        types.push(tipoRes);
    }
}

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
    ID 
    {
        vars.push($1);
        string t = dirFunc.get(scopeActual).varTable.vars.get($1);
        types.push(t);
    }
    ASIGNACION { operators.push("=");} expresion { makeQuadruple(); }
    PUNTOYCOMA
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
    expresion 
    {
        string var = vars.getTop(); vars.pop();
        types.pop();
        quadruples.add("PRINT", var, "_", "_");
    }
    imprime_pp
    | LETRERO
    {
        quadruples.add("PRINT", $1, "_","_");
    }
    imprime_pp
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
    MAYORQUE { operators.push(">");} exp { makeQuadruple();}
    | MENORQUE { operators.push("<");} exp { makeQuadruple();}
    | DIFERENTE { operators.push("!=");}  exp { makeQuadruple();}
    | IGUAL { operators.push("==");} exp { makeQuadruple();}
    |
;

exp:
    termino exp_p
;

exp_p:
    MAS { operators.push("+");} termino { makeQuadruple();} exp_p
    | MENOS  { operators.push("-");} termino  { makeQuadruple();} exp_p
    |
;

termino:
    factor termino_p
;

termino_p:
    POR  { operators.push("*");} factor  { makeQuadruple();} termino_p
    | ENTRE  { operators.push("/");}factor  { makeQuadruple();} termino_p
    |
;

factor:
    PARENIZQ expresion PARENDER
    | llamada
    | ID
    {
        vars.push($1);
        string type = dirFunc.get(scopeActual).varTable.vars.get($1);
        types.push(type);
    }
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
    {
        vars.push(to_string($1));
        types.push("entero");
    }
    | CTE_FLOT
    {
        vars.push(to_string($1));
        types.push("flotante");
    }
;

%%

int main() {
    cout << "Ingresa tu programa:" << endl;
    yyparse();
    quadruples.print();
    return 0;
}