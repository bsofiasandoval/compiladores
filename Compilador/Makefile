CXX    = g++
FLEX   = flex
BISON  = bison
# -Iinclude  : finds our headers (Node, Stack, Table, FuncDir, SemanticCube, QuadrupleBuilder)
# -I.        : finds parser.tab.h generated at root by bison
CXXFLAGS = -Ihelpers -I.

TARGET  = compilador
SRCS    = compilador.cpp parser.tab.c lex.yy.c
HEADERS = helpers/Node.h helpers/Stack.h helpers/Table.h \
          helpers/FuncDir.h helpers/SemanticCube.h \
          helpers/QuadrupleBuilder.h helpers/Memory.h

all: $(TARGET)

# 1. Generate parser (produces parser.tab.c and parser.tab.h)
parser.tab.c parser.tab.h: parser.y
	$(BISON) -d parser.y

# 2. Generate lexer (depends on parser.tab.h for token definitions)
lex.yy.c: scanner.l parser.tab.h
	$(FLEX) scanner.l

# 3. Compile everything — recompila si cambia cualquier header
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f parser.tab.c parser.tab.h lex.yy.c $(TARGET)

.PHONY: all clean
