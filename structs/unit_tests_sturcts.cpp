#include "bin_heap_min.cpp"
#include "DSU.cpp"
#include "dynamic_array.cpp"
#include "graph.cpp"
#include "hash_table.cpp"
#include "list.cpp"
#include "red_black_tree.cpp"
#include <memory>
#include <type_traits>
#include <vector>

bool test_bin_heap_construct() {
    vector <int> inp = {329, 457, 839, 436, 720, 335};
    Bin_heap help(inp);
    vector <int> ans, expect;
    expect = inp;
    sort(expect.begin(), expect.end());
    for (int i = 0; i < inp.size(); ++i)
    {
        ans.push_back(help.get_min());
    }
    return (ans == expect);
}

bool test_bin_heap_fill() {
    vector <int> inp = {329, 457, 839, 436, 720, 335};
    Bin_heap help(inp);
    vector <int> ans, expect;
    expect = inp;
    expect.push_back(0);
    sort(expect.begin(), expect.end());
    vector<int> tmp = {0};
    help.fill(tmp);
    for (int i = 0; i < inp.size() + 1; ++i)
    {
        ans.push_back(help.get_min());
    }
    return (ans == expect);
}
bool test_bin_heap_insert() {
    vector <int> inp = {329, 457, 839, 436, 720, 335};
    Bin_heap help(inp);
    vector <int> ans, expect;
    expect = inp;
    expect.push_back(0);
    sort(expect.begin(), expect.end());
    help.insert(0);
    for (int i = 0; i < inp.size() + 1; ++i)
    {
        ans.push_back(help.get_min());
    }
    return (ans == expect);
} 

bool test_dsu_make_set() {
    DSU<int> help(4);
    help.make_set(3);
    return true;
}

bool test_dsu_find_set() {
    DSU<int> help(4);
    help.make_set(3);
    help.make_set(2);
    return help.find_set(3);
}

bool test_dsu_union_sets() {
    DSU<int> help(4);
    help.make_set(3);
    help.make_set(2);
    help.union_sets(3, 2);
    return help.find_set(3);
}

bool test_dynamic_array() {
    dynamic_array<int> help1();
    dynamic_array<int> help2(3);
    dynamic_array<int> help3(help2);
    return true;
}

bool test_dynamic_array_resize() {
    dynamic_array<int> help(3);
    help.resize(4);
    help.resize(0);
    help.size();
    return true;
}

bool test_dynamic_array_push_back() {
    dynamic_array<int> help(3);
    help.push_back(1);
    help.push_back(1);
    help.push_back(1);
    help.resize(2);
    dynamic_array<int> * arr = new dynamic_array<int>();
    arr->push_back(42);
    return true;
}

int main() {
    cout << "Test_heap_bin_construct: " << test_bin_heap_construct() << endl;
    cout << "Test_heap_bin_fill: " << test_bin_heap_fill() << endl;
    cout << "Test_heap_bin_insert: " << test_bin_heap_insert() << endl;
    cout << "Test_dsu_make_set: " << test_dsu_make_set() << endl;
    cout << "Test_dsu_find_set: " << test_dsu_find_set() << endl;
    cout << "Test_dsu_union_sets: " << test_dsu_union_sets() << endl;
    cout << "Test_dynamic_array: " << test_dynamic_array() << endl;
    cout << "Test_dynamic_resize: " << test_dynamic_array() << endl;
    cout << "Test_dynamic_push_back: " << test_dynamic_array() << endl;
    return 0;
}