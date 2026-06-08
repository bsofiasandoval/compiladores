#pragma once
#include <vector>
#include <stack>
#include <string>
#include <iostream>
#include <stdexcept>
#include "../compilador/QuadrupleBuilder.h"
#include "../compilador/FuncDir.h"
#include "ExecutionMemory.h"
using namespace std;

enum Instruccion {
    ASIGNA,
    SUMA, RESTA, MULTIPLICA, DIVIDE,
    MAYOR, MENOR, IGUAL, DIFF,
    GOTO, GOTOF,
    IMPRIME,
    ERA, PARAM, GOSUB, REGRESA, FIN_FUNC,
    FIN,
    INV
};

inline Instruccion convertirInstruccion(const string& s) {
    if (s == "=")       return ASIGNA;
    if (s == "+")       return SUMA;
    if (s == "-")       return RESTA;
    if (s == "*")       return MULTIPLICA;
    if (s == "/")       return DIVIDE;
    if (s == ">")       return MAYOR;
    if (s == "<")       return MENOR;
    if (s == "==")      return IGUAL;
    if (s == "!=")      return DIFF;
    if (s == "GOTO")    return GOTO;
    if (s == "GOTOF")   return GOTOF;
    if (s == "PRINT")   return IMPRIME;
    if (s == "ERA")     return ERA;
    if (s == "PARAM")   return PARAM;
    if (s == "GOSUB")   return GOSUB;
    if (s == "RETURN")  return REGRESA;
    if (s == "ENDFUNC") return FIN_FUNC;
    if (s == "END")     return FIN;
    return INV;
}

class VirtualMachine {
    vector<Quadruple>&        quads;
    Table<string, FuncEntry>& funcDir;
    ExecutionMemory           mem;

    stack<ActivationRecord*> callStack;
    ActivationRecord*        pendingFrame = nullptr;
    int ip = 0;

    float izq(const Quadruple& quad) { return mem.getVal(stoi(quad.opIzq)); }
    float der(const Quadruple& quad) { return mem.getVal(stoi(quad.opDer)); }
    int   res(const Quadruple& quad) { return stoi(quad.resultado);          }

    void printVal(int addr) {
        if (mem.isStringAddr(addr))   cout << mem.getString(addr) << endl;
        else if (mem.isFloatAddress(addr)) cout << mem.getVal(addr) << endl;
        else                               cout << (int)mem.getVal(addr) << endl;
    }

    void cleanup() {
        while (!callStack.empty()) {
            delete callStack.top();
            callStack.pop();
        }
    }

    void pushFrame(ActivationRecord* frame) {
        callStack.push(frame);
        mem.setFrameActivo(frame);
    }

    void popFrame() {
        ActivationRecord* frame = callStack.top();
        callStack.pop();
        int retIp = frame->returnHere;
        delete frame;
        ip = retIp;
        mem.setFrameActivo(callStack.empty() ? nullptr : callStack.top());
    }

    bool executeQuad() {
        Quadruple& quad = quads[ip];
        switch (convertirInstruccion(quad.operador)) {

            case FIN: return false;

            case ASIGNA:     mem.setVal(res(quad), izq(quad));                        break;
            case SUMA:       mem.setVal(res(quad), izq(quad) + der(quad));             break;
            case RESTA:      mem.setVal(res(quad), izq(quad) - der(quad));             break;
            case MULTIPLICA: mem.setVal(res(quad), izq(quad) * der(quad));             break;
            case MAYOR:      mem.setVal(res(quad), izq(quad) > der(quad)  ? 1 : 0);   break;
            case MENOR:      mem.setVal(res(quad), izq(quad) < der(quad)  ? 1 : 0);   break;
            case IGUAL:      mem.setVal(res(quad), izq(quad) == der(quad) ? 1 : 0);   break;
            case DIFF:       mem.setVal(res(quad), izq(quad) != der(quad) ? 1 : 0);   break;

            case DIVIDE: {
                float denominador = der(quad);
                if (denominador == 0) throw runtime_error("Division entre cero");
                mem.setVal(res(quad), izq(quad) / denominador);
                break;
            }

            case GOTO:
                ip = res(quad); return true;

            case GOTOF:
                if (izq(quad) == 0) ip = res(quad);
                else                ip++;
                return true;

            case IMPRIME:
                printVal(stoi(quad.opIzq));
                break;

            case ERA: {
                FuncEntry& func = funcDir.get(quad.resultado);
                pendingFrame = new ActivationRecord(-1, func.localIntCount, func.tempIntCount, func.localFloatCount, func.tempFloatCount);
                break;
            }

            case PARAM:
                mem.setParam(pendingFrame, res(quad), izq(quad));
                break;

            case GOSUB:
                pendingFrame->returnHere = ip + 1;
                pushFrame(pendingFrame);
                pendingFrame = nullptr;
                ip = stoi(quad.resultado); return true;

            case REGRESA:
                mem.setVal(funcDir.get(quad.resultado).returnAddress, izq(quad));
                break;

            case FIN_FUNC:
                popFrame(); return true;

            default:
                throw runtime_error("Instruccion desconocida: " + quad.operador);
        }
        ip++;
        return true;
    }

public:
    VirtualMachine(QuadrupleBuilder& qb, Table<int,string>& ct, Table<string,FuncEntry>& fd)
        : quads(qb.getQuadruples()), funcDir(fd), mem(ct) {}

    void run() {
        FuncEntry& scopeGlobal = funcDir.get("global");
        ActivationRecord* falseBottom = new ActivationRecord(-1, 0, scopeGlobal.tempIntCount, 0, scopeGlobal.tempFloatCount);
        pushFrame(falseBottom);

        while (ip < quads.size()) {
            if (!executeQuad()) break;
        }

        cleanup();
    }
};
