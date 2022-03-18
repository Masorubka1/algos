#include "bin_heap_min.cpp"
#include "DSU.cpp"
#include "dynamic_array.cpp"
#include "graph.cpp"
#include "hash_table.cpp"
#include "list.cpp"
#include "red_black_tree.cpp"

bool test_bin_heap_construct() {
    vector <int> inp = {329, 457, 839, 436, 720, 335};
    Bin_heap help(inp);
    vector <int> ans(inp.size()), expect;
    expect = inp;
    sort(expect.begin(), expect.end());
    for (int i = 0; i < inp.size(); ++i)
    {
        ans[i] = help.get_min();
    }
    return (ans == expect);
}

bool test_bin_heap_fill() {
    vector <int> inp = {329, 457, 839, 436, 720, 335};
    Bin_heap help(inp);
    vector <int> ans(inp.size()), expect;
    expect = inp;
    sort(expect.begin(), expect.end());
    for (int i = 0; i < inp.size(); ++i)
    {
        ans[i] = help.get_min();
    }
    return (ans == expect);
} 

int main() {
    return 0;
}