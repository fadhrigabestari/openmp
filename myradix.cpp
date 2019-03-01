#include <algorithm>
#include <iostream>
#include <iterator>
#include <ctime>
#include <fstream>

using namespace std;

#define THREAD_COUNT 4

int getMaxElement(int *arr, int n) {
  int max = arr[0];

  for (int i = 0; i < n; i++) {
    if (max < n) {max = n;}
  }

  return max;
}

void printArr(int* arr, int n) {
  ofstream fstream;
  fstream.open("data/output");
  for (int i = 0; i < n; i++) {
    fstream << arr[i] << endl;
  }
}

void printArrei(int* arr, int n) {
  for (int i = 0; i < n; i++) {
    cout << arr[i] << endl;
  }
}

void rng(int* arr, int n) {
  int seed = 13516154;
  srand(seed);
  for(long i = 0; i < n; i++) {
    arr[i] = (int)rand();
  }
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
void serialRadixSort(int arr[], int n) 
{ 
    // Find the maximum number to know number of digits 
    int m = getMaxElement(arr, n); 
  
    // Do counting sort for every digit. Note that instead 
    // of passing digit number, exp is passed. exp is 10^i 
    // where i is current digit number 
    clock_t beginTime = clock();
    for (int exp = 1; m/exp > 0; exp *= 10){
      countSort(arr, n, exp);
    }
    clock_t endTime = clock();

    double elapsedTime = (double) endTime - beginTime / CLOCKS_PER_SEC;

    cout << "Serial Radix Sort Time: " << elapsedTime << endl;
}

// parallel radix sort
// get specific bit at index = idx
int* generateFlag(int* arr, int n, int idx) {
  int* flag = (int*) malloc(n * sizeof(int));

  #pragma omp parallel for num_threads(THREAD_COUNT)
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

  #pragma omp parallel for num_threads(THREAD_COUNT)
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

  #pragma omp parallel for num_threads(THREAD_COUNT)
  for (int i = 0; i < n; i++) {
    shouldArr[shouldIndex[i]] = arr[i];
  }

  #pragma omp parallel for num_threads(THREAD_COUNT)
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

  for (int i = 0; i < 32; i++) {
    split(arr, n, i);
  }
}

int main(int argc, char** argv) {
  int n;

  if (argc != 2){
    cout << "Wrong input" << endl;
    cout << "./radix_sort <N>" << endl;
    exit(0);
  } else {
    n = stoi(argv[1]);
  }


  int * arr = (int*) malloc(n * sizeof(int));
  int * c_arr = (int*) malloc(n * sizeof(int));

  rng(arr, n);
  rng(c_arr, n);
  printArrei(arr, n);
  printArrei(c_arr, n);

  clock_t beginTime = clock();
  radixSort(arr, n);
  clock_t endTime = clock();

  double elapsedTime = (double) endTime - beginTime / CLOCKS_PER_SEC;

  cout << "Parallel Radix Sort Time: " << elapsedTime << endl;
  serialRadixSort(c_arr, n);

  printArr(arr, n);
  cout << endl;
}
