cmake_minimum_required(VERSION 3.10)

project(ComputationalComplexity-p01-PushDownAutomaton)

file(GLOB_RECURSE SOURCES src/*.cc)

# add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
# add_link_options(-fsanitize=address)

add_executable(pushdown-automaton ${SOURCES})

target_include_directories(pushdown-automaton PRIVATE include)
target_compile_features(pushdown-automaton PRIVATE cxx_std_17)
