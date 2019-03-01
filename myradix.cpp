#include <algorithm>
#include <iostream>
#include <iterator>
#include <ctime>

using namespace std;

int getMaxElement(int *arr, int n) {
  int max = arr[0];

  for (int i = 0; i < n; i++) {
    if (max < n) {max = n;}
  }

  return max;
}

void printArr(int* arr, int n) {
  for (int i = 0; i < n; i++) {
    cout << i << " ";
  }
  cout << "\n";
}

void rng(int* arr, int n) {
  int seed = 13516154;
  srand(seed);
  for(long i = 0; i < n; i++) {
    arr[i] = (int)rand();
  }
}

// get specific bit at index = idx
int* generateFlag(int* arr, int n, int idx) {
  int* flag = (int*) malloc(n * sizeof(int));

  // parallel this
  for (int i = 0; i < n; i++) {
    if ((arr[i] >> idx) & 1 == 1) {
      flag[i] = 1;
    } else {
      flag[i] = 0;
    }
  }
  return flag;
}

// create I-down array
int* generateIDown(int* flag, int n) {
  int* iDown = (int*) malloc(n * sizeof(int));
  int val = 0;

  iDown[0] = val;
  for (int i = 1; i < n; i++) {
    if (flag[i - 1] == 0) {
      val++;
    }
    iDown[i] = val;
  }
  return iDown;
}

// create I-up array
int* generateIUp(int* flag, int n) {
  int* iUp = (int*) malloc(n * sizeof(int));
  int val = n - 1;

  iUp[n - 1] = val;
  for (int i = n - 2; i >= 0; i--) {
    if (flag[i + 1] == 1) {
      val--;
    }
    iUp[i] = val;
  }
  return iUp;
}

int* generateShouldIndex(int* flag, int* iDown, int* iUp, int n) {
  int* shouldIndex = (int*) malloc(n * sizeof(int));

  // parallel this
  for (int i = 0; i < n; i++) {
    if (flag[i] == 0) {
      shouldIndex[i] = iDown[i];
    } else {
      shouldIndex[i] = iUp[i];
    }
  }
  return shouldIndex;
}

// permute
void permute(int* arr, int* flag, int* iDown, int* iUp, int n) {
  int* shouldArr = (int*) malloc(n * sizeof(int));

  int* shouldIndex = generateShouldIndex(flag, iDown, iUp, n);

  // parallel this
  for (int i = 0; i < n; i++) {
    shouldArr[shouldIndex[i]] = arr[i];
  }

  // parallel this
  for (int i = 0; i < n; i++) {
    arr[i] = shouldArr[i];
  }
}

void split(int* arr, int n, int idx) {
  int* flag = generateFlag(arr, n, idx);
  int* iDown = generateIDown(flag, n);
  int* iUp = generateIUp(flag, n);

  permute(arr, flag, iDown, iUp, n);
}

void radixSort(int* arr, int n) {
  int maxElement = getMaxElement(arr, n);
  int idx = 0;

  while ((maxElement >> idx) > 0) {
    split(arr, n, idx);
    idx++;
  }
}

int main(int argc, char** agrv) {
  int n = 100000;
  int * arr = (int*) malloc(n * sizeof(int));
  rng(arr, n);
  clock_t beginTime = clock();
  radixSort(arr, n);
  clock_t endTime = clock();

  double elapsedTime = (double) endTime - beginTime / CLOCKS_PER_SEC;

  cout << "Time: " << elapsedTime;
}
