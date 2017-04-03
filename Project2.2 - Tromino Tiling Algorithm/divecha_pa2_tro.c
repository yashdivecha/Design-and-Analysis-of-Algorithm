/*
 * TROMINO TILING ALGORITHM.
 * @author Yash Diveha
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int counter=0;
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


void mat2x2(int **blocks,int n,int x,int y,int Lx,int Ly, int counter)
{
	
	if ( x == Lx )
		{
            if ( y == Ly )
            {
               blocks[x][y+1] = counter; 
				blocks[x+1][y] = counter; 
				blocks[x + 1][y + 1] = counter;	
			}
            else
            {
    
                blocks[x][y] = counter; 
				blocks[x + 1][y] = counter;	
				blocks[x + 1][y + 1] = counter; 
			}
		}
        else
        {
            if ( y== Ly )
            {
            
                blocks[x][y] = counter; 
				blocks[x][y + 1] = counter; 
				blocks[x + 1][y + 1] = counter;	
			}
            else
            {
            	
             	blocks[x][y] = counter; 
				blocks[x][y+1] = counter; 
				blocks[x+1][y] = counter; 
			}
		}
}


void tromino(int **blocks,int n,int x,int y,int Lx,int Ly)
{
	int half=n/2,i,j;

	int xcenter=x+half;
	int ycenter=y+half;

	counter++;
	int ulx = Lx, uly = Ly;
	int urx = half-1, ury = y+half;
	int llx = x+half, lly=half-1;
	int lrx = x+half, lry = y+half;

	if(n==2)
	{
		mat2x2(blocks,n,x,y,Lx,Ly, counter);
	}
	else
	{	
		
		if (Lx<xcenter)
		{
			llx = x+half, lly=half-1;
			lrx = x+half, lry = y+half;
			
			if (Ly<ycenter)
			{
				
				
				blocks[x + half-1][y + half] = counter; 
				blocks[x + half][y + half-1] = counter;
				blocks[x + half][y + half] = counter;	
				
				ulx = Lx, uly = Ly;
				urx = half-1, ury = y+half;		
			}
			else
			{
				
				blocks[x + half-1][y + half-1] = counter; 
				blocks[x + half][y + half-1] = counter;
				blocks[x + half][y + half] = counter; 
					
				ulx = half-1, uly = half-1;
				urx = Lx, ury = Ly;
				

			}
		}
		else
		{
			ulx = half-1, uly = half-1;
			urx = half-1, ury = y+half;
			if (Ly<ycenter)
			{
				
				blocks[x + half-1][y + half-1] = counter;
				blocks[x + half-1][y + half] = counter;
				blocks[x + half][y + half] = counter;	
				
				
				llx = Lx, lly=Ly;
				lrx = x+half, lry = y+half;

			}
			else
			{
				
				blocks[x + half-1][y + half-1] = counter; 
				blocks[x + half-1][y + half] = counter; 
				blocks[x + half][y + half-1] = counter; 
				
				
				llx = x+half, lly=half-1;
				lrx = Lx, lry = Ly;


			}	
		}


				tromino(blocks, half,x,y,ulx,uly); 
				tromino(blocks, half,x,y+half,urx,ury); 
				tromino(blocks, half,x+half,y,llx,lly);	
    			tromino(blocks, half,x+half,y+half,lrx,lry);

	} 

}


int main(int argc, char *argv[] )
{
  int n,i,j,x,y;
  if ( argc != 2 ) 
		printf("Enter Size of Board\n");
  else {

	n=atoi(argv[1]);
	if (n%2!=0)
	{
		printf("Improper size of Matrix (should be in 2^k)\n");
		exit(1);
	}
	else
	{
	srand(time(NULL));
	x=rand()% (n-1);
	y=rand()% (n-1);
	int **tile=allocateSpace(n);
	
	
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; j++)
			tile[i][j]=-1;
	//initializeBoard(tile, n);
	tile[x-1][y-1]=0;
	
	tromino(tile,n,0,0,x-1,y-1);

	displayMatrix(tile,n);

	}	
	}

	return 0;
}