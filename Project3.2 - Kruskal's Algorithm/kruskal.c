/*
*	Implementation of Kruskal Algorithm.
*	@author: Yash Divecha
* 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int size=0;
int e=0;		

//struct : To represent an edge having source, destination and weight.
struct Edge
{
	int src, dest, weight;
};

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

void displayMSTEdges(struct Edge *final, int e)
{
	//print the contents of final[] to display the built MST
    int i;
	printf("\nMinimum Spaning Tree using Kruskal's algorithm includes the following edges.\n");
    for (i = 0; i < e; ++i)
    	printf("Egde (%d,%d) = %d \n", final[i].src+1, final[i].dest+1, final[i].weight);   
	
}

/* Randomized Quick Sort */

/* This function swaps the two edges
 * @param: edge a and edge b 
 * @return: void
 */
void swap(struct Edge *a,struct Edge *b)
{
	struct Edge temp = *a;
	*a = *b;
	*b = temp;
}

/* This function is used to partition the graphs depending upong the weights.
 * @param: edge edge, start index and end index
 * @return: int
 */
int partition(struct Edge *edge,int start,int end)
{
	srand(time(NULL));
	int pivot = rand()%(end-start);
	pivot = pivot + start;

	swap(&edge[end],&edge[pivot]);
	pivot = end;
	int temp = edge[end].weight;
	int i = start-1;
	int j;
	for(j = start; j < end ;j++) {
	    if(edge[j].weight < temp) {
	        i++;
	        swap (&edge[i],&edge[j]);	   
	    }
	}
	i++;
  	swap (&edge[end],&edge[i]);
	return i;
}

/* This function is used to sort the number of edges depending upong the weight.
* @param: edge edge, start p and end r
* @return: void
*/
 void randomQuickSort(struct Edge *edge,int low,int high)
{
 if(low < high)
  {
    int q = partition(edge,low,high);  
    randomQuickSort(edge,low,q);    
    randomQuickSort(edge,q+1,high);
    
  }
}

/* A function to find3 root of an element i
* @param: set matrix, element i
* @return: int root
*/
int find3(int set[][2], int x)
{
	//find root of the tree with x
	int root=x;
	while (root != set[root][0])
		root=set[root][0];

	//compress path from x to root
	int node=x;
	while (node != root)
	{
		int parent=set[node][0];
		set[node][0]=root; // node points to root
		node=parent;
	}
	return root;
}


/*A function computes union of two sets of x and y
* Arguments: set matrix, sets x & y
* Returns: void
*/
void union3(int set[][2], int x, int y)
{
    int repx = find3(set, x);
    int repy = find3(set, y);
	//set[repx][1] = height (2nd column represents height)
    if (set[repx][1] == set[repy][1])
    {
    	set[repy][0]= repx;
        set[repx][1]++;			
    }
    else if (set[repx][1] > set[repy][1])
        set[repy][0] = repx;
    else
    {
        set[repx][0] = repy;
    }
}

/* Implementation of Kruskal Algorithm
*  @param: input graph matrix and size
*  @return: void
*/
 void kruskalAlgo(int **W,int V)
 {
 	int index=0,v;
 	struct Edge final[V];
	
	// Creates a Graph with respect to edges. 
	struct Edge *edge=(struct Edge*)malloc(sizeof(struct Edge));
	int i,j;
	for (i = 0; i<(size); i++){
		for (j=0; j < i; j++){			
			if(W[i][j]!=0 && W[i][j]!=999){
				edge[e].src=i;
				edge[e].dest=j;
				edge[e].weight=W[i][j];
				e++;
			}
		}
	}
 	//Sorted the egdes in non descentding order using Randomised Quick Sort.
	randomQuickSort(edge,0,e);

 	int set[V][2];    //Create V set with single elements
    for (v = 0; v < V; ++v)
    {
        set[v][0] = v;
        set[v][1] = 0;
    }

    e=0;  
   	while (e < V-1)
    {
        // Pick the smallest edge. And increment the index for next iteration.
        struct Edge nextEdge = edge[index++];
		
        int ucomp = find3(set,nextEdge.src);
        int vcomp = find3(set,nextEdge.dest);
		
        // With this edge no cycle, then include it in final.
		// Increment the index of final for next edge.
        if (ucomp != vcomp)
        {
            final[e++] = nextEdge;
            union3(set, ucomp, vcomp);
        }
        // Else discard the next edge
    }
    displayMSTEdges(final,e);
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
        printf("Invalid number of argument \nUsage: ./kruskal.out <filename>\n");       
    }
	else {
			char *fileName = argv[1];
			int **W = fileRead(fileName);
			printf("\nWeighted Adjacency matrix W: \n");	
			displayMatrix(W,size);
			kruskalAlgo(W,size);
		}
	return 0;
}