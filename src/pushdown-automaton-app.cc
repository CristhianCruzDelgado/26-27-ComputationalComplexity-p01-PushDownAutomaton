/**
 * Universidad de La Laguna ULL
 * Degree: Computer Engineering
 * Signature: Computational Complexity
 * Practice 01: Pushdown Automaton
 * Author: Cristhian Adoney Cruz Delgado
 * Email: alu0101648293@ull.edu.es
 */

#include "../include/pushdown-automaton-app.h"

PushDownAutomatonApp::PushDownAutomatonApp(int argc, char* argv[]) : 
    argc_(argc), 
    file_(nullptr), 
    trace_(false), 
    pushdown_automaton_() {
  for (int i = 0; i < argc; ++i) {
    argv_.push_back(std::string(argv[i]));
  }
}

void PushDownAutomatonApp::parseArgsAndRunPushDownAutomaton() {
  parseArgs();
  readPushDownAutomaton();
  runPushDownAutomaton();
}

void PushDownAutomatonApp::parseArgs() {
  if (argc_ == 2) {
    parseAuxiliaryArgs();
    throw std::invalid_argument("Help message display");
  } else if (argc_ == 5) {
    parseAppArgs();
  } else {
    throw std::invalid_argument("Invalid number of arguments");
  }
}

void PushDownAutomatonApp::parseAuxiliaryArgs() {
  if (argv_[1] == "-h" || argv_[1] == "--help") {
    std::cout << HELP_MESSAGE_; 
  } else {
    throw std::invalid_argument("Invalid argument");
  }
}

void PushDownAutomatonApp::parseAppArgs() {
  if (argv_[1] == "-config") {
    parseConfigArgs();
  } else {
    throw std::invalid_argument("Invalid argument");
  }
  if (argv_[3] == "-trace") {
    parseTraceArgs();
  } else {
    throw std::invalid_argument("Invalid argument");
  }      
}

void PushDownAutomatonApp::parseConfigArgs() {
  file_ = std::ifstream(argv_[2]);
  if (!file_) {
    throw std::runtime_error("Bad path " + argv_[2]);
  }
}

void PushDownAutomatonApp::parseTraceArgs() {
  if (argv_[4] == "y") {
    trace_ = true;
  } else if (argv_[4] == "n") {
    trace_ = false;
  } else {
    throw std::invalid_argument("Invalid argument");
  }
}

void PushDownAutomatonApp::readPushDownAutomaton() {
  file_ >> pushdown_automaton_;
  std::cout << pushdown_automaton_;
}

void PushDownAutomatonApp::runPushDownAutomaton() {
  String input_string;
  readInputString(input_string);
  String exit_string = String("exit");
  while (!(input_string == exit_string)) {
    pushdown_automaton_.test(input_string, trace_);
    readInputString(input_string);
  }
}

void PushDownAutomatonApp::readInputString(String& input_string) {
  std::cout << "Enter the input string to see if it is accepted or rejected by "
      << "the pushdown\nautomaton (to test the empty string, use '.'), (to exit"
      << " the app, enter 'exit' as\nthe input string): ";
  if (!(std::cin >> input_string)) {
    throw std::invalid_argument("Invalid input: no input string defined");
  }
  std::cout << "\n";
}

const std::string PushDownAutomatonApp::HELP_MESSAGE_ = 
    "Help: This program simulates a pushdown automaton (PDA)\
    \nTry:  ./pushdown-automaton\
    \n      -h|-help                                           ~ Help\
    \n      -config <../data/APv-[1|2|3].txt> -trace <y|n>     ~ Run\
    \n";
