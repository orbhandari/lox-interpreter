#ifndef LEXER_H
#define LEXER_H

#include "error/error.h"
#include "typing/token.h"
#include "typing/tokentypes.h"
#include <string>
#include <unordered_map>
#include <vector>

class Lexer {
    using enum TokenType;

  public:
    Lexer() = default;
    Lexer(std::string source);
    Lexer(Lexer&&) = default;
    Lexer(const Lexer&) = default;
    Lexer& operator=(Lexer&&) = default;
    Lexer& operator=(const Lexer&) = default;
    ~Lexer() = default;

    auto setSource(std::string source) -> void {
        m_source = source;
    }
    auto lexTokens() -> std::vector<Token>;
    auto lexToken() -> void;
    auto isAtEnd() -> bool;
    auto advance() -> char;
    auto addToken(TokenType token) -> void;
    auto addToken(TokenType token, Type literal) -> void;
    auto addStringToken() -> void;
    auto addNumberToken() -> void;
    auto addIdentifierOrKeywordToken() -> void;
    auto match(char expected) -> bool;
    auto peek() -> char;
    auto peekTwice() -> char;

    bool hadError() {
        return m_errorReporter.hadError();
    };
    bool hadRuntimeError() {
        return m_errorReporter.hadRuntimeError();
    };

  private:
    int m_start{0};
    int m_current{0};
    int m_line{1};
    std::string m_source;
    std::vector<Token> m_tokens;
    ErrorReporter m_errorReporter{"Lexer"};

    static const std::unordered_map<std::string, TokenType> reservedKeywordsMap;
};

#endif // LEXER_H
