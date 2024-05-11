//
// Created by ACER NITRO on 10/2/2023.
//

#include <iostream>
#include <stdexcept>

class Deque {
private:
    int* array;      
    int capacity;    
    int head;        
    int tail;        
    int size;        

public:
    Deque(int n = 20); // Constructor
    ~Deque(); // Destructor
    void addTail(int value);
    int removeHead();
    std::string dumpArray() const;
    void resize();
    std::string listQueue() const;
    bool isEmpty() const;
    void addHead(int value);
    int removeTail();
};
