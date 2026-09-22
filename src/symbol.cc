/**
 * Universidad de La Laguna ULL
 * Degree: Computer Engineering
 * Signature: Computational Complexity
 * Practice 01: Pushdown Automaton
 * Author: Cristhian Adoney Cruz Delgado
 * Email: alu0101648293@ull.edu.es
 */

#include "../include/symbol.h"

const char Symbol::EMPTY_SYMBOL = '.';

Symbol::Symbol(char symbol) : symbol_(symbol) {}

Symbol& Symbol::operator=(const Symbol& other) { 
  if (this != &other) {
    symbol_ = other.getSymbol();
  }
  return *this;
}

bool Symbol::operator<(const Symbol& other) const {
  return symbol_ < other.getSymbol();
}

bool Symbol::operator==(const Symbol& other) const {
  return symbol_ == other.getSymbol();
}

std::istream& operator>>(std::istream& is, Symbol& symbol) {
  symbol.read(is);
  return is;
}

std::ostream& operator<<(std::ostream& os, const Symbol& symbol) {
  symbol.write(os);
  return os;
}

char Symbol::getSymbol() const { 
  return symbol_; 
}

void Symbol::read(std::istream& is) {
  if (!(is >> symbol_)) {
    throw std::invalid_argument("Invalid input: symbol undefined");
  }
}

void Symbol::write(std::ostream& os) const {
  os << symbol_;
}
