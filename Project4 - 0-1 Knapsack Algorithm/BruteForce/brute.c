/**********************************************************************
 *	@title : Implemeenting 0/1 Knapsack using Brute Force Method.
 *	@author: Yash Divecha
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 int n=0;					// Number of items.
 int capacity=0;			// Knapsack capacity
 int finalKS[100];
 
/***************************************************************************************
 *	@function : Power (x raise to n)
 *	@param : x
 * 	@param : n (raise to n)
 *	@return: int (computes the x raise to n and return the value)
 ***************************************************************************************/ 
 int myPower(int x, int n)
 {
 	int result = 1;
 	int i;
 	for(i=0;i<n;++i)
 		result *= x;
 	return result;
 }

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
 *	@function : Outputs the files having max weight, max profit, items to include. 
 *	@param : fileName - Name of the output file 
 *	@param : w - max weight
 * 	@param : p - max profit 
 *	@param : finalKS - Items taken marked as 1, rest 0
 *	@return: void
 ***************************************************************************************/
void outputFile(char * fileName, int w, int p, int *finalKS)
{
	int k, fst1 = 0;
	printf("%s\n", "File brute_output.txt has been created with the required output");


	printf("Maximum Weight: %d\n", w);
	printf("Maximum Profit: %d\n", p);
	printf("Items included: ");
	for (k = 0; k < n; k++) 
	{
        if (finalKS[k] == 1 && fst1 == 0) 
        {
            printf("%d",k);
            fst1 = 1;
        }else if(finalKS[k] == 1 ){
        	printf(", %d",k);
        }
	}
	printf("\n");
	
	int fst=0;
	FILE *out_file = fopen(fileName, "w");
	fprintf(out_file, "%d\n", w);
	fprintf(out_file, "%d\n", p);
	for (k = 0; k < n; k++) {
            if (finalKS[k] == 1 && fst == 0) 
            {
                fprintf(out_file, "%d",k);
                fst = 1;
            }else if(finalKS[k] == 1 ){
            	fprintf(out_file, ", %d",k);
            }
        }       
     fclose(out_file);     
}


/***************************************************************************************
 *	@function : Implements brute force method for 0/1 Knapsack. 
 *	@param : w - weights of the n items 
 *	@param : p - profits of the n items.
 *	@return: void
 ***************************************************************************************/
void bruteForce(int *w, int *p)
{	
	int i,maxWeight=0,maxProfit=0,k;
    int bruteKS[n];
    finalKS[n];
	for (i = 0; i < n; ++i)
	{
		bruteKS[i]=0;
	}
    for (i = 0;i<myPower(2,(n+1)); i++) 
    {
        int j = n;
        int tempWeight = 0;
        int tempProfit = 0;
	
		j = 0;
		while(bruteKS[j] != 0 && j<n)
		{
			bruteKS[j] = 0;
			j++;			
		}
		bruteKS[j] = 1;
	
        for (k = 0; k < n; k++) 
        {
            if (bruteKS[k] == 1) 
            {
                tempWeight = tempWeight + w[k];
                tempProfit = tempProfit + p[k];
            }
        }

        if (tempProfit > maxProfit && tempWeight <= capacity) 
        {
            maxWeight = tempWeight;
            maxProfit = tempProfit;            
            for (k = 0; k < n; k++) 
        	 	finalKS[k]=bruteKS[k];	        
        }
    }

   outputFile("brute_output.txt", maxWeight, maxProfit, finalKS);
   
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
	    printf("Invalid number of argument \nUsage: ./brute.out <filename>\n");
	    exit(0);
	}

	char *fileName = argv[1];

	//This is used to get the number of items. 
	fileRead(fileName);

	//Create weight and profit array depepeding upon the number of items.
	int *w = malloc(n* sizeof(int));
	int *p = malloc(n* sizeof(int));

	//From the given file, get the weights, profits and knapsack capacity.
	getWPC(fileName,w,p);


	bruteForce(w,p);

	return 0;
}