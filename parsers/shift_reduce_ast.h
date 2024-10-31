#pragma once

// Token types for operations
enum TokenType {
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE
};

// Base AST node class
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual double evaluate() = 0;
    virtual void print(int indent = 0) = 0;
    
    // Alias for evaluate() to match the interface
    double eval() { return evaluate(); }
};

// Node for numeric values
class NumberNode : public ASTNode {
    double value;
public:
    NumberNode(double val);
    double evaluate() override;
    void print(int indent = 0) override;
};

// Node for binary operations
class BinaryOpNode : public ASTNode {
    ASTNode* left;
    TokenType op;
    ASTNode* right;
public:
    BinaryOpNode(ASTNode* l, TokenType o, ASTNode* r);
    ~BinaryOpNode();
    double evaluate() override;
    void print(int indent = 0) override;
};

// Node for unary operations
class UnaryOpNode : public ASTNode {
    TokenType op;
    ASTNode* operand;
public:
    UnaryOpNode(TokenType o, ASTNode* expr);
    ~UnaryOpNode();
    double evaluate() override;
    void print(int indent = 0) override;
};
