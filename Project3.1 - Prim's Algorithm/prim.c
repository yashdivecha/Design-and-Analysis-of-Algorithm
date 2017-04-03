/*
*	Implemented Prim Algorithm.
*	@author: Yash Divecha
* 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int size=0,queueSize=0;

struct MST
{
	int src, dest, weight;
};

struct Edge
{
	int cost;
	int prev;
	int index;
};

typedef enum { false, true } boolean;

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

/* This function free the space depending upon the size
 * @param - Size of the matrix
 * @return **matrix- allocated matrix
 */
void freeSpace(int **mat,int size)
{
	int i;
	for(i = 0; i < size; ++i) 
		free(mat[i]);
	free(mat);
}

/* This function displays the 2D array in matrix form.
 * @param  matrix - which needs to be displayed n - size of the matrix 
 * @return void 
 */
void displayMatrix(int **a, int n)
{
	int i,j;
	for(i=0;i<n;i++){
		for (j=0;j<n;j++)
			if(j==0)printf("| %5d ", a[i][j]);	
					else if(j==(n-1))printf("%5d |", a[i][j]);	
						else printf("%5d ", a[i][j]);
		printf("\n");		
		}
}

/* This functioon will display the edges which includes in MST
 * @param: MST and m is the size of structure 
 * @return : void 
 */
void displayMSTEdges(struct MST *mst , int m)
{
	int i;
	printf("\nMinimum Spaning Tree using Prim's algorithm includes the following edges.\n");
	for (i = 1; i < m; ++i)
		printf("Egde (%d,%d) = %d \n", mst[i].src+1, mst[i].dest+1, mst[i].weight);   
	
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


/* This function creates priority queue in sorted order.
 *  @param: Priority queue
 *  @return : void
 */
void priorityQueue(struct Edge queue[queueSize])
{
	int i,j;
	struct Edge temp;
	for(i=0;i<queueSize-1;i++){
		for(j=1;j<queueSize;j++){
			if(queue[i].cost > queue[j].cost)
			{
				temp = queue[i];
				queue[i] = queue[j];
				queue[j] = temp;
			}	
		}
	}
}

/* This function finds the vertex with minimun cost.
* @param: Priority Queue, queue size
* @return: structure of minimum wetex
*/ 
struct Edge deleteElement(struct Edge queue[], int n)
{
    struct Edge min = queue[0];    
	//Swap the indexed element with the last
    struct Edge temp = queue[0];
    queue[0] = queue[n - 1];
    queue[n - 1] = temp;  
    --n;
    return min;
}


/* This function implements Prims Algorithm
* @param:Adjacency input matrix
* @returns: void
*/
void primsAlgo(int **W)
{
	struct Edge edge[size];
	struct MST *mst=(struct MST*)malloc(sizeof(struct MST));
	int i,j,k;
	boolean visited[size];
	
	for (i = 0; i < size; ++i)
	{
		edge[i].cost=999;
		edge[i].prev=-1;
		visited[i]=false;
		edge[i].index=i;
	}
		edge[0].cost=0;
		edge[0].prev=0;
		
		int V=0, m=0;
		while(V<size)
		{
			int flag=0;
			for (j= 0; j < size; ++j)
			{
				if (visited[j]==true)
				{
					flag++;
				}
			}
			if (flag==size)
			{
				break;
			}
			queueSize=0;
			for (i = 0; i < size; ++i)
			{
				if (!visited[i])
				{							
					queueSize++;
				}
			}		
			struct Edge PQ[(queueSize)];
			int t=0;
			for (i = 0; i < size; ++i)
			{
				if (!visited[i])
				{					
					PQ[t++] = edge[i];					
				}
			}
			priorityQueue(PQ);					
			struct Edge minEdge=deleteElement(PQ,queueSize);
			int v=minEdge.index;
			mst[m].src=minEdge.prev;
			mst[m].dest=v;
			mst[m].weight=minEdge.cost;
			m++;
			visited[v]=true;
			for (k=0; k < size; ++k)
			{
				if(edge[k].cost > W[v][k])
				{
					edge[k].cost=W[v][k];
					edge[k].prev=v;
				}
			}

		}			
		displayMSTEdges(mst, m);
}


/*
 * This function is the start of the program. 
 * @param: argc - numbe of arguments and argv[] - command line arguments.
 * @return: 0 on success
 */

int main(int argc, char *argv[])
{ 
	if(argc != 2)
    {
        printf("Invalid number of argument \nUsage: ./prim.out <filename>\n");        
    }
    else {
			char *fileName = argv[1];
			int **W = fileRead(fileName);
			printf("\nWeighted Adjacency matrix w: \n");	
			displayMatrix(W,size);
			primsAlgo(W);
		}
	return 0;
}
