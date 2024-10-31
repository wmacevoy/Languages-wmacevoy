#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>

// Token definitions
enum TokenType
{
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOF,
    TOKEN_INVALID
};

struct Token
{
    TokenType type;
    double value; // Only for TOKEN_NUMBER

    Token(TokenType type = TOKEN_INVALID, double value = 0.0) : type(type), value(value) {}
};

std::string tokenTypeToString(TokenType type)
{
    switch (type)
    {
    case TOKEN_PLUS:
        return "+";
    case TOKEN_MINUS:
        return "-";
    case TOKEN_MULTIPLY:
        return "*";
    case TOKEN_DIVIDE:
        return "/";
    default:
        return "?";
    }
}

// Scanner class: converts input string into tokens
class Scanner
{
public:
    Scanner(const std::string &input) : input(input), pos(0) {}

    Token getNextToken()
    {
        while (currentChar() != '\0')
        {
            if (isspace(currentChar()))
            {
                skipWhitespace();
                continue;
            }
            if (isdigit(currentChar()) || currentChar() == '.')
            {
                return Token(TOKEN_NUMBER, number());
            }
            if (currentChar() == '+')
            {
                advance();
                return Token(TOKEN_PLUS);
            }
            if (currentChar() == '-')
            {
                advance();
                return Token(TOKEN_MINUS);
            }
            if (currentChar() == '*')
            {
                advance();
                return Token(TOKEN_MULTIPLY);
            }
            if (currentChar() == '/')
            {
                advance();
                return Token(TOKEN_DIVIDE);
            }
            if (currentChar() == '(')
            {
                advance();
                return Token(TOKEN_LPAREN);
            }
            if (currentChar() == ')')
            {
                advance();
                return Token(TOKEN_RPAREN);
            }

            // If we reach here, we have an invalid character
            throw std::runtime_error("Lexical error: invalid character");
        }
        return Token(TOKEN_EOF);
    }

private:
    std::string input;
    size_t pos;

    char currentChar() const
    {
        if (pos < input.size())
        {
            return input[pos];
        }
        else
        {
            return '\0';
        }
    }

    void advance()
    {
        pos++;
    }

    void skipWhitespace()
    {
        while (isspace(currentChar()))
        {
            advance();
        }
    }

    double number()
    {
        size_t start_pos = pos;
        bool has_dot = false;
        while (isdigit(currentChar()) || currentChar() == '.')
        {
            if (currentChar() == '.')
            {
                if (has_dot)
                {
                    // Error: multiple dots in number
                    throw std::runtime_error("Lexical error: invalid number format");
                }
                has_dot = true;
            }
            advance();
        }
        std::string num_str = input.substr(start_pos, pos - start_pos);
        return std::stod(num_str);
    }
};

// AST node classes: represent the structure of the parsed expressions
class ASTNode
{
public:
    virtual ~ASTNode() = default;
    virtual void print(int indent = 0, std::ostream &os = std::cout) const = 0;
    virtual double eval() const = 0;
};

class NumberNode : public ASTNode
{
public:
    NumberNode(double value) : value(value) {}

    void print(int indent = 0, std::ostream &os = std::cout) const override
    {
        os << std::string(indent, ' ') << "Number(" << value << ")\n";
    }
    double eval() const override
    {
        return value;
    }

    double value;
};

class UnaryOpNode : public ASTNode
{
public:
    TokenType op;
    ASTNode *expr;

    UnaryOpNode(TokenType op, ASTNode *expr) : op(op), expr(expr) {}

    ~UnaryOpNode()
    {
        delete expr;
    }

    void print(int indent = 0, std::ostream &os = std::cout) const override
    {
        os << std::string(indent, ' ') << "UnaryOp(" << tokenTypeToString(op) << ")\n";
        expr->print(indent + 2, os);
    }

    double eval() const override
    {
        switch (op)
        {
        case TOKEN_PLUS:
            return expr->eval();
        case TOKEN_MINUS:
            return -expr->eval();
        default:
            throw std::runtime_error("Runtime error: unknown unary operator");
        }
    }
};

class BinaryOpNode : public ASTNode
{
public:
    ASTNode *left;
    TokenType op; 
    ASTNode *right;

    BinaryOpNode(ASTNode *left, TokenType op, ASTNode *right)
        : left(left), op(op), right(right) {}

    ~BinaryOpNode()
    {
        delete left;
        delete right;
    }

    void print(int indent = 0, std::ostream &os = std::cout) const override
    {
        os << std::string(indent, ' ') << "BinaryOp(" << tokenTypeToString(op) << ")\n";
        left->print(indent + 2, os);
        right->print(indent + 2, os);
    }

    double eval() const override
    {
        switch (op)
        {
        case TOKEN_PLUS:
            return left->eval() + right->eval();
        case TOKEN_MINUS:
            return left->eval() - right->eval();
        case TOKEN_MULTIPLY:
            return left->eval() * right->eval();
        case TOKEN_DIVIDE:
            return left->eval() / right->eval();
        default:
            throw std::runtime_error("Runtime error: unknown binary operator");
        }
    }
};

// Parser class: builds the AST using tokens from the scanner
class Parser
{
public:
    Parser(Scanner &scanner) : scanner(scanner)
    {
        currentToken = scanner.getNextToken();
    }

    ASTNode *parse()
    {
        ASTNode *node = expression();
        if (currentToken.type != TOKEN_EOF)
        {
            throw std::runtime_error("Syntax error: unexpected token after expression");
        }
        return node;
    }

private:
    Scanner &scanner;
    Token currentToken;

    void eat(TokenType type)
    {
        if (currentToken.type == type)
        {
            currentToken = scanner.getNextToken();
        }
        else
        {
            throw std::runtime_error("Syntax error: unexpected token");
        }
    }

    ASTNode *expression()
    {
        ASTNode *node = term();

        while (currentToken.type == TOKEN_PLUS || currentToken.type == TOKEN_MINUS)
        {
            TokenType op = currentToken.type;
            eat(op);
            ASTNode *right = term();
            node = new BinaryOpNode(node, op, right);
        }
        return node;
    }

    ASTNode *term()
    {
        ASTNode *node = factor();

        while (currentToken.type == TOKEN_MULTIPLY || currentToken.type == TOKEN_DIVIDE)
        {
            TokenType op = currentToken.type;
            eat(op);
            ASTNode *right = factor();
            node = new BinaryOpNode(node, op, right);
        }
        return node;
    }

    ASTNode *factor()
    {
        if (currentToken.type == TOKEN_PLUS || currentToken.type == TOKEN_MINUS)
        {
            TokenType op = currentToken.type;
            eat(op);
            ASTNode *node = factor();
            return new UnaryOpNode(op, node);
        }
        else if (currentToken.type == TOKEN_NUMBER)
        {
            double value = currentToken.value;
            eat(TOKEN_NUMBER);
            return new NumberNode(value);
        }
        else if (currentToken.type == TOKEN_LPAREN)
        {
            eat(TOKEN_LPAREN);
            ASTNode *node = expression();
            eat(TOKEN_RPAREN);
            return node;
        }
        else
        {
            throw std::runtime_error("Syntax error: unexpected token in factor");
        }
    }
};

std::shared_ptr<ASTNode> parse(const std::string &input)
{
    Scanner scanner(input);
    Parser parser(scanner);
    ASTNode *root = parser.parse();
    return std::shared_ptr<ASTNode>(root);
}

int main(int argc, const char *argv[])
{
    for (int argi = 1; argi < argc; ++argi)
    {
        try
        {
            std::string input = argv[argi];
            auto expr = parse(input);
            std::cout << "parse(" << input << "):" << std::endl;
            expr->print(4);
            std::cout << "eval(" << input << ")=" << expr->eval() << std::endl;
        }
        catch (const std::exception &ex)
        {
            std::cerr << ex.what() << std::endl;
        }
    }
    return 0;
}
