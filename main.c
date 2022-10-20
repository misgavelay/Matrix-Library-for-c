#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

#include "matrix.h"







//**** Handling Memory ****//

matrix_t create_matrix(int rows, int cols)
{
    matrix_t mat = NULL;
    mat = (matrix_t)malloc(sizeof(struct matrix_re));
    if(NULL == mat){
        goto create_matrix_clean_up;
    }
    mat->num_rows = rows;
    mat->num_cols = cols;
    mat->matrix = (int **) malloc_matrix(rows, cols);
    if (NULL == mat->matrix) {
        free(mat);
        mat = NULL;
        goto create_matrix_clean_up;
    }

create_matrix_clean_up:
    return mat;
}


int** get_matrix(matrix_t mat){
    return mat->matrix;
}

int get_num_rows(matrix_t mat){
    return mat->num_rows;
}

int get_num_cols(matrix_t mat){
    return mat->num_cols;
}

int** malloc_matrix(int rows, int cols){

    int** a = NULL;
    int i = 0;
    a = malloc(rows*sizeof(int*));
    if (NULL == a) {
        goto cleanup;
    }

    for (i=0;i<rows;i++){
        a[i]=calloc(cols, sizeof(int));
        if (NULL == a[i]) {
            goto cleanup_rows;
        }
    }
    return a;


cleanup_rows:
    for (i = i -1;i>=0;i--){
        free(a[i]);
    }
    free(a);
    a = NULL;
cleanup:
    return a;

}

void destroy_matrix(matrix_t mat){
      for (int i=0;i<mat->num_rows;i++){
            free(mat->matrix[i]);
    }
    free(mat->matrix);
    free(mat);
}

void free_matrix(matrix_t mat){
    for (int row = 0; row < mat->num_rows; ++row) {
        free(mat->matrix[row]);
    }
    free(mat->matrix);

}
//**** Adding/Deliting Rows/Colloumns ****//

matrix_return_code add_row_last(matrix_t mat, int *row, int size_of_row)
{

    if(mat->num_cols == 0){
        mat->num_cols = size_of_row;
    }
    if(mat->num_cols != size_of_row){
        return MATRIX_DIMENTION_ERROR;
    }

    int *new_row = (int*)malloc(mat->num_cols*sizeof(int));
    if (NULL == new_row) {
        return MATRIX_ALLOC_ERROR;
    }

    matrix_t temp = (int**)realloc(mat->matrix, (mat->num_rows+1)*sizeof(int *));
    if (NULL == temp) {

        free(new_row);
        return MATRIX_ALLOC_ERROR;
    }

    mat->matrix = temp;
    mat->matrix[mat->num_rows] = new_row;


    memcpy(mat->matrix[mat->num_rows], row, mat->num_cols*sizeof(int));
    mat->num_rows += 1;
    return MATRIX_SUCESS;
}


matrix_return_code add_row(matrix_t mat, int* row, int size_of_row, int index){
    //TODO: raise
    if((index < 0)||index>=mat->num_rows){
        return MATRIX_INDEX_ERROR;
    }
    if(size_of_row != mat->num_cols){
        return MATRIX_DIMENTION_ERROR;
    }
    int i=0;
    int ** bigger_mat = malloc_matrix(mat->num_rows+1, mat->num_cols);
    if (NULL == bigger_mat) {
        return MATRIX_ALLOC_ERROR;
    }

    for (i;i<index;i++){
            memcpy(bigger_mat[i], mat->matrix[i], mat->num_cols*sizeof(int));
    }

    memcpy(bigger_mat[index],row,mat->num_cols*sizeof(int));

    for(i;i<mat->num_rows;i++){
       memcpy(bigger_mat[i+1],mat->matrix[i],mat->num_cols*sizeof(int));
    }

    free_matrix(mat);

    mat->matrix = bigger_mat;
    mat->num_rows+=1;

    return MATRIX_SUCESS;
}


matrix_return_code add_col(matrix_t mat,int* col, int col_size, int index){

    if(col_size != mat->num_cols){
        return MATRIX_DIMENTION_ERROR;
    }

    if((index<0)||(index>=mat->num_cols))
    {
        return MATRIX_INDEX_ERROR;
    }

    int **temp_matrix = (int**)malloc_matrix(mat->num_rows, mat->num_cols+1);
    if(NULL == temp_matrix){
        return MATRIX_ALLOC_ERROR;
    }
    int col_args = 0 ;
    for(int i=0;i<mat->num_rows;i++){
            int colloumn_flag = 0;
        for(int j=0;j<mat->num_cols+1;j++){
            if(j==index){
                temp_matrix[i][j] = col[col_args];
                col_args+=1;
                colloumn_flag+=1;
            }
            else
            {
                temp_matrix[i][j]=mat->matrix[i][j-colloumn_flag];
            }
        }

    }
    free_matrix(mat);
    mat->matrix = temp_matrix;
    mat->num_cols+=1;
    return MATRIX_SUCESS;
}


matrix_return_code delete_row(matrix_t mat, int index){
     if((index<0)||(index>mat->num_rows))
    {
        return MATRIX_INDEX_ERROR;
    }
    int** temp_matrix = (int**)malloc_matrix(mat->num_rows-1,mat->num_cols);
    if(NULL == temp_matrix){
        return MATRIX_ALLOC_ERROR;
    }
    int row_flag = 0;
    for(int i=0;i<mat->num_rows-1;i++){
        if(i==index){
            row_flag+=1;
        }
        memcpy(temp_matrix[i],mat->matrix[i+row_flag],mat->num_cols*sizeof(int));
    }
    free_matrix(mat);
    mat->matrix = temp_matrix;
    mat->num_rows-=1;
    return MATRIX_SUCESS;
}


matrix_return_code delete_col(matrix_t mat, int index){
     if((index<0)||(index>=mat->num_cols))
    {
        return MATRIX_INDEX_ERROR;
    }
    int** temp_matrix = (int**)malloc_matrix(mat->num_rows,mat->num_cols-1);
    if(NULL == temp_matrix){
        return MATRIX_ALLOC_ERROR;
    }
    for (int i=0;i<mat->num_rows;i++){
        int col_flag=0;
        for(int j=0;j<mat->num_cols-1;j++){
            if(j==index){
                col_flag+=1;
            }
            temp_matrix[i][j] = mat->matrix[i][j+col_flag];
        }
    }
    free_matrix(mat);
    mat->matrix = temp_matrix;
    mat->num_cols-=1;
    return MATRIX_SUCESS;
}

//**** Building Matrixs ****//
matrix_t build_input_matrix(int rows, int colloumns){
    matrix_t mat = create_matrix(rows,colloumns);
    if(NULL == mat){
        return MATRIX_ALLOC_ERROR;
    }
    for(int i=0;i<rows;i++){
        printf("enter %d values for the  row %d\n",colloumns,i+1);
        for(int j=0;j<colloumns;j++){

          scanf("%d",&mat->matrix[i][j]);
        }
    }
    return mat;


}


matrix_t build_matrix(int size_of_row, int num_args, ...){
    int i=0;
    matrix_t mat = create_matrix(0,0);
    if(NULL == mat){
        return MATRIX_ALLOC_ERROR;
    }
    va_list ap;
    va_start(ap, num_args);

    for(i=0;i<num_args;i++){
        add_row_last(mat,va_arg(ap,int*),size_of_row);
    }
    va_end(ap);
    return mat;

}

void print_matrix(matrix_t mat){

    int i,j;
    int rows = mat->num_rows;
    printf("Matrix is:\n");
    for(i=0;i<mat->num_rows;i++){
        for(j=0;j<mat->num_cols;j++){
            printf("\t %d",mat->matrix[i][j]);
        }
        printf("\n");
    }
}





matrix_return_code build_lower_matrix(matrix_t original,matrix_t new_matrix,int col){
     if((col<0)||(col>original->num_cols))
    {
        return MATRIX_INDEX_ERROR;
    }
    int row=0,coll=0;
    int rows = original->num_rows;
    for(int i=1;i<rows;i++){
        for(int j=0;j<rows;j++){
            if(j==col){
                continue;
            }
            new_matrix->matrix[row][coll]=original->matrix[i][j];
            coll++;
        }
        row++;
        coll=0;
    }
    return MATRIX_SUCESS;
}


//**** Linear Algebra ****//

matrix_return_code det(matrix_t mat,int* ptr){
    int rows = mat->num_rows;
    int cols = mat ->num_cols;
    if(rows != cols){
        return MATRIX_DIMENTION_ERROR;
    }
    int res= det_assis(mat);
    if  (NULL == res){
        return MATRIX_ALLOC_ERROR;
    }
    *ptr = res;
    return MATRIX_SUCESS;

}

int det_assis(matrix_t mat){

    int sum=0,i;
    int n = mat->num_rows;
    int** matrix = mat->matrix;
    if(n==2){
        return matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0];
    }
    else{
        for(i=0;i<n;i++){

            matrix_t temp_matrix = create_matrix(n-1,n-1);
            if(NULL == temp_matrix){
                return NULL;
            }
            build_lower_matrix(mat,temp_matrix,i);
           sum+=pow(-1,i)*matrix[0][i]*det_assis(temp_matrix);
           destroy_matrix(temp_matrix);
        }
    }
    return sum;
}





matrix_t matrix_mult(matrix_t left_matrix, matrix_t right_matrix){
    if (left_matrix->num_cols != right_matrix->num_rows){
        return MATRIX_DIMENTION_ERROR;
    }
    matrix_t res = create_matrix(left_matrix->num_rows,right_matrix->num_cols);
    if (NULL == res){
        return MATRIX_ALLOC_ERROR;
    }
    for(int i=0; i<left_matrix->num_rows;i++){
            for(int j=0; j<right_matrix->num_cols; j++){
                for(int k=0;k<left_matrix->num_cols;k++){
                    res->matrix[i][j]+=left_matrix->matrix[i][k]*right_matrix->matrix[k][j];
                }
            }
        }
    return res;
}


void mult_scalar(matrix_t mat, int scalar){
    for(int i=0; i<mat->num_rows; i++){
        for(int j=0; j<mat->num_cols;j++){
            mat->matrix[i][j]*= scalar;
        }
    }
}

void add_scalar(matrix_t mat, int scalar){
    for(int i=0; i<mat->num_rows; i++){
        for(int j=0; j<mat->num_cols;j++){
            mat->matrix[i][j]+= scalar;
        }
    }
}

void sub_scalar(matrix_t mat, int scalar){
    for(int i=0; i<mat->num_rows; i++){
        for(int j=0; j<mat->num_cols;j++){
            mat->matrix[i][j]-= scalar;
        }
    }
}



matrix_return_code add_matrixs(matrix_t left, matrix_t right){
    if((left->num_rows != right->num_rows)||(left->num_cols != right->num_cols)){
       return MATRIX_DIMENTION_ERROR;

    }


    for(int i =0; i<left->num_rows;i++){
        for(int j=0;j<right->num_cols;j++){
            left->matrix[i][j]+=right->matrix[i][j];
        }
    }
    return MATRIX_SUCESS;
}


matrix_return_code sub_matrixs(matrix_t left, matrix_t right){
    if((left->num_rows != right->num_rows)||(left->num_cols != right->num_cols)){
        return MATRIX_DIMENTION_ERROR;
    }
    for(int i =0; i<left->num_rows;i++){
        for(int j=0;j<right->num_cols;j++){
            left->matrix[i][j]-=right->matrix[i][j];
        }
    }
    return MATRIX_SUCESS;
}

bool is_equal(matrix_t mat1, matrix_t mat2)
{
    if (mat1->num_rows != mat2->num_rows)
        return false;

    if (mat1->num_cols != mat2->num_cols)
        return false;

    for (int row = 0; row < mat1->num_rows; row++) {
        for (int col = 0; col < mat1->num_cols; col++) {
            if (mat1->matrix[row][col] != mat2->matrix[row][col])
                return false;
        }
    }

    return true;
}


