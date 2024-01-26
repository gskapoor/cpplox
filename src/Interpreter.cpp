#include <memory>

#include "Interpreter.h"

std::any Interpreter::visit(const LiteralExpr& expr) {
  return expr.value;
}

std::any Interpreter::visit(const GroupExpr& expr) {
  return evaluate(expr.expr_in);
}

std::any Interpreter::visit(const UnaryExpr& expr) {
  std::any right = evaluate(expr.right);

  switch (expr.op.getType()){
    case TokenType::MINUS :
      return -1 * std::any_cast<double>(right);
    case TokenType::BANG :
      return !isTruthy(right);
  }
}

std::any Interpreter::visit(const BinaryExpr& expr) {
  std::any left = evaluate(expr.left);
  std::any right = evaluate(expr.right);

  switch (expr.op.getType()){
    case TokenType::GREATER:
      return (std::any_cast<double>(left)) > (std::any_cast<double>(right));
    case TokenType::LESS:
      return (std::any_cast<double>(left)) < (std::any_cast<double>(right));
    case TokenType::GREATER_EQUAL:
      return (std::any_cast<double>(left)) >= (std::any_cast<double>(right));
    case TokenType::LESS_EQUAL:
      return (std::any_cast<double>(left)) <= (std::any_cast<double>(right));
    case TokenType::EQUAL_EQUAL:
      return isEqual(left, right);
    case TokenType::BANG_EQUAL:
      return !isEqual(left, right);
    case TokenType::MINUS:
      return (std::any_cast<double>(left)) - (std::any_cast<double>(right));
    case TokenType::SLASH:
      return (std::any_cast<double>(left)) / (std::any_cast<double>(right));
    case TokenType::STAR:
      return (std::any_cast<double>(left)) * (std::any_cast<double>(right));
    case TokenType::PLUS:
      if (left.type() == typeid(double) && right.type() == typeid(double)){
        return (std::any_cast<double>(left)) + (std::any_cast<double>(right));
      }
      if (left.type() == typeid(std::string) && right.type() == typeid(std::string)){
        return (std::any_cast<std::string>(left)) + (std::any_cast<std::string>(right));
      }
    break;
  }
}

std::any Interpreter::visit(const TernaryExpr& expr) {

  return 1;
}

std::any Interpreter::evaluate(const std::unique_ptr<Expr>& expr) {
  return expr->accept(*this);
}

bool Interpreter::isTruthy(std::any value){
  if (!value.has_value()){
    return false;
  }
  if (value.type() == typeid(bool)){
    return std::any_cast<bool>(value);
  }

  // TODO: Consider making 0 falsy

  return true;
}

bool Interpreter::isEqual(std::any a, std::any b) {

  if (!a.has_value() && !b.has_value()){
    return true;
  }
  if (!a.has_value() || !b.has_value()){
    return false;
  }

  if (a.type() != b.type()){
    return false;
  }

  if (a.type() == typeid(bool)){
    return (std::any_cast<bool>(a)) ==  (std::any_cast<bool>(b));
  }

  if (a.type() == typeid(double)){
    return (std::any_cast<double>(a)) ==  (std::any_cast<double>(b));
  }

  if (a.type() == typeid(std::string)){
    return (std::any_cast<std::string>(a)) ==  (std::any_cast<std::string>(b));
  }

  return false;
}
