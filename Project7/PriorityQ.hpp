//
// Created by ACER NITRO on 11/14/2023.
//

#ifndef CS260_LAB7_PRIORITYQ_HPP
#define CS260_LAB7_PRIORITYQ_HPP

#include "Heap.hpp"

class PriorityQ {
private:
    Heap heap;

public:
    //Constructor & Destructor
    explicit PriorityQ(int initialCapacity = 10) : heap(initialCapacity) {}
    ~PriorityQ() = default;

    void addItem(int item);
    int getItem();
};

#endif //CS260_LAB7_PRIORITYQ_HPP
