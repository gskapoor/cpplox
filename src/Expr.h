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
  virtual void visit(const BinaryExpr &expr ) = 0;

  virtual void visit(const GroupExpr &expr ) = 0;

  virtual void visit(const LiteralExpr &expr ) = 0;

  virtual void visit(const UnaryExpr &expr ) = 0;

};

struct Expr
{
  virtual void accept(ExprVisitor &visitor) = 0;
};

struct BinaryExpr : Expr 
{
  const std::unique_ptr<Expr> left;
  const Token op;
  const std::unique_ptr<Expr> right;

  BinaryExpr(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right);

  void accept(ExprVisitor &visitor) override;
};

struct GroupExpr : Expr
{
  const std::unique_ptr<Expr> expr_in;

  explicit GroupExpr(std::unique_ptr<Expr> expr);

  void accept(ExprVisitor &visitor) override;
};

struct LiteralExpr : Expr
{
  const Literal value;

  explicit LiteralExpr(Literal value);

  void accept(ExprVisitor &visitor) override;
};

struct UnaryExpr : Expr
{
  const Token op;
  const std::unique_ptr<Expr> right;

  UnaryExpr(Token op, std::unique_ptr<Expr> right);

  void accept(ExprVisitor &visitor) override;
};

#endif