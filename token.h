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

    friend std::ostream& operator<<(std::ostream& out, const Token& token) {
        out << token.m_type << " " << token.m_lexeme << " ";
        if (token.m_literal.has_value()) {
            // TODO: note that if its a double, then we may need to set precision here
            std::visit([&out](const auto& v) { out << v; }, token.m_literal.value());
        } else {
            out << "Nil";
        }
        return out;
    }
};

#endif
