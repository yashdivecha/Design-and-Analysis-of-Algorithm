#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int readingNumberOfElements();
void display(int [], int);
void printStars(int [], int);

void insertionSort();
void countingSort();

void mergeSortMain();
void mergeSort(int [],int,int ,int );
void merge(int [],int, int,int,int,int);

void randomQuickSortMain();
void randomQuickSort(int [],int,int,int);
int partition(int [],int,int);
void swap(int *,int *);


int main(){
	int n,sortTypeNo;
	do{	
	printf("Select the type of Sorting method you want to use.\n");
	printf("1: Insertion Sort. \n2: Counting Sort. \n3: Merge Sort. \n4: Randomized Quick Sort.\n5: Exit.\n");
	scanf("%d", &sortTypeNo);
	switch(sortTypeNo){
		case(1):{
					printf("You have selected Insertion Sort.\n");
					insertionSort();		
					break;
			 	}
		case(2):{
					printf("You have selected Counting Sort.\n");
					countingSort();
					break;
				}
		case(3):{ 
					printf("You have selected Merge Sort.\n");
					mergeSortMain();
					break;
				}
		case(4):{ 
					printf("You have selected Randomized Quick Sort.\n");
					randomQuickSortMain();
					break;
				}
		case(5):{
					printf("Exiting the program.\n");
					exit(0);
				}
		default: printf("Please select a valid sort method.\n\n");
		}
	}while(sortTypeNo != 5);

	return 0;
}

/* Taking input n from the user */
int readingNumberOfElements(){
	int n;	
	printf("Enter the number of elements: ");
	scanf("%d",&n);
	return n;
}
/* Display an Array */
void display(int a[], int n){
	for(int i=0;i<n;i++)
    	printf("%d ",a[i]);
	printf("\n\n");
}
/* Printing Stars */
void printStars(int a[], int n){
	if(n<=20){
		printf("Printing Stars: \n"); display(a,n);
		for (int i = 0; i < n; i++){
			for (int j = 0; j < a[i]; j++){
				printf("*");
			}
			printf("\n");	
		}
	}
}


/* Insertion Sort */
void insertionSort(){
	int n =  readingNumberOfElements();
	if(n<1 || n > 1000){
  	    printf("Please enter number of elements between 1 and 1000. \n\n"); 	    
	}
	else{
		int a[n];	
		int i,j,temp;
		srand(time(NULL));

		for(i=0;i<n;i++){
		    if(n<=20)
		    	a[i] = rand()%16;			
		    else a[i] = rand();
		}		
		 
		printStars(a,n);
		printf("----------Before Sorting---------- \n"); 
		display(a,n);	
		
		//Insertion Sort Implementation   
		 for(i=1;i<n;i++){
		 	for(j=i;j>0;j--){ 			
		 		if(a[j] < a[j-1]){		//checks if the previous number is greater
		 			temp = a[j];
		 			a[j] = a[j-1];
		 			a[j-1] = temp;
		 			printStars(a,n);
		 		}
		 	}
		 }  

		printf("\n----------After Sorting---------- \n"); 
		display(a,n);		
	}
}


/* Counting Sort */
void countingSort(){
	int n = readingNumberOfElements();
	if(n<1 || n > 1000){
  	    printf("Please enter number of elements between 1 and 1000. \n\n");	    
	}
	else{
		int a[n];	
		int j, i,q;
		srand(time(NULL));

		for(i=0;i<n;i++){
		    if(n<=20)
				a[i] = rand()%16; 			
		   else a[i] = rand()%100; 
		}		
		printStars(a, n);
		printf("----------Before Sorting---------- \n"); display(a,n);	

		//Counting Sort Implementation. 
		int c[100], t[n];
		for (i = 0; i <= 99; i++)		//Initializing count arrary to 0
			c[i] = 0;
			
		for(i=0;i<n;i++)				//Filling the counting array with count of values. 
			c[a[i]] = c[a[i]]+1;
		q=0;
		for(j=0;j<=99;j++){
			while(c[j] > 0){
				a[q] = j;				//Generating final array depending on the count array.
				c[j] = c[j]-1;
				q=q+1;			
			printStars(a, n);
			}

		}
		printf("----------After Sorting---------- \n"); display(a,n);		
	}		
}


/* Merge Sort */
void mergeSortMain(){
	int n = readingNumberOfElements();
	if(n<1 || n > 1000){
  	    printf("Please enter number of elements between 1 and 1000. \n\n");	    
	}
	else{
		int a[n];	
		int i,j,q;
		srand(time(NULL));

		for(i=0;i<n;i++){
		    if(n<=20)
				a[i] = rand()%16; 			
		   else a[i] = rand(); 
		}		
		printStars(a, n);
		printf("----------Before Sorting---------- \n"); display(a,n);	
		mergeSort(a,n,0,n-1);
		printf("----------After Sorting---------- \n"); display(a,n);
	}
}
void mergeSort(int a[],int n,int lowIndex,int highIndex){
    int midIndex;
    if(lowIndex<highIndex){
        midIndex=(lowIndex+highIndex)/2;
        mergeSort(a,n,lowIndex,midIndex);                  //dividing left subarray - left recursion
        //printf("After 1st: \n");printStars(a,midIndex);
        mergeSort(a,n,midIndex+1,highIndex);               //divding right subarray - right recursion
        //printf("After 2nd: \n");printStars(a,highIndex);
        merge(a,n,lowIndex,midIndex,midIndex+1,highIndex); //merging/combining of two sorted sub-arrays
        printStars(a,n);
    }
}
void merge(int a[],int n, int s1,int e1,int s2,int e2){
    int temp[n];                    //array used for merging
    int i,j,k=0;
    i=s1;                           //start of the 1st list
    j=s2;                           //start of the 2nd list
        
    while(i<=e1 && j<=e2){          //till we have elements in both the lists
        if(a[i]<a[j])
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];
    }
    
    while(i<=e1)               //copy left over elements of the 1st list to temp
        temp[k++]=a[i++];
	
    while(j<=e2)               //copy left over elements of the 2nd list to temp
        temp[k++]=a[j++];
	
    for(i=s1,j=0;i<=e2;i++,j++) //finally transfer elements to original array a[] from temp[].
        a[i]=temp[j];
}


/* Randomized Quick Sort */
void randomQuickSortMain(){
	int n = readingNumberOfElements();
	if(n<1 || n > 1000){
  	    printf("Please enter number of elements between 1 and 1000. \n\n");	    
	}
	else{
		int a[n];	
		int i,j,q;
		srand(time(NULL));

		for(i=0;i<n;i++){
		    if(n<=20)
				a[i] = rand()%16; 			
		   else a[i] = rand(); 
		}		
		printStars(a, n);
		printf("----------Before Sorting---------- \n"); display(a,n);	
		randomQuickSort(a,n,0,n-1);
		printf("----------After Sorting---------- \n"); display(a,n);
	}
}
void randomQuickSort(int a[],int n,int p,int r){
 if(p < r)
  {
    int q = partition(a,p,r);
    printStars(a,n);
    randomQuickSort(a,n,p,q);    
    randomQuickSort(a,n,q+1,r);
    
  }
}
int partition(int a[],int start,int end){
	srand(time(NULL));
	int pivot = rand()%(end-start);
	pivot = pivot + start;
	swap(&a[end],&a[pivot]);
	pivot = end;
	int temp = a[end];
	int i = start-1;
	for(int j = start; j < end ;j++) {
	    if(a[j] < temp) {
	        i++;
	        swap (&a[i],&a[j]);	   
	    }
	}
	i++;
  	swap (&a[end],&a[i]);
	return i;
}
void swap(int *a,int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}