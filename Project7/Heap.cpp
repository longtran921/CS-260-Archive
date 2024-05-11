//
// Created by ACER NITRO on 11/14/2023.
//

#include "Heap.hpp"

//Private
void Heap::trickleUp(int index) {
    int parent = index / 2;
    int bottom = heapArray[index];

    while (index > 1 && heapArray[parent] > bottom) {
        heapArray[index] = heapArray[parent];
        index = parent;
        parent /= 2;
    }

    heapArray[index] = bottom;
}
void Heap::trickleDown(int index) {
    int largerChild;
    int top = heapArray[index];

    while (index <= heapSize / 2) {
        int leftChild = index * 2;
        int rightChild = leftChild + 1;

        if (rightChild <= heapSize && heapArray[rightChild] < heapArray[leftChild]) {
            largerChild = rightChild;
        } else {
            largerChild = leftChild;
        }

        if (top <= heapArray[largerChild]) {
            break;
        }

        heapArray[index] = heapArray[largerChild];
        index = largerChild;
    }

    heapArray[index] = top;
}
void Heap::resize() {
    int newCapacity = capacity * 2;
    int *newHeapArray = new int[newCapacity + 1];

    for (int i = 1; i <= capacity; ++i) {
        newHeapArray[i] = heapArray[i];
    }

    delete[] heapArray;
    heapArray = newHeapArray;
    capacity = newCapacity;
}

//Public
void Heap::addItem(int item) {
    if (heapSize == capacity) {
        resize();
    }

    heapArray[++heapSize] = item;
    trickleUp(heapSize);
}
int Heap::getItem() {
    if (heapSize == 0) {
        throw std::out_of_range("Heap is empty");
    }

    int minItem = heapArray[1];
    heapArray[1] = heapArray[heapSize--];
    trickleDown(1);

    return minItem;
}