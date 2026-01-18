#include "./interpreter/interpreter.h"
#include "./lexer/lexer.h"
#include "./parser/parser.h"
#include "typing/types.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <print>
#include <sstream>

void run(std::string);
void runFile(const std::string& path);
void runPrompt();

static Interpreter interpreter;

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
    auto tokens{lexer.lexTokens()};

    Parser<Type> parser{tokens};
    auto expression{parser.parse()};

    if (lexer.hadError() || parser.hadError()) {
        return;
    }

    interpreter.interpret(*expression);
}

// File script mode.
void runFile(const std::string& path) {
    std::ifstream file{path};

    std::stringstream buffer{};
    buffer << file.rdbuf();

    run(buffer.str());

    if (interpreter.hadError()) {
        std::exit(EXIT_FAILURE);
    }

    if (interpreter.hadRuntimeError()) {
        std::exit(EXIT_FAILURE);
    }
}

// REPL mode.
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
