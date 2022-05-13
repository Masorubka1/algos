#include <bits/stdc++.h>
#pragma once

using namespace std;

void radix_sort(vector <int> &a, int len) {
    if (a[0] / static_cast<int>(pow(10, len)) == 0) {
        return;
    }
    vector <vector <int>> cnt(10);
    for (int i = 0; i < a.size(); ++i) {
        int num = a[i];
        int last_need = (num / static_cast<int>(pow(10, len))) % 10;
        cnt[last_need].push_back(i);
    }
    vector <int> help;
    int i = 0;
    while (i < 10) {
        int j = 0;
        while  (j < cnt[i].size()) {
            int ind = cnt[i][j];
            help.push_back(a[ind]);
            j++;
        }
        i++;
    }
    a = help;
    radix_sort(a, len + 1);
}

/*int main()
{
    vector <int> a = {329, 457, 657, 839, 436, 720, 335};
    radix_sort(a, 0);
    for (int i = 0; i < a.size(); ++i)
    {
        cout << a[i] << " ";
    }
}*/
