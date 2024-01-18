#include <memory>
#include <iostream>

#include "Expr.h"

BinaryExpr::BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right):
  left(std::move(left)), op(std::move(op)), right(std::move(right))
{}

std::any BinaryExpr::accept(ExprVisitor &visitor){
  return visitor.visitBinaryExpr(*this);
}

GroupExpr::GroupExpr(std::unique_ptr<Expr> expr_in) : expr_in(std::move(expr_in))
{}

std::any GroupExpr::accept(ExprVisitor &visitor){
  return visitor.visitGroupExpr(*this);
}

LiteralExpr::LiteralExpr(std::any value) : value(std::move(value))
{}

std::any LiteralExpr::accept(ExprVisitor &visitor){
  return visitor.visitLiteralExpr(*this);
}

UnaryExpr::UnaryExpr(Token op, std::unique_ptr<Expr> right) : op(std::move(op)), right(std::move(right))
{}

std::any UnaryExpr::accept(ExprVisitor &visitor){
  return visitor.visitUnaryExpr(*this);
}
