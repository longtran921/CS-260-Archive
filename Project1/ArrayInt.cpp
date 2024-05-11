//
// Created by ACER NITRO on 10/2/2023.
//

#include "ArrayInt.hpp"

// Constructor
ArrayInt::ArrayInt(int n) {
    if (n < 1) n = 10;
    size = n;
    capacity = n;
    data = new int[n];
    nextIndex = 0;
}

// Destructor
ArrayInt::~ArrayInt() {
    delete[] data;
}

// Member functions (implementation)

int ArrayInt::getSize() const {
    return capacity;
}

void ArrayInt::resize(int size) {
    if (size <= capacity) {
        return;
    }

    int newCapacity = size;
    int* newData = new int[newCapacity];

    for (int i = 0; i < nextIndex; i++) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

void ArrayInt::append(int value) {
    if (nextIndex >= size) {
        resize(2 * size);
    }

    data[nextIndex] = value;
    nextIndex++;
}

int ArrayInt::getLast() const {
    if (nextIndex == 0) {
        throw std::out_of_range("Array is empty");
    }
    return data[nextIndex - 1];
}

void ArrayInt::deleteLast() {
    if (nextIndex == 0) {
        throw std::out_of_range("Cannot delete from an empty array");
    }
    nextIndex--;
}

std::string ArrayInt::listElements() const {
    if (nextIndex == 0) {
        return "Empty Array";
    }

    std::string result = std::to_string(data[0]);
    for (int i = 1; i < nextIndex; i++) {
        result += ", " + std::to_string(data[i]);
    }

    return result;
}

void ArrayInt::insertAt(int index, int value) {
    if (index < 0 || index > nextIndex) {
        throw std::out_of_range("Index out of range");
    }

    if (nextIndex >= capacity) {
        resize(2 * capacity);
    }

    for (int i = nextIndex; i > index; i--) {
        data[i] = data[i - 1];
    }

    data[index] = value;
    nextIndex++; // Update the nextIndex to reflect the new element
}

int ArrayInt::removeAt(int index) {
    if (index < 0 || index >= nextIndex) {
        throw std::out_of_range("Index out of range");
    }

    int removedValue = data[index];

    for (int i = index; i < nextIndex - 1; i++) {
        data[i] = data[i + 1];
    }

    nextIndex--;
    return removedValue;
}

bool ArrayInt::find(int value) const {
    for (int i = 0; i < nextIndex; i++) {
        if (data[i] == value) {
            return true;
        }
    }
    return false;
}

bool ArrayInt::findRemove(int value) {
    for (int i = 0; i < nextIndex; i++) {
        if (data[i] == value) {
            for (int j = i; j < nextIndex - 1; j++) {
                data[j] = data[j + 1];
            }
            nextIndex--;
            return true;
        }
    }
    return false;
}

int ArrayInt::findLargest() const {
    if (nextIndex == 0) {
        throw std::out_of_range("Array is empty");
    }

    int largest = data[0];
    for (int i = 1; i < nextIndex; i++) {
        if (data[i] > largest) {
            largest = data[i];
        }
    }
    return largest;
}

void ArrayInt::removeLargest() {
    if (nextIndex == 0) {
        throw std::out_of_range("Array is empty");
    }

    int largestIndex = 0;
    for (int i = 1; i < nextIndex; i++) {
        if (data[i] > data[largestIndex]) {
            largestIndex = i;
        }
    }

    for (int i = largestIndex; i < nextIndex - 1; i++) {
        data[i] = data[i + 1];
    }

    nextIndex--;
}

int ArrayInt::getAt(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }

    return data[index];
}

void ArrayInt::setAt(int index, int value) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }

    data[index] = value;
}

void ArrayInt::copyArray(const ArrayInt& other) {
    size = other.size;
    capacity = other.capacity;
    nextIndex = other.nextIndex;

    data = new int[capacity];
    for (int i = 0; i < nextIndex; i++) {
        data[i] = other.data[i];
    }
}

void ArrayInt::expandArray() {
    int newCapacity = capacity * 2;
    int* newData = new int[newCapacity];

    for (int i = 0; i < nextIndex; i++) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}
