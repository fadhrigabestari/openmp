#include<iostream>
#include <cmath>

#define BITS 3
#define BASE 1 << BITS

using namespace std;


int getMaxElement(int *arr, int n) {
  int max = arr[0];

  for (int i = 0; i < n; i++) {
    if (max < n) {max = n;}
  }

  return max;
}
// serial radix sort from geeks for geeks
// A function to do counting sort of arr[] according to 
// the digit represented by exp. 
void countSort(int arr[], int n, int exp) 
{ 
    int output[n]; // output array 
    int i, count[10] = {0}; 
  
    // Store count of occurrences in count[] 
    for (i = 0; i < n; i++) 
        count[ (arr[i]/exp)%10 ]++; 
  
    // Change count[i] so that count[i] now contains actual 
    //  position of this digit in output[] 
    for (i = 1; i < 10; i++) 
        count[i] += count[i - 1]; 
  
    // Build the output array 
    for (i = n - 1; i >= 0; i--) 
    { 
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i]; 
        count[ (arr[i]/exp)%10 ]--; 
    } 
  
    // Copy the output array to arr[], so that arr[] now 
    // contains sorted numbers according to current digit 
    for (i = 0; i < n; i++) 
        arr[i] = output[i]; 
} 
  
// The main function to that sorts arr[] of size n using  
// Radix Sort 
void radixsort(int arr[], int n) 
{ 
    // Find the maximum number to know number of digits 
    int m = getMaxElement(arr, n); 
  
    // Do counting sort for every digit. Note that instead 
    // of passing digit number, exp is passed. exp is 10^i 
    // where i is current digit number 
    for (int exp = 1; m/exp > 0; exp *= 10) 
        countSort(arr, n, exp); 
} 


// parallel radix sort 
void radixsort(int *arr, int n, int t_count) {
  int bSize = pow(2, BITS);
  int currentPosition = 0;

  int buckets = BASE;
  int mask = buckets - 1;

  int b[bSize];

  int maxElement = getMaxElement(arr, n);
  while ((maxElement >> (currentPosition * BITS)) > 0) {
    int bucket[1<<BITS] = { 0 };
    for (int i = 0; i < n; i++){
      bucket[(arr[i] >> (currentPosition * BITS)) & mask]++;
    }

    for (int i = 1; i < buckets; i++) {
      bucket[i] += bucket[i - 1];
    }

    for (int i = n - 1; i >= 0; i--)  {
      b[--bucket[(arr[i]>>(currentPosition*BITS)) & mask]] = arr[i];
    }

	#pragma omp parallel for
    for (int i = 0; i < n; i++){
      arr[i] = b[i];
    }

    currentPosition++;
  }
}

void rng(int* arr, int n){
	int seed = 13516031;
	srand(seed);
	for(long i = 0; i < n;i++){
		arr[i] = (int)rand();
	}
}

void print_array(int arr[], int n){
	for (int i = 0; i < n ; i++){
		cout << arr[i] << "\n";
	}
}

int main(int argc, char* argv[]) {
  int t_count = strtol(argv[1], NULL, 10);
  int data[10] = {0};
  rng(data, 10);
  print_array(data, 10);

  radixsort(data, 10, t_count);
  cout << "Hasil Sort" << "\n";
  for (int i = 0; i < 10; i++) {
    cout << data[i] << "\n";
  }
}
