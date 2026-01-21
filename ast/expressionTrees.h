#ifndef EXPRESSION_TREES_H
#define EXPRESSION_TREES_H

#include "../typing/token.h"
#include <memory>

/*
 * Each tree is templated to match the visitor that visits it, and C++ does not support templated
 * virtual functions either.
 */

namespace Expression {

template <typename R>
class Visitor;

template <typename R>
class Expression {
  public:
    Expression(const Expression&) = delete; // this also means no compiler supplied move
    Expression& operator=(const Expression&) = delete;

    Expression(Expression&&) noexcept = delete;
    Expression& operator=(Expression&&) = delete;

    Expression() = default;
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
    Binary(std::unique_ptr<Expression<R>> left_operand, Token op,
           std::unique_ptr<Expression<R>> right_operand)
        : m_left_operand{std::move(left_operand)}, m_right_operand{std::move(right_operand)},
          m_operator{op} {}

    Binary(const Binary&) = delete;
    Binary& operator=(const Binary&) = delete;

    Binary(Binary&&) noexcept = delete;
    Binary& operator=(Binary&&) = delete;

    R accept(const Visitor<R>& visitor) const override {
        return visitor.visit(*this);
    };

    const Expression<R>& left() const {
        return *m_left_operand;
    }
    const Expression<R>& right() const {
        return *m_right_operand;
    }
    const Token& op() const {
        return m_operator;
    }

  private:
    std::unique_ptr<Expression<R>> m_left_operand;
    std::unique_ptr<Expression<R>> m_right_operand;
    Token m_operator;
};

template <typename R>
class Grouping final : public Expression<R> {
  public:
    Grouping(std::unique_ptr<Expression<R>> expression) : m_expression{std::move(expression)} {};

    Grouping(const Grouping&) = delete;
    Grouping& operator=(const Grouping&) = delete;

    Grouping(Grouping&&) noexcept = delete;
    Grouping& operator=(Grouping&&) = delete;

    R accept(const Visitor<R>& visitor) const override {
        return visitor.visit(*this);
    };

    const Expression<R>& expr() const {
        return *m_expression;
    }

  private:
    std::unique_ptr<Expression<R>> m_expression;
};

template <typename R>
class Literal final : public Expression<R> {
  public:
    Literal(Type literal) : m_literal{literal} {}

    Literal(const Literal&) = delete;
    Literal& operator=(const Literal&) = delete;

    Literal(Literal&&) noexcept = delete;
    Literal& operator=(Literal&&) = delete;

    R accept(const Visitor<R>& visitor) const override {
        return visitor.visit(*this);
    };

    Type getLiteral() const {
        return m_literal;
    }

  private:
    Type m_literal;
};

template <typename R>
class Unary : public Expression<R> {
  public:
    // op stands for operator, as operator is a reserverd keyword
    Unary(Token op, std::unique_ptr<Expression<R>> right_operand)
        : m_operator{op}, m_right_operand{std::move(right_operand)} {};

    Unary(const Unary&) = delete;
    Unary& operator=(const Unary&) = delete;

    Unary(Unary&&) noexcept = delete;
    Unary& operator=(Unary&&) = delete;

    R accept(const Visitor<R>& visitor) const override {
        return visitor.visit(*this);
    };

    const Expression<R>& right() const {
        return *m_right_operand;
    }
    const Token& op() const {
        return m_operator;
    }

  private:
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
    Visitor& operator=(const Visitor&) = delete;

    Visitor(Visitor&&) noexcept = delete;
    Visitor& operator=(Visitor&&) = delete;

    virtual ~Visitor() = default;

    virtual R visit(const Binary<R>& expr) const = 0;
    virtual R visit(const Grouping<R>& expr) const = 0;
    virtual R visit(const Literal<R>& expr) const = 0;
    virtual R visit(const Unary<R>& expr) const = 0;
};

} // namespace Expression

#endif // EXPRESSION_TREES_H
