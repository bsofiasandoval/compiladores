#pragma once
#include <string>
#include <stdexcept>
#include "../estructuras/Table.h"
#include "ActivationRecord.h"
using namespace std;

class ExecutionMemory {
    int   globalInts  [1000] = {};
    float globalFloats[1000] = {};

    Table<int, string>& constants;
    ActivationRecord*   frameActivo = nullptr;

public:
    ExecutionMemory(Table<int, string>& constants) : constants(constants) {}

    void setFrameActivo(ActivationRecord* frame) { frameActivo = frame; }

    float getVal(int addr) {
        if (addr >= 1000 && addr < 2000) return (float)globalInts  [addr - 1000];
        if (addr >= 2000 && addr < 3000) return        globalFloats [addr - 2000];
        if (addr >= 7000 && addr < 8000) return (float)stoi(constants.get(addr));
        if (addr >= 8000 && addr < 9000) return        stof(constants.get(addr));

        if (addr >= 3000 && addr < 4000) return (float)frameActivo->ints  [addr - 3000];
        if (addr >= 4000 && addr < 5000) return        frameActivo->floats [addr - 4000];
        if (addr >= 5000 && addr < 6000) return (float)frameActivo->ints  [(addr - 5000) + frameActivo->localIntStart];
        if (addr >= 6000 && addr < 7000) return        frameActivo->floats [(addr - 6000) + frameActivo->localFloatStart];

        throw runtime_error("getVal: direccion invalida " + to_string(addr));
    }

    void setVal(int addr, float val) {
        if (addr >= 1000 && addr < 2000) { globalInts  [addr - 1000] = (int)val; return; }
        if (addr >= 2000 && addr < 3000) { globalFloats [addr - 2000] =      val; return; }

        if (addr >= 3000 && addr < 4000) { frameActivo->ints  [addr - 3000]                                    = (int)val; return; }
        if (addr >= 4000 && addr < 5000) { frameActivo->floats [addr - 4000]                                   =      val; return; }
        if (addr >= 5000 && addr < 6000) { frameActivo->ints  [(addr - 5000) + frameActivo->localIntStart]     = (int)val; return; }
        if (addr >= 6000 && addr < 7000) { frameActivo->floats [(addr - 6000) + frameActivo->localFloatStart]  =      val; return; }

        throw runtime_error("setVal: direccion invalida " + to_string(addr));
    }

    bool isFloatAddress(int addr) {
        return (addr >= 2000 && addr < 3000) ||
               (addr >= 4000 && addr < 5000) ||
               (addr >= 6000 && addr < 7000) ||
               (addr >= 8000 && addr < 9000);
    }

    bool isStringAddr(int addr) { return addr >= 9000 && addr < 10000; }

    void setParam(ActivationRecord* frame, int paramAddr, float val) {
        if (isFloatAddress(paramAddr))
            frame->floats[paramAddr - 4000] = val;
        else
            frame->ints  [paramAddr - 3000] = (int)val;
    }

    string getString(int addr) {
        string s = constants.get(addr);
        if (s.size() >= 2 && s.front() == '"') s = s.substr(1, s.size() - 2);
        return s;
    }

};
