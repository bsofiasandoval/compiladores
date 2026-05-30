#include <iostream>
#include <cstdio>
#include "QuadrupleBuilder.h"

extern int yyparse();
extern FILE* yyin;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo.ptt>" << std::endl;
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (!input) {
        std::cerr << "Error: no se pudo abrir '" << argv[1] << "'" << std::endl;
        return 1;
    }

    yyin = input;
    int result = yyparse();
    fclose(input);

    if (result != 0) {
        std::cerr << "Compilación fallida." << std::endl;
        return 1;
    }
    
    quadruples.print();
    return 0;
}
