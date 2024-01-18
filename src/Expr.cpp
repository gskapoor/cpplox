#include <memory>

#include "Expr.h"

BinaryExpr::BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right):
  left(std::move(left)), op(std::move(op)), right(std::move(right))
{}

std::any BinaryExpr::accept(ExprVisitor &visitor){
  visitor.visit(*this);
}

GroupExpr::GroupExpr(std::unique_ptr<Expr> expr_in) : expr_in(std::move(expr_in))
{}

std::any GroupExpr::accept(ExprVisitor &visitor){
  visitor.visit(*this);
}

LiteralExpr::LiteralExpr(std::any value) : value(std::move(value))
{}

std::any LiteralExpr::accept(ExprVisitor &visitor){
  visitor.visit(*this);
}

UnaryExpr::UnaryExpr(Token op, std::unique_ptr<Expr> right) : op(std::move(op)), right(std::move(right))
{}

std::any UnaryExpr::accept(ExprVisitor &visitor){
  visitor.visit(*this);
}
