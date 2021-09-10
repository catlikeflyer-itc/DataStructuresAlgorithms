#include <iostream>
#include <vector>
using namespace std;

int vectsum(vector<int> numVect){
    if (numVect.size() <= 1){
        return numVect[0];
    }
    else {
        vector<int> slice(numVect.begin() + 1, numVect.begin()+numVect.size());
        return numVect[0] + vectsum(slice);
    }
}

int main()
{
    vector<int> vec1 = {1, 3, 42, 234, 5, 3, 23};
    cout << vectsum(vec1) << endl;

    return 0;
}