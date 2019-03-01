#include<iostream>
#define BITS 3
#define BASE 1 << BITS

using namespace std;


int getMaxElement(int *arr) {
  int max = arr[0];

  for (int n : arr) {
    if (max < n) {max = n;}
  }

  return max;
}

void radixsort(int *arr, int n) {
  int firstElement = arr[0];
  int currentPosition = 0;

  int buckets = BASE;
  int mask = buckets - 1;

  int maxElement = getMaxElement(arr);
  while ((maxElement >> (post * BITS)) > 0) {
    // radix
  }
}
