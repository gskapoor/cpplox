#ifndef ASTPRINTER_H
#define ASTPRINTER_H
#pragma once

#include <vector>

#include "Expr.h"


class AstPrinter : private ExprVisitor {

public:
  std::string toString(const std::unique_ptr<Expr>& expr) ;

private:

  void visit(const TernaryExpr &expr ) override;

  void visit(const BinaryExpr &expr ) override;

  void visit(const GroupExpr &expr ) override;

  void visit(const LiteralExpr &expr ) override;

  void visit(const UnaryExpr &expr ) override;

  std::string out;
};

#endif