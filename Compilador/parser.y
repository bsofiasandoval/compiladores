%{
#include <iostream>
#include <string>
#include <vector>
#include "FuncDir.h"
#include "SemanticCube.h"
#include "QuadrupleBuilder.h"
#include "Memory.h"
#include "Stack.h"
using namespace std;

void yyerror(const char* s) {
    cerr << "Error sintáctico: " << s << endl;
}
int yylex();

SemanticCube cube;
MemoryManager memory;

Stack<string> operators;
Stack<string> vars;
Stack<string> types;
Stack<int> jumps;
QuadrupleBuilder quadruples;
string callTarget = "";
int paramCount = 0;

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
        string tempAddr = to_string(memory.getTempAddress(tipoRes));
        quadruples.add(op, varIzq, varDer, tempAddr);
        vars.push(tempAddr);
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
%token SI SINO MIENTRAS HAZ ESCRIBE REGRESA
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
        jumps.push(quadruples.nextQuad());
        quadruples.add("GOTO", "_", "_", "_");
    }
    programa_p programa_pp INICIO
    {
        quadruples.fillQuad(jumps.getTop(), to_string(quadruples.nextQuad()));
        jumps.pop();
    }
    cuerpo FIN
    {
        quadruples.add("END", "_", "_", "_");
        cout << "Programa válido!" << endl;
    }
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
        for (auto& id : idStack) {
            try {
                int addr = memory.getAddress(scopeActual, $5);
                dirFunc.get(scopeActual).varTable.vars.insert(id, VarInfo($5, addr));
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
    PARENIZQ funcs_p PARENDER
    { dirFunc.get(scopeActual).startQuad = quadruples.nextQuad(); }
    LLAVEIZQ funcs_pp cuerpo LLAVEDER PUNTOYCOMA
    {
        quadruples.add("ENDFUNC", "_", "_", "_");
        FuncEntry& f = dirFunc.get(scopeActual);
        f.localIntCount   = memory.localIntCount();
        f.localFloatCount = memory.localFloatCount();
        f.tempIntCount    = memory.tempIntCount();
        f.tempFloatCount  = memory.tempFloatCount();
        memory.resetLocal();
        scopeActual = "global";
    }

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
    PARENIZQ funcs_p PARENDER
    { dirFunc.get(scopeActual).startQuad = quadruples.nextQuad(); }
    LLAVEIZQ funcs_pp cuerpo regresa LLAVEDER PUNTOYCOMA
    {
        quadruples.add("ENDFUNC", "_", "_", "_");
        FuncEntry& f = dirFunc.get(scopeActual);
        f.localIntCount   = memory.localIntCount();
        f.localFloatCount = memory.localFloatCount();
        f.tempIntCount    = memory.tempIntCount();
        f.tempFloatCount  = memory.tempFloatCount();
        memory.resetLocal();
        scopeActual = "global";
    }
;

funcs_p:
    ID DOSPUNTOS tipo
    {
        int addr = memory.getAddress(scopeActual, $3);
        dirFunc.get(scopeActual).varTable.vars.insert($1, VarInfo($3, addr));
        dirFunc.get(scopeActual).params.push_back(ParamInfo($3, addr));
    }
    funcs_ppp
    |
;

funcs_pp:
    vars
    |
;

funcs_ppp:
    COMA ID DOSPUNTOS tipo
    {
        int addr = memory.getAddress(scopeActual, $4);
        dirFunc.get(scopeActual).varTable.vars.insert($2, VarInfo($4, addr));
        dirFunc.get(scopeActual).params.push_back(ParamInfo($4, addr));
    }
    funcs_ppp
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
        VarInfo info = dirFunc.get(scopeActual).varTable.vars.get($1);
        vars.push(to_string(info.address));
        types.push(info.tipo);
    }
    ASIGNACION { operators.push("=");} expresion { makeQuadruple(); }
    PUNTOYCOMA
;

llamada:
    ID
    {
        if (!dirFunc.contains($1)) {
            yyerror(("Función no declarada: " + string($1)).c_str());
            YYABORT;
        }
        callTarget = $1;
        paramCount = 0;
        quadruples.add("ERA", "_", "_", $1);
    }
    PARENIZQ llamada_p PARENDER
    {
        int expected = dirFunc.get(callTarget).params.size();
        if (paramCount != expected) {
            yyerror("Número incorrecto de parámetros");
            YYABORT;
        }
        quadruples.add("GOSUB", "_", "_", to_string(dirFunc.get(callTarget).startQuad));
    }
;

llamada_p:
    expresion
    {
        auto& params = dirFunc.get(callTarget).params;
        if (paramCount >= (int)params.size()) {
            yyerror("Demasiados parámetros");
            YYABORT;
        }
        string argVal  = vars.getTop();  vars.pop();
        string argTipo = types.getTop(); types.pop();
        if (argTipo != params[paramCount].tipo) {
            yyerror(("Tipo incorrecto en parámetro " + to_string(paramCount + 1)).c_str());
            YYABORT;
        }
        quadruples.add("PARAM", argVal, "_", to_string(params[paramCount].address));
        paramCount++;
    }
    llamada_pp
    |
;

llamada_pp:
    COMA llamada_p
    |
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
        int addr = memory.getConstAddress("string", $1);
        quadruples.add("PRINT", to_string(addr), "_", "_");
    }
    imprime_pp
;

imprime_pp:
    COMA imprime_p
    |
;

regresa:
    REGRESA expresion PUNTOYCOMA
    {
        string varExpr = vars.getTop(); vars.pop();
        types.pop();
        quadruples.add("RETURN", varExpr, "_", scopeActual);
    }
;

condicion:
    SI PARENIZQ expresion PARENDER
    {
        string exprRes = vars.getTop(); vars.pop();
        types.pop();
        jumps.push(quadruples.nextQuad());
        quadruples.add("GOTOF", exprRes, "_", "_");
    }
    cuerpo condicion_p PUNTOYCOMA
;

condicion_p:
    SINO
    {
        int falseJump = jumps.getTop(); jumps.pop();
        jumps.push(quadruples.nextQuad());
        quadruples.add("GOTO", "_", "_", "_");
        quadruples.fillQuad(falseJump, to_string(quadruples.nextQuad()));
    }
    cuerpo
    {
        int endJump = jumps.getTop(); jumps.pop();
        quadruples.fillQuad(endJump, to_string(quadruples.nextQuad()));
    }
    |
    {
        int falseJump = jumps.getTop(); jumps.pop();
        quadruples.fillQuad(falseJump, to_string(quadruples.nextQuad()));
    }
;

ciclo:
    MIENTRAS
    {
        jumps.push(quadruples.nextQuad());
    }
    PARENIZQ expresion PARENDER
    {
        string exprRes = vars.getTop(); vars.pop();
        types.pop();
        jumps.push(quadruples.nextQuad());
        quadruples.add("GOTOF", exprRes, "_", "_");
    }
    HAZ cuerpo
    {
        int falseJump = jumps.getTop(); jumps.pop();
        int loopStart = jumps.getTop(); jumps.pop();
        quadruples.add("GOTO", "_", "_", to_string(loopStart));
        quadruples.fillQuad(falseJump, to_string(quadruples.nextQuad()));
    }
    PUNTOYCOMA
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
        VarInfo info = dirFunc.get(scopeActual).varTable.vars.get($1);
        vars.push(to_string(info.address));
        types.push(info.tipo);
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
        int addr = memory.getConstAddress("entero", to_string($1));
        vars.push(to_string(addr));
        types.push("entero");
    }
    | CTE_FLOT
    {
        int addr = memory.getConstAddress("flotante", to_string($1));
        vars.push(to_string(addr));
        types.push("flotante");
    }
;

%%