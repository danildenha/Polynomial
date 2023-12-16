### **Polynomial Class Implementation README**

---

#### Project Overview:

- **Objective:** This project involves designing and implementing a Polynomial class in C++ to handle single-variable polynomials of degree 'n' over a specified numeric type (NumType). The implementation focuses on efficiency using linked lists of monomials.

  **See the picture that explains what is Polynomial**

  ![Polynomial Picture](https://media.geeksforgeeks.org/wp-content/uploads/20230713114538/Polynomial-(2).png)

#### Project Components:

- **Polynomial.h:** Contains the implementation of the Polynomial and Monomial classes using templates. The Polynomial class manages linked lists of Monomials and performs various polynomial operations.

- **PolynomialTestDriver.cpp:** This file serves as a driver program to test the functionalities of the implemented Polynomial class. It includes tests for input formats and function calls.

#### Implementation Approach:

- **Data Structure:** Utilizes linked lists to efficiently handle sparse polynomials, avoiding space inefficiency associated with vector implementations.

- **Input/Output Syntax:** Follows a specific syntax for input and output, using finite sequences of coefficient-degree pairs terminated by a zero sentinel for input. The output emphasizes readability and ease of comprehension.

