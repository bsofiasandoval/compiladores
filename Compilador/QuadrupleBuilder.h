// QuadrupleBuilder.h
#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;


struct Quadruple {
    string operador;
    string opIzq;
    string opDer;
    string resultado;

    Quadruple(string operador, string opIzq, string opDer, string resultado){
        this->operador = operador;
        this->opIzq = opIzq;
        this->opDer = opDer;
        this->resultado = resultado;
    }
};


class QuadrupleBuilder {
    private:
        vector<Quadruple> quadruples;
        int tempCount = 1;
    public:
        string newTemp(){
            return "t" + to_string(tempCount++);
        }

        void add(string operador, string opIzq, string opDer, string resultado){
            quadruples.push_back(Quadruple(operador, opIzq, opDer, resultado));
        }

        void print(){
            for(int i = 0; i < quadruples.size(); i++){
                cout << i + 1 << ". " << quadruples[i].operador << " " << quadruples[i].opIzq << " " << quadruples[i].opDer << " " << quadruples[i].resultado << endl;
            }
        }
};