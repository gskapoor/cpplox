#ifndef INTERPRETER_H
#define INTERPRETER_H
#pragma once

#include "Expr.h"

class Interpreter : ExprVisitor {

  public:
  
  std::any visit(const BinaryExpr& expr) override;
  std::any visit(const LiteralExpr& expr) override;
  std::any visit(const GroupExpr& expr) override;
  std::any visit(const UnaryExpr& expr) override;

  private:
  
  std::any evaluate(const std::unique_ptr<Expr>& expr);

};

#endif