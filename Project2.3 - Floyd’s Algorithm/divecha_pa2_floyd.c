/*
 * FLOYD ALGORITHM.
 * @author Yash Diveha
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int size=0; //This is used to dynamically find the size of the matrix.


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

 
/* This function reads the file, tokenized the line by "," and return the weighted matrix.
 * @param:  filename 
 * @return: weighted adjacency matrix, parameter char 
 */
int** fileRead(char *fileName)
{
   	
	FILE *fp;
   	size_t buff =0 ;
	char *token;
	char *line = NULL;
 	//fp = fopen("input1.txt", "r");
 	fp = fopen(fileName, "r");
	size=0;

	if(!fp) {
		printf("File does not exist. \n"); 
		exit(0);
	}

	//This is used to get the size of the matrix depending upon the number of rows in FILE
	while(!feof(fp))
	{
		getline(&line, &buff, fp);
		size++;
	}
	fclose(fp);

	FILE *fptr;
	//fptr = fopen("input1.txt", "r");
	fptr = fopen(fileName, "r");
		if(!fptr) {
			printf("File does not exist. \n"); 
			exit(0);
		}
	int **W = allocateSpace(size);

	int i=0;
	while(!feof(fptr))
	{       
		getline(&line, &buff, fptr);
		token = strtok(line, ",");
		int j=0;
		while(token!=NULL)
		{ 		
			W[i][j]=atoi(token);
			j++;
			token = strtok(NULL, ",\n"); 
		}
		i++;

	}
return W;
}


/* This function displays the 2D array in matrix form.
 * @param  matrix - which needs to be displayed n - size of the matrix 
 * @return void 
 */

void displayMatrix(int **a, int n){
int i,j;
for(i=0;i<n;i++){
	for (j=0;j<n;j++)
		if(j==0)printf("| %5d ", a[i][j]);	
				else if(j==(n-1))printf("%5d |", a[i][j]);	
					else printf("%5d ", a[i][j]);
	printf("\n");		
	}
}


/* This function recursively prints the intermediate paths between start and the end vertex.
 * @param  p - Path matrix gives shortes path q - starting index  r - ending index
 * @return void 
 */
void path(int **p,int q,int r)
{
	
	if(p[q][r]==0)
	return;
	if(q!=r)
	{
		path(p,q,p[q][r]);
		printf("v%d->",p[q][r]);		
		//path(p,k,r);
	}
		
}
 

/* This function implements FLOYD Algorithm
 * @param a - matrix on which operations are performed p - Path matrix which is generated to find paths n - size of the matrix 
 * @return void
 */
void floydAlgorithm(int **a,int **p,int n)
{
	int i,j,k;
	for(k=0;k<n;k++){
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				if(a[i][j]>(a[i][k]+a[k][j]))
				{
					a[i][j]=a[i][k]+a[k][j]; 					
					p[i][j]=k+1;
				} 
			}
		}
	}
} 

/* This function prints all the shortest path between all the vertices.
 * @param path matrix
 * @return void
 */
void printAllShortestPath(int **P){

	int i,j;
	for(i=0;i<size-1;i++)
	{
		for(j=0;j<size-1;j++)
		{
			printf("Shortest path between %d and %d: ", i+1, j+1);
			printf("v%d->", i+1);	
			path(P,i,j);
			printf("v%d \n", j+1);

		}
	printf("\n");
	}
}


/* This is the start of the program
 * @param void
 * @ return int 
 */

int main(int argc, char *argv[])
{
	int i,j, start, end;

	if(argc > 2)
    {
        printf("Invalid number of argument \nUsage: ./divecha_pa2_floyd <filename>\n");
        exit(0);
    }
	char *fileName = argv[1];

	int **W = fileRead(fileName);
	
	printf("\nWeighted Adjacency matrix w: \n");	displayMatrix(W,size-1);

	int **P = allocateSpace(size);

	floydAlgorithm(W,P,size-1);	
	
	printf("\nPath matrix:\n"); 	displayMatrix(P,size-1);	
	printf("\n");

	printAllShortestPath(P);

	printf("To find shortest path between any two vertex. \n");	

	printf("Enter Start Vertex: \t");	scanf("%d", &start);	
	printf("Enter End Vertex: \t");		scanf("%d", &end);


	printf("Shortest path between %d and %d: ", start, end);			
	printf("v%d->", start);	
	path(P,start-1,end-1);
	printf("v%d \n\n", end);

	freeSpace(W,size);
	freeSpace(P,size);
	
return 0;
}