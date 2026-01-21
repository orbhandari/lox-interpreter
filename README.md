# Lox Interpreter (C++ version)
A C++23 interpreter for the Lox programming language.

The Java version of the interpreter and language itself were created by Robert Nystrom at https://craftinginterpreters.com/. I decided to go with C++ as a *learning* opportunity.

## How it works
wip

## TODOs
- Implement a RPN (reverse Polish notation) Visitor class as practice.
- Support and implement comma expressions.
- Support and implement ternary operator `?:`.
- Add error production to handle binary operations without a left operand.
- Reorganize repo structure to be more conventional, perhaps with `src` and `include` directories.
- Add `GoogleTest` framework for structured test cases.
- Support binary operation on Number + string. The resulting operation should be a concatenated string.
- Find a better design pattern for the expression tree and statement tree split. It's very repetitive right now.
- Improve the null handling in `interpreter.cpp`.


## Some C++ learnings/notes
Correct me if I'm wrong!

- *On using `std::unique_ptr`*: In function or constructor parameters, we probably want to use pass by value rather than `const std::unique_ptr<T>&`. Why? It forces the caller to explicitly call `std::move`, which means they know ownership is being moved. If it wasn't pass by value, they may not be aware that ownership has been taken at all!
- *On template classes*: If we use template classes, the full definition must be seen by the compiler. That means the template declaration and the template definitions for that class are usually in the same file (there are "tricks" to bypass this, like the three-file approach).
