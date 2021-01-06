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
        /*start = new _list;
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
        }*/
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
        /*if (cur->elem == elem)
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
            T el = cur->elem;
            delete cur;
            return el;
        }
        else
        {
            cerr << "Warning there is nothing to pop\n";
            return 0;
        }*/
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