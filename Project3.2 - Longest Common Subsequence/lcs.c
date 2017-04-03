/*
 *	Longest Common Subsequence (LCS) of two strings.
 *	@author: Yash Divecha
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 

int c[1000][1000];      
int lengthLCS;          // Length of Common Longest Common Subsequence
char b[1000][1000];     // Direction Matrix

/* This function print LCS: when it encounters a diagonal it prints the element, else recursive calls.  
 * @param  char String X - to print the actual character incase of diagonal, 
 		   i = length of X [0...m-1] and j=length of Y [0..n-1].
 * @return void 
 */
void displayLCS(char *X, int i,int j)
{	
    if(i==0 || j==0)
        return;
    if(b[i][j]=='D')
    {	
    	lengthLCS++;
        displayLCS(X,i-1,j-1); 
        printf("%c",X[i-1]); //If it's diagonal then print 
    }
    else if(b[i][j]=='U')
		    displayLCS(X,i-1,j); // Recursive call to upper row in the same column
	else
        	displayLCS(X,i,j-1); // Recursive call to the left column in the same row.     
}

/* This function displays the Length matrix. 
 * @param  int a[][] - matrix that needs to be printed. 
   m = length of X [0...m-1] and n=length of Y [0..n-1].
 * @return void 
 */

void displayInt(int a[][1000], int m, int n)
{
	int i,j;
	for(i=0;i<m;i++){
		for (j=0;j<n;j++)
			if(j==0)printf("| %5d ", a[i][j]);	
					else if(j==(n-1))printf("%5d |", a[i][j]);	
						else printf("%5d ", a[i][j]);
		printf("\n");		
		}
}


/* This function displays the Path (D,U,L) matrix, depening upon this we can pop out elements for which we hit diagonal. 
 * @param  char a[][] - matrix that needs to be printed. 
   m = length of X [0...m-1] and n=length of Y [0..n-1].
 * @return void 
 */

void displayChar(char a[][1000], int m, int n)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		for (j=0;j<n;j++)
			if(j==0)printf("| %5c ", a[i][j]);	
					else if(j==(n-1))printf("%5c |", a[i][j]);	
						else printf("%5c ", a[i][j]);
		printf("\n");		
	}
} 

void intialize(int c[][1000], int m, int n)
{
	int i,j;
    for(i=0;i<=m;i++)
        c[i][0]=0;
    for(i=0;i<=n;i++)
        c[0][i]=0;    
}

/* This function computes the LCS of 2 string X and Y by updating the 2 matrixes Length c[][] and path b[][]. 
 * @param  char a[][] - matrix that needs to be printed. 
   m = length of X [0...m-1] and n=length of Y [0..n-1].
 * @return void 
 */

void lcs(char *X, char *Y, int m, int n)
{
    int i,j; 
	intialize(c,m,n);
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
        {
            if(X[i-1]==Y[j-1])
            {
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]='D';
            }
            else
            {	
            	if(c[i-1][j]>=c[i][j-1])
            	{
	                c[i][j]=c[i-1][j];
	                b[i][j]='U';
	        	}
	            else
	            {
		            c[i][j]=c[i][j-1];
	    	        b[i][j]='L';
	            }
	        }
        }

       // displayInt(c,m,n);
       // printf("\n");
       // displayChar(b,m,n);
       // printf("\n");
}

/* This function computes the LCS of 2 string X and Y by updating the 2 matrixes Length c[][] and path b[][]. 
 * @param  char a[][] - matrix that needs to be printed. 
   m = length of X [0...m-1] and n=length of Y [0..n-1].
 * @return void 
 */

int main(int argc, char *argv[])
{
	if(argc != 2)
    {
        printf("Invalid number of argument \nUsage: ./lcs.out <filename>\n");       
    }
	else{
			char *X,*Y;
			X =(char *) malloc(sizeof (char));
			Y=(char *) malloc(sizeof (char));
			
			int m,n;
			FILE *fp;
			size_t buff =0 ;
			fp = fopen(argv[1], "r");

			if(!fp) {
				printf("File does not exist. \n"); 
				exit(0);
			}

			getline(&X, &buff, fp);
			getline(&Y, &buff, fp);
			printf("X = %s", X);
			printf("Y = %s", Y);
			
			m=strlen(X);
			n=strlen(Y);

			lcs(X,Y,m,n);   

			//printf("\nThe LCS of X and Y is ");
			printf("\n");
			displayLCS(X,m,n);   
			//printf(" and length is %d", length); 
			printf("  %d \n", lengthLCS);
		}

    return 0;
}