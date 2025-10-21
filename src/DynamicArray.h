/*
 * DynamicArray.h
 *
 *  Created on: Oct 21, 2025
 *      Author: cyberdemon
 */

#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_

class DynamicArray {
private:
    int* data;
    int size;

public:
    DynamicArray(int arraySize);
    DynamicArray(const DynamicArray& other);
    ~DynamicArray();

    void print() const;
    bool setValue(int index, int value);
    bool getValue(int index, int& value) const;
    void append(int value);
    void add(const DynamicArray& other);
    void subtract(const DynamicArray& other);
    int getSize() const { return size; }
};
#endif /* DYNAMICARRAY_H_ */
