#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int extraMemoryAllocated;

// ----------------------------------------------------------------------------------------------------------------------
// Merge function is responsible for merging 2 sorted sub-arrays into 1
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1; // Calculates size of left sub-array
    int n2 = r - m; // calculates size of the right sub-array
    
    // 2 Temporary arrays, Left and Right
    int L[n1], R[n2];
    
    // Copying elements from original array into left and right sub-arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
  
    i = 0;
    j = 0;
    k = l;

    // Merge the two sub-arrays back into the original array in sorted order
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
  
    //Copying any remaining elements, if any, from the left sub-array
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    //Copying any remaining elements, if any, from the right sub-array
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if (l < r) {
        int m = l + (r - l) / 2;

        // recursively sorting the left half of the array
        mergeSort(pData, l, m);
        // recursively sorting the right half of the array
        mergeSort(pData, m + 1, r);
        // merges the 2 sorted halves into one sorted array
        merge(pData, l, m, r);
    }
}

// ----------------------------------------------------------------------------------------------------------------------
// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int i, key, j;
    for (i = 1; i < n; i++) {
        // stores current element into key variable
        key = pData[i];
        // initialize the index of the previous element in the array
        j = i - 1;

        while (j >= 0 && pData[j] > key) {
            // Moving the greater element to the right
            pData[j + 1] = pData[j];
            // Moving to the previous element for the next iteration
            j = j - 1;
        }
        // Inserting the key into its correct position in the sorted sequence
        pData[j + 1] = key;
    }
}

//-----------------------------------------------------------------------------------------------------------------------
// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            // Comparing adjacent elements and swapping if they are in the wrong order
            if (pData[j] > pData[j + 1]) {
                // temp variable to hold the current element
                int temp = pData[j];
                // Swapping the elements
                pData[j] = pData[j + 1];
                // Placing the current element in the correct position
                pData[j + 1] = temp;
            }
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------------
// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        // initializing the minimum element to the current index i
        min_idx = i;
        // finding the index of the min element in the unsorted portion
        for (j = i + 1; j < n; j++) {
            if (pData[j] < pData[min_idx]) {
                min_idx = j;// updating the index of the minimum element
             }
        }
        // Swapping the min element with the first element of the unsorted portion
        int temp = pData[min_idx];
        pData[min_idx] = pData[i];
        pData[i] = temp;
    }
    
}

//---------------------------------------------------------------------------------------------------------------------------------
// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
    int dataSz = 0;
    *ppData = NULL;
    if (inFile)
	{
        fscanf(inFile,"%d\n",&dataSz);
        *ppData = (int *)malloc(sizeof(int) * dataSz);
        if (*ppData)
		{
            for (int i=0;i<dataSz;++i)
			{
                fscanf(inFile,"%d\n",&((*ppData)[i]));
            }
        }
    }
    fclose(inFile);
    return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}