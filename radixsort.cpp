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

void radixsort(int *arr, int n) {
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

    for (int i = 0; i < n; i++){
      arr[i] = b[i];
    }

    currentPosition++;
  }
}

int main() {
  int data[] = {8, 8, 2, 1, 2, 7};

  radixsort(data, 6);
  for (int i = 0; i < 6; i++) {
    cout << data[i];
  }
}
