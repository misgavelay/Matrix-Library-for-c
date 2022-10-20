#include "matrix.h"
#include <stdio.h>

#define TEST(x) printf(#x ": "); printf(x() ? "PASS\n" : "FAIL\n");



bool test_get_matrix(){
     int row[] = {1,2,3,4};
    int row2[] = {5,6,7,8};
    int row3[] = {9,10,11,12};
    int val = 1 ;
    matrix_t test_mat = build_matrix(4,3,row,row2,row3);
    int** mat = get_matrix(test_mat);
    for(int i=0 ; i<3;i++){
        for(int j=0;j<4;j++){
           if(mat[i][j]!=val){
            return false;
           }
           val+=1;
        }
    }
    return true;

}

bool test_get_num_row(){
    int row[] = {1,2,3,4};
    int row2[] = {5,6,7,8};
    int row3[] = {9,10,11,12};
    matrix_t test_mat = build_matrix(4,3,row,row2,row3);
    int rows = get_num_rows(test_mat);

    if(3!=rows){
        return false;
    }
    return true;

}

bool test_get_num_cols(){
    int row[] = {1,2,3,4};
    int row2[] = {5,6,7,8};
    int row3[] = {9,10,11,12};
    matrix_t test_mat = build_matrix(4,3,row,row2,row3);
    int cols = get_num_cols(test_mat);

    if(4!=cols){
        return false;
    }
    return true;

}



bool test_det(){
    int row[] = {1,2,3,9};
    int row2[] = {3,4,5,11};
    int row3[] = {6,7,-2,15};
    int row4[] = {4,13,4,4};
    int* ptr;
    matrix_t mat = build_matrix(4,4,row,row2,row3,row4);
    det(mat,ptr);
    int res = *ptr;
    if(-1476 != res){
        return false;
    }
    return true;
}

bool test_det_errors(){
    int row[] = {1,2,3,9};
    int row2[] = {3,4,5,11};
    int row3[] = {6,7,-2,15};
    int* ptr;
    matrix_t mat = build_matrix(4,3,row,row2,row3);
    int dimention_error = det(mat,ptr);
    if(dimention_error!= MATRIX_DIMENTION_ERROR){
        return false;
    }
    return true;

}

bool test_add_col()
{
    int row[] = {1,2,3,9};
    int row2[] = {3,4,5,11};
    int row3[] = {6,7,8,15};
    int row4[] = {4,4,4,4};
    matrix_t mat = build_matrix(4,3,row,row2,row3);
    add_col(mat,row4,4,1);

    int test_row[] = {1,4,2,3,9};
    int test_row2[] = {3,4,4,5,11};
    int test_row3[] = {6,4,7,8,15};
    matrix_t test_mat = build_matrix(5,3,test_row,test_row2,test_row3);
    return is_equal(mat, test_mat);
}



bool test_add_col_errors(){
    int row[] = {1,2,3,9};
    int row2[] = {3,4,5,11};
    int row3[] = {6,7,8,15};
    int row4[] = {4,4,4,4};
    matrix_t test = build_matrix(4,3,row,row2,row3);
    int dimention_error = add_col(test,row4,3,2);
    int index_error1 = add_col(test,row4,4,-1);
    int index_error2 = add_col(test,row4,4,4);
    int sucsses = add_col(test,row4,4,2);
    if((index_error1 == MATRIX_INDEX_ERROR)&&(index_error2 == MATRIX_INDEX_ERROR)&&(dimention_error == MATRIX_DIMENTION_ERROR)&&(sucsses == MATRIX_SUCESS)){
        return true;
    }
    return false;
}


bool test_add_row(){
    int row[] = {1,2,3,9};
    int row2[] = {3,4,5,11};
    int row3[] = {6,7,8,15};
    int row4[] = {4,4,4,4};
    matrix_t test = build_matrix(4,3,row,row2,row3);
    add_row(test,row4,4,2);
    matrix_t test_mat = build_matrix(4,4,row,row2,row4,row3);
    return is_equal(test,test_mat);
}

bool test_add_row_errors(){
    int row[] = {1,2,3,9};
    int row2[] = {3,4,5,11};
    int row3[] = {6,7,8,15};
    int row4[] = {4,4,4,4};
    matrix_t test = build_matrix(4,3,row,row2,row3);
    int dimention_error = add_row(test,row4,3,2);
    int index_error1 = add_row(test,row4,4,-1);
    int index_error2 = add_row(test,row4,4,4);
    int sucsses = add_row(test,row4,4,2);
    if((index_error1 == MATRIX_INDEX_ERROR)&&(index_error2 == MATRIX_INDEX_ERROR)&&(dimention_error == MATRIX_DIMENTION_ERROR)&&(sucsses == MATRIX_SUCESS)){
        return true;
    }
    return false;
}

bool test_add_row_last(){
     int row[] = {1,2,3,9};
    int row2[] = {3,4,5,11};
    int row3[] = {6,7,8,15};
    int row4[] = {4,4,4,4};
    matrix_t test = build_matrix(4,3,row,row2,row3);
    add_row_last(test,row4,4);
    matrix_t test_mat = build_matrix(4,4,row,row2,row3,row4);
    return is_equal(test,test_mat);

}

bool test_add_row_last_errors(){
    int row[] = {1,2,3,9};
    int row2[] = {3,4,5,11};
    int row3[] = {6,7,8,15};
    int row4[] = {4,4,4,4};
    matrix_t test = build_matrix(4,3,row,row2,row3);
    int dimention_error = add_row_last(test,row4,3);
    int sucsses = add_row_last(test,row4,4);
    if((dimention_error == MATRIX_DIMENTION_ERROR)&&(sucsses == MATRIX_SUCESS)){
        return true;
    }
    return false;
}


bool test_delete_row(){
    int row[] = {1,2,3,9};
    int row2[] = {3,4,5,11};
    int row3[] = {6,7,8,15};
    int row4[] = {4,4,4,4};
    matrix_t test = build_matrix(4,4,row,row2,row3,row4);
    delete_row(test,1);
    matrix_t test_mat = build_matrix(4,3,row,row3,row4);
    return is_equal(test,test_mat);
}

bool test_delete_row_errors(){
    int row[] = {1,2,3,9};
    int row2[] = {3,4,5,11};
    int row3[] = {6,7,8,15};
    int row4[] = {4,4,4,4};
    matrix_t test = build_matrix(4,3,row,row2,row3);
    int index_error1 = delete_row(test,-1);
    int index_error2 = delete_row(test,4);
    int sucsses = delete_row(test,2);
    if((index_error1 == MATRIX_INDEX_ERROR)&&(index_error2 == MATRIX_INDEX_ERROR)&&(sucsses == MATRIX_SUCESS)){
        return true;
    }
    return false;
}




bool test_delete_col(){
    int row[] = {1,2,3,9};
    int row2[] = {3,4,5,11};
    int row3[] = {6,7,8,15};
    matrix_t test_mat = build_matrix(4,3,row,row2,row3);
    int test_row[] = {1,4,2,3,9};
    int test_row2[] = {3,4,4,5,11};
    int test_row3[] = {6,4,7,8,15};
    matrix_t mat = build_matrix(5,3,test_row,test_row2,test_row3);
    delete_col(mat,1);
    return is_equal(mat, test_mat);
}

bool test_delete_col_errors(){
    int row[] = {1,2,3,9};
    int row2[] = {3,4,5,11};
    int row3[] = {6,7,8,15};
    int row4[] = {4,4,4,4};
    matrix_t test = build_matrix(4,3,row,row2,row3);
    int index_error1 = delete_col(test,-1);
    int index_error2 = delete_col(test,4);
    int sucsses = delete_col(test,2);
    if((index_error1 == MATRIX_INDEX_ERROR)&&(index_error2 == MATRIX_INDEX_ERROR)&&(sucsses == MATRIX_SUCESS)){
        return true;
    }
    return false;
}




bool test_matrix_mult(){
    int row1[] = {-8,99};
    int row2[] = {56,6};
    int row3[]  = {790,1};
    int row4[] = {0,11};
    int row5[] = {68888,-567};
    int row6[] = {3,4};

    int row7[] = {122,456,2,-7777};
    int row8[]  ={14,11111,9,-3};

    matrix_t mat1 = build_matrix(2,6,row1,row2,row3,row4,row5,row6);
    matrix_t mat2 = build_matrix(4,2,row7,row8);

    matrix_t res = matrix_mult(mat1,mat2);

    int rrow1[] = {410,1096341,875,61919};
    int rrow2[] = {6916,92202,166,-435530};
    int rrow3[]  = {96394,371351,1589,-6143833};
    int rrow4[] = {154,122221,99,-33};
    int rrow5[] = {8396398,25112991,132673,-535740275};
    int rrow6[] = {422,45812,42,-23343};
     matrix_t test_res = build_matrix(4,6,rrow1,rrow2,rrow3,rrow4,rrow5,rrow6);

    return is_equal(res,test_res);

}

bool test_matrix_mult_errors(){
    int row1[] = {-8,99};
    int row2[] = {56,6};
    int row3[]  = {790,1};
    int row4[] = {0,11};
    int row5[] = {68888,-567};
    int row6[] = {3,4};

    int row7[] = {122,456,2,-7777};
    int row8[]  ={14,11111,9,-3};

    matrix_t mat1 = build_matrix(2,6,row1,row2,row3,row4,row5,row6);
    matrix_t mat2 = build_matrix(4,3,row7,row8,row8);

    int dimention_error = matrix_mult(mat1,mat2);
    if(dimention_error == MATRIX_DIMENTION_ERROR){
        return true;
    }
    return false;
}

test_mult_scalar(){
    int row1[] = {-8,99};
    int row2[] = {56,6};
    int row3[]  = {790,1};
    int row4[] = {0,11};
    int row5[] = {68888,-567};
    int row6[] = {3,4};

    matrix_t mat = build_matrix(2,6,row1,row2,row3,row4,row5,row6);

    int rrow1[] = {-8*13,99*13};
    int rrow2[] = {56*13,6*13};
    int rrow3[]  = {790*13,1*13};
    int rrow4[] = {0*13,11*13};
    int rrow5[] = {68888*13,-567*13};
    int rrow6[] = {3*13,4*13};
    matrix_t test_mat = build_matrix(2,6,rrow1,rrow2,rrow3,rrow4,rrow5,rrow6);
    mult_scalar(mat,13);
    return is_equal(mat,test_mat);

}

bool test_add_scalar(){
    int rrow1[] = {410,1096341,875,61919};
    int rrow2[] = {6916,92202,166,-435530};
    int rrow3[]  = {96394,371351,1589,-6143833};
    int rrow4[] = {154,122221,99,-33};
    int rrow5[] = {8396398,25112991,132673,-535740275};
    int rrow6[] = {422,45812,42,-23343};
     matrix_t mat = build_matrix(4,6,rrow1,rrow2,rrow3,rrow4,rrow5,rrow6);

    int row1[] = {410+78,1096341+78,875+78,61919+78};
    int row2[] = {6916+78,92202+78,166+78,-435530+78};
    int row3[]  = {96394+78,371351+78,1589+78,-6143833+78};
    int row4[] = {154+78,122221+78,99+78,-33+78};
    int row5[] = {8396398+78,25112991+78,132673+78,-535740275+78};
    int row6[] = {422+78,45812+78,42+78,-23343+78};
     matrix_t test_mat = build_matrix(4,6,row1,row2,row3,row4,row5,row6);
    add_scalar(mat,78);
    return is_equal(mat,test_mat);

}

bool test_sub_scalar(){
    int rrow1[] = {410,1096341,875,61919};
    int rrow2[] = {6916,92202,166,-435530};
    int rrow3[]  = {96394,371351,1589,-6143833};
    int rrow4[] = {154,122221,99,-33};
    int rrow5[] = {8396398,25112991,132673,-535740275};
    int rrow6[] = {422,45812,42,-23343};
     matrix_t mat = build_matrix(4,6,rrow1,rrow2,rrow3,rrow4,rrow5,rrow6);

    int row1[] = {410-222,1096341-222,875-222,61919-222};
    int row2[] = {6916-222,92202-222,166-222,-435530-222};
    int row3[]  = {96394-222,371351-222,1589-222,-6143833-222};
    int row4[] = {154-222,122221-222,99-222,-33-222};
    int row5[] = {8396398-222,25112991-222,132673-222,-535740275-222};
    int row6[] = {422-222,45812-222,42-222,-23343-222};
     matrix_t test_mat = build_matrix(4,6,row1,row2,row3,row4,row5,row6);
    sub_scalar(mat,222);
    return is_equal(mat,test_mat);

}

bool test_add_matrixs(){
    int row[] = {1,99,3,9};
    int row2[] = {3,4,5,11};
    int row3[] = {-2,7,8,15};
    int row4[] = {4,4,-13,4};
    matrix_t mat1 = build_matrix(4,4,row,row2,row3,row4);

    int rrow[] = {12,13,14,15};
    int rrow2[] = {16,17,18,19};
    int rrow3[] = {16,17,18,19};
    int rrow4[] = {16,17,18,19};
    matrix_t mat2 = build_matrix(4,4,rrow,rrow2,rrow3,rrow4);

    int rrrow[] = {1+12,99+13,3+14,9+15};
    int rrrow2[] = {3+16,4+17,5+18,11+19};
    int rrrow3[] = {-2+16,7+17,8+18,15+19};
    int rrrow4[] = {4+16,4+17,-13+18,4+19};
    matrix_t test_mat1 = build_matrix(4,4,rrrow,rrrow2,rrrow3,rrrow4);
    add_matrixs(mat1,mat2);
    return is_equal(mat1,test_mat1);
}

bool test_add_matrixs_errors(){
    int row[] = {1,99,3,9};
    int row2[] = {3,4,5,11};
    int row3[] = {-2,7,8,15};
    int row4[] = {4,4,-13,4};
    matrix_t mat1 = build_matrix(4,4,row,row2,row3,row4);

    int rrow[] = {12,13,14,15};
    int rrow2[] = {16,17,18,19};
    int rrow3[] = {16,17,18,19};

    matrix_t mat2 = build_matrix(4,3,rrow,rrow2,rrow3);

    int rrrow[] = {12,13,14};
    int rrrow2[] = {16,17,18};
    int rrrow3[] = {16,17,18};
    int rrrow4[] = {16,17,18};
    matrix_t mat3 = build_matrix(4,4,rrrow,rrrow2,rrrow3,rrrow4);

    matrix_t mat4 = build_matrix(4,4,rrow,rrow2,rrow3,rrrow4);

    int dimention_error1 =  add_matrixs(mat1,mat2);
    int dimention_error2 = add_matrixs(mat1,mat3);
    int sucsses = add_matrixs(mat1,mat4);

    if((sucsses == MATRIX_SUCESS)&&(dimention_error1 == MATRIX_DIMENTION_ERROR == dimention_error2)){
        return true;
    }
    return false;

}


bool test_sub_matrixs(){
    int row[] = {1,99,3,9};
    int row2[] = {3,4,5,11};
    int row3[] = {-2,7,8,15};
    int row4[] = {4,4,-13,4};
    matrix_t mat1 = build_matrix(4,4,row,row2,row3,row4);

    int rrow[] = {12,13,14,15};
    int rrow2[] = {16,17,18,19};
    int rrow3[] = {16,17,18,19};
    int rrow4[] = {16,17,18,19};
    matrix_t mat2 = build_matrix(4,4,rrow,rrow2,rrow3,rrow4);

    int rrrow[] = {1-12,99-13,3-14,9-15};
    int rrrow2[] = {3-16,4-17,5-18,11-19};
    int rrrow3[] = {-2-16,7-17,8-18,15-19};
    int rrrow4[] = {4-16,4-17,-13-18,4-19};
    matrix_t test_mat1 = build_matrix(4,4,rrrow,rrrow2,rrrow3,rrrow4);
    sub_matrixs(mat1,mat2);
    return is_equal(mat1,test_mat1);

}



bool test_sub_matrixs_errors(){
    int row[] = {1,99,3,9};
    int row2[] = {3,4,5,11};
    int row3[] = {-2,7,8,15};
    int row4[] = {4,4,-13,4};
    matrix_t mat1 = build_matrix(4,4,row,row2,row3,row4);

    int rrow[] = {12,13,14,15};
    int rrow2[] = {16,17,18,19};
    int rrow3[] = {16,17,18,19};

    matrix_t mat2 = build_matrix(4,3,rrow,rrow2,rrow3);

    int rrrow[] = {12,13,14};
    int rrrow2[] = {16,17,18};
    int rrrow3[] = {16,17,18};
    int rrrow4[] = {16,17,18};
    matrix_t mat3 = build_matrix(3,4,rrrow,rrrow2,rrrow3,rrrow4);

    matrix_t mat4 = build_matrix(4,4,rrow,rrow2,rrow3,rrrow4);

    int dimention_error1 =  sub_matrixs(mat1,mat2);
    int dimention_error2 = sub_matrixs(mat1,mat3);
    int sucsses = sub_matrixs(mat1,mat4);

    if((sucsses == MATRIX_SUCESS)&&(dimention_error1 == MATRIX_DIMENTION_ERROR)&&(dimention_error2 == MATRIX_DIMENTION_ERROR)){
        return true;
    }
    return false;

}

int main()
{
    TEST(test_get_matrix);
    TEST(test_get_num_cols);
    TEST(test_get_num_row);
    printf("\n");
    TEST(test_add_col);
    TEST(test_add_col_errors);
    printf("\n");
    TEST(test_add_row);
    TEST(test_add_row_errors);
    printf("\n");
    TEST(test_add_row_last);
    TEST(test_add_row_last_errors);
    printf("\n");
    TEST(test_delete_row);
    TEST(test_delete_row_errors);
    printf("\n");
    TEST(test_delete_col);
    TEST(test_delete_col_errors);
    printf("\n");
    TEST(test_det);
    TEST(test_det_errors);
    printf("\n");
    TEST(test_matrix_mult);
    TEST(test_matrix_mult_errors);
    printf("\n");
    TEST(test_mult_scalar);
    TEST(test_add_scalar);
    TEST(test_sub_scalar);
    printf("\n");
    TEST(test_add_matrixs);
    TEST(test_add_matrixs);
    printf("\n");
    TEST(test_sub_matrixs);
    TEST(test_sub_matrixs_errors);


    return 0;
}
