#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "matrix.hpp"

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

void run_matrix_tests() {
    std::cout << "🧪 Running Matrix Tests...\n";
    try {
        Matrix A(2, 2);
        A.at(0,0) = 1.0; A.at(0,1) = 2.0;
        A.at(1,0) = 3.0; A.at(1,1) = 4.0;

        Matrix B(2, 2);
        B.at(0,0) = 5.0; B.at(0,1) = 6.0;
        B.at(1,0) = 7.0; B.at(1,1) = 8.0;

        std::cout << "A:\n"; A.print();
        std::cout << "B:\n"; B.print();

        Matrix C = A + B;
        std::cout << "C = A + B:\n"; C.print();

        bool pass = (C.at(0,0) == 6.0 && C.at(1,1) == 12.0);
        std::cout << (pass ? "✅ All tests passed!\n\n" : "❌ Test failed!\n\n");
    } catch (const std::exception& e) {
        std::cout << "❌ Exception: " << e.what() << "\n\n";
    }
}

int main() {
    std::cout << "🔬 SciShell v0.1.3 | Type 'help' for commands, 'exit' to quit\n\n";
    std::vector<std::string> history;
    std::string input;

    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, input);
        std::string cmd = trim(input);
        if (cmd.empty()) continue;
        history.push_back(cmd);

        if (cmd == "exit" || cmd == "quit") break;
        else if (cmd == "clear" || cmd == "cls") {
            #ifdef _WIN32 system("cls"); #else system("clear"); #endif
            continue;
        } else if (cmd == "help") {
            std::cout << "📖 Commands: help, clear/cls, history, test, exit\n\n";
            continue;
        } else if (cmd == "history") {
            std::cout << "📜 History:\n";
            for (size_t i = 0; i < history.size(); ++i) std::cout << "  " << (i+1) << ". " << history[i] << "\n";
            std::cout << "\n"; continue;
        } else if (cmd == "test") {
            run_matrix_tests(); continue;
        } else {
            std::cout << "⚠️ Unknown command: '" << cmd << "'\n\n";
        }
    }
    std::cout << "👋 Exiting. Goodbye!\n";
    return 0;
}