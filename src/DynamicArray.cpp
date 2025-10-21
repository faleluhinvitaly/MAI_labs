/*
 * DynamicArray.cpp
 *
 *  Created on: Oct 21, 2025
 *      Author: cyberdemon
 */
#include "DynamicArray.h"
#include <iostream>
#include <cstring>

using namespace std;

DynamicArray::DynamicArray(int arraySize) {
    size = (arraySize <= 0) ? 1 : arraySize;
    data = new int[size];
    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }
}

DynamicArray::DynamicArray(const DynamicArray& other) {
    size = other.size;
    data = new int[size];
    memcpy(data, other.data, size * sizeof(int));
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

void DynamicArray::print() const {
    cout << "[";
    for (int i = 0; i < size; i++) {
        cout << data[i];
        if (i < size - 1) cout << ", ";
    }
    cout << "]" << endl;
}

bool DynamicArray::setValue(int index, int value) {
    if (index < 0 || index >= size) return false;
    if (value < -100 || value > 100) return false;
    data[index] = value;
    return true;
}

bool DynamicArray::getValue(int index, int& value) const {
    if (index < 0 || index >= size) return false;
    value = data[index];
    return true;
}

void DynamicArray::append(int value) {
    if (value < -100 || value > 100) return;
    
    int* newData = new int[size + 1];
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    newData[size] = value;
    
    delete[] data;
    data = newData;
    size++;
}

void DynamicArray::add(const DynamicArray& other) {
    for (int i = 0; i < size; i++) {
        int otherValue = (i < other.size) ? other.data[i] : 0;
        data[i] += otherValue;
    }
}

void DynamicArray::subtract(const DynamicArray& other) {
    for (int i = 0; i < size; i++) {
        int otherValue = (i < other.size) ? other.data[i] : 0;
        data[i] -= otherValue;
    }
}
