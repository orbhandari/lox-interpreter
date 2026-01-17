#ifndef ERROR_H
#define ERROR_H

#include "typing/token.h"
#include "typing/tokentypes.h"
#include <print>
#include <string_view>

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

  private:
    std::string m_name{"???"};
    bool m_hadError{false};
};
#endif // !ERROR_H
