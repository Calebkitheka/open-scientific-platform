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
        }
        else if (std::isalpha(input[i]) || input[i] == '_') {
            size_t start = i;
            while (i < n && (std::isalnum(input[i]) || input[i] == '_')) ++i;
            tokens.push_back({TokType::ID, input.substr(start, i - start)});
        }
        else {
            switch (input[i]) {
                case '+': tokens.push_back({TokType::OP_PLUS, "+"}); break;
                case '-': tokens.push_back({TokType::OP_MINUS, "-"}); break;
                case '*': tokens.push_back({TokType::OP_MUL, "*"}); break;
                default: throw std::invalid_argument(std::string("Unexpected character: ") + input[i]);
            }
            ++i;
        }
    }
    tokens.push_back({TokType::END, ""});
    return tokens;
}

Matrix resolve_operand(const Token& t, const std::unordered_map<std::string, Matrix>& ws) {
    if (t.type == TokType::NUM) {
        double val = std::stod(t.lexeme);
        Matrix m(1, 1); m.at(0, 0) = val; return m;
    }
    if (t.type == TokType::ID) {
        auto it = ws.find(t.lexeme);
        if (it == ws.end()) throw std::invalid_argument("Undefined variable: " + t.lexeme);
        return it->second;
    }
    throw std::invalid_argument("Expected operand, got operator");
}

Matrix apply_op(const Matrix& left, TokType op, const Matrix& right) {
    if (op == TokType::OP_PLUS) return left + right;
    if (op == TokType::OP_MINUS) {
        Matrix neg(right.rows, right.cols);
        for (size_t i = 0; i < right.data.size(); ++i) neg.data[i] = -right.data[i];
        return left + neg;
    }
    if (op == TokType::OP_MUL) {
        // Handle scalar * matrix or matrix * scalar
        if (left.rows == 1 && left.cols == 1) {
            double s = left.at(0, 0);
            Matrix res(right.rows, right.cols);
            for (size_t i = 0; i < right.data.size(); ++i) res.data[i] = s * right.data[i];
            return res;
        }
        if (right.rows == 1 && right.cols == 1) {
            double s = right.at(0, 0);
            Matrix res(left.rows, left.cols);
            for (size_t i = 0; i < left.data.size(); ++i) res.data[i] = left.data[i] * s;
            return res;
        }
        throw std::invalid_argument("Matrix-matrix multiplication requires operator overloading (coming soon). Use scalar multiplication for now.");
    }
    throw std::invalid_argument("Unknown operator");
}

Matrix evaluate(const std::vector<Token>& tokens, const std::unordered_map<std::string, Matrix>& ws) {
    if (tokens.empty() || tokens.back().type != TokType::END) throw std::invalid_argument("Malformed expression");
    size_t pos = 0;

    Matrix result = resolve_operand(tokens[pos++], ws);

    while (tokens[pos].type == TokType::OP_PLUS || tokens[pos].type == TokType::OP_MINUS || tokens[pos].type == TokType::OP_MUL) {
        TokType op = tokens[pos++].type;
        if (tokens[pos].type == TokType::END) throw std::invalid_argument("Missing operand after operator");
        Matrix next = resolve_operand(tokens[pos++], ws);
        result = apply_op(result, op, next);
    }
    return result;
}