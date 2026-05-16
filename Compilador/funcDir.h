// funcDir.h
#pragma once
#include <unordered_map>
#include <string>
#include <stdexcept>
#include "Table.h"
using namespace std;

class VarEntry {
    string nombre;
    string tipo;
}

class FuncEntry {
    string nombre;
    string tipo;
    Table<string, VarEntry> dirVars;
};

Table<string, FuncEntry> dirFunc;