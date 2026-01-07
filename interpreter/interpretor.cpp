#include "interpreter.h"
#include <stdexcept>

Type Interpreter::interpret(const Expression<Type>& expr) const {
    throw std::runtime_error("unimplemented");
}

Type Interpreter::visit(const Binary<Type>& expr) const {
    throw std::runtime_error("unimplemented");
}
Type Interpreter::visit(const Grouping<Type>& expr) const {
    throw std::runtime_error("unimplemented");
}
Type Interpreter::visit(const Literal<Type>& expr) const {
    throw std::runtime_error("unimplemented");
}
Type Interpreter::visit(const Unary<Type>& expr) const {
    throw std::runtime_error("unimplemented");
}
