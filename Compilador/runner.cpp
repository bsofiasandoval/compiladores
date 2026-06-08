#include <iostream>
#include <cstdio>
#include "helpers/compilador/QuadrupleBuilder.h"
#include "helpers/compilador/Memory.h"
#include "helpers/compilador/FuncDir.h"
#include "helpers/vm/VirtualMachine.h"

extern int yyparse();
extern FILE* yyin;
extern QuadrupleBuilder quadruples;
extern MemoryManager memory;


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

    
    VirtualMachine vm(quadruples, memory.constantTable, dirFunc);
    vm.run();
   // quadruples.print();
    return 0;
}
