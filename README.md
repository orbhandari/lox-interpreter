# Lox Interpreter (C++ version)
A C++23 interpreter for the Lox programming language.

The Java version of the interpreter and language itself were created by Robert Nystrom at https://craftinginterpreters.com/. I decided to go with C++ as a *learning* opportunity.

## How it works
wip

## TODOs
- Implement a RPN (reverse Polish notation) Visitor class as practice
- Support and implement comma expressions
- Support and implement ternary operator `?:`
- Add error production to handle binary operations without a left operand
- Reorganize repo structure to be more conventional, perhaps with `src` and `include` directories
- Add `GoogleTest` framework for structured test cases
- Support binary operation on Number + string. The resulting operation should be a concatenated string.
