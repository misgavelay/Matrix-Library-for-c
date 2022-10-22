# Matrix Library
A library in C for matrices

## Usage

### Building Matrices
The library provides various ways to create matrices and handles the memory allocation,
1. Building via cli input
2. Building via dynamic arrays
3. Building a zero matrix by size.

All of the above return an `matrix_t` object which can be manipulated by adding and deleting rows or columns from a matrix object.

### Matrix Arithmetics
`matrix_t` supports multiple matrix arithmetics,
1. Matrix multiplication
2. Determinant
3. adding/subtracting matrices
4. Multiplying/adding/subtracting scala
