#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include "Table.h"
using namespace std;

struct VarInfo {
    string tipo;
    int address;
    VarInfo() : tipo(""), address(-1) {}
    VarInfo(const string& t, int a) : tipo(t), address(a) {}
};

struct ParamInfo {
    string tipo;
    int address;
    ParamInfo(const string& t, int a) : tipo(t), address(a) {}
};

struct VarTable {
    Table<string, VarInfo> vars; // nombre -> {tipo, dirección virtual}
};

struct FuncEntry {
    string tipo;
    VarTable varTable;
    vector<ParamInfo> params;   // parámetros en orden de declaración
    int startQuad     = -1;     // cuádruplo donde empieza el cuerpo
    int localIntCount   = 0;
    int localFloatCount = 0;
    int tempIntCount    = 0;
    int tempFloatCount  = 0;

    FuncEntry() : tipo("nula") {}
    FuncEntry(const string& t) : tipo(t) {}
};

Table<string, FuncEntry> dirFunc;
string scopeActual = "global";
vector<string> idStack;
