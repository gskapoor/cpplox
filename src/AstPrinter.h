#ifndef ASTPRINTER_H
#define ASTPRINTER_H
#pragma once

#include <vector>

#include "Expr.h"


class AstPrinter : private ExprVisitor {

public:
  std::string toString(const std::unique_ptr<Expr>& expr) ;

private:

  std::any visit(const BinaryExpr &expr ) override;

  std::any visit(const GroupExpr &expr ) override;

  std::any visit(const LiteralExpr &expr ) override;

  std::any visit(const UnaryExpr &expr ) override;

  std::any visit(const TernaryExpr &expr ) override;

  std::string out = "";
};

#endif