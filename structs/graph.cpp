#include <bits/stdc++.h>
#include "../structs/DSU.cpp"
#pragma once

using namespace std;

template <class T>
class Graph
{
public:
    int n, m;
    Graph();
    ~Graph();
    vector<int> paint(vector<int> &help);
    void FloydWarshall(vector<vector<int>> &help);
    void FordBellman(int v);
    void dijkstra(int v);
    void kruskal();
    void dfs(int v, vector <vector <int>> &g, vector <int> &used);
    vector<pair<int, int>> top_sort();

private:
    bool is_oriented;
    bool f;
    bool check_dif_color(int v, vector<int> &help);
    vector<pair<T, pair<int, int>>> G;
    vector<pair<T, pair<int, int>>> tree;
    vector<vector<T>> g;
};

template <class T>
vector<int> Graph<T>::paint(vector<int> &help)
{
    if (help.size() == 0)
    {
        f = 0;
    }
    if (help.size() != g.size())
    {
        for (int i = 1; i <= 5 && !f; ++i)
        {
            help.push_back(i);
            paint(help, 0);
            help.pop_back();
        }
    }
    while (!f && next_permutation(help.begin(), help.end()))
    {
        for (int i = 0; i < g.size() && !f; ++i)
        {
            f = check_dif_color(i + 1, help);
        }
    }
    if (f)
    {
        return help;
    }
}

template <class T>
bool Graph<T>::check_dif_color(int v, vector<int> &help)
{
    for (int i = 1; i < g.size(); ++i)
    {
        for (auto j : g[i])
        {
            if (help[i] == help[j])
            {
                return false;
            }
        }
    }
    return true;
}

template <class T>
void Graph<T>::FloydWarshall(vector<vector<int>> &matrix)
{
    for (int k = 0; k < matrix.size(); k++)
    {
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix.size(); j++)
            {
                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }
    return;
}

template <class T>
void Graph<T>::FordBellman(int v)
{
    vector<int> d(g.size(), 1e9);
    d[v] = 0;
    for (;;)
    {
        bool any = false;
        for (int j = 0; j < m; ++j)
        {
            if (d[g[j].a] < 1e9)
                if (d[g[j].b] > d[g[j].a] + g[j].cost)
                {
                    d[g[j].b] = d[g[j].a] + g[j].cost;
                    any = true;
                }
        }
        if (!any)
        {
            break;
        }
    }
    for (auto i : d)
    {
        cout << i << " ";
    }
    cout << endl;
}

template <class T>
void Graph<T>::dijkstra(int u)
{
    vector<int> dist(n, 1e9), p(n);
    dist[u] = 0;
    p[u] = u;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push(make_pair(0, u));
    while (!q.empty())
    {
        pair<int, int> u = q.top();
        q.pop();
        if (u.first > dist[u.second])
        {
            continue;
        }
        for (int i = 0; i < (int)g[u.second].size(); i++)
        {
            int v = g[u.second][i].second, len = g[u.second][i].first;
            if (dist[v] > dist[u.second] + len)
            {
                p[v] = u.second;
                dist[v] = dist[u.second] + len;
                q.push(make_pair(dist[v], v));
            }
        }
    }
}

template <class T>
void Graph<T>::kruskal()
{
    int i, uRep, vRep;
    DSU<T> a(G.size());
    sort(G.begin(), G.end());
    for (i = 0; i < G.size(); i++)
    {
        uRep = a.find_set(G[i].second.first);
        vRep = a.find_set(G[i].second.second);
        if (uRep != vRep)
        {
            tree.push_back(G[i]);
            a.union_set(uRep, vRep);
        }
    }
}

template <class T>
vector<pair<int, int>> Graph<T>::top_sort()
{
    vector<pair<int, int>> tout;
    int tim = 0;
    vector<int> used(g.size());
    for (int i = 0; i < g.size(); ++i)
    {
        if (!used[i])
        {
            Top_sort(g, used, tim, tout);
        }
    }
    return tout;
}

template <class T>
void Graph<T>::dfs(int v, vector <vector <int>> &g, vector <int> &used) {
    used[v] = 1;
    for (int i = 0; i < g[v].size(); ++i){
        if (!used[i])
            Graph<T>::dfs(i, g, used);
    }
}

void Top_sorted(int u, vector <vector <int>> &g, vector <int> &used, int tim, vector<pair<int, int>> &tout)
{
    used[u] = 1;
    for (auto v : g[u])
    {
        if (!used[v])
        {
            Top_sorted(v, g, used, tim + 1, tout);
        }
    }
    tout[u].second = u;
    tout[u].first = tim + 1;
}
