#include <iostream>
#include <string>

int main() {
    std::cout << "🔬 SciShell v0.1.0 | Day 1 Online\n";
    std::cout << "Type 'exit' to quit.\n\n";
    
    std::string input;
    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, input);
        
        if (input == "exit" || input == "quit") {
            std::cout << "👋 Goodbye!\n";
            break;
        }
        std::cout << "⚠️ Command not recognized yet. Type 'exit' to quit.\n";
    }
    return 0;
}