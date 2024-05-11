//
// Created by ACER NITRO on 11/14/2023.
//

#ifndef CS260_LAB7_RECSORTS_HPP
#define CS260_LAB7_RECSORTS_HPP

#include <iostream>
#include <vector>

//Heap
void heapHelper(int array[], int length, int index);
void heapSort(int array[], int length);

//Merge
void functionM(int array[], int left, int middle, int right);
void mergeSortHelper(int array[], int left, int right);
void mergeSort(int array[], int length);

//Quick
int partition(int array[], int low, int high);
void quickSortHelper(int array[], int low, int high);
void quickSort(int array[], int length);

//Thinking Problem
int findNthHelper(int array[], int low, int high, int n);
int findNth(int array[], int length, int n);

#endif //CS260_LAB7_RECSORTS_HPP
