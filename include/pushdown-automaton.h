/**
 * Universidad de La Laguna ULL
 * Degree: Computer Engineering
 * Signature: Computational Complexity
 * Practice 01: Pushdown Automaton
 * Author: Cristhian Adoney Cruz Delgado
 * Email: alu0101648293@ull.edu.es
 */

#ifndef PUSHDOWN_AUTOMATON_H_
#define PUSHDOWN_AUTOMATON_H_

#include "alphabet.h"
#include "string.h"
#include "symbol.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

struct Transition {
  Symbol input_symbol;
  Symbol stack_symbol;
  std::string next_state;
  String pushdown_string;
};

class PushDownAutomaton {
 public:
  static const char* HORIZONTAL_LINE;
  PushDownAutomaton() = default;
  const Alphabet& getInputAlphabet() const;
  const Alphabet& getStackAlphabet() const;
  const std::vector<std::string>& getStates() const;
  const std::string& getInitialState() const;
  const Symbol& getInitialStackSymbol() const;
  std::vector<Transition> getTransitions(const std::string&,
      const Symbol&, const Symbol&) const;
  friend std::istream& operator>>(std::istream&, PushDownAutomaton&);
  friend std::ostream& operator<<(std::ostream&, const PushDownAutomaton&);
 private:
  Alphabet input_alphabet_; 
  Alphabet stack_alphabet_;
  std::vector<std::string> states_;
  std::string initial_state_;
  Symbol initial_stack_symbol_;
  std::vector<std::string> final_states_;
  std::multimap<std::string, Transition> transition_function_;
  void read(std::istream&);
  void readLineComments(std::istream&);
  void readStates(std::istream&);
  void readInputAlphabet(std::istream&);
  void readStackAlphabet(std::istream&);
  void readInitialState(std::istream&);
  void readInitialStackSymbol(std::istream&);
  void readTransitionFunction(std::istream&);
  void write(std::ostream&) const;
};

#endif
