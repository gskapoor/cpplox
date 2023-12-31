#include "Literal.h"

std::string getLiteralString(const Literal& value){

  switch (value.index()) {
    case 0:
      return std::get<0>(value);
    case 1: {
      std::string result = std::to_string(std::get<1>(value));
      auto pos = result.find(".000000");
      if (pos != std::string::npos){
        result.erase(pos, std::string::npos);
      } else {
        result.erase(result.find_last_not_of('0') + 1, std::string::npos);
      }
      return result;
    }
    default:
      static_assert(
        std::variant_size_v<Literal> == 2,
        "Incorrect Literal size!"
      );
      return "";
  }
}

OptionalLiteral makeOptionalLiteral(double d){
  return OptionalLiteral(std::in_place, d);
}

OptionalLiteral makeOptionalLiteral(std::string& lexeme){
  return OptionalLiteral(std::in_place, lexeme);
}
