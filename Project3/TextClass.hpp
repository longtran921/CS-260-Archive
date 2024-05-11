//
// Created by ACER NITRO on 10/12/2023.
//

#ifndef UNTITLED8_TEXTCLASS_HPP
#define UNTITLED8_TEXTCLASS_HPP

#include <string>

class TextClass {
public:
    TextClass();
    ~TextClass();

    void addHead(char value);
    void addTail(char value);
    char getHead() const;
    char getTail() const;
    void removeHead();
    void removeTail();
    bool find(char value) const;
    bool findRemove(char value);
    std::string displayList() const;
    void append(const TextClass& otherList);
    void removeLast();
    void insertLast(char value);
    bool findNext(char value);

private:
    struct Node {
        char data;
        Node* prev;
        Node* next;
        explicit Node(char val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    Node* lastFound;
};




#endif //UNTITLED8_TEXTCLASS_HPP
