#include <bits/stdc++.h>

#define N 300001
#pragma once

template <class T>
class DSU {
 public:
    explicit DSU(int n = N) {
        this->parent.resize(n);
        for (int i = 0; i < n; ++i) {
            this->parent[i] = i;
        }
        this->rank.resize(n);
    }
    ~DSU() {
        this->parent.clear();
        this->rank.clear();
    }

    int find_set(int v) {
        if (v == this->parent[v]) {
            return v;
        }
        return this->parent[v] = this->find_set(this->parent[v]);
    }

    void make_set(int v) {
        this->parent[v] = v;
        this->rank[v] = 0;
    }
    void union_sets(int a, int b) {
        a = this->find_set(a);
        b = this->find_set(b);
        if (a != b) {
            if (this->rank[a] < this->rank[b]) {
                std::swap(a, b);
            }
            this->parent[b] = a;
            if (this->rank[a] == this->rank[b]) {
                ++this->rank[a];
            }
        }
    }

 private:
    std::vector<int> parent;
    std::vector<int> rank;
};
