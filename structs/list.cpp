#include <bits/stdc++.h>
#include <cstring>

template <class T>
class List {
 public:
    struct _list {
        T elem;
        _list *next;
        ~_list() { delete next; next = nullptr;}
    };

    explicit List(int n = 0) {
        start = nullptr;
        cur = nullptr;
        capacity = n;
    }
    ~List() {
        delete this->start;
    }

    void push(T elem) {
        if (this->capacity == 0) {
            this->start = new _list;
            this->start->elem = elem;
            this->start->next = nullptr;
            this->capacity = 1;
            this->cur = this->start;
            return;
        }
        _list *prev = this->cur;
        this->cur = new _list;
        this->cur->elem = elem;
        prev->next = cur;
        this->capacity++;
    }
    void reverse() {
        if (this->capacity <= 1) {
            return;
        }
        _list *curr = this->start;
        _list *prev = nullptr;
        while (curr != nullptr) {
            std::swap(prev, curr->next);
            std::swap(prev, curr);
        }
        this->start = prev;
    }

    T pop() {
        if (this->capacity == 0) {
            throw "-1 elem left";
            return 0;
        }
        T el = this->cur->elem;
        _list *ans = nullptr;
        if (this->capacity == 1) {
            this->start = nullptr;
        } else {
            _list *tmp = this->start;
            while (tmp->next != this->cur) {
                tmp = tmp->next;
            }
            tmp->next = nullptr;
            ans = tmp;
        }
        if (ans != nullptr) {
            delete ans->next;
        }
        this->capacity--;
        this->cur = ans;
        return el;
    }

 private:
    _list *start;
    _list *cur;
    int capacity;
};
