#include <string>
#include <iostream>
#include <memory>

#include "AstPrinter.h"

std::string AstPrinter::toString(const std::unique_ptr<Expr>& expr) {
  expr->accept(*this);
  return out;
}

std::any AstPrinter::visit(const BinaryExpr& expr) {
  out += "(" + expr.op.getLexeme() + " ";

  // Get left expression
  expr.left->accept(*this);
  out += " ";

  // Get right expression
  expr.right->accept(*this);
  out += " ";

  out += ")";

  return 0;
}

std::any AstPrinter::visit(const GroupExpr& expr) {
  out += "(group ";
  expr.expr_in->accept(*this);
  out += ")";

  return 0;
}

std::any AstPrinter::visit(const LiteralExpr& expr){
  out += getLiteralString(expr.value);

  return 0;
}

std::any AstPrinter::visit(const UnaryExpr& expr){
  out += "(" + expr.op.getLexeme() + " ";
  expr.right->accept(*this);
  out += ")";

  return 0;
}

/*
int main(){
  std::unique_ptr<Expr> expression = std::make_unique<BinaryExpr>(
    std::make_unique<UnaryExpr>(
      Token(TokenType::MINUS, "-", std::nullopt, 1),
      std::make_unique<LiteralExpr>(Literal(1.0))
    ),
    Token(TokenType::STAR, "*", std::nullopt, 1),
    std::make_unique<GroupExpr>(
      std::make_unique<LiteralExpr>(Literal(2.0))
    )
  );

  AstPrinter a;

  std::cout << a.toString(expression) << std::endl;

  return 0;
}
*/