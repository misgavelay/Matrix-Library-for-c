#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <math.h>
#include <string.h>
#include <stdbool.h>


struct matrix_re {
    int** matrix;
    int num_rows;
    int num_cols;

};

typedef struct matrix_re * matrix_t;

typedef enum {
    MATRIX_GENERAL_ERROR,
    MATRIX_INDEX_ERROR,
    MATRIX_DIMENTION_ERROR,
    MATRIX_ALLOC_ERROR,
    MATRIX_SUCESS = 0
} matrix_return_code;


/*
get_matrix():
Input : matrix_t mat
Output: int** - returns the matrix of matrix_t. A pointer that points to an array with n (n=matrix_t->num_rows) pointers.
Each pointer in the  array points to an array with k (k=matrix_t->num_colss) intgers
*/
int** get_matrix(matrix_t mat);



/*
get_num_rows():
Input : matrix_t mat
Output: int - returns the number of rows the matrix in matrix_t has
*/
int get_num_rows(matrix_t mat);



/*
get_num_rows():
Input : matrix_t mat
Output: int - returns the number of coloumns the matrix in matrix_t has
*/
int get_num_cols(matrix_t mat);




/*
creat_matrix():
Input : int rows, int cols
Output : matrix_t
Function : Creats a new matrix_t with the given number of coloumns and rows, and sets the initial calues of the matrix to zero
Example :
        matrix_t new_mat = create_matrix(2,2)
        get_matrix(new_mat) = [0,0]
                              [0,0]
       get_num_rows(new_mat) = 2
       get_num_cols(new_mat) = 2
*/
matrix_t create_matrix(int rows, int cols);



/*
det():
Input : matrix_t mat , int* det
Output:
Function: calculates the determint of the given matrix, and sets the value at the adress pointed by det to the result
*/
matrix_return_code det(matrix_t mat,int* det);


/*
det_assis():
Input : matrix_t mat
Output: int
Function: calculates the determint of the given matrix returns the result
*/
int det_assis(matrix_t mat);



/*
malloc_matrix():
Input : int coloumns, int rows
Output : int**
Function : Allocates a place in the heap memory for a matrix of integers, returns a pointer that points to an array with n (n=rows) pointers.
Each pointer in the  array points to an array with k (k=coloumns) intgers
*/
int** malloc_matrix(int coloumns,int rows);



/*
mult_scalar():
Input: matrix_t mat, int scalar
Output:
Function : Multiplies each number in mat by scalar
*/
void mult_scalar(matrix_t mat, int scalar);



/*
add_scalar():
Input : matrix_t mat, int scalar
Output :
Function : Adds scalar to each number in mat
*/
void add_scalar(matrix_t mat, int scalar);



/*
sub_scalar():
Input :matrix_t mat, int scalar
Output :
Function : subs scalar to each number in mat
*/
void sub_scalar(matrix_t mat, int scalar);



/*
free_matrix():
Input : matrix_t mat
Output :
Function : Frees the space in the heap memory the was allocated for the matirx in mat (the place allocated for the mat struct is untouched)
*/
void free_matrix(matrix_t mat);


/*
add_row_last():
Input : matrix_t mat, int* row, int size_of_row (the size of the given row)
Output :
Function : Adds row to the end of mat
Example:
        row = [1,1,1]

                          [0,0,0]
        get_matrix(mat) = [0,0,0]
                          [0,0,0]

        add_row_last(mat,row,3)

                          [0,0,0]
        get_matrix(mat) = [0,0,0]
                          [0,0,0]
                          [1,1,1]

*/
matrix_return_code add_row_last(matrix_t mat, int *row, int size_of_row);



/*
add_col():
Input : matrix_t mat, int* col, int size_of_col (the size of the given row),int index
Output :
Function : Adds the given coloumn to the matrix at the given index, and pushes the rest of the coloumns right
Example:
        col = [1,1,1]

                          [0,2,3]
        get_matrix(mat) = [0,2,3]
                          [0,2,3]

        add_col(mat,row,3,1)

                          [0,1,2,3]
        get_matrix(mat) = [0,1,2,3]
                          [0,1,2,3]


*/
matrix_return_code add_col(matrix_t mat,int* col, int col_size, int index);



/*
add_row():
Input : matrix_t mat, int* row, int size_of_row (the size of the given row), int index
Output :
Function : Adds the given row to the matrix at the given index and pushes the rest of the rows up
Example:
        row = [1,1,1]

                          [0,0,0]
        get_matrix(mat) = [2,2,2]
                          [3,3,3]

        add_row(mat,row,3,1)

                          [0,0,0]
        get_matrix(mat) = [1,1,1]
                          [2,2,2]
                          [3,3,3]

*/
matrix_return_code add_row(matrix_t mat, int* row, int size_of_row, int index);



/*
delete_row():
Input : matrix_t mat, int index
Output :
Function : Deletes the row at the given index from the matrix
Example:
                          [0,0,0]
        get_matrix(mat) = [1,1,1]
                          [2,2,2]
                          [3,3,3]

        delete_row(mat,1)

                          [0,0,0]
        get_matrix(mat) = [2,2,2]
                          [3,3,3]

*/
matrix_return_code delete_row(matrix_t mat, int index);



/*
delete_col():
Input : matrix_t mat, int index
Output :
Function : Deletes the coloumn at the given index from the matrix
Example:
                          [0,1,2,3]
        get_matrix(mat) = [0,1,2,3]
                          [0,1,2,3]

        delete_col(mat,1)

                          [0,2,3]
        get_matrix(mat) = [0,2,3]
                          [0,2,3]
*/
matrix_return_code delete_col(matrix_t mat, int index);



/*
buile_lower_matrix():
Input : matrix_t original, matrix_t new_matrix, int col
Output :
Function : builds the new_matrix to be the same as the original but with out the first row and the coloumn at the given index (index = col),
Used, in recursive calculation of determinent
Example:
                          [0,0,0,0]
   get_matrix(original) = [0,1,2,3]
                          [0,1,2,3]
                          [0,1,2,3]
        matrix_t new_mat = create_matrix(3,3)

        build_lower_matrix(mat,new_mat,1)

                          [0,2,3]
    get_matrix(new_mat) = [0,2,3]
                          [0,2,3]
*/
matrix_return_code build_lower_matrix(matrix_t original,matrix_t new_matrix,int col);



/*
add_matrixs():
Input : matrix_t left, matrix_t right
Output :
Function : Adds each element from the right matrix to each compatible element in left matrix
-
Example:
                          [0,1,2,3]
       get_matrix(mat1) = [0,1,2,3]
                          [0,1,2,3]
                          [0,1,2,3]

                          [0,1,1,1]
       get_matrix(mat2) = [1,1,1,1]
                          [1,1,1,1]
                          [2,2,2,2]

       add_matrixs(mat1,mat2)

                          [0,2,3,4]
       get_matrix(mat1) = [1,2,3,4]
                          [1,2,3,4]
                          [2,3,4,5]

*/
matrix_return_code add_matrixs(matrix_t left, matrix_t right);



/*
sub_matrixs():
Input : matrix_t left, matrix_t right
Output :
Function : subs each element from the right matrix to each compatible element in left matrix
-
Example:
                          [0,1,2,3]
       get_matrix(mat1) = [0,1,2,3]
                          [0,1,2,3]
                          [0,1,2,3]

                          [0,1,1,1]
       get_matrix(mat2) = [1,1,1,1]
                          [1,1,1,1]
                          [2,2,2,2]

       sub_matrixs(mat1,mat2)

                          [0,0,1,2]
       get_matrix(mat1) = [-1,0,1,2]
                          [-1,0,1,2]
                          [-2,-1,0,1]

*/
matrix_return_code sub_matrixs(matrix_t left, matrix_t right);




/*
build_input_matrix():
Input : int rows, int cols
Output : matrix_t
Function : Creates a new matrix_t with the given number of coloumns and rows, Asks for input to determin the matrix values
*/
matrix_t build_input_matrix(int rows, int colloumns);



/*
build_matrix():
Input : int rows, int cols, int num_args, int* row...
Output : matrix_t
Function : Creates a new matrix_t with the given number of coloumns and rows, with the given rows
Example:

        int row[] = {1,2,3,9};
        int row2[] = {3,4,5,11};
        int row3[] = {6,7,8,15};
        matrix_t mat = build_matrix(4,3,row,row2,row3);

                            [1,2,3,9]
        get_matrix(mat) =   [3,4,5,11]
                            [6,7,8,15]

*/
matrix_t build_matrix(int size_of_row, int num_args,  ...);



/*
matrix_mult():
Input : matrix_t left, matrix_t right
Output : matrix_t res
Function : preforms matrix multiplication and returns the result as a new matrix_t
-
Example:
                          [1,2]
       get_matrix(mat1) = [3,4]
                          [5,6]
                          [7,8]


       get_matrix(mat2) = [9,10,11]
                          [12,13,14]


       matrix_t res = matrix_mult(mat1,mat2)

                         [33,36,39]
       get_matrix(res) = [75,82,89]
                         [117,128,139]
                         [159,174,189]

*/
matrix_t matrix_mult(matrix_t left_matrix, matrix_t right_matrix);


/*
is_equal():
Input : matrix_t mat1, matrix_t mat2
Output : bool
Function: returns true if both matrix_t are exactly the same, false elsewhere
*/
bool is_equal(matrix_t mat1, matrix_t mat2);



#endif // MATRIX_H_INCLUDED
