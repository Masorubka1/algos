#include <bits/stdc++.h>

using namespace std;

int partition(vector <int> &a, int l, int r)
{
    int ind_cmp = (l + r) / 2;//rand() % (r - l);
    int i = l;
    int j = r;
    while (i <= j)
    {
        while (a[i] < a[ind_cmp])
        {
            ++i;
        }
        while (a[j] > a[ind_cmp])
        {
            --j;
        }
        if (i >= j)
            break;
        swap(a[i], a[j]);
        i++;
        j--;
    }
    return j;
}

void quick_sort(vector <int> &a, int l, int r)
{
    if (l >= r)
        return;
    int ind_cmp = partition(a, l, r);
    quick_sort(a, l, ind_cmp);
    quick_sort(a, ind_cmp + 1, r);
}

int main()
{
    srand(time(NULL));
    vector <int> a = {329, 457, 839, 436, 720, 335};
    quick_sort(a, 0, a.size() - 1);
    for (int i = 0; i < a.size(); ++i)
    {
        cout << a[i] << " ";
    }
}
