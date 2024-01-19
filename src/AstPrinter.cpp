#include <string>
#include <iostream>
#include <memory>

#include "AstPrinter.h"

std::string AstPrinter::toString(const std::unique_ptr<Expr>& expr) {
  expr->accept(*this);
  return out;
}

std::any AstPrinter::visitBinaryExpr(const BinaryExpr& expr) {
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

std::any AstPrinter::visitGroupExpr(const GroupExpr& expr) {
  out += "(group ";
  expr.expr_in->accept(*this);
  out += ")";

  return 0;
}

std::any AstPrinter::visitLiteralExpr(const LiteralExpr& expr){

  std::any literal = expr.value;
  if (!literal.has_value()){
    out += "| NO VALUE FOUND |";
  } else if (literal.type() == typeid(std::string)){
    out += '"' + std::any_cast<std::string>(literal) + '"';
  } else if (literal.type() == typeid(double)){
    out += std::to_string(std::any_cast<double>(literal));
  } else {
    out += "| INVALID VALUE |";
  }

  return std::any{};
}

std::any AstPrinter::visitUnaryExpr(const UnaryExpr& expr){

  out += "(" + expr.op.getLexeme() + " ";
  expr.right->accept(*this);
  out += ")";

  return 0;
}

std::any AstPrinter::visitTernaryExpr(const TernaryExpr& expr){
  out += "(";

  // Get left expression
  expr.left->accept(*this);
  out += " ? ";

  // very mid
  expr.middle->accept(*this);

  out += " : ";

  // Get right expression
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
