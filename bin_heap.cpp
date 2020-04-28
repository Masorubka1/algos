#include <bits/stdc++.h>

using namespace std;

class Bin_heap
{
    //on_min
    vector <int> a;
    Bin_heap(vector <int> &inp)
    {
        a.resize(inp.size());
        a[0] = inp[0];
        for (int i = 1; i < inp.size(); ++i)
        {
            a[i] = inp[i];
            shift_up(i);
        }
    }
    void shift_down(int i)
    {
        while (2 * i + 1 < a.size())
        {
            int l = 2 * i + 1;
            int r = 2 * i + 2;
            int help = l;
            if (r + 1 < a.size() && a[l] >= a[r])
            {
                help = r;
            }
            if (a[i] < a[help])
            {
                break;
            }
            swap(a[i], a[help]);
            i = help;
        }
    }
    void shift_up(int i)
    {
        while (a[i] < a[(i - 1) / 2])
        {
            swap(a[i], a[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
    int get_min()
    {
        int min = a[0];
        swap(a[a.size() - 1], a[0]);
        a.resize(a.size() - 1);
        shift_down(0);
        return min;
    }
    void insert(int el)
    {
        a.resize(a.size() + 1);
        a[a.size() - 1] = el;
        shift_up(a.size() - 1);
    }
};

int main()
{
    vector <int> a = {329, 457, 839, 436, 720, 335};
    Bin_heap help(a);
    for (int i = 0; i < a.size(); ++i)
    {
        cout << help.a[i] << " ";
    }
}
