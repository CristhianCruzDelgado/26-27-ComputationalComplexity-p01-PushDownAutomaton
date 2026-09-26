/**
 * Universidad de La Laguna ULL
 * Degree: Computer Engineering
 * Signature: Computational Complexity
 * Practice 01: Pushdown Automaton
 * Author: Cristhian Adoney Cruz Delgado
 * Email: alu0101648293@ull.edu.es
 */

#include "../include/pushdown-automaton.h"

const char* PushDownAutomaton::HORIZONTAL_LINE = "--------------------"
  "------------------------------------------------------------\n";

const Alphabet& PushDownAutomaton::getInputAlphabet() const { 
  return input_alphabet_; 
}

const Alphabet& PushDownAutomaton::getStackAlphabet() const { 
  return stack_alphabet_; 
}

const std::vector<std::string>& PushDownAutomaton::getStates() const { 
  return states_; 
}

const std::string& PushDownAutomaton::getInitialState() const { 
  return initial_state_; 
}

const Symbol& PushDownAutomaton::getInitialStackSymbol() const { 
  return initial_stack_symbol_; 
}

std::vector<Transition> PushDownAutomaton::getTransitions(
    const std::string& state,
    const Symbol& input_symbol,
    const Symbol& stack_symbol) const {
  std::vector<Transition> matching;
  auto [first, last] = transition_function_.equal_range(state);
  for (auto it = first; it != last; ++it) {
    const auto& t = it->second;
    bool matches_input = (t.input_symbol == input_symbol) ||
                         (t.input_symbol == Symbol(Symbol::EMPTY_SYMBOL));
    bool matches_stack = (t.stack_symbol == stack_symbol);
    if (matches_input && matches_stack) {
      matching.push_back(t);
    }
  }
  return matching;
}

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

void PushDownAutomaton::read(std::istream& is) {
  readLineComments(is);
  readStates(is);
  readInputAlphabet(is);
  readStackAlphabet(is);
  readInitialState(is);
  readInitialStackSymbol(is);
  readTransitionFunction(is);
}

void PushDownAutomaton::readLineComments(std::istream& is) {
  while (is.peek() == '#' || is.peek() == '\n' || is.peek() == '\r') {
    std::string dummy;
    std::getline(is, dummy);
  }
}

void PushDownAutomaton::readStates(std::istream& is) {
  std::string line_read;
  if (!std::getline(is, line_read)) {
    throw std::invalid_argument("Invalid input: no states defined");
  }
  std::istringstream line_stream(line_read);
  std::string state;
  states_.clear();  
  while (line_stream >> state) {
    states_.push_back(state);
  }
  if (states_.empty()) {
    throw std::invalid_argument("Invalid input: no states defined");
  }
}

void PushDownAutomaton::readInputAlphabet(std::istream& is) {
  if (!(is >> input_alphabet_)) {
    throw std::invalid_argument("Invalid input: malformed input alphabet");
  }
}

void PushDownAutomaton::readStackAlphabet(std::istream& is) {
  if (!(is >> stack_alphabet_)) {
    throw std::invalid_argument("Invalid input: malformed stack alphabet");
  }
}

void PushDownAutomaton::readInitialState(std::istream& is) {
  std::string initial_state;
  if (!std::getline(is, initial_state)) {
    throw std::invalid_argument("Invalid input: no initial state defined");
  }
  if (std::find(states_.begin(), states_.end(), initial_state) ==
      states_.end()) {
    throw std::invalid_argument(
      "Invalid input: the initial state is not contained in the set of states");
  }
  initial_state_ = initial_state;
}

void PushDownAutomaton::readInitialStackSymbol(std::istream& is) {
  std::string line_read;
  if (!std::getline(is, line_read)) {
    throw std::invalid_argument(
      "Invalid input: no initial stack symbol defined");
  }
  std::istringstream line_stream(line_read);
  char character;
  if (!(line_stream >> character)) {
    throw std::invalid_argument(
      "Invalid input: no initial stack symbol defined");
  }
  Symbol initial_stack_symbol(character);
  if (!stack_alphabet_.includes(initial_stack_symbol)) {
    throw std::invalid_argument(
      "Invalid input: initial stack symbol is not contained in the stack "
      "alphabet");
  }
  initial_stack_symbol_ = initial_stack_symbol;
}

void PushDownAutomaton::readTransitionFunction(std::istream& is) {
  std::string line_read;
  transition_function_.clear();
  while (std::getline(is, line_read)) {
    std::istringstream line_stream(line_read);
    std::string current_state;
    Symbol input_symbol;
    Symbol stack_symbol;
    std::string next_state;
    std::string pushdown_string;
    if (!(line_stream >> current_state >> input_symbol >> stack_symbol >>
          next_state >> pushdown_string)) {
      throw std::invalid_argument("Invalid input: malformed transition");
    }
    transition_function_.insert({current_state, 
      {input_symbol, stack_symbol, next_state, pushdown_string}});
  }
  if (transition_function_.empty()) {
    throw std::invalid_argument("Invalid input: transition function undefined");
  }
}

void PushDownAutomaton::write(std::ostream& os) const {
  os << "PushDown Automaton (PDA)\n" << HORIZONTAL_LINE 
     << "Σ:  " << input_alphabet_
     << "\nΓ:  " << stack_alphabet_ 
     << "\nQ:  ";
  for (const std::string& state : states_) {
    os << state << " ";
  }
  os << "\nq0: " << initial_state_ 
     << "\nZ:  " << initial_stack_symbol_
     << "\nF:  " << "∅" 
     << "\nδ:\n";
  for (const auto& [state, transition] : transition_function_) {
    os << "(" << state << ", " << transition.input_symbol << ", "
       << transition.stack_symbol << ") --> (" << transition.next_state << ", "
       << transition.pushdown_string << ")\n";
  }
  os << HORIZONTAL_LINE;
}
