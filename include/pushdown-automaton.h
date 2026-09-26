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

using StateTransition =
  std::pair<std::pair<Symbol, Symbol>, std::pair<std::string, String>>;
using StateTransitions = 
  std::multimap<std::pair<Symbol, Symbol>, std::pair<std::string, String>>;
using IndexOfStateTransition = std::pair<int, StateTransition>;
using TransitionFunction = std::vector<StateTransitions>;

class PushDownAutomaton {
 public:
  PushDownAutomaton() = default;
  friend std::istream& operator>>(std::istream&, PushDownAutomaton&);
  friend std::ostream& operator<<(std::ostream&, const PushDownAutomaton&);
  void test(const String&, bool) const;
 private:
  Alphabet input_alphabet_;
  Alphabet stack_alphabet_;
  std::vector<std::string> states_;
  std::string initial_state_;
  Symbol initial_stack_symbol_;
  std::vector<std::string> final_states_;
  TransitionFunction transition_function_;
  static const std::string& HORIZONTAL_LINE;
  void read(std::istream&);
  void readLineComments(std::istream&);
  void readStates(std::istream&);
  void readInputAlphabet(std::istream&);
  void readStackAlphabet(std::istream&);
  void readInitialState(std::istream&);
  void readInitialStackSymbol(std::istream&);
  void readTransitionFunction(std::istream&);
  void write(std::ostream&) const;
  bool hasStringInputAlphabetSymbols(const String&) const;
  bool isStringAcceptedByStackEmptyAlgorithm(const String&, bool) const;
  bool moveTroughStates(const std::string&, const String&, 
      const std::stack<Symbol>&, int, bool) const;
  std::vector<IndexOfStateTransition> getAvailableTransitions(
      const std::string&, const Symbol&, const Symbol&) const;
  void writeTrace(int, const std::string&, const String&, 
      const std::stack<Symbol>&, 
      const std::vector<IndexOfStateTransition>&) const;
  void writeStack(std::stack<Symbol>) const;
};

#endif
