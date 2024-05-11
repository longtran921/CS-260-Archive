//
// Created by ACER NITRO on 11/14/2023.
//

#include "recSorts.hpp"

//Heap
void heapHelper(int array[], int length, int index) { //Heapify helper
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < length && array[left] > array[largest]) {
        largest = left;
    }

    if (right < length && array[right] > array[largest]) {
        largest = right;
    }

    if (largest != index) {
        std::swap(array[index], array[largest]);
        heapHelper(array, length, largest);
    }
}
void heapSort(int array[], int length) {
    // Build heap (rearrange array)
    for (int i = length / 2 - 1; i >= 0; --i) {
        heapHelper(array, length, i);
    }

    // Extract elements from heap one by one
    for (int i = length - 1; i >= 0; --i) {
        std::swap(array[0], array[i]);
        heapHelper(array, i, 0);
    }
}

//Merge
void functionM(int array[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = array[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = array[middle + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k++] = L[i++];
        } else {
            array[k++] = R[j++];
        }
    }

    while (i < n1) {
        array[k++] = L[i++];
    }

    while (j < n2) {
        array[k++] = R[j++];
    }
}
void mergeSortHelper(int array[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSortHelper(array, left, middle);
        mergeSortHelper(array, middle + 1, right);
        functionM(array, left, middle, right);
    }
}
void mergeSort(int array[], int length) {
    mergeSortHelper(array, 0, length - 1);
}

//Quick

int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (array[j] <= pivot) {
            ++i;
            std::swap(array[i], array[j]);
        }
    }

    std::swap(array[i + 1], array[high]);
    return i + 1;
}
void quickSortHelper(int array[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(array, low, high);
        quickSortHelper(array, low, pivotIndex - 1);
        quickSortHelper(array, pivotIndex + 1, high);
    }
}
void quickSort(int array[], int length) {
    quickSortHelper(array, 0, length - 1);
}

//Thinking Problem
int findNthHelper(int array[], int low, int high, int n) {
    if (low <= high) {
        int pivotIndex = partition(array, low, high);
        if (pivotIndex == n) {
            return array[pivotIndex];
        } else if (pivotIndex < n) {
            return findNthHelper(array, pivotIndex + 1, high, n);
        } else {
            return findNthHelper(array, low, pivotIndex - 1, n);
        }
    }
    throw std::out_of_range("Value not found");
}
int findNth(int array[], int length, int n) {
    if (n >= length || n < 0) {
        throw std::out_of_range("Index out of range");
    }

    return findNthHelper(array, 0, length - 1, n);
}