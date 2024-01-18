#ifndef ASTPRINTER_H
#define ASTPRINTER_H
#pragma once

#include <vector>

#include "Expr.h"


class AstPrinter : private ExprVisitor {

public:
  std::string toString(const std::unique_ptr<Expr>& expr) ;

private:

  std::any visitBinaryExpr(const BinaryExpr &expr ) override;

  std::any visitGroupExpr(const GroupExpr &expr ) override;

  std::any visitLiteralExpr(const LiteralExpr &expr ) override;

  std::any visitUnaryExpr(const UnaryExpr &expr ) override;

  std::string out = "";
};

#endif