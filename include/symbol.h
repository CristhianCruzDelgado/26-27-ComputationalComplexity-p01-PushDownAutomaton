/**
 * Universidad de La Laguna ULL
 * Degree: Computer Engineering
 * Signature: Computational Complexity
 * Practice 01: Pushdown Automaton
 * Author: Cristhian Adoney Cruz Delgado
 * Email: alu0101648293@ull.edu.es
 */

#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <iostream>
#include <stdexcept>

class Symbol {
 public:
  static const char EMPTY_SYMBOL;
  Symbol() = default;
  Symbol(char);
  bool operator==(const Symbol&) const;
  bool operator<(const Symbol&) const;
  char getSymbol() const;
  friend std::istream& operator>>(std::istream&, Symbol&);
  friend std::ostream& operator<<(std::ostream&, const Symbol&);
 private:
  char symbol_;
  void read(std::istream&);
  void write(std::ostream&) const;
};

#endif
