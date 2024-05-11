//
// Created by ACER NITRO on 10/2/2023.
//

#include "Deque.hpp"

// Constructor
Deque::Deque(int n) {
    if (n < 1) {
        n = 20; // Default size
    }
    array = new int[n];
    capacity = n;
    head = 0;
    tail = 0;
    size = 0;
}

// Destructor
Deque::~Deque() {
    delete[] array;
}

void Deque::addTail(int value) {
    if (size == capacity) {
        resize();
    }
    array[tail] = value;
    tail = (tail + 1) % capacity;
    size++;
}

int Deque::removeHead() {
    if (isEmpty()) {
        throw std::out_of_range("Deque is empty");
    }
    int value = array[head];
    head = (head + 1) % capacity;
    size--;
    return value;
}

std::string Deque::dumpArray() const {
    std::string result;
    for (int i = 0; i < size; i++) {
        result += std::to_string(array[i]) + " ";
    }
    return result;
}

void Deque::resize() {
    int newCapacity = capacity * 2;
    int* newArray = new int[newCapacity];
    for (int i = 0, j = head; i < size; i++, j = (j + 1) % capacity) {
        newArray[i] = array[j];
    }
    delete[] array;
    array = newArray;
    head = 0;
    tail = size;
    capacity = newCapacity;
}

std::string Deque::listQueue() const {
    std::string result;
    for (int i = 0, j = head; i < size; i++, j = (j + 1) % capacity) {
        result += std::to_string(array[j]) + " ";
    }
    return result;
}

bool Deque::isEmpty() const {
    return size == 0;
}

void Deque::addHead(int value) {
    if (size == capacity) {
        resize();
    }
    head = (head - 1 + capacity) % capacity;
    array[head] = value;
    size++;
}

int Deque::removeTail() {
    if (isEmpty()) {
        throw std::out_of_range("Deque is empty");
    }
    tail = (tail - 1 + capacity) % capacity;
    int value = array[tail];
    size--;
    return value;
}
