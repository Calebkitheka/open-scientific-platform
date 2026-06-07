#include "parser.hpp"
#include <cctype>
#include <stdexcept>

std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    size_t i = 0, n = input.size();
    while (i < n) {
        if (std::isspace(input[i])) { ++i; continue; }
        if (std::isdigit(input[i]) || input[i] == '.') {
            size_t start = i;
            while (i < n && (std::isdigit(input[i]) || input[i] == '.')) ++i;
            tokens.push_back({TokType::NUM, input.substr(start, i - start)});
        } else if (std::isalpha(input[i]) || input[i] == '_') {
            size_t start = i;
            while (i < n && (std::isalnum(input[i]) || input[i] == '_')) ++i;
            tokens.push_back({TokType::ID, input.substr(start, i - start)});
        } else {
            switch (input[i]) {
                case '+': tokens.push_back({TokType::OP_PLUS, "+"}); break;
                case '-': tokens.push_back({TokType::OP_MINUS, "-"}); break;
                case '*': tokens.push_back({TokType::OP_MUL, "*"}); break;
                default: throw std::invalid_argument(std::string("Unexpected char: ") + input[i]);
            }
            ++i;
        }
    }
    tokens.push_back({TokType::END, ""});
    return tokens;
}

class ExprParser {
    const std::vector<Token>& tokens;
    const Workspace& ws;
    size_t pos;

    Token peek() const { return tokens[pos]; }
    void advance() { if (pos < tokens.size()) ++pos; }

    Matrix parse_factor() {
        Token t = peek(); advance();
        if (t.type == TokType::NUM) {
            double val = std::stod(t.lexeme);
            Matrix m(1, 1); m.at(0, 0) = val; return m;
        }
        if (t.type == TokType::ID) {
            auto it = ws.find(t.lexeme);
            if (it == ws.end()) throw std::invalid_argument("Undefined variable: " + t.lexeme);
            return it->second;
        }
        throw std::invalid_argument("Expected number or variable");
    }

    Matrix parse_term() {
        Matrix left = parse_factor();
        while (peek().type == TokType::OP_MUL) {
            advance();
            left = left * parse_factor();
        }
        return left;
    }

    Matrix parse_expression() {
        Matrix left = parse_term();
        while (peek().type == TokType::OP_PLUS || peek().type == TokType::OP_MINUS) {
            bool is_add = peek().type == TokType::OP_PLUS;
            advance();
            Matrix right = parse_term();
            left = is_add ? (left + right) : (left - right);
        }
        return left;
    }

public:
    ExprParser(const std::vector<Token>& t, const Workspace& w) : tokens(t), ws(w), pos(0) {}
    Matrix run() { return parse_expression(); }
};

Matrix evaluate_expression(const std::vector<Token>& tokens, const Workspace& ws) {
    if (tokens.empty() || tokens.back().type != TokType::END) throw std::invalid_argument("Malformed expression");
    return ExprParser(tokens, ws).run();
}