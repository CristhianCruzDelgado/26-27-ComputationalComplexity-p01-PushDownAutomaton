/**
 * Universidad de La Laguna ULL
 * Degree: Computer Engineering
 * Signature: Computational Complexity
 * Practice 01: Pushdown Automaton
 * Author: Cristhian Adoney Cruz Delgado
 * Email: alu0101648293@ull.edu.es
 */

#include "../include/string.h"

String::String(const std::string& string) {
  if (string.empty()) {
    return;
  }
  if (string.size() == 1 && string[0] == Symbol::EMPTY_SYMBOL) {
    return;
  }
  for (char character : string) {
    if (character == Symbol::EMPTY_SYMBOL) {
      throw std::invalid_argument("String cannot contain the empty symbol");
    }
    Symbol symbol(character);
    string_.push_back(symbol);
  }
}

Symbol& String::operator[](std::size_t index) { 
  return string_[index]; 
}

const Symbol& String::operator[](std::size_t index) const { 
  return string_[index]; 
}

bool String::operator==(const String& string) const { 
  return string_ == string.getString();
}

bool String::operator<(const String& string) const { 
  return size() < string.size();
}

const std::vector<Symbol>& String::getString() const { 
  return string_; 
}

std::size_t String::size() const { 
  return string_.size(); 
}

bool String::empty() const {
  return string_.empty();
}

void String::popFront() {
  if (!empty()) {
    string_.erase(string_.begin());
  }
}

std::istream& operator>>(std::istream& is, String& string) {
  string.read(is);
  return is;
}

std::ostream& operator<<(std::ostream& os, const String& string) {
  string.write(os);
  return os;
}

void String::read(std::istream& is) {
  std::string string;
  if (!std::getline(is, string)) {
    throw std::invalid_argument("Invalid input: string undefined");
  }
  String tmp(string);
  *this = std::move(tmp);
}

void String::write(std::ostream& os) const {
  if (string_.empty()) {
    os << Symbol::EMPTY_SYMBOL;
  } else {
    for (const Symbol& symbol : string_) {
      os << symbol;
    }
  }
}
