%{
#include <iostream>
#include <string>
#include <vector>
#include "helpers/compilador/FuncDir.h"
#include "helpers/compilador/SemanticCube.h"
#include "helpers/compilador/QuadrupleBuilder.h"
#include "helpers/compilador/Memory.h"
#include "helpers/estructuras/Stack.h"
using namespace std;

void yyerror(const char* s) {
    cerr << "Error sintáctico: " << s << endl;
}
int yylex();

SemanticCube cube;
MemoryManager memory;

Table<string, FuncEntry> dirFunc;
string scopeActual = "global";
vector<string> idStack;

Stack<string> operators;
Stack<string> vars;
Stack<string> types;
Stack<int> jumps;
QuadrupleBuilder quadruples;
string callTarget = "";
int paramCount = 0;

VarInfo lookupVar(const string& name) {
    if (scopeActual != "global" &&
        dirFunc.get(scopeActual).varTable.vars.contains(name))
        return dirFunc.get(scopeActual).varTable.vars.get(name);
    if (dirFunc.get("global").varTable.vars.contains(name))
        return dirFunc.get("global").varTable.vars.get(name);
    throw runtime_error("Variable no declarada: " + name);
}

void registerParam(const string& name, const string& tipo) {
    int addr = memory.getAddress(scopeActual, tipo);
    dirFunc.get(scopeActual).varTable.vars.insert(name, VarInfo(tipo, addr));
    dirFunc.get(scopeActual).params.push_back(ParamInfo(tipo, addr));
}

void finalizeFunc() {
    quadruples.add("ENDFUNC", "_", "_", "_");
    FuncEntry& f = dirFunc.get(scopeActual);
    f.localIntCount   = memory.localIntCount();
    f.localFloatCount = memory.localFloatCount();
    f.tempIntCount    = memory.tempIntCount();
    f.tempFloatCount  = memory.tempFloatCount();
    memory.resetLocal();
    scopeActual = "global";
}

string popExpr() {
    string addr = vars.getTop(); vars.pop();
    types.pop();
    return addr;
}

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
        FuncEntry& g = dirFunc.get("global");
        g.tempIntCount   = memory.tempIntCount();
        g.tempFloatCount = memory.tempFloatCount();
        quadruples.add("END", "_", "_", "_");
        // cout << "Programa válido!" << endl;
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
        string tipVar = $5;
        for (auto& id : idStack) {
            try {
                int addr = memory.getAddress(scopeActual, tipVar);
                dirFunc.get(scopeActual).varTable.vars.insert(id, VarInfo(tipVar, addr));
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
        string funcName = $2;
        try {
            dirFunc.insert(funcName, FuncEntry("nula"));
        } catch (runtime_error&) {
            yyerror("Función doblemente declarada");
            YYABORT;
        }
        scopeActual = funcName;
    }
    PARENIZQ funcs_p PARENDER
    { dirFunc.get(scopeActual).startQuad = quadruples.nextQuad(); }
    LLAVEIZQ funcs_pp cuerpo LLAVEDER PUNTOYCOMA
    { finalizeFunc(); }

    | tipo ID
    {
        string tipoReturn = $1;
        string funcName = $2;
        try {
            dirFunc.insert(funcName, FuncEntry(tipoReturn));
        } catch (runtime_error&) {
            yyerror("Función doblemente declarada");
            YYABORT;
        }
        int retAddr = memory.getAddress("global", tipoReturn);
        dirFunc.get(funcName).returnAddress = retAddr;
        scopeActual = funcName;
    }
    PARENIZQ funcs_p PARENDER
    { dirFunc.get(scopeActual).startQuad = quadruples.nextQuad(); }
    LLAVEIZQ funcs_pp cuerpo regresa LLAVEDER PUNTOYCOMA
    { finalizeFunc(); }
;

funcs_p:
    ID DOSPUNTOS tipo
    {
        registerParam($1, $3);
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
        registerParam($2, $4);
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
        VarInfo info;
        try { info = lookupVar($1); }
        catch (runtime_error& e) { yyerror(e.what()); YYABORT; }
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
        quadruples.add("PRINT", popExpr(), "_", "_");
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
        quadruples.add("RETURN", popExpr(), "_", scopeActual);
    }
;

condicion:
    SI PARENIZQ expresion PARENDER
    {
        jumps.push(quadruples.nextQuad());
        quadruples.add("GOTOF", popExpr(), "_", "_");
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
        jumps.push(quadruples.nextQuad());
        quadruples.add("GOTOF", popExpr(), "_", "_");
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
    {
        string tipoReturn = dirFunc.get(callTarget).tipo;
        if(tipoReturn == "nula"){
            yyerror("No se puede usar una funcion void en una expresion");
            YYABORT;
        }
        int returnAddr = dirFunc.get(callTarget).returnAddress;
        int tempAddr = memory.getTempAddress(tipoReturn);
        quadruples.add("=", to_string(returnAddr), "_", to_string(tempAddr));
        vars.push(to_string(tempAddr));
        types.push(tipoReturn);
    }
    | ID
    {
        VarInfo info;
        try { info = lookupVar($1); }
        catch (runtime_error& e) { yyerror(e.what()); YYABORT; }
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
        int valor = $1;
        int addr = memory.getConstAddress("entero", to_string(valor));
        vars.push(to_string(addr));
        types.push("entero");
    }
    | CTE_FLOT
    {
        float valor = $1;
        int addr = memory.getConstAddress("flotante", to_string(valor));
        vars.push(to_string(addr));
        types.push("flotante");
    }
;

%%