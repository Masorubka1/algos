#include <bits/stdc++.h>

using namespace std;

template <class T>
class List
{
public:
    struct _list
    {
        T elem;
        _list* next;
        _list* prev;
    };
    List(int n = 0)
    {
        start = new _list;
        _list* cur = start;
        _list* prev = nullptr;
        capacity = 1;
        for (int i = 0; i < n - 1; ++i)
        {
            cur->next = new _list;
            cur->prev = prev;
            prev= cur;
            cur = cur->next;
            capacity++;
        }
    }
    void push(T elem)
    {
        _list* cur = start;
        _list* prev = nullptr;
        while (cur != nullptr || cur->elem == nullptr)
        {
            prev = cur;
            cur = cur->next;
        }
        if (cur == nullptr)
        {
            cur = new _list;
            cur->elem = elem;
            prev-> next = cur;
            cur->prev = prev;
            capacity++;
        }
        else
        {
            cur->elem = elem;
        }
    }
    void pop(T elem)
    {
        _list* cur = start;
        while (cur->elem != elem && cur != nullptr)
        {
            cur = cur->next;
        }
        if (cur->elem == elem)
        {
            if (capacity == 1)
            {
                start = nullptr;
                capacity--;
            }
            if (cur->prev == nullptr)
            {
                start = cur->next;
            }
            else if (cur->next == nullptr)
            {
                cur->prev->next = nullptr;
            }
            else
            {
                cur->prev->next = cur->next;
                cur->next->prev = cur->prev;
            }
            delete cur;
        }
        else
        {
            cerr << "Warning there is nothing to pop\n";
        }

    }
    ~List()
    {
        stack <_list*> q;
        _list* cur = start;
        do
        {
            if (cur != nullptr)
            {
                q.push(cur);
                cur = cur->next;
            }
            else
            {
                q.pop();
                capacity--;
            }
        }
        while (!q.empty())
    }
private:
    _list start;
    int capacity;
};