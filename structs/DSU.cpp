#include <bits/stdc++.h>

#define N 300001
#pragma once

template <class T>
class DSU {
 public:
    explicit DSU(int n = N) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
        rank.resize(n);
    }

    int find_set(int v) {
        if (v == parent[v]) {
            return v;
        }
        return parent[v] = this->find_set(parent[v]);
    }

    void make_set(int v) {
        parent[v] = v;
        rank[v] = 0;
    }
    void union_sets(int a, int b) {
        a = this->find_set(a);
        b = this->find_set(b);
        if (a != b) {
            if (rank[a] < rank[b]) {
                std::swap(a, b);
            }
            parent[b] = a;
            if (rank[a] == rank[b]) {
                ++rank[a];
            }
        }
    }

 private:
    std::vector<int> parent;
    std::vector<int> rank;
};
