#ifndef TYPES_H
#define TYPES_H
#include <string>
#include <optional>
#include <variant>

using Boolean = bool;
using Number = double;
using String = std::string;

// std::nullopt will represent Nil in Lox
using Type = std::optional<std::variant<Boolean, Number, String>>;

#endif // !TYPES_H
