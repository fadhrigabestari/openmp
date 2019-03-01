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
