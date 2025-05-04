#include <iostream>
#include <omp.h>  // Ensure Dev-C++ supports this

using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void sequentialBubbleSort(int *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void parallelBubbleSort(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        int phase = i % 2;
#pragma omp parallel for
        for (int j = phase; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int *a = new int[n];
    int *b = new int[n];

    cout << "Enter array elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }

    double start, end;

    start = omp_get_wtime();
    sequentialBubbleSort(a, n);
    end = omp_get_wtime();
    cout << "\nTime (Sequential): " << (end - start) << " seconds\n";

    start = omp_get_wtime();
    parallelBubbleSort(b, n);
    end = omp_get_wtime();
    cout << "Time (Parallel): " << (end - start) << " seconds\n";

    cout << "\nSorted Array:\n";
    for (int i = 0; i < n; i++) {
        cout << b[i] << " ";
    }
    cout << endl;

    delete[] a;
    delete[] b;

    return 0;
}
