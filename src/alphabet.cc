/**
 * Universidad de La Laguna ULL
 * Degree: Computer Engineering
 * Signature: Computational Complexity
 * Practice 01: Pushdown Automaton
 * Author: Cristhian Adoney Cruz Delgado
 * Email: alu0101648293@ull.edu.es
 */

#include "../include/alphabet.h"

Alphabet::Alphabet(const std::string& alphabet) {
  for (char symbol : alphabet) {
    if (symbol == Symbol::EMPTY_SYMBOL) {
      throw std::invalid_argument("Alphabet cannot include empty symbol");
    }
    if (symbol == ' ') {
      continue;
    }
    alphabet_.insert(Symbol(symbol));
  }
  if (alphabet_.empty()) {
    throw std::invalid_argument("Alphabet cannot be empty");
  } 
}

Alphabet& Alphabet::operator=(const Alphabet& other) {
  if (this != &other) {
    alphabet_ = other.getAlphabet();
  }
  return *this;
}

std::istream& operator>>(std::istream& is, Alphabet& alphabet) {
  alphabet.read(is);
  return is;
}

std::ostream& operator<<(std::ostream& os, const Alphabet& alphabet) {
  alphabet.write(os);
  return os;
}

const std::set<Symbol>& Alphabet::getAlphabet() const { 
  return alphabet_; 
}

bool Alphabet::includes(Symbol& symbol) {
  return alphabet_.find(symbol) != alphabet_.end();
}

void Alphabet::read(std::istream& is) {
  std::string alphabet;
  if (!std::getline(is, alphabet)) {
    throw std::invalid_argument("Invalid input: alphabet undefined");
  }
  alphabet_ = Alphabet(alphabet).getAlphabet(); 
}

void Alphabet::write(std::ostream& os) const {
  os << "{";
  for (auto i = alphabet_.begin(); i != alphabet_.end(); ++i) {
    os << *i << (std::next(i) != alphabet_.end() ? ", " : ""); 
  }
  os << "}";
}
