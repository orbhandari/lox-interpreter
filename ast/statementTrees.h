#ifndef STATEMENT_TREES
#define STATEMENT_TREES

#include "expressionTrees.h"

namespace Statement {

template <typename R>
class Visitor;

template <typename R>
class Statement {
  public:
    Statement(const Statement&) = delete; // this also means no compiler supplied move
    Statement& operator=(const Statement&) = delete;

    Statement(Statement&&) noexcept = delete;
    Statement& operator=(Statement&&) = delete;

    Statement() = default;
    virtual ~Statement() = default;

    virtual R accept(const Visitor<R>& visitor) const = 0;
};

/*
 * Statement trees.
 */
template <typename R>
class PrintStatement : public Statement<R> {
  public:
    PrintStatement(std::unique_ptr<Expression::Expression<R>> expr) : m_expr{std::move(expr)} {}

    PrintStatement(const PrintStatement&) = delete;
    PrintStatement& operator=(const PrintStatement&) = delete;

    PrintStatement(PrintStatement&&) noexcept = delete;
    PrintStatement& operator=(PrintStatement&&) = delete;

    R accept(const Visitor<R>& visitor) const override {
        return visitor.visit(*this);
    };

  private:
    std::unique_ptr<Expression::Expression<R>> m_expr;
};

template <typename R>
class ExpressionStatement : public Statement<R> {
  public:
    ExpressionStatement(std::unique_ptr<Expression::Expression<R>> expr) : m_expr{std::move(expr)} {}

    ExpressionStatement(const ExpressionStatement&) = delete;
    ExpressionStatement& operator=(const ExpressionStatement&) = delete;

    ExpressionStatement(ExpressionStatement&&) noexcept = delete;
    ExpressionStatement& operator=(ExpressionStatement&&) = delete;

    R accept(const Visitor<R>& visitor) const override {
        return visitor.visit(*this);
    };

  private:
    std::unique_ptr<Expression::Expression<R>> m_expr;
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

    virtual R visit(const ExpressionStatement<R>& expr) const = 0;
    virtual R visit(const PrintStatement<R>& expr) const = 0;
};

} // namespace Statement

#endif
