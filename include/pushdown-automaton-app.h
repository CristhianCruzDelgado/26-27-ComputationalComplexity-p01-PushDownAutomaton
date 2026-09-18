/**
 * Universidad de La Laguna ULL
 * Degree: Computer Engineering
 * Signature: Computational Complexity
 * Practice 01: Pushdown Automaton
 * Author: Cristhian Adoney Cruz Delgado
 * Email: alu0101648293@ull.edu.es
 */

#ifndef PUSHDOWN_AUTOMATON_APP_H
#define PUSHDOWN_AUTOMATON_APP_H

#include "pushdown-automaton.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class PushDownAutomatonApp {
 public:
  PushDownAutomatonApp(int argc, char* argv[]);
  void parseArgsAndRunPushDownAutomaton();

 private:
  void parseArgs();
  void parseAuxiliaryArgs();
  void parseAppArgs();
  void parseConfigArgs();
  void parseTraceArgs();
  void runPushDownAutomaton();

  int argc_;
  std::vector<std::string> argv_;
  std::ifstream file_;
  bool trace_;
  PushDownAutomaton pushdown_automaton_;

  static const std::string HELP_MESSAGE_;
};

#endif
