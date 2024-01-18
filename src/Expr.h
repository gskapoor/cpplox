#ifndef EXPR_H
#define EXPR_H
#pragma once

#include <any>
#include <memory>
#include "Token.h"

struct BinaryExpr;
struct GroupExpr;
struct LiteralExpr;
struct UnaryExpr;

struct ExprVisitor
{
  virtual std::any visit(const BinaryExpr &expr ) = 0;

  virtual std::any visit(const GroupExpr &expr ) = 0;

  virtual std::any visit(const LiteralExpr &expr ) = 0;

  virtual std::any visit(const UnaryExpr &expr ) = 0;

};

struct Expr
{
  virtual std::any accept(ExprVisitor &visitor) = 0;
};

struct BinaryExpr : Expr 
{
  const std::unique_ptr<Expr> left;
  const Token op;
  const std::unique_ptr<Expr> right;

  BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right);

  std::any accept(ExprVisitor &visitor) override;
};

struct GroupExpr : Expr
{
  const std::unique_ptr<Expr> expr_in;

  explicit GroupExpr(std::unique_ptr<Expr> expr);

  std::any accept(ExprVisitor &visitor) override;
};

struct LiteralExpr : Expr
{
  const std::any value;

  explicit LiteralExpr(std::any value);

  std::any accept(ExprVisitor &visitor) override;
};

struct UnaryExpr : Expr
{
  const Token op;
  const std::unique_ptr<Expr> right;

  UnaryExpr(Token op, std::unique_ptr<Expr> right);

  std::any accept(ExprVisitor &visitor) override;
};

#endif