/**
 * Universidad de La Laguna ULL
 * Degree: Computer Engineering
 * Signature: Computational Complexity
 * Practice 01: Pushdown Automaton
 * Author: Cristhian Adoney Cruz Delgado
 * Email: alu0101648293@ull.edu.es
 */

#ifndef PUSHDOWN_AUTOMATON_SIMULATOR_H_
#define PUSHDOWN_AUTOMATON_SIMULATOR_H_

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#include "pushdown-automaton.h"
#include "string.h"
#include "symbol.h"

class PushDownAutomatonSimulator {
 public:
  PushDownAutomatonSimulator() = default;
  void test(const PushDownAutomaton&, const String&, bool) const;
 private:
  bool hasStringValidInputSymbols(const PushDownAutomaton&,
                                  const String&) const;
  bool isStringAcceptedByStackEmptyAlgorithm(const PushDownAutomaton&,
                                             const String&, bool) const;
  bool step(const PushDownAutomaton&, const std::string&, const String&, 
            const std::stack<Symbol>&, int, bool) const;
  void writeTrace(int, const std::string&, const String&, 
                  const std::stack<Symbol>&, 
                  const std::vector<Transition>&) const;
};

#endif
