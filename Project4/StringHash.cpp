//
// Created by ACER NITRO on 10/19/2023.
//

#include "StringHash.hpp"

StringHash::StringHash(int size) : tableSize(size), table(new std::string[size]) {
    for (int i = 0; i < size; i++) {
        table[i] = empty;
    }
}

StringHash::~StringHash() {
    delete[] table;
}

int StringHash::hash(const std::string& value) const {
    int hash = 0;
    for (char c : value) {
        hash += c;
    }
    return hash % tableSize;
}

void StringHash::addItem(const std::string& value) {
    int index = hash(value);

    while (table[index] != empty && table[index] != deleted) {
        index = (index + 1) % tableSize;
    }

    table[index] = value;
}

bool StringHash::findItem(const std::string& value) {
    int index = hash(value);

    while (table[index] != empty) {
        if (table[index] == value) {
            return true;
        }
        index = (index + 1) % tableSize;
    }

    return false;
}

void StringHash::removeItem(const std::string& value) {
    int index = hash(value);

    while (table[index] != empty) {
        if (table[index] == value) {
            table[index] = deleted;
            return;
        }
        index = (index + 1) % tableSize;
    }
}

std::string StringHash::displayTable() const {
    std::string result;
    for (int i = 0; i < tableSize; i++) {
        result += table[i] + "\n";
    }
    return result;
}