#ifndef TOKEN_H
#define TOKEN_H

#include "tokentypes.h"
#include "types.h"
#include <string>

class Token {
  private:
    TokenType m_type{};
    std::string m_lexeme;
    Type m_literal;
    [[maybe_unused]] int m_line;

  public:
    Token(TokenType type, std::string_view lexeme, Type literal, int line)
        : m_type{type}, m_lexeme(lexeme), m_literal{literal}, m_line{line} {}

    std::string getLexeme() const {
        return m_lexeme;
    }

    TokenType getType() const {
        return m_type;
    }

    Type getLiteral() const {
        return m_literal;
    }

    int getLine() const {
        return m_line;
    }

    friend std::ostream& operator<<(std::ostream& out, const Token& token) {
        out << token.m_type << " " << token.m_lexeme << " " << token.m_literal;
        return out;
    }
};

#endif
