#ifndef ERROR_H
#define ERROR_H

#include <print>

class ErrorReporter {

  public:
    void report(int lineNumber, std::string_view where, std::string_view message) {
        std::println("[line {}] Error{}: {}", lineNumber, where, message);
        hadError = true;
    }

    void error(int lineNumber, std::string_view message) {
        report(lineNumber, "", message);
    }

  private:
    bool hadError{false};
};
#endif // !ERROR_H
