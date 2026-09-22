/**
 * Universidad de La Laguna ULL
 * Degree: Computer Engineering
 * Signature: Computational Complexity
 * Practice 01: Pushdown Automaton
 * Author: Cristhian Adoney Cruz Delgado
 * Email: alu0101648293@ull.edu.es
 */

#include "../include/pushdown-automaton.h"

std::istream& operator>>(std::istream& is, 
  PushDownAutomaton& pushdown_automaton) { 
  pushdown_automaton.read(is);
  return is; 
}

std::ostream& operator<<(std::ostream& os, 
  const PushDownAutomaton& pushdown_automaton) { 
  pushdown_automaton.write(os);
  return os; 
}

void PushDownAutomaton::run(bool trace) {

}

void PushDownAutomaton::read(std::istream& is) {
  readLineComments(is);
  readStates(is);
  readInputAlphabet(is);
  readPushdownAlphabet(is);
  readInitialState(is);
  readPushdownInitialSymbol(is);
  readTransitionFunction(is);
}

void PushDownAutomaton::readLineComments(std::istream& is) {
  std::string line_read;
  while (is.peek() == '#') {
    std::getline(is, line_read);
  }
}

void PushDownAutomaton::readStates(std::istream& is) {
  std::string line_read;
  if (!std::getline(is, line_read)) {
    throw std::invalid_argument("Invalid input: no states defined");
  }
  std::istringstream states(line_read);
  std::string state;
  while (states >> state) {
    states_.push_back(state);
  }
  if (states_.empty()) {
    throw std::invalid_argument("Invalid input: no states defined");
  }
}

void PushDownAutomaton::readInputAlphabet(std::istream& is) {
  is >> input_alphabet_;
}

void PushDownAutomaton::readPushdownAlphabet(std::istream& is) {
  is >> pushdown_alphabet_;
}

void PushDownAutomaton::readInitialState(std::istream& is) {
  std::string line_read;
  if (!std::getline(is, line_read)) {
    throw std::invalid_argument("Invalid input: no initial state defined");
  }
  std::istringstream line(line_read);
  std::string initial_state;
  if (!(line >> initial_state)) {
    throw std::invalid_argument("Invalid input: no initial state defined");
  }
  std::string extra;
  if (line >> extra) {
    throw std::invalid_argument(
      "Invalid input: more than one initial state defined");
  }
  if (std::find(states_.begin(), states_.end(), initial_state) == states_.end()) {
    throw std::invalid_argument(
      "Invalid input: the initial state is not contained in the set of states");
  }
  initial_state_ = initial_state;
}

void PushDownAutomaton::readPushdownInitialSymbol(std::istream& is) {
  std::string line_read;
  if (!std::getline(is, line_read)) {
    throw std::invalid_argument(
      "Invalid input: no initial pushdown symbol defined");
  }
  std::istringstream line(line_read);
  char symbol;
  if (!(line >> symbol)) {
    throw std::invalid_argument(
      "Invalid input: no initial pushdown symbol defined");
  }
  char extra;
  if (line >> extra) {
    throw std::invalid_argument(
      "Invalid input: invalid initial pushdown symbol");
  }
  Symbol pushdown_initial_symbol(symbol);
  if (!pushdown_alphabet_.includes(pushdown_initial_symbol)) {
    throw std::invalid_argument(
      "Invalid input: the initial pushdown symbol is not contained "
      "in the pushdown alphabet");
  }
  pushdown_initial_symbol_ = pushdown_initial_symbol;
}

void PushDownAutomaton::readTransitionFunction(std::istream& is) {
  std::string line_read;
  std::string last_state;
  StateTransitions state_transitions;
  while (std::getline(is, line_read)) {
    std::istringstream transition(line_read);
    std::string current_state;
    Symbol input_symbol;
    Symbol pushdown_symbol;
    std::string next_state;
    std::string pushdown_string;
    if (!(transition >> current_state >> input_symbol >> pushdown_symbol
      >> next_state >> pushdown_string)) {
      throw std::invalid_argument("Invalid input: malformed transition");
    }
    std::string extra;
    if (transition >> extra) {
      throw std::invalid_argument("Invalid input: malformed transition");
    }
    if (!last_state.empty() && last_state != current_state) {
      transition_function_.push_back(state_transitions);
      state_transitions.clear();
    }
    state_transitions.insert(
      {{input_symbol, pushdown_symbol}, {next_state, pushdown_string}});
    last_state = current_state;
  }
  if (!state_transitions.empty()) {
    transition_function_.push_back(state_transitions);
  }
}

void PushDownAutomaton::write(std::ostream& os) const {
  os << "PushDown Automaton (PDA)\n--------------------";
  os << "------------------------------------------------------------\n";
  os << "Σ:  " << input_alphabet_ << "\n";
  os << "Γ:  " << pushdown_alphabet_ << "\n";
  os << "Q:  ";
  for (const std::string& state : states_) {
    os << state << " ";
  }
  os << "\n";
  os << "q0: " << initial_state_ << "\n";
  os << "Z:  " << pushdown_initial_symbol_ << "\n";
  os << "F:  "; // << not implemented
  os << "δ:\n";
  int state = 0;
  for (const StateTransitions& state_transitions : transition_function_) {
    for (const auto& transition : state_transitions) {
      os << "(" << states_[state] << ", " << transition.first.first << ", " ;
      os << transition.first.second << ") --> (" << transition.second.first;
      os << ", " << transition.second.second << ")\n";
    }
    ++state;
  }
  os << "--------------------";
  os << "------------------------------------------------------------\n";
}