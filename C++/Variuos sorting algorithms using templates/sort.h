#pragma once
template <class T>
int insertionsort(T arr[], int n) {
	if (n == 1) { // cheak if list is one element 
		return 0;
	}
	T temp, ops=0;
	for (int i = 0; i < n-1; i++) {
		temp = arr[i+1];
		for (int j = i; j >= 0; j--) {

			if (temp < arr[j]) {
				arr[j + 1] = arr[j]; ops++; //barometer oporation
				arr[j] = temp; ops++; //barometer oporation
			}
			else {
				arr[j + 1] = temp; ops++; break; //barometer oporation
			}

		}

	}
	return ops;
}

template <class T>
void swap(T* a, T* b) {
	T t = *a;
	*a = *b;
	*b = t; 
}
template <class T>
int partition(T arr[], int low, int high, int &ops ) {

	int pivot = arr[high]; // set piviot to the last element

	int i = (low - 1);

	for (int j = low; j < high; j++) {
		if (arr[j] <= pivot) {
			i++;  ops++;//barometer oporation
			swap(&arr[i], &arr[j]);  ops += 3; //barometer oporations in swap
		}
		ops+=2; //baromitere oporations in each for loop
	}

	swap(&arr[i + 1], &arr[high]);

	return (i + 1); //return piviot index
}
template <class T>
void qsort(T arr[], int low, int high,int &ops) {
	if (high > low) {
		 
		int pivot = partition(arr, low, high, ops);

		qsort( arr, low, pivot -1, ops);  //upper part of the array
		qsort( arr, pivot + 1, high, ops); //lower part of the array

	}

}
template <class T>
int quicksort(T arr[], int n) {
	int ops = 0, low = 0, high = n - 1; 

	qsort( arr , low, high, ops);  // the main quickesort function 
	return ops;
}
template <class T>
void merge(T arr[], int l, int m, int r,int &ops)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	
	// create temporay variable size arrays in heap
	T *L = new T[n1];
	T *R = new T[n2];
	// Copy data to temp arrays L and R
	for (i = 0; i < n1; i++)
	{
		L[i] = arr[l + i]; ops++; //barometer oporation
	}

	for (j = 0; j < n2; j++)
	{
		R[j] = arr[m + 1 + j]; ops++; //barometer oporation
	}

	//Merge the temp arrays back into arr[l..r]
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
		ops += 7;
	}

	// Copy the remaining elements of L, if there are any 
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++; ops += 4;
	}

	// Copy the remaining elements of R, if there are any 
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++; ops += 4;
	}
}

template <class T>
int mergesort(T arr[], int n)
{
	int ops=0;
	int curr_size;  // current size of subarrays start from 1 to n/2
					
	int left_start; //starting index of left subarray
					

	// Merge subarrays from bottom up.  
	for (curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size)
	{
		// Pick starting point of different subarrays of current size
		for (left_start = 0; left_start < n - 1; left_start += 2 * curr_size)
		{
			// Find ending point of left subarray. mid+1 is starting
			// point of right
			int mid = min(left_start + curr_size - 1, n - 1); 

			int right_end = min(left_start + 2 * curr_size - 1, n - 1); 

			// Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
			merge(arr, left_start, mid, right_end,ops);
		}
		
	}
	return ops;
}

template <class T>
int shellsort(T arr[], int n) {
	int ops=0, h=1,j;

	while ((3 * h + 1) < n) { h = 3 * h + 1; } // knuth sequence for determining the gap between comparision blocks for optimization 

	for (int gap =h; gap > 0; gap = (gap-1)/3 )
	{
		ops += 2;
		// Do a gapped insertion sort for this gap size.
		// keep adding one more element until the entire array is sorted

		for (int i = gap; i < n; i += 1)
		{
			
			T temp = arr[i];  ops += 3; //barometer oporations 

			// shift earlier gap-sorted elements up until the correct
			// location for a[i] is found

			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)

			{
				arr[j] = arr[j - gap]; ops += 3; //barometer oporations
			}

			//  put temp in its correct location
			arr[j] = temp; ops++; //barometer oporation
		}
	}
	return 0;
}