#ifndef TREES_H
#define TREES_H

#include "../typing/token.h"
#include <initializer_list>
#include <memory>
#include <string>

/*
 * Each tree is templated to match the visitor that visits it, and C++ does not support templated
 * virtual functions either.
 *
 * Members are chosen to use pointers to utilize dynamic dispatching, but this might prove to be
 * slow.
 */

template <typename R>
class Visitor;

template <typename R>
class Expression {
  public:
    Expression(const Expression<R>&) = delete; // this also means no compiler supplied move
    Expression(Expression<R>&&) = default;
    virtual ~Expression() = default;

    virtual R accept(const Visitor<R>& visitor) const = 0;
};

/*
 * Expression trees.
 */
template <typename R>
class Binary final : public Expression<R> {
  public:
    // op stands for operator, as operator is a reserverd keyword
    Binary(Expression<R>* left_operand, Token op, Expression<R>* right_operand)
        : m_left_operand{left_operand}, m_right_operand{right_operand}, m_operator{op} {}

    Binary(const Binary&) = delete;
    Binary(const Binary&&) = default;

    R accept(const Visitor<R>& visitor) const override {
        return visitor.visit(this);
    };

    std::unique_ptr<Expression<R>> m_left_operand;
    std::unique_ptr<Expression<R>> m_right_operand;
    Token m_operator;
};

template <typename R>
class Grouping final : public Expression<R> {
  public:
    Grouping(Expression<R>* expression) : m_expression{expression} {};
    Grouping(const Grouping&) = delete;
    Grouping(Grouping&&) = default;

    R accept(const Visitor<R>& visitor) const override {
        return visitor.visit(this);
    };

    std::unique_ptr<Expression<R>> m_expression;
};

template <typename R>
class Literal final : public Expression<R> {
  public:
    Literal(Type literal) : m_literal{literal} {}
    Literal(const Literal&) = delete;
    Literal(Literal&&) = default;

    R accept(const Visitor<R>& visitor) const override {
        return visitor.visit(this);
    };

    Type m_literal;
};

template <typename R>
class Unary : public Expression<R> {
  public:
    // op stands for operator, as operator is a reserverd keyword
    Unary(Token op, Expression<R>* right_operand)
        : m_operator{op}, m_right_operand{right_operand} {};
    R accept(const Visitor<R>& visitor) const override {
        return visitor.visit(this);
    };

    Unary(const Unary&) = delete;
    Unary(const Unary&&) = default;

    std::unique_ptr<Expression<R>> m_right_operand;
    Token m_operator;
};

/*
 * Use the visitor pattern to minimize code changes in the syntax trees themselves. Separates the
 * algorithm (here) from the class types (trees.h)
 */
template <typename R>
class Visitor {
  public:
    Visitor() = default;
    Visitor(const Visitor&) = delete;
    Visitor(Visitor&&) = default;

    virtual ~Visitor() = default;

    virtual R visit(const Binary<R>* expr) const = 0;
    virtual R visit(const Grouping<R>* expr) const = 0;
    virtual R visit(const Literal<R>* expr) const = 0;
    virtual R visit(const Unary<R>* expr) const = 0;
};

/*
 * Mainly for debugging how interpreter sees the trees.
 */
class AstPrinter : Visitor<std::string> {
  public:
    AstPrinter() = default;
    AstPrinter(const AstPrinter&) = delete;
    AstPrinter(AstPrinter&&) = default;

    std::string print(Expression<std::string>* expr) const {
        return expr->accept(*this);
    }

    std::string visit(const Binary<std::string>* expr) const override {
        return parenthesize(expr->m_operator.getLexeme(),
                            {expr->m_left_operand.get(), expr->m_right_operand.get()});
    }

    std::string visit(const Grouping<std::string>* expr) const override {
        return parenthesize("group", {expr->m_expression.get()});
    }

    std::string visit(const Literal<std::string>* expr) const override {
        return toString(expr->m_literal);
    }

    std::string visit(const Unary<std::string>* expr) const override {
        return parenthesize(expr->m_operator.getLexeme(), {expr->m_right_operand.get()});
    }

    std::string parenthesize(std::string_view name,
                             std::initializer_list<Expression<std::string>* const> exprs) const {

        std::string buffer{};
        buffer += "(";
        buffer += name;

        for (const auto& expr : exprs) {
            buffer.append(" ");
            buffer.append(expr->accept(*this));
        }

        buffer += ")";

        return buffer;
    }
};
#endif // !TREES_H
