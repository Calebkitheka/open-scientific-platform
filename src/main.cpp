#pragma warning(disable : 4996) // MSVC: suppress system() deprecation warning

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Trim leading/trailing whitespace
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

int main() {
    std::cout << "🔬 SciShell v0.1.2 | Type 'help' for commands, 'exit' to quit\n\n";
    
    std::vector<std::string> history;
    std::string input;

    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, input);
        
        std::string cmd = trim(input);
        if (cmd.empty()) continue; // Skip blank lines

        history.push_back(cmd);

        if (cmd == "exit" || cmd == "quit") {
            std::cout << "👋 Exiting SciShell. Goodbye!\n";
            break;
        } 
        else if (cmd == "clear" || cmd == "cls") {
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
            continue;
        } 
        else if (cmd == "help") {
            std::cout << "📖 Available commands:\n"
                      << "  help      - Show this message\n"
                      << "  clear/cls - Clear terminal\n"
                      << "  history   - Show command history\n"
                      << "  exit      - Quit\n\n";
            continue;
        } 
        else if (cmd == "history") {
            std::cout << "📜 Command History:\n";
            for (size_t i = 0; i < history.size(); ++i) {
                std::cout << "  " << (i + 1) << ". " << history[i] << "\n";
            }
            std::cout << "\n";
            continue;
        } 
        else {
            std::cout << "⚠️  Unknown command: '" << cmd << "'\n"
                      << "💡 Type 'help' for available commands.\n\n";
        }
    }
    return 0;
}