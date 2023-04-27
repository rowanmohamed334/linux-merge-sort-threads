#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//global variable 
int i = 0;

//SIZE of the array
int R;
int buff[255];
int A[255];

//structure for array elements
struct Sub{
	int low;
	int high;
};

void *mergeSort(void *args);

//function to read input from file
int *read_input(){
	FILE *fp;
	fp = fopen("input-sort.txt", "r");
	while(fscanf(fp, "%d", &buff[i])!=EOF){
		i++;
		R = buff[0];
	}
	fclose(fp);	
	return buff;
}


void array_formation(int *array){
	//initilization of the array
	A[R];
	i = 1;
	for(int j=0; j<R; j++){
		A[j] = array[i];
		i++;
	}		
}

// Merges two subarrays of arr[].
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// create temp arrays
	int L[n1], R[n2];

	// Copy data to temp arrays L[] and R[]
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	// Merge the temp arrays back into arr[l..r]
	i = 0; 
	j = 0; 
	k = l; 
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}


	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}


void *mergeSort(void *args)
{
	struct Sub *a = args;
	int l = a->low;
	int r = a->high;
	if (l < r) {
		
		int m = l + (r - l) / 2;
		
		// Sort first and second halves
		struct Sub *no1 = (struct Sub*) malloc(sizeof(struct Sub));
		no1->low = l;
		no1->high = m;
		struct Sub *no2 = (struct Sub*) malloc(sizeof(struct Sub));
		no2->low = m+1;
		no2->high = r;
		pthread_t thr1;
		pthread_t thr2;
		
		int test_id = pthread_create(&thr1, NULL, mergeSort, no1);
		pthread_create(&thr2, NULL, mergeSort, no2);
		
		pthread_join(thr1, NULL);
		pthread_join(thr2, NULL);
		merge(A, l, m, r);
	}
}


void writeArray(int A[], int size)
{

	FILE *wfpr = fopen("output_sort.txt", "w");
	if(wfpr == NULL){
		printf("could not open the file\n");
	}
	fprintf(wfpr, "sorted array:\n");
	int i;
	for (i = 0; i < size; i++)
		fprintf(wfpr, "%d ", A[i]);
	fprintf(wfpr, "\n");
}

int main()
{
	int *input;
	input = read_input();
	array_formation(input);
	int arr_size = sizeof(A) / sizeof(A[0]);
	struct Sub *no = (struct Sub*) malloc(sizeof(struct Sub));
	no->low = 0;
	no->high = R - 1;
	pthread_t thr;
	pthread_create(&thr, NULL, mergeSort, no);
	pthread_join(thr, NULL);
	writeArray(A, R);
	return 0;
}

