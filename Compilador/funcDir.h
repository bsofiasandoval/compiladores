// FuncDir.h
#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include "Table.h"
using namespace std;

struct VarTable {
    Table<string, string> vars; // nombre -> tipo
};

struct FuncEntry {
    string tipo;
    VarTable varTable;

    FuncEntry() : tipo("nula") {}
    FuncEntry(const string& t) : tipo(t) {}
};

Table<string, FuncEntry> dirFunc; // scope , funcion
string scopeActual = "global";
vector<string> idStack;