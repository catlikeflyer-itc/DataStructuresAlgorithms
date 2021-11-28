#include <iostream>
#include "array.h"

template <typename T>
Array<T>::Array(int size) 
{
    maxSize = size;
    pData = new T [maxSize];
}

template <typename T>
Array<T>::~Array(void) 
{
    delete [] pData;  // Delete the spaces
}

template <typename T>
bool Array<T>::setData(int pos, T data) 
{
    if (pos < 0 || pos >= maxSize) // if not exists
        return false;
    pData[pos] = data;
    return true;
}

template <typename T>
bool Array<T>::getData(int pos, T &data) 
{
    if (pos < 0 || pos >= maxSize)
        return false;
    data = pData[pos];
    return true;
}

