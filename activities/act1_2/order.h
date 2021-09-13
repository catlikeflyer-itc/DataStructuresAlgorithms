/**
 * @file order.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef Order_h
#define Order_h
#include <iostream>
#include <vector>

template <class T>
class Order
{
    public:
        static std::vector<T> quickSort(std::vector<T>, bool(*)(T,T));
        static std::vector<T> quickSort(std::vector<T>, int, int, bool(*)(T,T));
    
        static bool asc(T,T);
        static bool desc(T,T);
};

template <class T>
bool Order<T>::asc(T a, T b)
{
    return a < b;
}

template <class T>
bool Order<T>::desc(T a, T b)
{
    return a > b;
}

template <class T>
std::vector<T> Order<T>::quickSort(std::vector<T> v, bool comp (T, T))
{
    int size = (int) v.size() - 1;
    return quickSort(v, 0, size, comp);
}

template <class T>
std::vector<T> Order<T>::quickSort(std::vector<T> v, int first, int last, bool comp (T, T))
{
    int left = first;
    int right = last;

    T pivot = v[first];
    
    if(first < last)
    {
        while(left < right)
        {
            while((left < right) && !compara(pivot, v[left])) left++; // <=
            while(compara(pivot, v[right]) ) right--; // >
            
            if(left < right)
            {
                std::swap(v[left], v[right]);
            }
        }
        
        std::swap(v[first], v[right]);
        
        v = quickSort(v, first, right-1, comp);
        v = quickSort(v, left, last, comp);
    }
    
    return v;
}

#endif