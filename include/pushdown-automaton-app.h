/**
 * Universidad de La Laguna ULL
 * Degree: Computer Engineering
 * Signature: Computational Complexity
 * Practice 01: Pushdown Automaton
 * Author: Cristhian Adoney Cruz Delgado
 * Email: alu0101648293@ull.edu.es
 */

#ifndef PUSHDOWN_AUTOMATON_APP_H_
#define PUSHDOWN_AUTOMATON_APP_H_

#include "pushdown-automaton.h"
#include "pushdown-automaton-simulator.h"

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
  void readPushDownAutomaton();
  void runPushDownAutomaton();
  void readInputString(String&);
  int argc_;
  std::vector<std::string> argv_;
  std::string config_path_;
  bool trace_;
  PushDownAutomaton pushdown_automaton_;
  PushDownAutomatonSimulator pushdown_automaton_simulator_;
  static const char* HELP_MESSAGE_;
};

#endif
