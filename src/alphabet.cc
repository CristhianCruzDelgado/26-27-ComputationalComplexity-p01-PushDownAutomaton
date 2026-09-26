/**
 * Universidad de La Laguna ULL
 * Degree: Computer Engineering
 * Signature: Computational Complexity
 * Practice 01: Pushdown Automaton
 * Author: Cristhian Adoney Cruz Delgado
 * Email: alu0101648293@ull.edu.es
 */

#include "../include/alphabet.h"

Alphabet::Alphabet(const std::string& alphabet_string) {
  for (char character : alphabet_string) {
    if (character == Symbol::EMPTY_SYMBOL) {
      throw std::invalid_argument("Alphabet cannot include empty symbol");
    }
    if (character == ' ') {
      continue;
    }
    Symbol symbol(character);
    alphabet_.insert(symbol);
  }
  if (alphabet_.empty()) {
    throw std::invalid_argument("Alphabet cannot be empty");
  } 
}

const std::set<Symbol>& Alphabet::getAlphabet() const { 
  return alphabet_; 
}

std::size_t Alphabet::size() const {
  return alphabet_.size();
}

bool Alphabet::empty() const {
  return alphabet_.empty();
}

bool Alphabet::includes(const Symbol& symbol) const {
  return alphabet_.find(symbol) != alphabet_.end();
}

std::istream& operator>>(std::istream& is, Alphabet& alphabet) {
  alphabet.read(is);
  return is;
}

std::ostream& operator<<(std::ostream& os, const Alphabet& alphabet) {
  alphabet.write(os);
  return os;
}

void Alphabet::read(std::istream& is) {
  std::string alphabet_string;
  if (!std::getline(is, alphabet_string)) {
    throw std::invalid_argument("Invalid input: alphabet undefined");
  }
  Alphabet tmp(alphabet_string);
  *this = std::move(tmp);
}

void Alphabet::write(std::ostream& os) const {
  os << "{";
  bool first = true;
  for (const Symbol& symbol : alphabet_) {
    if (!first) {
      os << ", ";
    }
    os << symbol;
    first = false;
  }
  os << "}";
}
