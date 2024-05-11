//
// Created by ACER NITRO on 11/14/2023.
//

#ifndef CS260_LAB7_HEAP_HPP
#define CS260_LAB7_HEAP_HPP

#include <stdexcept>

class Heap {
private:
    int *heapArray;
    int heapSize;
    int capacity;

    void trickleUp(int index);
    void trickleDown(int index);
    void resize();

public:
    //Constructor & Destructor
    explicit Heap(int initialCapacity = 10) : heapSize(0), capacity(initialCapacity) {
        heapArray = new int[capacity + 1];
    }
    ~Heap() {
        delete[] heapArray;
    }

    void addItem(int item);
    int getItem();
};

#endif //CS260_LAB7_HEAP_HPP
