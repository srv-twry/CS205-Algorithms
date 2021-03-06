/*

	Name- Saurav Roll-1601CS41
	The aim of this program is to analyze the performance of the quicksort algorithm using various partitioning techniques.
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define MAX 1000000000

//global variables
int n,power,i;
long *array;
clock_t c1,c2;
double value;

//utility to print the array
void printArray(){
	for(i=0;i<n;i++){
		printf("%ld ",array[i]);
	}
	printf("\n");
}

//function to populate array with random values
void populateValues(){

	for(i=0;i<n;i++){
		array[i] = rand() % (MAX);
	}
	
}

//function to return the median of three numbers.
int median(int r, int s, int t){
	int arr[3];
	arr[0]=r;
	arr[1]=s;
	arr[2]=t;
	
	int j,k;
	
	//sorting
	for(j=0;j<3;j++){
		for(k=j+1;k<3;k++){
			if(arr[j]>arr[k]){
				int temp = arr[k];
				arr[k]=arr[j];
				arr[j] = temp;
			}
		}
	}

	return arr[1];
}

//function to swap two elements of the array.
void swap(long* a, long* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Function to partition the array around a pivot.
int partition(int start,int end,int pivotType){
	int pivot,random;
	int r,s,t;
	
	//determining the value of the pivot according to pivotType
	switch(pivotType){
		case 0:
			pivot = array[start];
			random = start;
			break;
		
		case 1:
			random= start + rand() % (end - start + 1);
			pivot = array[random];
			break;
		
		case 2:
			r = start;
		 	s = start + (end-start+1)/2;
			t = end;
			
			pivot = median(array[r],array[s],array[t]);
			if (pivot == array[r])
			{
				random = r;
			}else if (pivot == array[s])
			{
				random = s;
			}else{
				random = t;
			}
			break;
		
		case 3:
			r = start+ (end-start+1)/4;
		 	s = start + (end-start+1)/2;
			t = start + 3*(end-start+1)/4;
			
			pivot = median(array[r],array[s],array[t]);
			if (pivot == array[r])
			{
				random = r;
			}else if (pivot == array[s])
			{
				random = s;
			}else{
				random = t;
			}
			break;
	}
		
	swap(array+random,array+end);
	
	//finding the right position of pivot.
	int k = start-1,j;
	for(j=start;j< end;j++){
		if(array[j] <= pivot){
			k++;
			swap(array+k,array+j);
		}
	}
	swap(array+k+1,array+end);
	return k+1;
}

//function to sort the array using quicksort
void quickSort(int start , int end, int pivotType){

	if(start < end){
		int partitionIndex = partition(start,end,pivotType);
		
		//recursive calls
		quickSort(start,partitionIndex-1,pivotType);
		quickSort(partitionIndex+1,end,pivotType);
	}
	
}

//function to swap few elements of the sorted array.
void swapFewElements(){
	
	int p,q,j;
	for(j=0;j<100;j++){
		p = rand() %n;
		q = rand() %n;
	
		swap(array+p,array+q);
	}
	
}


//main function
int main(){

	srand((unsigned int)time(NULL));
	
	
	//formatting for the output
	power=4;
	n = 1000;
	printf("--------------------------Performance of Quick-Sort-------------------------\n");
	printf("----------------------------------------------------------------------------\n\n");
	printf("N\t   Pivot-type\t\tRandom\tSorted\tAlmost-sorted\n");

	//running for each value of k
	while(power<=7){
	
		//allocating space for the array.
		n*=10;
		array = (long*)malloc(n*sizeof(long));
	
		//run quicksort for each pivotType
		int z;
		for(z=0;z<4;z++){
			
			//populating with random values
			populateValues();
			
			//applying it on the random array.
			c1 = clock();
			quickSort(0,n-1,z);
			c2 = clock();
			value = (double)(c2-c1)/(double)CLOCKS_PER_SEC;
			
			//formatting
			if(z==0){
				printf("%d\t     FIRST\t\t%.3f\t",n,value);
			}else if(z==1){
				printf("%d\t     RANDOM\t\t%.3f\t",n,value);
			}else if(z==2){
				printf("%d\tMEDIAN OF THREE 1\t%.3f\t",n,value);
			}else{
				printf("%d\tMEDIAN OF THREE 2\t%.3f\t",n,value);
			}
			//applying it on the already sorted array.
			if (power<=5)
			{
				c1 = clock();
				quickSort(0,n-1,z);
				c2 = clock();
				value = (double)(c2-c1)/(double)CLOCKS_PER_SEC;
				
				printf(" %.3f\t",value);
			}else if(z!=0){
				c1 = clock();
				quickSort(0,n-1,z);
				c2 = clock();
				value = (double)(c2-c1)/(double)CLOCKS_PER_SEC;
				
				printf(" %.3f\t",value);
			}else{
				printf(" TOO SLOW\t");
			}
			
			
			swapFewElements();
			
			//applying it on the almost sorted array.
			c1 = clock();
			quickSort(0,n-1,z);
			c2 = clock();
			value = (double)(c2-c1)/(double)CLOCKS_PER_SEC;
			
			printf(" %.3f\n",value);


		}
		//free the memory used.
		free(array);
		
		power++;
		printf("\n");
	}
	
	
	return 0;
}
