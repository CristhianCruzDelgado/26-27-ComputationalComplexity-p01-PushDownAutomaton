/**
 * Universidad de La Laguna ULL
 * Degree: Computer Engineering
 * Signature: Computational Complexity
 * Practice 01: Pushdown Automaton
 * Author: Cristhian Adoney Cruz Delgado
 * Email: alu0101648293@ull.edu.es
 */

#include "../include/pushdown-automaton-app.h"

#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
  try {
    PushDownAutomatonApp pushdown_automaton_app(argc, argv);
    pushdown_automaton_app.parseArgsAndRunPushDownAutomaton();
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  } catch (...) {
    std::cerr << "Error: ???\n";
    return 2;
  }
  return 0;
}
