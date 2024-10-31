CXXFLAGS=-std=c++17 -O3 -g -Wall -Wextra

# Makefile
build:
	docker build -t shift_reduce_calc .
# Compiler and tools
CXX = g++
FLEX = flex
BISON = bison

# Source files
LEXER_FILE = shift_reduce_lexer.l
PARSER_FILE = shift_reduce_parser.y
MAIN_FILE = shift_reduce_main.cpp
AST_FILE = shift_reduce_ast.h

# Generated files
LEXER_CPP = shift_reduce_lexer.cpp
LEXER_HPP = shift_reduce_lexer.h
PARSER_CPP = shift_reduce_parser.cpp
PARSER_HPP = shift_reduce_parser.h

# Object files
OBJECTS = $(MAIN_FILE:.cpp=.o) $(LEXER_CPP:.cpp=.o) $(PARSER_CPP:.cpp=.o) $(AST_FILE:.h=.o)

# Executable name
EXECUTABLE = calc

# Default target
all: $(EXECUTABLE)

# Build the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lfl

# Build main.o
shift_reduce_main.o: $(MAIN_FILE) $(PARSER_HPP) $(LEXER_HPP) $(AST_FILE)
	$(CXX) $(CXXFLAGS) -c -o $@ $(MAIN_FILE)

# Build parser object
$(PARSER_CPP:.cpp=.o): $(PARSER_CPP) $(PARSER_HPP) $(AST_FILE)
	$(CXX) $(CXXFLAGS) -c -o $@ $(PARSER_CPP)

# Build lexer object
$(LEXER_CPP:.cpp=.o): $(LEXER_CPP) $(PARSER_HPP)
	$(CXX) $(CXXFLAGS) -c -o $@ $(LEXER_CPP)

# Generate parser files using Bison
$(PARSER_CPP) $(PARSER_HPP): $(PARSER_FILE)
	$(BISON) --defines=$(PARSER_HPP) -o $(PARSER_CPP) $(PARSER_FILE)

# Generate lexer files using Flex
$(LEXER_CPP) $(LEXER_HPP): $(LEXER_FILE)
	$(FLEX) -o $(LEXER_CPP) $(LEXER_FILE)

# Build shift_reduce_ast.o
shift_reduce_ast.o: shift_reduce_ast.cpp shift_reduce_ast.h
	$(CXX) $(CXXFLAGS) -c -o shift_reduce_ast.o shift_reduce_ast.cpp

# Clean generated and compiled files
clean:
	rm -f $(EXECUTABLE) $(OBJECTS) $(LEXER_CPP) $(LEXER_HPP) $(PARSER_CPP) $(PARSER_HPP)

# Phony targets
.PHONY: all clean
