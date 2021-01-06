#include <bits/stdc++.h>

using namespace std;

#define N 300001

template <class T>
class DSU
{
public:
    DSU(int n = N)
    {
        parent.resize(n);
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
        rank.resize(n);
    }
    void make_set(int v)
    {
        parent[v] = v;
        rank[v] = 0;
    }
    int find_set(int v)
    {
        if (v == parent[v])
        {
            return v;
        }
        return parent[v] = find_set(parent[v]);
    }
    void union_sets(int a, int b)
    {
        a = find_set(a);
        b = find_set(b);
        if (a != b)
        {
            if (rank[a] < rank[b])
            {
                swap(a, b);
            }
            parent[b] = a;
            if (rank[a] == rank[b])
            {
                ++rank[a];
            }
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
};