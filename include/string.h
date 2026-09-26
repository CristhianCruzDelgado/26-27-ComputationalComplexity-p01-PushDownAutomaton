/**
 * Universidad de La Laguna ULL
 * Degree: Computer Engineering
 * Signature: Computational Complexity
 * Practice 01: Pushdown Automaton
 * Author: Cristhian Adoney Cruz Delgado
 * Email: alu0101648293@ull.edu.es
 */

#ifndef STRING_H_
#define STRING_H_

#include "symbol.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class String {
 public:
  String() = default;
  String(const std::string&);
  Symbol& operator[](std::size_t);
  const Symbol& operator[](std::size_t) const;
  bool operator==(const String&) const;
  bool operator<(const String&) const;
  const std::vector<Symbol>& getString() const;
  std::size_t size() const;
  bool empty() const;
  void popFront();
  friend std::istream& operator>>(std::istream&, String&);
  friend std::ostream& operator<<(std::ostream&, const String&);
 private:
  std::vector<Symbol> string_;
  void read(std::istream&);
  void write(std::ostream&) const;
};

#endif
