/**
 * Universidad de La Laguna ULL
 * Degree: Computer Engineering
 * Signature: Computational Complexity
 * Practice 01: Pushdown Automaton
 * Author: Cristhian Adoney Cruz Delgado
 * Email: alu0101648293@ull.edu.es
 */

#include "../include/pushdown-automaton-app.h"

const char* PushDownAutomatonApp::HELP_MESSAGE_ = 
  "Help: This program simulates a pushdown automaton (PDA)\n"
  "Try:  ./pushdown-automaton\n"
  "      -h|-help                                           ~ Help\n"
  "      -config <../data/APv-[1|2|3].txt> -trace <y|n>     ~ Run\n";

PushDownAutomatonApp::PushDownAutomatonApp(int argc, char* argv[]) : 
    argc_(argc), config_path_(), trace_(false), pushdown_automaton_(),
    pushdown_automaton_simulator_() {
  argv_.reserve(argc);
  for (int i = 0; i < argc; ++i) {
    argv_.emplace_back(argv[i]);
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
    throw std::invalid_argument("Unknown argument. Use -h for help");
  }
}

void PushDownAutomatonApp::parseAppArgs() {
  if (argv_[1] == "-config") {
    config_path_ = argv_[2];
  } else {
    throw std::invalid_argument("Expected -config option as first parameter");
  }
  if (argv_[3] == "-trace") {
    if (argv_[4] == "y") {
      trace_ = true;
    } else if (argv_[4] == "n") {
      trace_ = false;
    } else {
      throw std::invalid_argument("Invalid trace option: expected 'y' or 'n'");
    } 
  } else {
    throw std::invalid_argument("Expected -trace option as third parameter");
  }      
}

void PushDownAutomatonApp::readPushDownAutomaton() {
  std::ifstream file(config_path_);
  if (!file.is_open()) {
    throw std::runtime_error("Cannot open configuration file: " + config_path_);
  }
  file >> pushdown_automaton_;
  std::cout << pushdown_automaton_;
}

void PushDownAutomatonApp::runPushDownAutomaton() {
  String input_string;
  const String exit_string("exit");
  readInputString(input_string);
  while (!(input_string == exit_string)) {
    pushdown_automaton_simulator_.test(
      pushdown_automaton_, input_string, trace_);
    readInputString(input_string);
  }
}

void PushDownAutomatonApp::readInputString(String& input_string) {
  std::cout << "Enter the input string to see if it is accepted or rejected by "
    "the pushdown\nautomaton (press enter for empty string, write "
    "'exit' to quit)\n> ";
  if (!(std::cin >> input_string)) {
    throw std::invalid_argument("Invalid input: stream read failure");
  }
  std::cout << "\n";
}
