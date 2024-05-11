//
// Created by ACER NITRO on 10/19/2023.
//

#include "ChainHash.hpp"

ChainHash::ChainHash(int size) : tableSize(size), numItems(0), table(new ChainLink*[size]) {
    for (int i = 0; i < size; i++) {
        table[i] = nullptr;
    }
}

ChainHash::~ChainHash() {
    for (int i = 0; i < tableSize; i++) {
        ChainLink* current = table[i];
        while (current != nullptr) {
            ChainLink* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}

int ChainHash::hash(const std::string& value) const {
    int hash = 0;
    for (char c : value) {
        hash += c;
    }
    return hash % tableSize;
}

void ChainHash::addItem(const std::string& value) {
    if (numItems >= tableSize * 2) {
        expandTable();
    }

    int index = hash(value);
    auto* newNode = new ChainLink(value);
    newNode->next = table[index];
    table[index] = newNode;
    numItems++;
}

bool ChainHash::findItem(const std::string& value) {
    int index = hash(value);
    ChainLink* current = table[index];
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void ChainHash::removeItem(const std::string& value) {
    int index = hash(value);
    ChainLink* current = table[index];
    ChainLink* prev = nullptr;

    while (current != nullptr) {
        if (current->data == value) {
            if (prev == nullptr) {
                table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            numItems--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

std::string ChainHash::displayTable() const {
    std::string result;
    for (int i = 0; i < tableSize; i++) {
        ChainLink* current = table[i];
        while (current != nullptr) {
            result += current->data + " ";
            current = current->next;
        }
        if (result.empty()) {
            result = "_empty_";
        }
        result += "\n";
    }
    return result;
}

void ChainHash::expandTable() {
    int newSize = tableSize * 2;

    auto** newTable = new ChainLink*[newSize];
    for (int i = 0; i < newSize; i++) {
        newTable[i] = nullptr;
    }

    for (int i = 0; i < tableSize; i++) {
        ChainLink* current = table[i];
        while (current != nullptr) {
            int newIndex = hash(current->data) % newSize;
            auto* newNode = new ChainLink(current->data);
            newNode->next = newTable[newIndex];
            newTable[newIndex] = newNode;
            current = current->next;
        }
    }

    delete[] table;
    table = newTable;
    tableSize = newSize;
}