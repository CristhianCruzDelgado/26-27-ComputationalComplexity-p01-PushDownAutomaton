/**
 * Universidad de La Laguna ULL
 * Degree: Computer Engineering
 * Signature: Computational Complexity
 * Practice 01: Pushdown Automaton
 * Author: Cristhian Adoney Cruz Delgado
 * Email: alu0101648293@ull.edu.es
 */

#ifndef PUSHDOWN_AUTOMATON_H
#define PUSHDOWN_AUTOMATON_H

#include "alphabet.h"
#include "string.h"
#include "symbol.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using InputAndPushdownSymbol = std::pair<Symbol, Symbol>;
using NextStateAndPushdownString = std::pair<String, String>;
using StateTransitions = 
  std::multimap<InputAndPushdownSymbol, NextStateAndPushdownString>;
using TransitionFunction = std::vector<StateTransitions>;

class PushDownAutomaton {
 public:
  PushDownAutomaton() = default;
  friend std::istream& operator>>(std::istream&, PushDownAutomaton&);
  friend std::ostream& operator<<(std::ostream&, const PushDownAutomaton&);
  void run(bool);
 private:
  Alphabet input_alphabet_;
  Alphabet pushdown_alphabet_;
  std::vector<std::string> states_;
  std::string initial_state_;
  Symbol pushdown_initial_symbol_;
  TransitionFunction transition_function_;
  void read(std::istream&);
  void readLineComments(std::istream&);
  void readStates(std::istream&);
  void readInputAlphabet(std::istream&);
  void readPushdownAlphabet(std::istream&);
  void readInitialState(std::istream&);
  void readPushdownInitialSymbol(std::istream&);
  void readTransitionFunction(std::istream&);
  void write(std::ostream&) const;
};

#endif
