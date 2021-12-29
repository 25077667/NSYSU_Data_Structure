#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int *generateArray(int size) { return new int[size]; }

void getRawArray(vector<pair<int *, int>> &arraySets) {
  ifstream file("input.txt", ifstream::in);
  int n;
  while (file >> n) {
    int *arr = generateArray(n);
    for (int i = 0; i < n; i++)
      file >> arr[i];
    arraySets.push_back(make_pair(arr, n));
  }
  file.close();
}

void outputResult(string sortingAlgorithm, int *arr, int size,
                  float deltaTime) {
  ofstream outputFile(sortingAlgorithm + to_string(size) + ".txt",
                      ofstream::out);
  outputFile << "The total time is " << deltaTime << " seconds\n";
  for (auto i = 0; i < size; i++)
    outputFile << arr[i] << "\n";
  outputFile.close();
}

void insertionSort(int *arr, int n) {
  int i, j, key;
  for (i = 1; i < n; i++) {
    key = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

void merge(int *arr, int front, int tail, int middle) {
  int leftSize = middle - front + 1, rightSize = tail - middle;

  int *leftSubArray = new int[leftSize], *rightSubArray = new int[rightSize];

  memcpy(leftSubArray, arr + front, leftSize * sizeof(int));
  memcpy(rightSubArray, arr + middle + 1, rightSize * sizeof(int));

  int i = 0, j = 0, k = front;
  while (i < leftSize && j < rightSize) {
    if (leftSubArray[i] <= rightSubArray[j])
      arr[k++] = leftSubArray[i++];
    else
      arr[k++] = rightSubArray[j++];
  }
  while (i < leftSize) // still have element in leftSubArray
    arr[k++] = leftSubArray[i++];
  while (j < rightSize)
    arr[k++] = rightSubArray[j++];
  delete[] leftSubArray;
  delete[] rightSubArray;
}

void mergeSort(int *arr, int front, int tail) {
  if (front < tail) {
    int middle = (front + tail) / 2;
    mergeSort(arr, front, middle);
    mergeSort(arr, middle + 1, tail);
    merge(arr, front, tail, middle);
  }
}

int getIndexAndDivide(int *arr, int front, int tail) {
  int pivot = arr[tail];
  int i = front - 1;
  for (auto j = front; j < tail; j++)
    if (arr[j] < pivot)
      swap(arr[++i], arr[j]);
  swap(arr[++i], arr[tail]);
  return i;
}

void quickSort(int *arr, int front, int tail) {
  if (front < tail) {
    int divideIndex = getIndexAndDivide(arr, front, tail);
    quickSort(arr, front, divideIndex - 1);
    quickSort(arr, divideIndex + 1, tail);
  }
}

int compareOfqSsort(const void *a, const void *b) {
  return (*(long int *)a - *(long int *)b);
}

int main() {
  vector<pair<int *, int>> arraySets;
  int modeSelection = 0;
  clock_t deltaTime;
  getRawArray(arraySets);
  cout << "read file done" << endl;

  cin >> modeSelection;
  switch (modeSelection) {
  case 1:
    cout << "insertion Sort" << endl;
    for (auto arrayIndex : arraySets) {
      deltaTime = clock();
      insertionSort(arrayIndex.first, arrayIndex.second - 1);
      deltaTime = clock() - deltaTime;
      outputResult(string("insertion Sort"), arrayIndex.first,
                   arrayIndex.second, ((float)deltaTime) / CLOCKS_PER_SEC);
      cout << "The total time is " << ((float)deltaTime) / CLOCKS_PER_SEC
           << " seconds\n";
    }
    break;
  case 2:
    cout << "merge Sort" << endl;
    for (auto arrayIndex : arraySets) {
      deltaTime = clock();
      mergeSort(arrayIndex.first, 0, arrayIndex.second - 1);
      deltaTime = clock() - deltaTime;
      outputResult(string("merge Sort"), arrayIndex.first, arrayIndex.second,
                   ((float)deltaTime) / CLOCKS_PER_SEC);
      cout << "The total time is " << ((float)deltaTime) / CLOCKS_PER_SEC
           << " seconds\n";
    }
    break;
  case 3:
    cout << "quick Sort" << endl;
    for (auto arrayIndex : arraySets) {
      deltaTime = clock();
      quickSort(arrayIndex.first, 0, arrayIndex.second - 1);
      deltaTime = clock() - deltaTime;
      outputResult(string("quick Sort"), arrayIndex.first, arrayIndex.second,
                   ((float)deltaTime) / CLOCKS_PER_SEC);
      cout << "The total time is " << ((float)deltaTime) / CLOCKS_PER_SEC
           << " seconds\n";
    }
    break;
  case 4:
    cout << "stdlib  qSort" << endl;
    for (auto arrayIndex : arraySets) {
      deltaTime = clock();
      qsort(arrayIndex.first, arrayIndex.second, sizeof(int), compareOfqSsort);
      deltaTime = clock() - deltaTime;
      outputResult(string("stdlib  qSort"), arrayIndex.first, arrayIndex.second,
                   ((float)deltaTime) / CLOCKS_PER_SEC);
      cout << "The total time is " << ((float)deltaTime) / CLOCKS_PER_SEC
           << " seconds\n";
    }
    break;
  case 5:
    cout << "STL Sort" << endl;
    for (auto arrayIndex : arraySets) {
      deltaTime = clock();
      sort(arrayIndex.first, arrayIndex.first + arrayIndex.second);
      deltaTime = clock() - deltaTime;
      outputResult(string("STL Sort"), arrayIndex.first, arrayIndex.second,
                   ((float)deltaTime) / CLOCKS_PER_SEC);
      cout << "The total time is " << ((float)deltaTime) / CLOCKS_PER_SEC
           << " seconds\n";
    }
    break;
  default:
    break;
  }
  return 0;
}
