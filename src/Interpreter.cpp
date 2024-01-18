#include <memory>

#include "Interpreter.h"

std::any Interpreter::visit(const LiteralExpr& expr) {
  return expr.value;
}

std::any Interpreter::visit(const GroupExpr& expr) {
  return evaluate(expr.expr_in);
}

std::any Interpreter::visit(const UnaryExpr& expr) {
  auto right = evaluate(expr.right);

  switch (expr.op.getType()){
    case TokenType::MINUS :
      return -1 * std::any_cast<double>(right);
  }
}

std::any Interpreter::evaluate(const std::unique_ptr<Expr>& expr) {
  return expr->accept(*this);
}

