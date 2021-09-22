#ifndef search_hpp
#define search_hpp
#include <vector>
#include "data.hpp"

#pragma once

class Search
{
    public:
        Search(){}
        ~Search(){}

        int binarySearch(std::vector<Data>, Data);
        int binarySearch(std::vector<Data>, Data, int, int);
};

#endif