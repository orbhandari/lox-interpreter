#include "./lexer/lexer.h"
#include <fstream>
#include <iostream>
#include <print>
#include <sstream>
#include <vector>

void run(std::string);
void runFile(const std::string& path);
void runPrompt();

int main(int argc, char* argv[]) {
    if (argc > 2) {
        std::println("Usage: cpplox [script]");
    } else if (argc == 2) {
        runFile(argv[1]);
    } else {
        runPrompt();
    }

    return 0;
}

void run(std::string source) {
    Lexer lexer{source};
    std::vector<Token> tokens{lexer.lexTokens()};

    for (const auto& token : tokens) {
        std::cout << token << "\n";
    }
}

void runFile(const std::string& path) {
    std::ifstream file{path};

    std::stringstream buffer{};
    buffer << file.rdbuf();

    run(buffer.str());
}

void runPrompt() {
    std::string line{};
    while (true) {
        std::print("> ");
        std::getline(std::cin, line);
        if (line.empty()) {
            break;
        }
        run(line);
    }
}
