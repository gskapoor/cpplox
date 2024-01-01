#include <memory>

#include "Expr.h"

BinaryExpr::BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right):
  left(std::move(left)), op(std::move(op)), right(std::move(right))
{}

void BinaryExpr::accept(ExprVisitor &visitor){
  return visitor.visit(*this);
}

GroupExpr::GroupExpr(std::unique_ptr<Expr> expr_in) : expr_in(std::move(expr_in))
{}

void GroupExpr::accept(ExprVisitor &visitor){
  return visitor.visit(*this);
}

LiteralExpr::LiteralExpr(Literal value) : value(std::move(value))
{}

void LiteralExpr::accept(ExprVisitor &visitor){
  return visitor.visit(*this);
}

UnaryExpr::UnaryExpr(Token op, std::unique_ptr<Expr> right) : op(std::move(op)), right(std::move(right))
{}

void UnaryExpr::accept(ExprVisitor &visitor){
  return visitor.visit(*this);
}
