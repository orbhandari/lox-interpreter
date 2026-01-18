#ifndef PARSER_H
#define PARSER_H

#include "../ast/trees.h"
#include "../error.h"
#include "../typing/token.h"
#include <cassert>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <vector>

/*
 * Recursive descent parser.
 * Concrete implementation are at the bottom of the file. This is required due to templating.
 */
template <typename R>
class Parser {
  public:
    Parser(const std::vector<Token>& tokens) : m_tokens{tokens} {}
    // or: Parser(std::vector<Token> tokens) : m_tokens{std::move(tokens)} {}

    /*
     * Kicks off the parsing of an AST.
     */
    std::unique_ptr<Expression<R>> parse();

  private:
    struct ParseError;

    /*
     * Recursive functions to consume.
     */
    std::unique_ptr<Expression<R>> expression();
    std::unique_ptr<Expression<R>> equality();
    std::unique_ptr<Expression<R>> comparison();
    std::unique_ptr<Expression<R>> term();
    std::unique_ptr<Expression<R>> factor();
    std::unique_ptr<Expression<R>> unary();
    std::unique_ptr<Expression<R>> primary();

    /*
     * Helper functions to perform parsing.
     */
    bool match(std::initializer_list<TokenType> types);
    bool check(TokenType type);
    bool isAtEnd();
    Token advance();
    Token previous();
    Token peek();
    Token consume(TokenType type, std::string_view message);
    ParseError error(Token token, std::string_view message);
    void synchronize();

  private:
    struct ParseError : public std::runtime_error {
        explicit ParseError(std::string msg) : std::runtime_error(std::move(msg)) {}
    };

    std::vector<Token> m_tokens;
    int m_current{0};
    ErrorReporter m_errorReporter{"Parser"};
};

template <typename R>
auto Parser<R>::parse() -> std::unique_ptr<Expression<R>> {
    try {
        return expression();
    } catch (const ParseError&) {
        std::println(std::cerr, "Parse error caught at top level parse().");
        return nullptr;
    } catch (...) {
        std::println(std::cerr, "Unknown error caught at top level parse().");
        return nullptr;
    }
}

template <typename R>
auto Parser<R>::expression() -> std::unique_ptr<Expression<R>> {
    return equality();
}

template <typename R>
auto Parser<R>::equality() -> std::unique_ptr<Expression<R>> {
    auto expr = comparison();

    while (match({TokenType::_bang_equal, TokenType::_equal_equal})) {
        Token oper = previous();
        auto right = comparison();
        expr = std::make_unique<Binary<R>>(std::move(expr), oper, std::move(right));
    }

    return expr;
}

template <typename R>
auto Parser<R>::comparison() -> std::unique_ptr<Expression<R>> {
    auto expr = term();

    while (match({TokenType::_greater, TokenType::_greater_equal, TokenType::_less,
                  TokenType::_less_equal})) {
        Token oper = previous();
        auto right = term();
        expr = std::make_unique<Binary<R>>(std::move(expr), oper, std::move(right));
    }

    return expr;
}

template <typename R>
auto Parser<R>::term() -> std::unique_ptr<Expression<R>> {
    auto expr = factor();

    while (match({TokenType::_minus, TokenType::_plus})) {
        Token oper = previous();
        auto right = factor();
        expr = std::make_unique<Binary<R>>(std::move(expr), oper, std::move(right));
    }

    return expr;
}

template <typename R>
auto Parser<R>::factor() -> std::unique_ptr<Expression<R>> {
    auto expr = unary();

    while (match({TokenType::_slash, TokenType::_star})) {
        Token oper = previous();
        auto right = unary();
        expr = std::make_unique<Binary<R>>(std::move(expr), oper, std::move(right));
    }

    return expr;
}

template <typename R>
auto Parser<R>::unary() -> std::unique_ptr<Expression<R>> {
    if (match({TokenType::_minus, TokenType::_bang})) {
        Token oper = previous();
        auto right = unary();
        return std::make_unique<Unary<R>>(oper, std::move(right));
    }

    return primary();
}

template <typename R>
auto Parser<R>::primary() -> std::unique_ptr<Expression<R>> {
    if (match({TokenType::_true})) {
        return std::make_unique<Literal<R>>(true);
    }
    if (match({TokenType::_false})) {
        return std::make_unique<Literal<R>>(false);
    }
    if (match({TokenType::_nil})) {
        return std::make_unique<Literal<R>>(std::nullopt);
    }
    if (match({TokenType::_number, TokenType::_string})) {
        return std::make_unique<Literal<R>>(previous().getLiteral());
    }
    if (match({TokenType::_left_paren})) {
        auto expr = expression();
        consume(TokenType::_right_paren, "Expect ')' after expression.");
        return std::make_unique<Grouping<R>>(std::move(expr));
    }

    throw error(peek(), "Expected expression.");
}

// Helper functions
template <typename R>
auto Parser<R>::match(std::initializer_list<TokenType> types) -> bool {
    for (auto type : types) {
        if (check(type)) {
            advance();
            return true;
        }
    }
    return false;
}

template <typename R>
auto Parser<R>::check(TokenType type) -> bool {
    if (isAtEnd()) {
        return false;
    }
    return peek().getType() == type;
}

template <typename R>
auto Parser<R>::advance() -> Token {
    if (!isAtEnd()) {
        ++m_current;
    }
    return previous();
}

template <typename R>
auto Parser<R>::isAtEnd() -> bool {
    return peek().getType() == TokenType::_eof;
}

template <typename R>
auto Parser<R>::peek() -> Token {
    assert(m_current < std::ssize(m_tokens) && "Out of bounds access.");
    return m_tokens[m_current];
}

template <typename R>
auto Parser<R>::previous() -> Token {
    assert(m_current - 1 < std::ssize(m_tokens) && "Out of bounds access.");
    return m_tokens[m_current - 1];
}

template <typename R>
auto Parser<R>::consume(TokenType type, std::string_view message) -> Token {
    if (check(type)) {
        return advance();
    }
    throw error(peek(), message);
}

template <typename R>
auto Parser<R>::error(Token token, std::string_view message) -> ParseError {
    m_errorReporter.error(token, message);
    return ParseError{std::string{message}};
}

template <typename R>
auto Parser<R>::synchronize() -> void {
    advance();

    while (!isAtEnd()) {
        if (previous().getType() == TokenType::_semicolon) {
            return;
        }

        switch (peek().getType()) {
        case TokenType::_class:
        case TokenType::_fun:
        case TokenType::_var:
        case TokenType::_for:
        case TokenType::_if:
        case TokenType::_while:
        case TokenType::_print:
        case TokenType::_return:
            return;
        default:
            break;
        }

        advance();
    }
}

#endif // PARSER_H
