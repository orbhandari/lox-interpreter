#include "trees.h"
#include <iostream>
#include <memory>
#include <optional>

int main(int argc, char* argv[]) {
    using Expr = Expression<std::string>;
    using Binary = Binary<std::string>;
    using Unary = Unary<std::string>;
    using Literal = Literal<std::string>;
    using Grouping = Grouping<std::string>;

    std::unique_ptr<Expr> expr{
        new Binary{std::make_unique<Unary>(Token{TokenType::_minus, "-", std::nullopt, 1},
                                           std::make_unique<Literal>(123.0)),
                   Token{TokenType::_star, "*", std::nullopt, 1},
                   std::make_unique<Grouping>(std::make_unique<Literal>(45.67))}};
    std::unique_ptr<Expr> expr1{new Literal{123.0}};

    std::unique_ptr<Expr> expr2{std::make_unique<Unary>(
        Token{TokenType::_minus, "-", std::nullopt, 1}, std::make_unique<Literal>(123.0))};

    AstPrinter astPrinter{};
    std::cout << astPrinter.print(*expr) << std::endl;

    std::cout << std::endl;

    return 0;
}
