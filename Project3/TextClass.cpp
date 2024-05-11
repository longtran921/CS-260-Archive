//
// Created by ACER NITRO on 10/12/2023.
//

#include "TextClass.hpp"
#include <stdexcept>

TextClass::TextClass() : head(nullptr), tail(nullptr), lastFound(nullptr) {}

TextClass::~TextClass() = default;

void TextClass::addHead(char value) {
    Node* newNode = new Node(value);
    if (head == nullptr) { head = tail = newNode;
    } else { newNode->next = head; head->prev = newNode; head = newNode;
    }
}

void TextClass::addTail(char value) {
    Node* newNode = new Node(value);
    if (tail == nullptr) { head = tail = newNode;
    } else { newNode->prev = tail; tail->next = newNode; tail = newNode;
    }
}

char TextClass::getHead() const {
    if (head == nullptr) {
        throw std::out_of_range("Out of Range exception thrown");
    }
    return head->data;
}

char TextClass::getTail() const {
    if (tail == nullptr) {
        throw std::out_of_range("Out of Range exception thrown");
    }
    return tail->data;
}

void TextClass::removeHead() {
    if (head != nullptr) {
        Node* temp = head;
        head = head->next;
        if (head != nullptr) { head->prev = nullptr;
        } else { tail = nullptr;
        } delete temp;
    }
}

void TextClass::removeTail() {
    if (tail != nullptr) {
        Node* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) { tail->next = nullptr;
        } else { head = nullptr;}
        delete temp;
    }
}

bool TextClass::find(char value) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool TextClass::findRemove(char value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            if (current == head) {
                removeHead();
            } else if (current == tail) {
                removeTail();
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
            }
            return true;
        }
        current = current->next;
    }
    return false;
}

std::string TextClass::displayList() const {
    std::string result;
    Node* current = head;
    while (current != nullptr) {
        result += current->data;
        if (current != tail) {
            result += " "; //If this is " " instead of "", everything except thinking problem looks ok
        } //But the thinking problem results look like a mess, but I'll keep it this way, personally I prefer ""
        current = current->next;
    }
    return result;
}

void TextClass::append(const TextClass& otherList) {
    Node* current = otherList.head;
    while (current != nullptr) {
        addTail(current->data);
        current = current->next;
    }
}

void TextClass::removeLast() {
    if (lastFound != nullptr) {
        if (lastFound == head) {
            removeHead();
        } else if (lastFound == tail) {
            removeTail();
        } else {
            lastFound->prev->next = lastFound->next;
            lastFound->next->prev = lastFound->prev;
            delete lastFound;
        }
        lastFound = nullptr;
    }
}

void TextClass::insertLast(char value) {
    if (lastFound != nullptr) {
        Node* newNode = new Node(value);
        newNode->next = lastFound;
        newNode->prev = lastFound->prev;
        if (lastFound->prev != nullptr) {
            lastFound->prev->next = newNode;
        } else {
            head = newNode;
        }
        lastFound->prev = newNode;
    }
}

bool TextClass::findNext(char value) {
    Node* current = (lastFound == nullptr) ? head : lastFound->next;

    while (current != nullptr) {
        if (current->data == value) {
            lastFound = current;
            return true;
        }
        current = current->next;
    }

    if (lastFound != nullptr) {
        // wrap
        current = head;
        while (current != lastFound) {
            if (current->data == value) {
                lastFound = current;
                return true;
            }
            current = current->next;
        }
    }

    lastFound = nullptr;
    return false;
}