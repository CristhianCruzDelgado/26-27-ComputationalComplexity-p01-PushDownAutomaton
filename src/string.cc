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
  if (string.size() > 1 || string[0] != Symbol::EMPTY_SYMBOL) {
    for (char symbol : string) {
      if (symbol == Symbol::EMPTY_SYMBOL) {
        throw std::runtime_error("String cannot contain empty symbol");
      }
      string_.push_back(Symbol(symbol));
    }
  }
}

String& String::operator=(const String& other) {
  if (this != &other) {
    string_ = other.getString();
  }
  return *this;
}

Symbol& String::operator[](int index) { 
  return string_[index]; 
}

const Symbol& String::operator[](int index) const { 
  return string_[index]; 
}

bool String::operator<(const String& string) const { 
  return this->length() < string.length();
}

bool String::operator==(const String& string) const { 
  return string_ == string.getString();
}

std::istream& operator>>(std::istream& is, String& string) {
  string.read(is);
  return is;
}

std::ostream& operator<<(std::ostream& os, const String& string) {
  string.write(os);
  return os;
}

const std::vector<Symbol>& String::getString() const { 
  return string_; 
}

int String::length() const { 
  return string_.size(); 
}

bool String::empty() const {
  return length() == 0;
}

void String::popFront() {
  if (!empty()) {
    string_.erase(string_.begin());
  }
}

void String::pushBack(const Symbol& symbol) {
  string_.push_back(symbol);
}

void String::popBack() {
  string_.pop_back();
}

void String::read(std::istream& is) {
  std::string string;
  if (!std::getline(is, string)) {
    throw std::invalid_argument("Invalid input: string undefined");
  }
  string_ = String(string).getString();
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
