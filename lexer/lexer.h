#include "../error.h"
#include "../typing/token.h"
#include "../typing/tokentypes.h"
#include <string>
#include <unordered_map>
#include <vector>

class Lexer {
    using enum TokenType;

  public:
    Lexer(std::string source);
    Lexer(Lexer&&) = default;
    Lexer(const Lexer&) = default;
    Lexer& operator=(Lexer&&) = default;
    Lexer& operator=(const Lexer&) = default;
    ~Lexer() = default;

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

  private:
    int m_start{0};
    int m_current{0};
    int m_line{1};
    std::string m_source;
    std::vector<Token> m_tokens;
    ErrorReporter m_errorReporter;

    static const std::unordered_map<std::string, TokenType> reservedKeywordsMap;
};
