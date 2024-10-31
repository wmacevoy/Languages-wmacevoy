#include "shift_reduce_ast.h"
#include <iostream>
#include <string>

// NumberNode implementation
NumberNode::NumberNode(double val) : value(val) {}

double NumberNode::evaluate() {
    return value;
}

void NumberNode::print(int indent) {
    std::string spaces(indent, ' ');
    std::cout << spaces << "Number: " << value << std::endl;
}

// BinaryOpNode implementation
BinaryOpNode::BinaryOpNode(ASTNode* l, TokenType o, ASTNode* r) 
    : left(l), op(o), right(r) {}

BinaryOpNode::~BinaryOpNode() {
    delete left;
    delete right;
}

double BinaryOpNode::evaluate() {
    switch(op) {
        case TOKEN_PLUS: return left->evaluate() + right->evaluate();
        case TOKEN_MINUS: return left->evaluate() - right->evaluate();
        case TOKEN_MULTIPLY: return left->evaluate() * right->evaluate();
        case TOKEN_DIVIDE: return left->evaluate() / right->evaluate();
        default: return 0.0;
    }
}

void BinaryOpNode::print(int indent) {
    std::string spaces(indent, ' ');
    std::cout << spaces << "Binary Operation: ";
    switch(op) {
        case TOKEN_PLUS: std::cout << "+"; break;
        case TOKEN_MINUS: std::cout << "-"; break;
        case TOKEN_MULTIPLY: std::cout << "*"; break;
        case TOKEN_DIVIDE: std::cout << "/"; break;
    }
    std::cout << std::endl;
    
    left->print(indent + 2);
    right->print(indent + 2);
}

// UnaryOpNode implementation
UnaryOpNode::UnaryOpNode(TokenType o, ASTNode* expr) 
    : op(o), operand(expr) {}

UnaryOpNode::~UnaryOpNode() {
    delete operand;
}

double UnaryOpNode::evaluate() {
    if (op == TOKEN_MINUS) {
        return -operand->evaluate();
    }
    return operand->evaluate();
}

void UnaryOpNode::print(int indent) {
    std::string spaces(indent, ' ');
    std::cout << spaces << "Unary Operation: ";
    switch(op) {
        case TOKEN_MINUS: std::cout << "-"; break;
        default: std::cout << "+"; break;
    }
    std::cout << std::endl;
    
    operand->print(indent + 2);
} 