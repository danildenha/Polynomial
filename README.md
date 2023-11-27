#Polynomial Class Implementation README
This project involves the design and implementation of a Polynomial class in C++, catering to single-variable polynomials of degree 'n' over a specified numeric type (NumType). The Polynomial class utilizes double linked lists of monomials for efficient storage and management.

Project Components:

Polynomial.h: Contains the implementation of the Polynomial and Monomial classes using templates. The Polynomial class manages linked lists of Monomials and performs various polynomial operations.
P06PolynomialDriver.cpp: This file serves as a driver program to test the functionalities of the implemented Polynomial class. It includes tests for input formats and function calls.
Implementation Approach:

Data Structure: Utilizes linked lists to efficiently handle sparse polynomials, avoiding space inefficiency associated with vector implementations.
Input/Output Syntax: Follows a specific syntax for input and output, using finite sequences of coefficient-degree pairs terminated by a zero sentinel for input. The output emphasizes readability and ease of comprehension.
