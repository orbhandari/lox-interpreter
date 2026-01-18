#include "interpreter.h"
#include "typing/tokentypes.h"
#include "typing/types.h"

Type Interpreter::evaluate(const Expression<Type>& expr) const {
    return expr.accept(*this);
}

Type Interpreter::visit(const Binary<Type>& expr) const {

    auto left{evaluate(expr.left())};
    auto right{evaluate(expr.right())};

    switch (expr.op().getType()) {
    // TODO: Handle null optionals rather than .value.
    // TODO: What if std::get fails? i.e. wrong variant?
    case TokenType::_plus:
        // TODO: handle string concat, and bool concat?
        return std::get<Number>(left.value()) + std::get<Number>(right.value());
    case TokenType::_minus:
        return std::get<Number>(left.value()) - std::get<Number>(right.value());
    case TokenType::_slash:
        // Since it's a double, division by 0 will not crash.
        return std::get<Number>(left.value()) / std::get<Number>(right.value());
    case TokenType::_star:
        return std::get<Number>(left.value()) * std::get<Number>(right.value());
    // Rely on the variant operators overloads themselves.
    case TokenType::_greater:
        return left > right;
    case TokenType::_greater_equal:
        return left >= right;
    case TokenType::_less:
        return left < right;
    case TokenType::_less_equal:
        return left <= right;
    case TokenType::_equal_equal:
        return left == right;
    case TokenType::_bang_equal:
        return left != right;
    // Unreachable case.
    default:
        return std::nullopt;
    }
}

Type Interpreter::visit(const Grouping<Type>& expr) const {
    return evaluate(expr);
}

Type Interpreter::visit(const Literal<Type>& expr) const {
    return expr.getLiteral();
}

Type Interpreter::visit(const Unary<Type>& expr) const {

    auto right{evaluate(expr.right())};

    switch (expr.op().getType()) {
    // TODO: Handle null optionals rather than .value.
    // TODO: What if std::get fails? i.e. wrong variant?
    case TokenType::_minus:
        // TODO: handle NULL values?
        return std::get<Number>(right.value());
    case TokenType::_bang:
        // TODO: handle NULL values?
        // what is truthy?
        return !std::get<Boolean>(right.value());
    // Unreachable case.
    default:
        return std::nullopt;
    }
}
