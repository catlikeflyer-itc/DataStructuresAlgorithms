// Template declaration
template <typename T>
class Array {
    private: 
        T *pData;
        int maxSize;

    public: 
        Array(int size=100);
        ~Array(void);
        bool setData(int pos, T data);
        bool getData(int pos, T &data);
};