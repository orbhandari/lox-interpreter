#include "astPrinter.h"

std::string AstPrinter::print(Expression<std::string>& expr) const {
    return expr.accept(*this);
}

std::string AstPrinter::visit(const Binary<std::string>& expr) const {
    return parenthesize(expr.op().getLexeme(), {expr.left(), expr.right()});
}

std::string AstPrinter::visit(const Grouping<std::string>& expr) const {
    return parenthesize("group", {expr.expr()});
}

std::string AstPrinter::visit(const Literal<std::string>& expr) const {
    return toString(expr.getLiteral());
}

std::string AstPrinter::visit(const Unary<std::string>& expr) const {
    return parenthesize(expr.op().getLexeme(), {expr.right()});
}

std::string AstPrinter::parenthesize(
    std::string_view name,
    std::initializer_list<std::reference_wrapper<const Expression<std::string>>> exprs) const {

    std::string buffer{};

    buffer += "(";
    buffer += name;

    for (const auto& expr : exprs) {
        buffer.append(" ");
        buffer.append(expr.get().accept(*this));
    }

    buffer += ")";
    return buffer;
}
