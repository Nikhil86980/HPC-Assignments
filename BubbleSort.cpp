#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <omp.h>

using namespace std;

// Function to generate random array
void generateRandomArray(vector<int>& arr, int size) {
arr.resize(size);
for (int i = 0; i < size; ++i)
arr[i] = rand() % 10000;
}

// Sequential Bubble Sort
void bubbleSortSequential(vector<int>& arr) {
int n = arr.size();
for (int i = 0; i < n - 1; ++i)
for (int j = 0; j < n - i - 1; ++j)
if (arr[j] > arr[j + 1])
swap(arr[j], arr[j + 1]);
}

// Parallel Bubble Sort using OpenMP (Odd-Even Transposition)
void bubbleSortParallel(vector<int>& arr) {
int n = arr.size();
for (int i = 0; i < n; ++i) {
if (i % 2 == 0) {
#pragma omp parallel for default(none) shared(arr, n)
for (int j = 0; j < n - 1; j += 2)
if (arr[j] > arr[j + 1])
swap(arr[j], arr[j + 1]);
} else {
#pragma omp parallel for default(none) shared(arr, n)
for (int j = 1; j < n - 1; j += 2)
if (arr[j] > arr[j + 1])
swap(arr[j], arr[j + 1]);
}
}
}

int main() {
srand(time(nullptr));

int size;
char choice;
cout << "Enter the number of elements to sort: ";
cin >> size;

vector<int> arr(size), arr_seq, arr_par;

cout << "Do you want to enter the elements manually? (y/n): ";
cin >> choice;

if (choice == 'y' || choice == 'Y') {
    cout << "Enter " << size << " elements:\n";
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }
} else {
    generateRandomArray(arr, size);
}

arr_seq = arr;
arr_par = arr;

// Sequential sort timing
auto start_seq = chrono::high_resolution_clock::now();
bubbleSortSequential(arr_seq);
auto end_seq = chrono::high_resolution_clock::now();

// Parallel sort timing
auto start_par = chrono::high_resolution_clock::now();
bubbleSortParallel(arr_par);
auto end_par = chrono::high_resolution_clock::now();

chrono::duration<double> time_seq = end_seq - start_seq;
chrono::duration<double> time_par = end_par - start_par;

cout << "Sequential Bubble Sort Time: " << time_seq.count() << " seconds" << endl;
cout << "Parallel Bubble Sort Time:   " << time_par.count() << " seconds" << endl;

return 0;
}
