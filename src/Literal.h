#ifndef LITERAL_H
#define LITERAL_H
#pragma once

#include <variant>
#include <string>
#include <optional>

using Literal = std::variant<std::string, double, bool>;
using OptionalLiteral = std::optional<Literal>;

std::string getLiteralString(const Literal& value);

OptionalLiteral makeOptionalLiteral(double d);

OptionalLiteral makeOptionalLiteral(const std::string& lexeme);

#endif