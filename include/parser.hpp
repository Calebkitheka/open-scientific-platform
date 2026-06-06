#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <cstddef>

// Forward declaration to avoid including matrix.hpp here and
// to prevent include-path issues in editors/IDEs. The full
// definition of Matrix must be available where these functions
// are implemented or where Matrix is used concretely.
class Matrix;

enum class TokType { NUM, ID, OP_PLUS, OP_MINUS, OP_MUL, END };
struct Token { TokType type; std::string lexeme; };

// Splits raw input into tokens
std::vector<Token> tokenize(const std::string& input);

// Evaluates a token stream against the current workspace
Matrix evaluate(const std::vector<Token>& tokens, const std::unordered_map<std::string, Matrix>& ws);