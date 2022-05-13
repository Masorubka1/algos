#include <bits/stdc++.h>
#pragma once

using namespace std;

void merge(vector <int> &a, int l, int r) {
    int mid = (l + r) / 2;
    vector <int> ans;
    int i = l;
    int j = mid;
    while (i < mid && j < r) {
        if (a[i] <= a[j]) {
            ans.push_back(a[i]);
            ++i;
        } else {
            ans.push_back(a[j]);
            ++j;
        }
    }
    while (i < mid) {
        ans.push_back(a[i]);
        ++i;
    }
    while (j < r) {
        ans.push_back(a[j]);
        ++j;
    }
    for (int i = l; i < r; ++i) {
        a[i] = ans[i - l];
    }
}

void merge_sort(vector <int> &a, int l, int r) {
    if (l + 1 == r) {
        return;
    }
    merge_sort(a, l, (l + r) / 2);
    merge_sort(a, (r + l) / 2, r);
    merge(a, l, r);
}

/*int main()
{
    vector <int> a = {329, 457, 839, 436, 720, 335};
    merge_sort(a, 0, a.size());
    for (int i = 0; i < a.size(); ++i)
    {
        cout << a[i] << " ";
    }
}*/
