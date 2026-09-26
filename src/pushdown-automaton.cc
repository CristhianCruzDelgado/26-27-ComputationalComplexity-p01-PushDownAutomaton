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

void PushDownAutomaton::test(const String& string, bool trace) const {
  if (!hasStringInputAlphabetSymbols(string)) {
    throw std::invalid_argument(
      "Invalid input: string must have input alphabet symbols");
  }
  if (isStringAcceptedByStackEmptyAlgorithm(string, trace)) {
    std::cout << "\n" << string << " ∈ L\n";
  } else {
    std::cout << "\n" << string << " ∉ L\n";
  }
  std::cout << HORIZONTAL_LINE;
}

const std::string& PushDownAutomaton::HORIZONTAL_LINE =
    "--------------------"
    "------------------------------------------------------------\n";

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

void PushDownAutomaton::readStackAlphabet(std::istream& is) {
  is >> stack_alphabet_;
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
  if (std::find(states_.begin(), states_.end(), initial_state) ==
      states_.end()) {
    throw std::invalid_argument(
        "Invalid input: the initial state is not contained in the set of "
        "states");
  }
  initial_state_ = initial_state;
}

void PushDownAutomaton::readInitialStackSymbol(std::istream& is) {
  std::string line_read;
  if (!std::getline(is, line_read)) {
    throw std::invalid_argument(
        "Invalid input: no initial stack symbol defined");
  }
  std::istringstream line(line_read);
  char symbol;
  if (!(line >> symbol)) {
    throw std::invalid_argument(
        "Invalid input: no initial stack symbol defined");
  }
  char extra;
  if (line >> extra) {
    throw std::invalid_argument("Invalid input: invalid initial stack symbol");
  }
  Symbol initial_stack_symbol(symbol);
  if (!stack_alphabet_.includes(initial_stack_symbol)) {
    throw std::invalid_argument(
        "Invalid input: the initial stack symbol is not contained in the stack"
        " alphabet");
  }
  initial_stack_symbol_ = initial_stack_symbol;
}

void PushDownAutomaton::readTransitionFunction(std::istream& is) {
  std::string line_read;
  std::string last_state;
  StateTransitions state_transitions;
  while (std::getline(is, line_read)) {
    std::istringstream transition(line_read);
    std::string current_state;
    Symbol input_symbol;
    Symbol stack_symbol;
    std::string next_state;
    std::string stack_string;
    if (!(transition >> current_state >> input_symbol >> stack_symbol >>
          next_state >> stack_string)) {
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
        {{input_symbol, stack_symbol}, {next_state, stack_string}});
    last_state = current_state;
  }
  if (!state_transitions.empty()) {
    transition_function_.push_back(state_transitions);
  }
}

void PushDownAutomaton::write(std::ostream& os) const {
  os << "PushDown Automaton (PDA)\n"
     << HORIZONTAL_LINE << "Σ:  " << input_alphabet_
     << "\nΓ:  " << stack_alphabet_ << "\nQ:  ";
  for (const std::string& state : states_) {
    os << state << " ";
  }
  os << "\nq0: " << initial_state_ << "\nZ:  " << initial_stack_symbol_
     << "\nF:  " << "∅" << "\nδ:\n";
  int state = 0;
  for (const StateTransitions& state_transitions : transition_function_) {
    for (const auto& transition : state_transitions) {
      os << "(" << states_[state] << ", " << transition.first.first << ", "
         << transition.first.second << ") --> (" << transition.second.first
         << ", " << transition.second.second << ")\n";
    }
    ++state;
  }
  os << HORIZONTAL_LINE;
}

bool PushDownAutomaton::hasStringInputAlphabetSymbols(
    const String& string) const {
  for (int i = 0; i < string.length(); ++i) {
    if (!input_alphabet_.includes(string[i])) {
      return false;
    }
  }
  return true;
}

bool PushDownAutomaton::isStringAcceptedByStackEmptyAlgorithm(
    const String& string, bool trace) const {
  if (trace) {
    std::cout << "TRACE:\n  current-state current-string stack-string"
              << " avilable-transitions\n";
  }
  std::stack<Symbol> symbol_stack;
  symbol_stack.push(initial_stack_symbol_);
  int iteration = 0;
  return moveTroughStates(
    initial_state_, string, symbol_stack, iteration, trace);
}

bool PushDownAutomaton::moveTroughStates(
    const std::string& current_state, 
    const String& current_string,
    const std::stack<Symbol>& symbol_stack, 
    int iteration, 
    bool trace) const {
  std::vector<IndexOfStateTransition> available_transitions;
  if (!current_string.empty() && !symbol_stack.empty()) {
    available_transitions = getAvailableTransitions(
        current_state, current_string[0], symbol_stack.top());
  }
  if (trace) {
    writeTrace(iteration, current_state, current_string, symbol_stack,
        available_transitions);
  }
  ++iteration;
  if (current_string.empty() && symbol_stack.empty()) {
    return true;
  }
  if (current_string.empty() || symbol_stack.empty()) {
    return false;
  }
  for (const IndexOfStateTransition& available_transition :
      available_transitions) {
    const StateTransition& transition = available_transition.second;
    std::string next_state = transition.second.first;
    String next_string = current_string;
    std::stack<Symbol> next_stack = symbol_stack;
    next_string.popFront();
    next_stack.pop();
    const String& pushdown_string = transition.second.second;
    for (std::size_t i = pushdown_string.length(); i > 0; --i) {
      next_stack.push(pushdown_string[i - 1]);
    }
    if (moveTroughStates(next_state, next_string, next_stack, trace, iteration)) {
      return true;
    }
  }
  return false;
}

std::vector<IndexOfStateTransition> PushDownAutomaton::getAvailableTransitions(
    const std::string& current_state, 
    const Symbol& current_symbol,
    const Symbol& current_stack_symbol) const {
  std::vector<IndexOfStateTransition> available_transitions;
  const auto state_iterator =
      std::find(states_.begin(), states_.end(), current_state);
  if (state_iterator == states_.end()) {
    return available_transitions;
  }
  const int state_index = std::distance(states_.begin(), state_iterator);
  const StateTransitions& state_transitions =
      transition_function_.at(state_index);
  int transition_index = 0;
  for (const StateTransition& state_transition : state_transitions) {
    if (state_transition.first.first == current_symbol &&
        state_transition.first.second == current_stack_symbol) {
      available_transitions.push_back({transition_index, state_transition});
    }
    ++transition_index;
  }
  return available_transitions;
}

void PushDownAutomaton::writeTrace(
    int iteration,
    const std::string& current_state,
    const String& current_string,
    const std::stack<Symbol>& symbol_stack,
    const std::vector<IndexOfStateTransition>& available_transitions) const {
  std::cout << iteration << std::setw(3) << current_state
            << std::setw(13) << current_string << std::setw(15);
  writeStack(symbol_stack);
  std::cout << std::setw(10);
  for (const IndexOfStateTransition& available_transition :
       available_transitions) {
    std::cout << current_state << "["
              << available_transition.first << "] ";
  } 
  std::cout << "\n";
}

void PushDownAutomaton::writeStack(
    std::stack<Symbol> symbol_stack) const {
  std::string stack_string;
  while (!symbol_stack.empty()) {
    stack_string.push_back(symbol_stack.top().getSymbol());
    symbol_stack.pop();
  }
  std::reverse(stack_string.begin(), stack_string.end());
  std::cout << String(stack_string);
}
