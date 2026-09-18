# 26-27-ComputationalComplexity-p01-PushDownAutomaton

The automaton processes an input string by reading symbols from the input and manipulating its stack according to the transition function. A string is accepted if, after the entire input has been consumed, the automaton either reaches an accepting state or empties its stack, depending on the acceptance criterion used.

The program will request the input strings one at a time through the keyboard. For each string, the automaton will process the input and display the current state trace on the screen at the corresponding step of the computation.

## Problem description

A pushdown automaton (PDA) is a formal computational model defined as a 7-tuple

$$M = (Q, \Sigma, \Gamma, \delta, q_0, Z_0, F)$$

where:

($Q$) is a finite set of states.

($\Sigma$) is the input alphabet.

($\Gamma$) is the stack alphabet.

($\delta$) is the transition function, defined as 
$\delta: Q \times (\Sigma \cup {\varepsilon}) \times \Gamma \rightarrow \mathcal{P}(Q \times \Gamma^*)$

($q_0 \in Q$) is the initial state.

($Z_0 \in \Gamma$) is the initial stack symbol.

($F \subseteq Q$) is the set of accepting states.

## Available pushdown automaton

> **Selected: Termination due to empty stack**

> Termination due reaching a final state

## Run code

1. mkdir build
2. cd build
3. cmake ..
4. make
5. /pushdown-automaton -h|--help

## Other information

This code was developed by 
* [Cristhian Adoney Cruz Delgado](https://github.com/CristhianCruzDelgado)

Contact emails 
* <alu0101648293@ull.edu.es>

This code was designed for Computational Complexity, \
signature of the Computer Engineering degree, \
that is studied at the Univeridad de La Laguna.

_18 September 2026_
