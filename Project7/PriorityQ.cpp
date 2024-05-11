//
// Created by ACER NITRO on 11/14/2023.
//

#include "PriorityQ.hpp"

void PriorityQ::addItem(int item) {
    heap.addItem(item);
}

int PriorityQ::getItem() {
    return heap.getItem();
}
