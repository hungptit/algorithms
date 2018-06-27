# Introdution #

This repository contains implementations for many popular algorithms using modern C++. Some commonly used algorithms are moved to src folder so I can reuse them in other projects. 

# FAQs #

## What is the coding style ##

I mainly use google coding style for classes and functions. All solutions are, however, wrtten as unittests using [Catch2](https://github.com/catchorg/Catch2). 

## What are the main design of this package. ##

Most of classes in **src** folder are created using Policy Based Design. This approach can help to improve the flexibilty of the core algorithms and it also reduces the complexity of the testsuite without sarcrificing the performance of core algorithms. For example, by splitting the DFS algorithm into a generic DFS core algorithm and visting policy we can have different DFS variations with minimum effort. See this [book](https://www.amazon.com/Modern-Design-Generic-Programming-Patterns/dp/0201704315) for more inforation about the benefit of the Policy Based Design..  


