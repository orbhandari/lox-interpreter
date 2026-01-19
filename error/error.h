#ifndef ERROR_H
#define ERROR_H

#include "typing/token.h"
#include "typing/tokentypes.h"
#include <print>
#include <stdexcept>
#include <string_view>

struct LoxRuntimeError : public std::runtime_error {
    Token m_token;

    LoxRuntimeError(Token token, std::string_view message)
        : std::runtime_error{static_cast<std::string>(message)}, m_token{token} {};
};

class ErrorReporter {
  public:
    ErrorReporter(std::string_view name) : m_name{name} {};
    void report(int lineNumber, std::string_view where, std::string_view message) {
        std::println("[line {}] Error{}: {}", lineNumber, where, message);
        m_hadError = true;
    }

    void error(int lineNumber, std::string_view message) {
        report(lineNumber, "", message);
    }

    void error(Token token, std::string_view message) {
        if (token.getType() == TokenType::_eof)
            report(token.getLine(), " at end", message);
        else
            report(token.getLine(), " at '" + token.getLexeme() + "'", message);
    }

    void runtimeError(LoxRuntimeError error) {
        std::cout << error.what() << "\n";
        std::cout << "[line " << error.m_token.getLine() << "]" << "\n";

        m_hadRuntimeError = true;
    }

    bool hadError() const {
        return m_hadError;
    };
    bool hadRuntimeError() const {
        return m_hadRuntimeError;
    };

  private:
    std::string m_name{"???"};
    bool m_hadError{false};
    bool m_hadRuntimeError{false};
};

#endif // !ERROR_H
