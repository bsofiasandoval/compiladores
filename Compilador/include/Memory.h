#pragma once
#include <string>
#include <map>
#include <stdexcept>
using namespace std;

class MemoryManager {
    static const int GLOBAL_INT_START   = 1000;
    static const int GLOBAL_FLOAT_START = 2000;
    static const int LOCAL_INT_START    = 3000;
    static const int LOCAL_FLOAT_START  = 4000;
    static const int TEMP_INT_START     = 5000;
    static const int TEMP_FLOAT_START   = 6000;
    static const int CONST_INT_START    = 7000;
    static const int CONST_FLOAT_START  = 8000;
    static const int CONST_STR_START    = 9000;
    static const int RANGE_SIZE         = 1000;

    int globalInt, globalFloat;
    int localInt,  localFloat;
    int tempInt,   tempFloat;
    int constInt,  constFloat, constStr;

    void checkOverflow(int current, int start) {
        if (current - start >= RANGE_SIZE)
            throw runtime_error("Memoria agotada en segmento");
    }

public:
    map<int, string> constantTable;

    MemoryManager() :
        globalInt(GLOBAL_INT_START),   globalFloat(GLOBAL_FLOAT_START),
        localInt(LOCAL_INT_START),     localFloat(LOCAL_FLOAT_START),
        tempInt(TEMP_INT_START),       tempFloat(TEMP_FLOAT_START),
        constInt(CONST_INT_START),     constFloat(CONST_FLOAT_START),
        constStr(CONST_STR_START) {}

    int getAddress(const string& scope, const string& tipo) {
        if (scope == "global") {
            if      (tipo == "entero")   { checkOverflow(globalInt,   GLOBAL_INT_START);   return globalInt++;   }
            else if (tipo == "flotante") { checkOverflow(globalFloat, GLOBAL_FLOAT_START); return globalFloat++; }
            else throw runtime_error("Tipo desconocido en memoria global: " + tipo);
        } else {
            if      (tipo == "entero")   { checkOverflow(localInt,   LOCAL_INT_START);   return localInt++;   }
            else if (tipo == "flotante") { checkOverflow(localFloat, LOCAL_FLOAT_START); return localFloat++; }
            else throw runtime_error("Tipo desconocido en memoria local: " + tipo);
        }
    }

    int getTempAddress(const string& tipo) {
        if      (tipo == "entero")   { checkOverflow(tempInt,   TEMP_INT_START);   return tempInt++;   }
        else if (tipo == "flotante") { checkOverflow(tempFloat, TEMP_FLOAT_START); return tempFloat++; }
        else throw runtime_error("Tipo desconocido en temporales: " + tipo);
    }

    int getConstAddress(const string& tipo, const string& valor) {
        int addr;
        if (tipo == "entero")   { checkOverflow(constInt, CONST_INT_START);   addr = constInt++;   }
        else if (tipo == "flotante") { checkOverflow(constFloat, CONST_FLOAT_START); addr = constFloat++; }
        else                    { checkOverflow(constStr, CONST_STR_START);    addr = constStr++;   }
        constantTable[addr] = valor;
        return addr;
    }

    void resetLocal() {
        localInt  = LOCAL_INT_START;
        localFloat = LOCAL_FLOAT_START;
        tempInt   = TEMP_INT_START;
        tempFloat = TEMP_FLOAT_START;
    }

    int localIntCount()   { return localInt   - LOCAL_INT_START; }
    int localFloatCount() { return localFloat - LOCAL_FLOAT_START; }
    int tempIntCount()    { return tempInt    - TEMP_INT_START; }
    int tempFloatCount()  { return tempFloat  - TEMP_FLOAT_START; }
};
