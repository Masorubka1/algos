#include "heap_sort.cpp"
#include "merge_sort.cpp"
#include "quick_sort.cpp"
#include "radix_sort.cpp"
#include "heap_sort.cpp"
#include <bits/stdc++.h>

using namespace std;

vector <int> test_heap_sort(vector <int> &inp) {
    Bin_heap help(inp);
    vector <int> ans(inp.size());
    for (int i = 0; i < inp.size(); ++i)
    {
        ans[i] = help.get_min();
    }
    return ans;
}

vector <int> test_merge_sort(vector <int> &inp) {
    vector<int> ans = inp;
    merge_sort(ans, 0, ans.size());
    return ans;
}

vector <int> test_quick_sort(vector <int> &inp) {
    vector <int> ans = inp;
    quick_sort(ans, 0, ans.size() - 1);
    return ans;
}

vector <int> test_radix_sort(vector <int> &inp) {
    vector <int> ans = inp;
    radix_sort(ans, 0);
    return ans;
}

int main(){
    vector <int> a = {329, 457, 839, 436, 720, 335};
    vector <int> expect = a;
    sort(expect.begin(), expect.end());
    cout << "heap_sort: " << (test_heap_sort(a) == expect) << endl;
    cout << "merge_sort: " << (test_merge_sort(a) == expect) << endl;
    cout << "radix_sort: " << (test_heap_sort(a) == expect) << endl;
    cout << "quick_sort: " << (test_heap_sort(a) == expect) << endl;
    for (auto i : expect) {
        cout << i << " ";
    }
    cout << endl;
}
