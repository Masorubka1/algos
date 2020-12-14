#include <bits/stdc++.h>

using namespace std;

template <typename T>
class Dianamic_array
{
private:
    T *a;
    int size;
    int capacity;
    void change_size(int len)
    {
        T *t = new T[len];
        for (int i = 0; i < min(size, len); ++i)
        {
            t[i] = a[i];
        }
        size = len;
        a = t;
    }
public:
    Dianamic_array::Dianamic_array(int len)
    {
        change_size(len);
    }
    ~Dianamic_array::Dianamic_array()
    {
        delete *a;
    }
    int Size()
    {
        return size;
    }
    void resize(int len)
    {
        change_size(len)
    };
    T get_item(int ind)
    {
        return a[ind];
    }
    void push_back(T elem)
    {
        change_size(size + 1);
        a[size] = elem;
    }
    void pop_back()
    {
        change_size(size - 1);
    }
};
