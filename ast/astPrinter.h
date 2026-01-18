#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include "trees.h"
#include <initializer_list>
#include <string>
#include <string_view>

// Mainly for debugging how the interpreter sees the trees.
class AstPrinter : public Visitor<std::string> {
  public:
    AstPrinter() = default;

    AstPrinter(const AstPrinter&) = delete;
    AstPrinter& operator=(const AstPrinter&) = delete;

    AstPrinter(AstPrinter&&) noexcept = delete;
    AstPrinter& operator=(AstPrinter&&) = delete;

    std::string print(const Expression<std::string>& expr) const;

    std::string visit(const Binary<std::string>& expr) const override;
    std::string visit(const Grouping<std::string>& expr) const override;
    std::string visit(const Literal<std::string>& expr) const override;
    std::string visit(const Unary<std::string>& expr) const override;

  private:
    std::string parenthesize(
        std::string_view name,
        std::initializer_list<std::reference_wrapper<const Expression<std::string>>> exprs) const;
};

#endif // AST_PRINTER_H
