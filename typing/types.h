#ifndef TYPES_H
#define TYPES_H

#include <optional>
#include <ostream>
#include <string>
#include <variant>

using Boolean = bool;
using Number = double;
using String = std::string;

// std::nullopt will represent Nil in Lox
using NonNullType = std::variant<Boolean, Number, String>;
using Type = std::optional<NonNullType>;

inline std::ostream& operator<<(std::ostream& out, Type type) {
    if (type.has_value()) {
        // TODO: note that if its a double, then we may need to set precision here
        std::visit([&out](const auto& v) { out << v; }, type.value());
    } else {
        out << "Nil";
    }
    return out;
}

inline std::string toString(Type type) {
    // TODO: this is ugly. any improvements?
    if (type.has_value()) {
        auto nonNilType{type.value()};
        if (std::holds_alternative<Boolean>(nonNilType)) {
            return std::to_string(std::get<Boolean>(nonNilType));
        } else if (std::holds_alternative<Number>(nonNilType)) {
            return std::to_string(std::get<Number>(nonNilType));
        } else if (std::holds_alternative<String>(nonNilType)) {
            return std::get<String>(nonNilType);
        } else {
            return "unknown type";
        }
    } else {
        return "nil";
    }
}

#endif // !TYPES_H
