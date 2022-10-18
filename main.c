#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>



//TODO: deal with errors
//TODO: del_col not working
//TODO: change add row/coloumn delete row/col to void
//TODO : deal with malloc fail evry where
//Question for nadav: how excatlly does it work. if i do mat1 = mat 2? and let say then destryo mat1 etc'
// what is "user" supoose to do if malloc at add row fail?
//Check: how i delt with malloc error in create matrix




struct matrix_re {
    int** matrix;
    int num_rows;
    int num_cols;

};

typedef struct matrix_re * matrix_t;

int det();
int** malloc_matrix(int coloumns,int rows);
void add_row_last(matrix_t mat, int *row, int size_of_row);
void build_lower_matrix(matrix_t original,matrix_t new_matrix,int col);
void mult_scalar(matrix_t mat, int scalar);
void add_scalar(matrix_t mat, int scalar);
void sub_scalar(matrix_t mat, int scalar);
matrix_t create_matrix(int rows, int cols);
matrix_t add_row(matrix_t mat, int* row,int size_of_row, int index);
matrix_t build_input_matrix(int rows, int colloumns);
matrix_t matrix_multiplication(matrix_t left_matrix, matrix_t right_matrix);
matrix_t add_matrixs(matrix_t left, matrix_t right);
matrix_t sub_matrixs(matrix_t left, matrix_t right);
matrix_t build_matrix(int size_of_row, int num_args,  ...);
matrix_t add_col(matrix_t mat,int* col, int col_size, int index);
matrix_t delete_row(matrix_t mat, int index);
matrix_t delete_col(matrix_t mat, int index);

int main()
{
//Test all scalar shit:
//    matrix_t a = build_input_matrix(3,3);
//    print_matrix(a);
//    matrix_t b = build_input_matrix(3,3);
//    print_matrix(b);
//    int scalar = 3;
//    mult_scalar(a,scalar);
//    print_matrix(a);
//    add_scalar(a,3);
//    print_matrix(a);
//    sub_scalar(a,2);
//    print_matrix(a);
//    matrix_t res = add_matrixs(a,b);
//    print_matrix(res);
//    res = sub_matrixs(a,b);
//    print_matrix(res);

//Test add row lost:
//matrix_t mat = create_matrix(0,0);
int row[] = {1,2,3,9};
int row2[] = {3,4,5,11};
int row3[] = {6,7,8,15};
//int row4[] = {0,0,0};
//add_row_last(mat,row,4);
//add_row_last(mat,row2,4);
//add_row_last(mat,row3,4);
//print_matrix(mat);
int row4[] = {4,4,4,4};
//matrix_t test = add_row(mat,row4,4,3);
//print_matrix(test);


//Test add row:
matrix_t mat = build_matrix(4,3,row,row2,row3);
print_matrix(mat);

//Test add_coloumn:
matrix_t test = add_col(mat,row4,4,1);
print_matrix(test);
matrix_t test2 = delete_col(test,2);
print_matrix(test2);
}


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
create_matrix_clean_up:
    return mat;
}



int** malloc_matrix(int rows, int cols){

    int** a = NULL;
    int i = 0;
    a = malloc(rows*sizeof(int*));  //it is common practice to "cast" (int**)malloc to tell me that it returns int**
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
cleanup:
    return a;

}

void destroy_matrix(matrix_t mat){
      for (int i=0;i<mat->num_rows;i++){
            free(mat->matrix[i]);
    }
    free(mat->matrix);
}

//**** Adding/Deliting Rows/Colloumns ****//

void add_row_last(matrix_t mat, int *row, int size_of_row) //do i have to pass number of ellements?
                                                    //how do i raise error?
                                                    //handle a case where he gives a row of 4 elements and gives size of row 3?
{
    // TODO: add check malloc  ???
    // TODO: assert(num_elements(row) == mat->num_cols)
    // TODO: if num_cols == 0 && num_rows == 0 as add row and update cols and rows
                            ////Why plus 1?
    if(mat->num_cols == 0){
        mat->num_cols = size_of_row;
    }
    if(mat->num_cols != size_of_row){
        return -1;
    }
    mat->matrix = (int**)realloc(mat->matrix, (mat->num_rows+1)*sizeof(int *));
    mat->matrix[mat->num_rows] = (int*)malloc(mat->num_cols*sizeof(int));
    memcpy(mat->matrix[mat->num_rows], row, mat->num_cols*sizeof(int));//(destenation,source,in byte how much you wanna  coppy)
    mat->num_rows += 1;
}


matrix_t add_row(matrix_t mat, int* row,int size_of_row, int index){              //Looks good?
    //TODO: raise
    //TODO: change to void
    if((index < 0)||index>mat->num_rows){
        return -1;
    }
    if(size_of_row != mat->num_cols){
        return -1;
    }
    int i=0;
    matrix_t temp_matrix = create_matrix(mat->num_rows+1,mat->num_cols);
    for (i;i<index;i++){
            memcpy(temp_matrix->matrix[i],mat->matrix[i],mat->num_cols*sizeof(int));
    }
    memcpy(temp_matrix->matrix[index],row,mat->num_cols*sizeof(int));
    for(i;i<mat->num_rows;i++){
       memcpy(temp_matrix->matrix[i+1],mat->matrix[i],mat->num_cols*sizeof(int));
    }
    return temp_matrix;
}


matrix_t add_col(matrix_t mat,int* col, int col_size, int index){   //TODO: deal with errors
                                                                    //if index to big
    if(col_size != mat->num_cols){
        return -1;
    }

    if((index<0)||(index>mat->num_cols))
    {
        return -1;
    }

    matrix_t temp_matrix = create_matrix(mat->num_rows,mat->num_cols+1);
    int col_args = 0 ;
    for(int i=0;i<mat->num_rows;i++){
            int colloumn_flag = 0;
        for(int j=0;j<mat->num_cols+1;j++){
            if(j==index){
                temp_matrix->matrix[i][j] = col[col_args];
                col_args+=1;
                colloumn_flag+=1;
            }
            else
            {
                temp_matrix->matrix[i][j]=mat->matrix[i][j-colloumn_flag];
            }
        }

    }
    return temp_matrix;
}


matrix_t delete_row(matrix_t mat, int index){
    matrix_t temp_matrix = create_matrix(mat->num_rows-1,mat->num_cols);
    int row_flag = 0;
    for(int i=0;i<mat->num_rows-1;i++){
        if(i==index){
            row_flag+=1;
        }
        memcpy(temp_matrix->matrix[i],mat->matrix[i+row_flag],mat->num_cols*sizeof(int));
    }
    return temp_matrix;
}


matrix_t delete_col(matrix_t mat, int index){
    matrix_t temp_matrix = create_matrix(mat->num_rows,mat->num_cols-1);
    for (int i=0;i<mat->num_rows;i++){
        int col_flag=0;
        for(int j=0;j<mat->num_cols-1;j++){
            if(j==index){
                col_flag+=1;
            }
            temp_matrix->matrix[i][j]==mat->matrix[i][j+col_flag];
        }
    }
    return temp_matrix;
}

//**** Building Matrixs ****//
matrix_t build_input_matrix(int rows, int colloumns){             ////What is the end game? the user will need to to martix_t mat = build...?
    matrix_t mat = create_matrix(rows,colloumns);
    for(int i=0;i<rows;i++){
        printf("enter %d values for the  row %d\n",colloumns,i+1);
        for(int j=0;j<colloumns;j++){

          scanf("%d",&mat->matrix[i][j]);
        }
    }
    return mat;


}


matrix_t build_matrix(int size_of_row, int num_args, ...){
    int i=0;                                            //TODO: deal with dimention error, cant to it with out checking size of row
    matrix_t mat = create_matrix(0,0);               //more explantion on variadic function
    va_list ap;    //argument paramater
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





void build_lower_matrix(matrix_t original,matrix_t new_matrix,int col){
    int k=0,m=0; //k == row index  ; m==coloumn index
    int rows = original->num_rows;
    for(int i=1;i<rows;i++){
        for(int j=0;j<rows;j++){
            if(j==col){
                continue;
            }
            new_matrix->matrix[k][m]=original->matrix[i][j];
            m++;
        }
        k++;
        m=0;
    }
}


//**** Linear Algebra ****//
int det(matrix_t mat){
    int rows = mat->num_rows;
    int cols = mat ->num_cols;
    if(rows != cols){
        return -1 ;
    }
    int sum=0,i;
    int n = rows;
    int** matrix = mat->matrix;
    if(n==2){
        return matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0];
    }
    else{
        for(i=0;i<n;i++){

            matrix_t temp_matrix = create_matrix(n-1,n-1);
            build_lower_matrix(mat,temp_matrix,i);
           sum+=pow(-1,i)*matrix[0][i]*det(temp_matrix);
           destroy_matrix(temp_matrix);
        }
    }
    return sum;
}





matrix_t matrix_multiplication(matrix_t left_matrix, matrix_t right_matrix){
    if (left_matrix->num_cols != right_matrix->num_rows){
        return -1;
    }
    matrix_t res = create_matrix(left_matrix->num_rows,right_matrix->num_cols);
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



matrix_t add_matrixs(matrix_t left, matrix_t right){
    if((left->num_rows != right->num_rows)||(left->num_cols != right->num_cols)){
       return -1;
                                                                                      ////how to finsish here???
    }
    matrix_t res = create_matrix(left->num_rows,right->num_cols);
    for(int i =0; i<left->num_rows;i++){
        for(int j=0;j<right->num_cols;j++){
            res->matrix[i][j]=left->matrix[i][j]+right->matrix[i][j];
        }
    }
    return res;
}


matrix_t sub_matrixs(matrix_t left, matrix_t right){
    if((left->num_rows != right->num_rows)||(left->num_cols != right->num_cols)){
        return -1;
                                                                                      ////how to finsish here???
    }
    matrix_t res = create_matrix(left->num_rows,right->num_cols);
    for(int i =0; i<left->num_rows;i++){
        for(int j=0;j<right->num_cols;j++){
            res->matrix[i][j]=left->matrix[i][j]-right->matrix[i][j];
        }
    }
    return res;
}



