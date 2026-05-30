#pragma once
#include <unordered_map>
#include <string>
#include <stdexcept>
using namespace std;

class SemanticCube {
private:
    unordered_map<string, unordered_map<string, unordered_map<string, string>>> cube;

public:
    SemanticCube() {
        cube = {
            {"entero", {
                {"entero", {
                    {"+", "entero"}, {"-", "entero"}, {"*", "entero"}, {"/", "flotante"},
                    {"<", "entero"}, {">", "entero"}, {"==", "entero"}, {"!=", "entero"},
                    {"=", "entero"}
                }},
                {"flotante", {
                    {"+", "flotante"}, {"-", "flotante"}, {"*", "flotante"}, {"/", "flotante"},
                    {"<", "entero"}, {">", "entero"}, {"==", "entero"}, {"!=", "entero"},
                    {"=", "error"}
                }}
            }},
            {"flotante", {
                {"entero", {
                    {"+", "flotante"}, {"-", "flotante"}, {"*", "flotante"}, {"/", "flotante"},
                    {"<", "entero"}, {">", "entero"}, {"==", "entero"}, {"!=", "entero"},
                    {"=", "error"}
                }},
                {"flotante", {
                    {"+", "flotante"}, {"-", "flotante"}, {"*", "flotante"}, {"/", "flotante"},
                    {"<", "entero"}, {">", "entero"}, {"==", "entero"}, {"!=", "entero"},
                    {"=", "flotante"}
                }}
            }}
        };
    }

    string validate(const string& tipoIzq, const string& tipoDer, const string& op) {
        try {
            string resultado = cube.at(tipoIzq).at(tipoDer).at(op);
            if (resultado == "error")
                throw runtime_error("Operación inválida: " + tipoIzq + " " + op + " " + tipoDer);
            return resultado;
        } catch (const out_of_range&) {
            throw runtime_error("Operación inválida: " + tipoIzq + " " + op + " " + tipoDer);
        }
    }
};