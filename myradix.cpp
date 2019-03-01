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
int* generateFlag(int* arr, int n, int idx, int thread_count) {
  int* flag = (int*) malloc(n * sizeof(int));

  #pragma omp parallel for num_threads(thread_count)
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

int* generateShouldIndex(int* flag, int* iDown, int* iUp, int n, int thread_count) {
  int* shouldIndex = (int*) malloc(n * sizeof(int));

  #pragma omp parallel for num_threads(thread_count)
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
void permute(int* arr, int* flag, int* iDown, int* iUp, int n, int thread_count) {
  int* shouldArr = (int*) malloc(n * sizeof(int));

  int* shouldIndex = generateShouldIndex(flag, iDown, iUp, n, thread_count);

  #pragma omp parallel for num_threads(thread_count)
  for (int i = 0; i < n; i++) {
    shouldArr[shouldIndex[i]] = arr[i];
  }

  #pragma omp parallel for num_threads(thread_count)
  for (int i = 0; i < n; i++) {
    arr[i] = shouldArr[i];
  }
}

void split(int* arr, int n, int idx, int thread_count) {
  int* flag = generateFlag(arr, n, idx, thread_count);
  int* iDown = generateIDown(flag, n);
  int* iUp = generateIUp(flag, n);

  permute(arr, flag, iDown, iUp, n, thread_count);
}

void radixSort(int* arr, int n, int thread_count) {
  int maxElement = getMaxElement(arr, n);
  int idx = 0;

  while ((maxElement >> idx) > 0) {
    split(arr, n, idx, thread_count);
    idx++;
  }
}

int main(int argc, char** argv) {
  int thread_count;

  if (argc != 2){
    cout << "Wrong input" << endl;
    cout << "./radix_sort thread_count" << endl;
    exit(0);
  } else {
    thread_count = stoi(argv[1]);
  }
  
  int n;
  cout << "Insert the size of the array :" << endl;
  cin >> n;
  int * arr = (int*) malloc(n * sizeof(int));
  int * c_arr = (int*) malloc(n * sizeof(int));

  rng(arr, n);
  for (int i = 0; i< n; i++){
    c_arr[i] = arr[i];
  }

  clock_t beginTime = clock();
  radixSort(arr, n, thread_count);
  clock_t endTime = clock();

  double elapsedTime = (double) endTime - beginTime / CLOCKS_PER_SEC;

  cout << "Parallel Radix Sort Time: " << elapsedTime << endl;
  serialRadixSort(c_arr, n);
}
