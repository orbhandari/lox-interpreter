#include "../ast/trees.h"
#include "error.h"
#include "typing/types.h"

/*
 * Tree-walking interpreter.
 */
class Interpreter : Visitor<Type> {
  public:
    Interpreter() = default;

    Interpreter(const Interpreter&) = delete;
    Interpreter& operator=(const Interpreter&) = delete;

    Interpreter(Interpreter&&) noexcept = delete;
    Interpreter& operator=(Interpreter&&) = delete;

    ~Interpreter() = default;

    void interpret(const Expression<Type>& expression) ;
    Type evaluate(const Expression<Type>& expr) const;
    Type visit(const Binary<Type>& expr) const;
    Type visit(const Grouping<Type>& expr) const;
    Type visit(const Literal<Type>& expr) const;
    Type visit(const Unary<Type>& expr) const;
    void checkNumberOperand(Token opertor, Type operand) const;
    void checkNumberOperands(Token opertor, Type leftOperand, Type rightOperand) const;

    bool hadError() const {
        return m_errorReporter.hadError();
    };
    bool hadRuntimeError() const {
        return m_errorReporter.hadRuntimeError();
    };

  private:
    ErrorReporter m_errorReporter{"Interpreter"};
};
