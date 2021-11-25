/*
 *
 * hash map file
 * hash.cpp
 * Emiliano Cabrera A01025453, Do Hyun Nam A01025276
 * 
 */

#include <vector>
#include <iostream>

template <class Key, class Val>
class Hash{
    private:
        int _capacity = 0;

        std::vector<std::vector<std::pair<Key, Val>>> _values;

        int hashFunction(Key) const;

    public:
        Hash(int);
        ~Hash();
        int capacity() const;

        void put(Key,Val);
        Val get(Key);
        void deleteVal(Key);
        
    template <typename Kn, typename Vn>
    friend std::ostream & operator <<(std::ostream & os, const Hash<Kn,Vn> & hm);
};

template <class Key, class Val>
int Hash<Key,Val>::hashFunction(Key k) const{
    return k % this-> _capacity;
}

template <class Key, class Val>
Hash<Key,Val>::Hash(int cap){
    this-> _capacity = cap;
    this-> _values = std::vector<std::vector<std::pair<Key,Val>>>(cap);
}

template <class Key, class Val>
Hash<Key,Val>::~Hash(){
    delete this-> _status;
    delete this-> _values;
}

template <class Key, class Val>
int Hash<Key,Val>::capacity() const{
    return this-> _capacity;
}

// input function, time complexity of O(1)
template <class Key, class Val>
void Hash<Key,Val>::put(Key k, Val v){
    int index = hashFunction(k);

    this->_values.at(index).push_back(std::make_pair(k,v));
}

// extraction function, time complexity of O(n)
template <class Key, class Val>
Val Hash<Key,Val>::get(Key k){
    int index = hashFunction(k), i;
    bool flag = false;

    for(i = 0; i < this->_values[index].size(); i++){
        if(this->_values[index][i].first == k){
            flag = true;
            break;
        }
    }

    if(flag) return this->_values.at(index).at(i).first;
    return -404;
}

//deletion function, time complexity of O(n)
template <class Key, class Val>
void Hash<Key,Val>::deleteVal(Key k){
    int index = hashFunction(k), i;
    bool flag = false;

    for(i = 0; i < this->_values[index].size(); i++){
        if(this->_values[index][i].first == k){
            flag = true;
            break;
        }
    }

    if(flag) this->_values.at(index).erase(_values.at(index).begin() + i);
}