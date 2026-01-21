#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include "expressionTrees.h"
#include <initializer_list>
#include <string>
#include <string_view>

/*
 * Mainly for debugging how the interpreter sees the expression trees.
 */
class AstPrinter : public Expression::Visitor<std::string> {
  public:
    AstPrinter() = default;

    AstPrinter(const AstPrinter&) = delete;
    AstPrinter& operator=(const AstPrinter&) = delete;

    AstPrinter(AstPrinter&&) noexcept = delete;
    AstPrinter& operator=(AstPrinter&&) = delete;

    std::string print(const Expression::Expression<std::string>& expr) const;

    std::string visit(const Expression::Binary<std::string>& expr) const override;
    std::string visit(const Expression::Grouping<std::string>& expr) const override;
    std::string visit(const Expression::Literal<std::string>& expr) const override;
    std::string visit(const Expression::Unary<std::string>& expr) const override;

  private:
    std::string parenthesize(
        std::string_view name,
        std::initializer_list<std::reference_wrapper<const Expression::Expression<std::string>>>
            exprs) const;
};

#endif // AST_PRINTER_H
