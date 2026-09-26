/**
 * Universidad de La Laguna ULL
 * Degree: Computer Engineering
 * Signature: Computational Complexity
 * Practice 01: Pushdown Automaton
 * Author: Cristhian Adoney Cruz Delgado
 * Email: alu0101648293@ull.edu.es
 */

#include "pushdown-automaton-simulator.h"

#include <algorithm>
#include <stdexcept>

void PushDownAutomatonSimulator::test(const PushDownAutomaton& pda,
                                      const String& string,
                                      bool trace) const {
  if (!hasStringValidInputSymbols(pda, string)) {
    throw std::invalid_argument(
      "Invalid input: string must have input alphabet symbols");
  }
  if (isStringAcceptedByStackEmptyAlgorithm(pda, string, trace)) {
    std::cout << "\n" << string << " ∈ L\n";
  } else {
    std::cout << "\n" << string << " ∉ L\n";
  }
  std::cout << PushDownAutomaton::HORIZONTAL_LINE;
}

bool PushDownAutomatonSimulator::hasStringValidInputSymbols(
    const PushDownAutomaton& pda, const String& string) const {
  for (std::size_t i = 0; i < string.size(); ++i) {
    if (!pda.getInputAlphabet().includes(string[i])) {
      return false;
    }
  }
  return true;
}

bool PushDownAutomatonSimulator::isStringAcceptedByStackEmptyAlgorithm(
    const PushDownAutomaton& pda, const String& string, bool trace) const {
  if (trace) {
    std::cout << "TRACE:\n" << std::left 
              << std::setw(6) << "iter"
              << std::setw(16) << "current state"
              << std::setw(16) << "current string"
              << std::setw(16) << "stack content"
              << "available transitions\n";
  }
  std::string initial_state = pda.getInitialState();
  std::stack<Symbol> symbol_stack;
  symbol_stack.push(pda.getInitialStackSymbol());
  return step(pda, initial_state, string, symbol_stack, 0, trace);
}

bool PushDownAutomatonSimulator::step(
    const PushDownAutomaton& pda,
    const std::string& current_state,
    const String& current_string,
    const std::stack<Symbol>& symbol_stack,
    int iteration,
    bool trace) const {
  if (current_string.empty() && symbol_stack.empty()) {
    if (trace) {
      writeTrace(iteration, current_state, current_string, symbol_stack, {});
    }
    return true;
  }
  if (symbol_stack.empty()) {
    if (trace) {
      writeTrace(iteration, current_state, current_string, symbol_stack, {});
    }
    return false;
  }
  Symbol empty_symbol(Symbol::EMPTY_SYMBOL);
  Symbol current_symbol = 
    current_string.empty() ? empty_symbol : current_string[0];
  Symbol current_stack_symbol = symbol_stack.top();
  std::vector<Transition> available_transitions = 
    pda.getTransitions(current_state, current_symbol, current_stack_symbol);
  if (trace) {
    writeTrace(iteration, current_state, current_string, symbol_stack,
               available_transitions);
  }
  if (available_transitions.empty()) {
    if (trace) {
      std::cout << std::string(54, ' ') << "⤴︎\n";
    }
    return false;
  }
  for (const Transition& transition : available_transitions) {
    String next_string = current_string;
    std::stack<Symbol> next_stack = symbol_stack;
    if (!(transition.input_symbol == empty_symbol) && !next_string.empty()) {
      next_string.popFront();
    }
    next_stack.pop();
    const String& pushdown_string = transition.pushdown_string;
    for (std::size_t i = pushdown_string.size(); i > 0; --i) {
      if (!(pushdown_string[i - 1] == empty_symbol)) {
        next_stack.push(pushdown_string[i - 1]);
      }
    }
    if (step(pda, transition.next_state, next_string, next_stack, 
        iteration + 1, trace)) {
      return true;
    }
  }
  return false;
}

void PushDownAutomatonSimulator::writeTrace(
    int iteration,
    const std::string& current_state,
    const String& current_string,
    const std::stack<Symbol>& symbol_stack,
    const std::vector<Transition>& available_transitions) const {
  std::string stack_string;
  if (symbol_stack.empty()) {
    stack_string = Symbol::EMPTY_SYMBOL;
  } else {
    std::stack<Symbol> tmp = symbol_stack;
    while (!tmp.empty()) {
      stack_string.push_back(tmp.top().getSymbol());
      tmp.pop();
    }
  }
  std::ostringstream string_ss;
  if (current_string.empty()) {
    string_ss << Symbol::EMPTY_SYMBOL;
  } else {
    string_ss << current_string;
  }
  std::cout << std::left 
            << std::setw(6) << iteration
            << std::setw(16) << current_state
            << std::setw(16) << string_ss.str()
            << std::setw(16) << stack_string;
  if (available_transitions.empty()) {
    std::cout << "\n";
    return;
  }
  for (std::size_t i = 0; i < available_transitions.size(); ++i) {
    if (i > 0) {
      std::cout << std::string(54, ' ');
    }
    const auto& transition = available_transitions[i];
    std::cout << "(" << current_state << ", " << transition.input_symbol << ", "
              << transition.stack_symbol << ") -> (" << transition.next_state << ", "
              << transition.pushdown_string << ")\n";
  }
}
