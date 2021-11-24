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

        std::vector<std::vector<std::pair<Key,Val>>> _values;

        int hashFunction(Key) const;

    public:
        Hash(int);
        ~Hash();
        int capacity() const;

        void put(Key,Val);
        Val get(Key);
        
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
    delete this-> _keys;
    delete this-> _values;
}

template <class Key, class Val>
int Hash<Key,Val>::capacity() const{
    return this-> _capacity;
}

template <class Key, class Val>
void Hash<Key,Val>::put(Key k, Val v){
    int index = hashFunction(k);

    this->_values.at(index).push_back(std::make_pair(k,v)); // doesn't work
    //                     ^--- does not detect a vector from here. It does not allow function calls after the first access operator, be it .at() or [ ].
}

template <class Key, class Val>
Val Hash<Key,Val>::get(Key k){ // doesn't work
    int index = hashFunction(k), int_index = 0;

    for(int i = 0; i < this-> _keys[index].size(); i++){
        if(this-> _keys[index][i] == k) int_index = i;
        //                    ^--- does not detect a vector from here. It does not allow function calls after the first access operator, be it .at() or [ ].
    }

    return this->_values.at(index).at(int_index).first;
    //                            ^--- does not detect a vector from here. It does not allow function calls after the first access operator, be it .at() or [ ].
}