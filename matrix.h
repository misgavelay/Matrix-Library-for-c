#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <math.h>
#include <string.h>

//TO DO: matrix multiplication, matrix hafiha, mult/ add/sub scalar





struct matrix_re {
    int **matrix;
    int num_rows;
    int num_cols;

};

//struct Point p = {1 ,2};
//p.x;
//p.y;
//
//struct Point *p_pointer = &p;
//p_pointer->x === (*p_pointer).x
                                          //
typedef struct matrix_re * matrix_t;

int** buildMatrix(int rows, int colloumns);
void buildLowerMatrix(int** a,int** b,int colloumn,int n);
int det();
int** malloc_matrix(int coloumns,int rows);
int** matrix_multiplication(int** a,int left_matrix_colloumns, int left_matrix_rows, int** b, int right_matrix_colloumns, int right_matrix_rows);
int** add_matrixs(int** a,int left_martix_rows, int left_matrix_colloumns, int** b, int right_matrix_rows, int right_matrix_colloumns);
int** sub_matrixs(int** a,int left_martix_rows, int left_matrix_colloumns, int** b, int right_matrix_rows, int right_matrix_colloumns);
int** add_row(int** a, int matrix_rows, int matrix_colloumns, int row);
void sub_scalar(int** a ,int rows, int colloumns, int scalar);
void mult_scalar(int** a ,int rows, int colloumns, int scalar);
void add_scalar(int** a ,int rows, int colloumns, int scalar);
void zero_matrix(int** a, int matrix_rows, int matrix_colloumns);

matrix_t create_matrix(int rows, int cols);
void addRow(matrix_t mat, int *row);


int matrix_get(row, col);


#endif // MATRIX_H_INCLUDED
