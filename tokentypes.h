#ifndef TOKEN_TYPES_H
#define TOKEN_TYPES_H

#include <iostream>

enum class TokenType {
    _invalid_token,

    // Single character tokens
    _left_paren,
    _right_paren,
    _left_brace,
    _right_brace,
    _comma,
    _dot,
    _minus,
    _plus,
    _semicolon,
    _slash,
    _star,

    // One or two character tokens
    _bang,
    _bang_equal,
    _equal,
    _equal_equal,
    _greater,
    _greater_than,
    _less,
    _less_than,

    // literals
    _identifier,
    _string,
    _number,

    // keywords
    _and,
    _class,
    _else,
    _fun,
    _if,
    _nil,
    _or,
    _print,
    _return,
    _super,
    _this,
    _true,
    _false,
    _while,

    _eof,
};

inline std::ostream& operator<<(std::ostream& out, const TokenType& token) {
    using enum TokenType; // C++20; remove this and qualify with TokenType:: if needed

    switch (token) {
    case _invalid_token:
        out << "invalid_token";
        break;

    // Single character tokens
    case _left_paren:
        out << "left_paren";
        break;
    case _right_paren:
        out << "right_paren";
        break;
    case _left_brace:
        out << "left_brace";
        break;
    case _right_brace:
        out << "right_brace";
        break;
    case _comma:
        out << "comma";
        break;
    case _dot:
        out << "dot";
        break;
    case _minus:
        out << "minus";
        break;
    case _plus:
        out << "plus";
        break;
    case _semicolon:
        out << "semicolon";
        break;
    case _slash:
        out << "slash";
        break;
    case _star:
        out << "star";
        break;

    // One or two character tokens
    case _bang:
        out << "bang";
        break;
    case _bang_equal:
        out << "bang_equal";
        break;
    case _equal:
        out << "equal";
        break;
    case _equal_equal:
        out << "equal_equal";
        break;
    case _greater:
        out << "greater";
        break;
    case _greater_than:
        out << "greater_than";
        break;
    case _less:
        out << "less";
        break;
    case _less_than:
        out << "less_than";
        break;

    // literals
    case _identifier:
        out << "identifier";
        break;
    case _string:
        out << "string";
        break;
    case _number:
        out << "number";
        break;

    // keywords
    case _and:
        out << "and";
        break;
    case _class:
        out << "class";
        break;
    case _else:
        out << "else";
        break;
    case _fun:
        out << "fun";
        break;
    case _if:
        out << "if";
        break;
    case _nil:
        out << "nil";
        break;
    case _or:
        out << "or";
        break;
    case _print:
        out << "print";
        break;
    case _return:
        out << "return";
        break;
    case _super:
        out << "super";
        break;
    case _this:
        out << "this";
        break;
    case _true:
        out << "true";
        break;
    case _false:
        out << "false";
        break;
    case _while:
        out << "while";
        break;

    case _eof:
        out << "eof";
        break;
    }

    return out;
}

#endif
