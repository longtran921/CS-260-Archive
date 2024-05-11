//
// Created by ACER NITRO on 10/2/2023.
//

#ifndef UNTITLED4_ARRAYINT_HPP
#define UNTITLED4_ARRAYINT_HPP

#pragma once
#include <stdexcept>
#include <string>

class ArrayInt {
private:
    int* data;         // Pointer to dynamically allocated array
    int size;          // Current size of the array
    int capacity;      // Current capacity of the array
    int nextIndex;     // Index for the next available location

public:
    // Constructor
    ArrayInt(int n = 10);

    // Destructor
    ~ArrayInt();

    // Member functions
    int getSize() const;
    void resize(int size);
    void append(int value);
    int getLast() const;
    void deleteLast();
    std::string listElements() const;
    void insertAt(int index, int value);
    int removeAt(int index);
    bool find(int value) const;
    bool findRemove(int value);
    int findLargest() const;
    void removeLargest();
    int getAt(int index) const;
    void setAt(int index, int value);

    // Helper function for copying array elements
    void copyArray(const ArrayInt& other);

    // Helper function for expanding the array capacity
    void expandArray();
};

#endif // ARRAYINT_HPP
