/*
 * STRASSEN MATRIX MULTIPLICATION.
 * @author Yash Diveha
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* This function displays the 2D array in matrix form.
 * @param  matrix - which needs to be displayed n - size of the matrix 
 * @return void 
 */

void displayMatrix(int **matrix, int n){
    int i=0, j=0;
    for(i=0;i<n;i++){
    	for(j=0;j<n;j++)
    			if(j==0)printf("| %5d ", matrix[i][j]);	
    				else if(j==(n-1))printf("%5d| ", matrix[i][j]);	
    					else printf("%5d ", matrix[i][j]);	
    	printf("\n");
    	}
    printf("\n");
}


/* This function allocates the space depending upon the size
 * @param - Size of the matrix
 * @return **matrix- allocated matrix
 */

int** allocateSpace(int n){
    int i,j;
    int **matrix = (int **) malloc(sizeof (int *) * n);
    for(i=0;i<n;i++)
    	matrix[i]=malloc(n*sizeof(int));

    for(i=0;i<n;i++)
    	for(j=0;i<n;i++)
    		matrix[i][j] = 0;

    return matrix;
}


/* This function frees the space depending upon the size.
 * @param **matrix- Need to free the space of matrix 	n- Size of the matrix
 * @return void 
 */

void freeSpace(int **matrix, int n){
    int i;
    for(i =0;i<n;i++)
    	free(matrix[i]);
    free(matrix);
}


/* This function adds/ subtracts 2 matrices depending upon last int value.
 * @param A - First matrix  B - Second Matrix  n- Size of the matrix  _add_sub - performs addition (1) | performs subtraction (1)
 * @return added/subtracted matrix
 */

int** matrixAddSub(int **A, int **B, int n, int _add_sub){
    int i,j;
    int ** C = allocateSpace(n);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(_add_sub ==1)
                C[i][j] = A[i][j]+B[i][j];
            else if(_add_sub == 0)
                    C[i][j] = A[i][j]-B[i][j];
            }
        }
    return C;
}


/* This function multiply 2 matrices.
 * @param A - First matrix  B - Second Matrix  n- Size of the matrix  
 * @return multiplied matrix using STANDARD MULTIPLICATION
 */

int** standardMatrixMult(int **A, int **B, int n){
    int i,j,k;
    int **C = allocateSpace(n);
    for(i=0;i<n;i++)
    	for(j=0;j<n;j++)
    		for(k=0;k<n;k++)
    			C[i][j] += A[i][k]*B[k][j];
    return C;
}


/* This function multiply 2 matrices using Strassen Algorithm.
 * @param A - First matrix  B - Second Matrix  n- Size of the matrix  
 * @return multiplied matrix using STRASSEN MULTIPLICATION
 */

int** strassenMatrixMult(int **A, int **B, int n){
	int **C = allocateSpace(n);
	if(n==2)
	{
        //Computing normal matrix multiplication.
		int M[7];
		M[0] = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
        M[1] = (A[1][0] + A[1][1]) * B[0][0];
	    M[2] = (B[0][1] - B[1][1]) * A[0][0];
	    M[3] = (B[1][0] - B[0][0]) * A[1][1];
	    M[4] = (A[0][0] + A[0][1]) * B[1][1];
	    M[5] = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1]);
	    M[6] = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);

	    C[0][0] = M[0] + M[3] - M[4] + M[6];
        C[0][1] = M[2] + M[4];
	    C[1][0] = M[1] + M[3];
	    C[1][1] = M[0] - M[1] + M[2] + M[5];
	
	}else{

        //Initilization
	    int **A11, **B11;
        int **A12, **B12;
        int **A21, **B21;
        int **A22, **B22;

        n = n / 2; 

        int i, j; 

        //Allocate memory for smaller sub matrices for A and B
        A11 = allocateSpace(n);        A12 = allocateSpace(n);
        A21 = allocateSpace(n);        A22 = allocateSpace(n);

        B11 = allocateSpace(n);        B12 = allocateSpace(n);
        B21 = allocateSpace(n);        B22 = allocateSpace(n);

	   //Dividing A and B matrix into sub matrices.
        for (i=0; i<n; i++) {
            for (j=0; j<n; j++) {
                
                A11[i][j] = A[i][j];		A12[i][j] = A[i][j+n];
                A21[i][j] = A[i+n][j];      A22[i][j] = A[i+n][j+n];

                B11[i][j] = B[i][j];        B12[i][j] = B[i][j+n];
                B21[i][j] = B[i+n][j];      B22[i][j] = B[i+n][j+n];
                            
            }
        }
              
        //Allocate memory for temporary matrices.
        int **M1 = allocateSpace(n);        int **M2 = allocateSpace(n);
        int **M3 = allocateSpace(n);        int **M4 = allocateSpace(n);
        int **M5 = allocateSpace(n);        int **M6 = allocateSpace(n);
        int **M7 = allocateSpace(n);
  
	   
        //Compute M1..M7
        M1 = strassenMatrixMult( matrixAddSub(A11,A22,n,1), matrixAddSub(B11,B22,n,1), n);
        M2 = strassenMatrixMult( matrixAddSub(A21,A22,n,1), B11, n);
        M3 = strassenMatrixMult( A11, matrixAddSub(B12,B22,n,0), n);
        M4 = strassenMatrixMult( A22, matrixAddSub(B21,B11,n,0),  n);
        M5 = strassenMatrixMult( matrixAddSub(A11,A12,n,1), B22, n);
        M6 = strassenMatrixMult( matrixAddSub(A21,A11,n,0), matrixAddSub(B11,B12,n,1), n);
        M7 = strassenMatrixMult( matrixAddSub(A12,A22,n,0), matrixAddSub(B21,B22,n,1), n);


        //Allocate C sub matrices.	   
        int **C11 = allocateSpace(n);        int **C12 = allocateSpace(n);
        int **C21 = allocateSpace(n);        int **C22 = allocateSpace(n);

       //Computer smaller C sub matrices.
	   C11 = matrixAddSub(matrixAddSub(matrixAddSub(M1,M4,n,1), M5, n, 0), M7, n, 1);
       C12 = matrixAddSub(M3,M5,n,1);
	   C21 = matrixAddSub(M2,M4,n,1);
       C22 = matrixAddSub(matrixAddSub(matrixAddSub(M1,M3, n,1), M2, n, 0), M6, n, 1); 

       //Form C using smaller C sub matrices.
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                C[i][j] = C11[i][j];                C[i][j+n] = C12[i][j];
                C[i+n][j] = C21[i][j];              C[i+n][j+n] = C22[i][j];
            }
        }

	//FreeSpace
	freeSpace(M1,n);	freeSpace(M2,n);	freeSpace(M3,n);	freeSpace(M4,n);
	freeSpace(M5,n);	freeSpace(M6,n);	freeSpace(M7,n);
	freeSpace(A11,n);	freeSpace(A12,n);	freeSpace(A21,n);	freeSpace(A22,n);
	freeSpace(B11,n);	freeSpace(B12,n);	freeSpace(B21,n);	freeSpace(B22,n);
	freeSpace(C11,n);	freeSpace(C12,n);	freeSpace(C21,n);	freeSpace(C22,n);

	}
return C;
}


int main(int argc, char *argv[])
{
    int **A, **B, **C, **D;
    int n = atoi(argv[1]);
    int i,j;

    if(argc > 2)
    {
        printf("Invalid number of arguments \nUsage: ./divecha_pa2_stra <size_of_matrix(power of 2)>\n");
        exit(1);
    }

    while(n%2!=0){
        printf("Enter the size of the matrices (Power of 2): \t");
        scanf("%d", &n);
    }
    

    A = allocateSpace(n);
    B = allocateSpace(n);
    C = allocateSpace(n);

    srand(time(NULL));
    for(i=0;i<n;i++)
        for(j=0;j<n;j++){
            A[i][j] = rand()%21 +(-10); //Generates random number between -10 to 10.
            B[i][j] = rand()%21 +(-10); //Generates random number between -10 to 10.
        }


    printf("A:\n");
    displayMatrix(A, n);
    printf("B: \n");
    displayMatrix(B, n);


    //Using Standard multiplication method.
    C = standardMatrixMult(A, B, n);
    printf("Result of Standard Matrix Multiplication:\n");
    displayMatrix(C, n);


    //Using Strassen multiplication method.
    C = strassenMatrixMult(A, B, n);
    printf("Result of Strassen Matrix Multiplication:\n");
    displayMatrix(C, n);	

    freeSpace(A,n);
    freeSpace(B,n);
    freeSpace(C,n);

return 0;
}