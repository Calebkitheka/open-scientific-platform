#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "matrix.hpp"

using Workspace = std::unordered_map<std::string, Matrix>;

enum class TokType { NUM, ID, OP_PLUS, OP_MINUS, OP_MUL, END };
struct Token { TokType type; std::string lexeme; };

std::vector<Token> tokenize(const std::string& input);
Matrix evaluate_expression(const std::vector<Token>& tokens, const Workspace& ws);