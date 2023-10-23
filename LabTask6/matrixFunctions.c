#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 128

typedef char String[MAX_STRING];
/*---------------------------------------------------------------------------*/

double* input_matrix(int* rows, int* columns, char* matrixName) {
    int check = 0;
    // check, prompt and receive user inputs
    while(check == 0){
        printf("Please enter the dimensions (rows columns) of %s: ", matrixName);
        scanf("%d %d", rows, columns);
        if((*rows >= 0) && (*columns >= 0)){
            check = 1;
        }
    }
    
    //allocate nessesary memory for the matrix
    double* matrix = (double*)malloc((*rows) * (*columns) * sizeof(double));
    
    //get user inputs of matrix values
    printf("Enter the values of %s:\n", matrixName);
    for(int r = 0; r < *rows; r++){
        for(int c = 0; c < *columns; c++){
	    printf("Enter the value for location (%d, %d): ", r, c);
	    scanf("%lf", &matrix[r * (*columns) + c]);
        } //end of inside for
    } //end of first for
    return matrix;
}


int matrix_multiply(double* m1, int m1_rows, int m1_columns, double* m2, int m2_rows, int m2_columns, double* m3){
    //check if valid for multiplication
    if(m1_columns != m2_rows){
        return 0;
    }

    //perform the multiplication
    for(int r = 0; r < m1_rows; r++){
        for(int c = 0; c < m2_columns; c++){
            double sum = 0;
	    for(int x = 0; x < m2_rows; x++){
		sum = sum + m1[r * m1_columns + x] * m2[x * m2_columns + c];
	    }
	    m3[r * m2_columns + c] = sum;
        }
    }
    return 1; //multiplication sucessful
}

void output_matrix(double *m, int rows, int columns){
    for(int r = 0; r < rows; r++){
        for(int c = 0; c < columns; c++){
	    printf("%.2lf ", m[r * columns + c]); //print row by row
	}
        printf("\n"); //indicates new row
    }
}

int main(void) {

    double *m1,*m2,*m3;
    int m1_rows,m1_columns,m2_rows,m2_columns;

    if (((m1 = input_matrix(&m1_rows,&m1_columns,"Matrix 1")) != NULL) &&
((m2 = input_matrix(&m2_rows,&m2_columns,"Matrix 2")) != NULL) &&
((m3 = malloc(m1_rows*m2_columns*sizeof(double))) != NULL)) {
        printf("Matrix 1\n");
        output_matrix(m1,m1_rows,m1_columns);
        printf("Matrix 2\n");
        output_matrix(m2,m2_rows,m2_columns);
        if (matrix_multiply(m1,m1_rows,m1_columns,m2,m2_rows,m2_columns,m3)) {
            printf("Product\n");
            output_matrix(m3,m1_rows,m2_columns);
            free(m1);
            free(m2);
            free(m3);
            return(0);
        } else {
            printf("Error in dimensions\n");
            free(m1);
            free(m2);
            free(m3);
            return(-1);
        }
    } else {
        free(m1);
        free(m2);
        free(m3);
        printf("Error allocating memory\n");
        return(-2);
    }
}
