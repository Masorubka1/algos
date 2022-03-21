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
        start = nullptr;
    }
    void push(T elem)
    {
        _list* cur = start;
        _list* prev = nullptr;
        if (start == nullptr)
        {
            start = new _list;
            start->elem = elem;
            start->next = nullptr;
            start->prev = nullptr;
            capacity++;
            return;
        }
        while (cur != nullptr)
        {
            prev = cur;
            cur = cur->next;
        }
        cur = new _list;
        cur->elem = elem;
        prev->next = cur;
        cur->prev = prev;
        capacity++;
    }
    T pop()
    {
        _list* cur = start;
        _list* prev = nullptr;
        while (cur->next != nullptr)
        {
            prev = cur;
            cur = cur->next;
        }
        if (prev == nullptr)
        {
            start = nullptr;
        }
        T el = cur->elem;
        if (prev != nullptr)
            prev->next = nullptr;
        capacity--;
        return el;
    }
    void reverse()
    {
        if (start == nullptr)
        {
            return;
        }
        struct _list* curr;
        struct _list* next;
        struct _list* prev = nullptr;
        curr = start;
        while(curr)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        start = prev;
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
            else if (capacity > 0)
            {
                q.pop();
                capacity--;
            }
        }
        while (!q.empty());
    }
private:
    _list* start;
    int capacity;
};