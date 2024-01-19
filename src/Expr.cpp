#include <memory>
#include <iostream>

#include "Expr.h"

BinaryExpr::BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right):
  left(std::move(left)), op(std::move(op)), right(std::move(right))
{}

std::any BinaryExpr::accept(ExprVisitor &visitor){
  return visitor.visit(*this);
}

GroupExpr::GroupExpr(std::unique_ptr<Expr> expr_in) : expr_in(std::move(expr_in))
{}

std::any GroupExpr::accept(ExprVisitor &visitor){
  return visitor.visit(*this);
}

LiteralExpr::LiteralExpr(std::any value) : value(std::move(value))
{}

std::any LiteralExpr::accept(ExprVisitor &visitor){
  return visitor.visit(*this);
}

UnaryExpr::UnaryExpr(Token op, std::unique_ptr<Expr> right) : op(std::move(op)), right(std::move(right))
{}

std::any UnaryExpr::accept(ExprVisitor &visitor){
  return visitor.visit(*this);
}

TernaryExpr::TernaryExpr(std::unique_ptr<Expr> left, std::unique_ptr<Expr> middle, std::unique_ptr<Expr> right):left(std::move(left)), middle(std::move(middle)), right(std::move(right))
{}

std::any TernaryExpr::accept(ExprVisitor &visitor){
  return visitor.visit(*this);
}