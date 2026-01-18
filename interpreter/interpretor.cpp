#include "error.h"
#include "interpreter.h"
#include "typing/tokentypes.h"
#include "typing/types.h"
#include <variant>

void Interpreter::interpret(const Expression<Type>& expression) {
    try {
        Type value{evaluate(expression)};
        std::cout << value << std::endl;

    } catch (const LoxRuntimeError& e) {
        m_errorReporter.runtimeError(e);
    }
}

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
        // TODO: Clean this up, and perhaps support boolean additions?
        if (std::holds_alternative<Number>(left.value()) &&
            std::holds_alternative<Number>(right.value())) {
            return std::get<Number>(left.value()) + std::get<Number>(right.value());
        } else if (std::holds_alternative<String>(left.value()) &&
                   std::holds_alternative<String>(right.value())) {
            return std::get<String>(left.value()) + std::get<String>(right.value());
        }

        throw LoxRuntimeError{expr.op(), "Operands must be two numbers or two strings."};

    case TokenType::_minus:
        checkNumberOperands(expr.op(), left, right);
        return std::get<Number>(left.value()) - std::get<Number>(right.value());

    case TokenType::_slash:
        // Since it's a double, division by 0 will not crash.
        checkNumberOperands(expr.op(), left, right);
        return std::get<Number>(left.value()) / std::get<Number>(right.value());

    case TokenType::_star:
        checkNumberOperands(expr.op(), left, right);
        return std::get<Number>(left.value()) * std::get<Number>(right.value());

    // Rely on the variant operators overloads themselves.
    // Null values are treated as less than any other values.
    // Null values are equal to each other.
    // Underlying variant type is compared if not null.
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

    default:
        return std::nullopt;
    }

    // Unreachable.
    return std::nullopt;
}

Type Interpreter::visit(const Grouping<Type>& expr) const {
    return evaluate(expr.expr());
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
        checkNumberOperand(expr.op(), right);
        return std::get<Number>(right.value());
    case TokenType::_bang:
        // TODO: handle NULL values?
        // what is truthy?
        return !std::get<Boolean>(right.value());
    default:
        return std::nullopt;
    }

    // Unreachable.
    return std::nullopt;
}

void Interpreter::checkNumberOperand(Token opertor, Type operand) const {

    if (operand.has_value() && std::holds_alternative<Number>(operand.value())) {
        return;
    }

    throw LoxRuntimeError{opertor, "Unary operand must be a number."};
}

void Interpreter::checkNumberOperands(Token opertor, Type leftOperand, Type rightOperand) const {

    if (leftOperand.has_value() && rightOperand.has_value() &&
        std::holds_alternative<Number>(leftOperand.value()) &&
        std::holds_alternative<Number>(rightOperand.value())) {
        return;
    }

    throw LoxRuntimeError{opertor, "Binary operand must be a number."};
}
