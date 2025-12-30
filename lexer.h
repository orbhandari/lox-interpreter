#include "token.h"
#include "tokentypes.h"
#include <string>
#include <vector>
#include "error.h"

class Lexer {
    using enum TokenType;

  public:
    Lexer(std::string source);
    Lexer(Lexer&&) = default;
    Lexer(const Lexer&) = default;
    Lexer& operator=(Lexer&&) = default;
    Lexer& operator=(const Lexer&) = default;
    ~Lexer();

    auto lexTokens() -> std::vector<Token>;
    auto lexToken() -> void;
    auto isAtEnd() -> bool;
    auto consume() -> char;
    auto addToken(TokenType token) -> void;
    auto addToken(TokenType token, Type literal) -> void;

  private:
    int m_start{0};
    int m_current{0};
    int m_line{1};
    std::string m_source;
    std::vector<Token> m_tokens;
    ErrorReporter m_errorReporter;
};
