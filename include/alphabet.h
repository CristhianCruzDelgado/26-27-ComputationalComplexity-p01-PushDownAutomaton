/**
 * Universidad de La Laguna ULL
 * Degree: Computer Engineering
 * Signature: Computational Complexity
 * Practice 01: Pushdown Automaton
 * Author: Cristhian Adoney Cruz Delgado
 * Email: alu0101648293@ull.edu.es
 */

#ifndef ALPHABET_H_
#define ALPHABET_H_

#include "symbol.h"

#include <iostream>
#include <set>
#include <stdexcept>
#include <string>

class Alphabet {
 public:
  Alphabet() = default;
  Alphabet(const std::string&);
  Alphabet& operator=(const Alphabet&);
  friend std::istream& operator>>(std::istream&, Alphabet&);
  friend std::ostream& operator<<(std::ostream&, const Alphabet&);
  const std::set<Symbol>& getAlphabet() const;
  bool includes(Symbol&);
 private:
  std::set<Symbol> alphabet_;
  void read(std::istream&);
  void write(std::ostream&) const;
};

#endif