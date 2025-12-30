#include "lexer.h"
#include "tokentypes.h"
#include "types.h"
#include <optional>
#include <string>

Lexer::Lexer(std::string source) : m_source{source} {}

auto Lexer::consume() -> char {
    return m_source[m_current++];
}

auto Lexer::addToken(TokenType token) -> void {
    addToken(token, std::nullopt);
}

auto Lexer::addToken(TokenType token, Type literal) -> void {
    std::string lexeme{m_source.substr(m_start, m_current - m_start + 1)};
    m_tokens.emplace_back(token, lexeme, literal, m_line);
}

auto Lexer::lexToken() -> void {

    char c{consume()};
    switch (c) {
    case '(':
        addToken(_left_paren);
        break;
    case ')':
        addToken(_right_paren);
        break;
    case '{':
        addToken(_left_brace);
        break;
    case '}':
        addToken(_right_brace);
        break;
    case ',':
        addToken(_comma);
        break;
    case '.':
        addToken(_dot);
        break;
    case '-':
        addToken(_minus);
        break;
    case '+':
        addToken(_plus);
        break;
    case ';':
        addToken(_semicolon);
        break;
    case '*':
        addToken(_star);
        break;
    default:
       m_errorReporter.error(m_line, "Unexpected character.");
       break; 
    }
}

auto Lexer::isAtEnd() -> bool {
    // TODO: Is there a way NOT to static cast? Should the index variables themselves be of
    // std::size_t?
    return m_current >= static_cast<int>(m_source.length());
}

auto Lexer::lexTokens() -> std::vector<Token> {

    while (!isAtEnd()) {
        m_start = m_current;
        lexToken();
    }

    m_tokens.emplace_back(_eof, "", std::nullopt, m_line);
    return m_tokens;
}
