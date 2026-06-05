#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cctype>
#include "matrix.hpp"

// Utility: trim whitespace
std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

// Validate simple variable names (letters/numbers/underscore, starts with letter)
bool is_valid_identifier(const std::string& id) {
    if (id.empty() || !std::isalpha(static_cast<unsigned char>(id[0]))) return false;
    for (char c : id) {
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '_') return false;
    }
    return true;
}

// Parse "[1, 2; 3, 4]" into a Matrix
Matrix parse_matrix_literal(const std::string& raw) {
    std::string inner = raw;
    if (inner.size() < 2 || inner.front() != '[' || inner.back() != ']') {
        throw std::invalid_argument("Matrix must be enclosed in [ ]");
    }
    inner = inner.substr(1, inner.size() - 2); // strip brackets

    std::vector<std::vector<double>> rows;
    std::stringstream ss(inner);
    std::string row_str;

    while (std::getline(ss, row_str, ';')) {
        std::vector<double> row_data;
        std::stringstream row_ss(row_str);
        std::string cell;
        while (std::getline(row_ss, cell, ',')) {
            row_data.push_back(std::stod(trim(cell)));
        }
        rows.push_back(row_data);
    }

    if (rows.empty()) throw std::invalid_argument("Empty matrix");
    size_t cols = rows[0].size();
    Matrix result(rows.size(), cols);
    for (size_t r = 0; r < rows.size(); ++r) {
        if (rows[r].size() != cols) throw std::invalid_argument("Inconsistent column count across rows");
        for (size_t c = 0; c < cols; ++c) {
            result.at(r, c) = rows[r][c];
        }
    }
    return result;
}

int main() {
    std::cout << "🔬 SciShell v0.1.4 | Type 'help', assign variables, or type 'exit'\n\n";
    
    std::unordered_map<std::string, Matrix> workspace;
    std::vector<std::string> history;
    std::string input;

    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, input);
        std::string cmd = trim(input);
        if (cmd.empty()) continue;
        history.push_back(cmd);

        try {
            // 1. Built-in commands
            if (cmd == "exit" || cmd == "quit") break;
            if (cmd == "clear" || cmd == "cls") {
                #ifdef _WIN32 system("cls"); #else system("clear"); #endif
                continue;
            }
            if (cmd == "help") {
                std::cout << "📖 Commands: help, clear/cls, history, ws, exit\n"
                          << "📝 Assign: A = [1, 2; 3, 4]\n"
                          << "🔍 Lookup: Type variable name (e.g., A)\n"
                          << "📋 Workspace: ws\n\n";
                continue;
            }
            if (cmd == "history") {
                std::cout << "📜 History:\n";
                for (size_t i = 0; i < history.size(); ++i) std::cout << "  " << (i+1) << ". " << history[i] << "\n";
                std::cout << "\n"; continue;
            }
            if (cmd == "ws") {
                std::cout << "📦 Workspace Variables:\n";
                if (workspace.empty()) std::cout << "  (empty)\n";
                for (const auto& [name, mat] : workspace) std::cout << "  " << name << " [" << mat.rows << "x" << mat.cols << "]\n";
                std::cout << "\n"; continue;
            }

            // 2. Assignment: VAR = [matrix]
            size_t eq_pos = cmd.find('=');
            if (eq_pos != std::string::npos) {
                std::string var_name = trim(cmd.substr(0, eq_pos));
                std::string value_str = trim(cmd.substr(eq_pos + 1));
                
                if (!is_valid_identifier(var_name)) throw std::invalid_argument("Invalid variable name. Use letters/numbers/underscore.");
                workspace[var_name] = parse_matrix_literal(value_str);
                std::cout << var_name << " =\n";
                workspace[var_name].print();
                continue;
            }

            // 3. Variable lookup
            if (workspace.count(cmd)) {
                std::cout << cmd << " =\n";
                workspace[cmd].print();
                continue;
            }

            // 4. Unknown
            std::cout << "⚠️ Unknown command or variable: '" << cmd << "'\n\n";

        } catch (const std::exception& e) {
            std::cout << "❌ Error: " << e.what() << "\n\n";
        }
    }
    std::cout << "👋 Exiting. Goodbye!\n";
    return 0;
}