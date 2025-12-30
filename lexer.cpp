#include "lexer.h"
#include "tokentypes.h"
#include "types.h"
#include <cctype>
#include <optional>
#include <stdexcept>
#include <string>

Lexer::Lexer(std::string source) : m_source{source} {}

const std::unordered_map<std::string, TokenType> Lexer::reservedKeywordsMap{
    {"and", _and},   {"class", _class}, {"else", _else},   {"fun", _fun},       {"if", _if},
    {"nil", _nil},   {"or", _or},       {"print", _print}, {"return", _return}, {"super", _super},
    {"this", _this}, {"true", _true},   {"false", _false}, {"while", _while},   {"var", _var},
};

auto Lexer::advance() -> char {
    return m_source[m_current++];
}

auto Lexer::addToken(TokenType token) -> void {
    addToken(token, std::nullopt);
}

auto Lexer::addToken(TokenType token, Type literal) -> void {
    std::string lexeme{m_source.substr(m_start, m_current - m_start)};
    m_tokens.emplace_back(token, lexeme, literal, m_line);
}

auto Lexer::lexToken() -> void {
    // TODO: remove char literals and abstract as constants
    char c{advance()};
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
    case '!':
        match('=') ? addToken(_bang_equal) : addToken(_bang);
        break;
    case '=':
        match('=') ? addToken(_equal_equal) : addToken(_equal);
        break;
    case '>':
        match('=') ? addToken(_greater_equal) : addToken(_greater);
        break;
    case '<':
        match('=') ? addToken(_less_equal) : addToken(_less);
        break;
    case '/':
        if (match('/')) {
            while (peek() != '\n' && !isAtEnd()) {
                advance();
            }
        } else {
            addToken(_slash);
        }
        break;
    case ' ':
    case '\r':
    case '\t':
        break;
    case '\n':
        ++m_line;
        break;
    case '"':
        addStringToken();
        break;
    default:
        if (std::isdigit(static_cast<unsigned char>(c))) {
            addNumberToken();
        } else if (std::isalpha(static_cast<unsigned char>(c))) {
            addIdentifierOrKeywordToken();
        }

        else {
            m_errorReporter.error(m_line, "Unexpected character.");
        }
        break;
    }
}

auto Lexer::addStringToken() -> void {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') {
            ++m_line;
        }
        advance();
    }

    if (isAtEnd()) {
        m_errorReporter.error(m_line, "Unterminated string.");
        return;
    }

    advance(); // consume the closing quotes

    String literal{
        m_source.substr(m_start + 1, m_current - m_start - 2)}; // string slicing syntax...
    addToken(_string, literal);
}

auto Lexer::addNumberToken() -> void {

    while (std::isdigit(static_cast<unsigned char>(peek()))) {
        advance();
    }

    // here m_current is NO longer a digit
    if (peek() == '.' && std::isdigit(static_cast<unsigned char>(peekTwice()))) {
        advance();

        while (std::isdigit(static_cast<unsigned char>(peek()))) {
            advance();
        }
    }

    try {
        Number literal{std::stod(m_source.substr(m_start, m_current - m_start))};
        addToken(_number, literal);
    } catch (const std::runtime_error& e) {
        m_errorReporter.error(m_line, e.what());
    }
}

auto Lexer::addIdentifierOrKeywordToken() -> void {
    while (std::isalpha(static_cast<unsigned char>(peek()))) {
        advance();
    }

    std::string munched{m_source.substr(m_start, m_current - m_start)};
    if (auto search{reservedKeywordsMap.find(munched)}; search != reservedKeywordsMap.end()) {
        addToken(search->second);
    } else {
        addToken(_identifier);
    }
}

auto Lexer::match(char expected) -> bool {

    if (isAtEnd())
        return false;

    if (m_source[m_current] != expected) {
        return false;
    }

    ++m_current;
    return true;
}

auto Lexer::peek() -> char {
    if (isAtEnd()) {
        return '\0';
    }
    return m_source[m_current];
}

auto Lexer::peekTwice() -> char {
    // TODO: same as peek()
    if (m_current + 1 >= static_cast<int>(m_source.length())) {
        return '\0';
    }

    return m_source[m_current + 1];
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
