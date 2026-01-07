#include "../ast/trees.h"

class Interpreter : Visitor<Type> {
  public:
    Interpreter() = default;

    Interpreter(const Interpreter&) = delete;
    Interpreter& operator=(const Interpreter&) = delete;

    Interpreter(Interpreter&&) noexcept = delete;
    Interpreter& operator=(Interpreter&&) = delete;

    ~Interpreter() = default;
    
    Type interpret(const Expression<Type>& expr) const;
    Type visit(const Binary<Type>& expr) const;
    Type visit(const Grouping<Type>& expr) const;
    Type visit(const Literal<Type>& expr) const;
    Type visit(const Unary<Type>& expr) const;
};
