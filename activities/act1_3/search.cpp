#include "search.hpp"

int Search::binarySearch(std::vector<Data> item_vector, Data value){
        int size = item_vector.size() - 1;
        return Search::binarySearch(item_vector, value, 0, size);
    }

int Search::binarySearch(std::vector<Data> item_vector, Data value, int lower_bound, int upper_bound){
    if (lower_bound >= upper_bound){
        return -1;
    }
    else{
        int middle = (lower_bound + upper_bound)/2;
            
        if (item_vector[middle] == value){
            return middle;
        }
        else if (value < item_vector[middle]){
            return Search::binarySearch(item_vector, value, lower_bound, middle);
        }
        else{
            return Search::binarySearch(item_vector, value, middle + 1, upper_bound);
        }
    }
}