/*****************************************************************************************
 *	@title : Implemeenting 0/1 Knapsack using Backtracking Method.
 *	@author: Yash Divecha
 ****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n=0;					// Number of items.
int capacity=0;				// Knapsack capacity
int maxWeight=0;			// Maximum weight of 0/1 knapsack
int maxProfit=0;			// Maximum profit of 0/1 knapsack
int cnt=0;					
//int *include=(int*)malloc(sizeof(int));
int include[50];
int bestSet[50];
int solution[50][2];
typedef enum { false, true } bool;

/***************************************************************************************
 *	@function : Reads the input file and captures n (number of items in knapsack)
 *	@param : fileName - Name of the input file 
 *	@return: void
 ***************************************************************************************/
void fileRead(char *fileName)
{
   	
	FILE *fp;
   	size_t buff =0 ;
	char *line = NULL;
 	//fp = fopen("knapsack.txt", "r");
 	fp = fopen(fileName, "r");

 	// Check if File exist ? 
	if(!fp) {
		printf("File does not exist. \n"); 
		exit(0);
	}

	// Gets the number of items. 
	getline(&line, &buff, fp);
	n = atoi(line);
	
	// Close the file.
	fclose(fp);
	
}

/***************************************************************************************
 *	@function : Creates weight and profit arrays and get the knapsack capacity.
 *	@param : fileName - Name of the input file 
 *	@param: w - weight array
 * 	@param: p - profit array
 *	@return: void
 ***************************************************************************************/
void getWPC(char *fileName, int *w, int *p)
{
   	
	FILE *fp;
   	size_t buff =0 ;
	char *token;
	char *line = NULL;
 	//fp = fopen("knapsack.txt", "r");
 	fp = fopen(fileName, "r");

	// Check if File exist ? 
	if(!fp) {
		printf("File does not exist. \n"); 
		exit(0);
	}

	//Gets the number of items. 
	getline(&line, &buff, fp);
	n = atoi(line);
	
	//Weights of n items
	int j=0;
	getline(&line, &buff, fp);	
	token = strtok(line,",");
	while(token!=NULL)
	{
		w[j]=atoi(token);
		j++;
		token = strtok(NULL, ",\n");
	}	

	//Profits of n items.
	j=0;
	getline(&line, &buff, fp);	
	token = strtok(line,",");
	while(token!=NULL)
	{
		p[j]=atoi(token);
		j++;
		token = strtok(NULL, ",\n");
	}

	//Capacity of the Knapsack.
	getline(&line, &buff, fp);	
	capacity = atoi(line);
	
	//Close the file
	fclose(fp);
}


/***************************************************************************************
 *	@function : Sorts the arrays depending upon the  profit/weight.
 *	@param: w - weights of n items 
 * 	@param: p - profits of n items
 *	@return: void
 ***************************************************************************************/
void sortProfitWeight(int *w, int *p)
{
	int i,j;
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < i; ++j)
		{
			//if ((p[j]/w[j])<(p[j+1]/w[j+1]))
			if (p[j]<p[j+1])
			{
				int tempProfit=p[j];
				p[j]=p[j+1];
				p[j+1]=tempProfit;

				int tempWeight=w[j];
				w[j]=w[j+1];
				w[j+1]=tempWeight;
				
				int temp = solution[j][1];
				solution[j][1] = solution[j+1][1];
				solution[j+1][1] = temp;
			}
		}
	}
}

/***************************************************************************************
 *	@function : Finds the bound. 
 *	@param: w - weights of n items 
 * 	@param: p - profits of n items
 *	@param: i - Counter (Initially 0)
 *	@param: profit - Profit of 1st item 
 *	@param: weight - Weight of 1st item
 *	@return: double - bound 
 ***************************************************************************************/
double KWF2(int *w,int *p,int i,int weight, int profit)
{
	int x[n];
	int j;
	double bound = profit;
	for(j=i;j<n;j++)
   	x[j] = 0; 			//Initialize variables to 0 
	while (weight < capacity && i <= n)		//not "full" and more items
	{        
	    if(weight + w[i] <= capacity)    	// room for next item        
	    {
	         x[i]=1;                   		// item i is added to knapsack
	         weight = weight + w[i]; 
	         bound = bound +p[i];
	    }
	   	else
	   	{
	        x[i]=(capacity - weight)/w[i];	// fraction of i added to knapsack	     
	        bound = bound + p[i]*x[i];
	    }
   	i= i+1;			//next item
   	}                            
	return bound;
}

/***************************************************************************************
 *	@function : Checks if the function is promising or not
 *	@param: w - weights of n items 
 * 	@param: p - profits of n items
 *	@param: i - Counter (Initially 0)
 *	@param: profit - Profit of 1st item 
 *	@param: weight - Weight of 1st item
 *	@return: bool - true if promising and false if not promising
 ***************************************************************************************/
bool promising(int *w,int *p,int i,int profit, int weight)
{
	int j,k;
	int totalWeight;
	double bound;
	if(weight>=capacity)
	{
		return false;
	}else{
			
			bound = KWF2(w,p,i+1,weight, profit); 
			return (bound>maxProfit);
		}
}

/***************************************************************************************
 *	@function : Implementation of 0/1 Knapsack Backtracking method. 
 *	@param: w - weights of n items 
 * 	@param: p - profits of n items
 *	@param: i - Counter (Initially 0)
 *	@param: profit - Profit of 1st item 
 *	@param: weight - Weight of 1st item
 *	@return: void
 ***************************************************************************************/
void backTracking(int *w, int *p, int i, int profit, int weight)
{

	if(weight<=capacity && profit>maxProfit)
	{
		int i;
		maxWeight=weight;
		maxProfit=profit;
		for(i=0;i<50;i++)			
			{	
				bestSet[i] = include[i];
				//printf("%d",include[i] );
			}
	}
	bool isPromising=promising(w,p,i,profit,weight);	
	
	if(isPromising)
	{
		include[cnt++] = 1;
		backTracking(w,p,i+1,profit+p[i+1],weight+w[i+1]); 
		include[cnt++] = 0;
		backTracking(w,p,i+1,profit,weight);
	}
}

/***************************************************************************************
 *	@function : Outputs the files having max weight, max profit, items to include. 
 *	@param : fileName - Name of the output file 
 *	@param : w - max weight
 * 	@param : p - max profit 
 *	@param : bestSet (which item to include [1])
 *  @param : weight of n items
 *  @param : weight Temp of n items to get the index.
 * 	@param : Solution - to get the which items 
 *	@return: void
 ***************************************************************************************/
void outputFile(char *fileName,int maxWeight, int maxProfit, int *bestSet, int *w, int *wTemp, int solution[][2])
{
	
	printf("%s\n", "File backtrack_output.txt has been created with the required output");
	FILE *out_file = fopen(fileName, "w");	
	fprintf(out_file, "%d\n", maxWeight);
	fprintf(out_file, "%d\n", maxProfit);
	
	int i, j;
	int *tempArray = (int *)malloc(n* sizeof(int));
	for( i=0;i< n;i++ )
		tempArray[i] = 999;

	
	
	for(i=0;i<50; i++){
		if(bestSet[i] == 1)
			tempArray[i] = solution[i][1];
	}
	
	
	/*for( i=0;i<50; i++){
		if(bestSet[i] == 1)
			for( j=0;j<n;j++)				
				if(w[i] == wTemp[j])
					tempArray[i] = j;
					//printf("%d ", j);
	}
	*/
	for (i = 0; i < n; ++i){
		for (j = 0; j < i; ++j){			
			if (tempArray[j]>tempArray[j+1])
			{
				int temp=tempArray[j];
				tempArray[j]=tempArray[j+1];
				tempArray[j+1]=temp;
			}
		}
	}

	for(i=0;i<n;i++){
		if(tempArray[i] == 999) break;
		if(tempArray[i+1] == 999)
			fprintf(out_file,"%d", tempArray[i]);
		else fprintf(out_file,"%d, ", tempArray[i]);
	}
	fclose(out_file);   
	
}

/***************************************************************************************
 *	@function : Start of the program
 *	@param : argc - Number of arguements. 
 *	@param : argv - argument array
 *	@return: int - returns 0 on successfuly completion.
 ***************************************************************************************/
int main(int argc, char *argv[])
{
 	
 	if(argc != 2)
    {
        printf("Invalid number of argument \nUsage: ./backtrack.out <filename>\n");
        exit(0);
    }

	char *fileName = argv[1];

	//This is used to get the number of items. 
	fileRead(fileName);

	//Create weight and profit array depepeding upon the number of items.
	int *w = malloc(n* sizeof(int));
	int *p = malloc(n* sizeof(int));
	int i,j;

	for(i=0;i<50;i++)
	{
		include[i] = -1;
		bestSet[i] = -1;
	}
	
	//From the given file, get the weights, profits and knapsack capacity.
	getWPC(fileName,w,p);

	/*	 Printing weights and profits of n items
	for(int i=0;i<n;i++)
		printf("%d ", w[i]);
	printf("\n");

	for(int i=0;i<n;i++)
		printf("%d ", p[i]);
	printf("\n");
	*/

	//Weight Temp to get the index of which item to include.
	int *wTemp = malloc(n* sizeof(int));
	for(i=0;i<n;i++)
		wTemp[i] = w[i];

	for(i=0;i<50;i++){
		for(j=0;j<2;j++){
				solution[i][0] = i;
				solution[i][1] = i;
		}
	}
	
	//Step 1: Sort in non-ascending order
	sortProfitWeight(w,p);


	
	//Step 2: Call the Knapsack Back Tracking method. 
	backTracking(w,p,-1,0,0);

	//Step 3: Output into a file.
	outputFile("backtrack_output.txt", maxWeight, maxProfit, bestSet, w, wTemp, solution);


	// Uncomment this to see the output on the screen
	
	printf("Maximum Weight: %d\n", maxWeight);
	printf("Maximum Profit: %d\n", maxProfit);

	/*
	for(i=0;i< n;i++ ){
		for(j=0;j<2;j++){
			printf("%d ", solution[i][j]);
		}
	printf("\n");
	}
	*/
	
	int *tempArray = (int *)malloc(n* sizeof(int));
	for(i=0;i< n;i++ )
		tempArray[i] = 999;

	for(i=0;i<50; i++){
		if(bestSet[i] == 1)
			tempArray[i] = solution[i][1];
	}
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < i; ++j)
		{
			
			if (tempArray[j]>tempArray[j+1])
			{
				int temp=tempArray[j];
				tempArray[j]=tempArray[j+1];
				tempArray[j+1]=temp;
			}
		}
	}

	printf("Items included: ");
	for( i=0;i<n;i++)
	{
		if(tempArray[i] == 999) break;
		if(tempArray[i+1] == 999)
			printf("%d", tempArray[i]);
		else printf("%d, ", tempArray[i]);
	}
	printf("\n");
	

 	return 0;
}