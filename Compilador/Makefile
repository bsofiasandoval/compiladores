CXX    = g++
FLEX   = flex
BISON  = bison

CXXFLAGS = -Ihelpers -Ihelpers/estructuras -Ihelpers/compilador -Ihelpers/vm -I.

TARGET  = compilador
SRCS    = runner.cpp parser.tab.c lex.yy.c
HEADERS = helpers/estructuras/Node.h helpers/estructuras/Stack.h helpers/estructuras/Table.h \
          helpers/compilador/FuncDir.h helpers/compilador/SemanticCube.h \
          helpers/compilador/QuadrupleBuilder.h helpers/compilador/Memory.h \
          helpers/vm/ActivationRecord.h helpers/vm/ExecutionMemory.h helpers/vm/VirtualMachine.h

all: $(TARGET)

# 1. Generar parser
parser.tab.c parser.tab.h: parser.y
	$(BISON) -d parser.y

# 2. Generar lexer
lex.yy.c: scanner.l parser.tab.h
	$(FLEX) scanner.l

# 3. Compilar todo, recompila si cambia cualquier header
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f parser.tab.c parser.tab.h lex.yy.c $(TARGET)

.PHONY: all clean
