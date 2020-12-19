#include <bits/stdc++.h>

using namespace std;

template <class T>
class black_red_tree
{
    // 0 - black
    // 1 - red
    typedef struct node
    {
        node* left;
        node* right;
        node* parent;
        node* next;
        node* prev;
        int typ;
        T elem;
    } node;
public:
    //set <T> a;
    black_red_tree()
    {
        root = new node;
        root->elem = 0;
        root->parent = nullptr;
        root->left = nullptr;
        root->right = nullptr;
        root->next = nullptr;
        root->right = nullptr;
        root->typ = 0;
    }
    ~black_red_tree()
    {
        destroy_tree(root);
    }
    node* search(T key)
    {
        node* current = root;
        while(current != nullptr)
        {
            if(key < current->elem)
            {
                return current;
            }
            else
            {
                current = (key < current->elem) ? current->left : current->right;
            }
        }
        return nullptr;
    }
    void del_node(T key)
    {
        node* cur = search(key);
        if (cur == nullptr)
        {
            return;
        }
        delete_node(cur);
    }
    void Print()
    {
        print();
        //cout << endl;
    }
    void inorder(node* cur, vector <node*> &tmp)
    {
        if(cur == NULL)
        {
            return;
        }
        inorder(cur->left, tmp);
        tmp.push_back(cur);
        inorder(cur->right, tmp);
    }
    void sew_tree()
    {
        vector <node*> tmp;
        inorder(root, tmp);
        if (tmp.size() == 1)
        {
            tmp[0]->next = tmp[0];
            tmp[0]->prev = tmp[0];
        }
        tmp[0]->prev = tmp[tmp.size() - 1];
        for (int i = 1; i < tmp.size(); ++i)
        {
            tmp[i - 1]->next = tmp[i];
            tmp[i]->prev = tmp[i - 1];
        }
        tmp.back()->next = tmp[0];
        cout << tmp.size() << endl;
    }
    void insert(T el)
    {
        if (root->elem == T(0))
        {
            root = new node;
            root->elem = el;
            root->parent = nullptr;
            root->left = nullptr;
            root->right = nullptr;
            root->typ = 0;
            return;
        }
        node *current, *parent, *x;
        current = root;
        parent = nullptr;
        while (current != nullptr)
        {
            if (el == current->elem)
            {
                return;
            }
            parent = current;
            if (el < current->elem)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        x = new node;
        x->elem = el;
        x->parent = parent;
        x->left = nullptr;
        x->right = nullptr;
        x->typ = 1;
        if(el < parent->elem)
        {
            parent->left = x;
        }
        else
        {
            parent->right = x;
        }
        insert_balance(x);
        sew_tree();
    }
    node* mini()
    {
        node* cur = root;
        while (cur->left != nullptr)
        {
            cur = cur->left;
        }
        return cur;
    }
    node* maxi()
    {
        node* cur = root;
        while (cur->right != nullptr)
        {
            cur = cur->right;
        }
        return cur;
    }
private:
    node* root;
    void print()
    {
        /*if (cur == nullptr)
        {
            return;
        }
        print(cur->left);
        cout << cur->elem << " ";
        print(cur->right);*/
        node* cur = mini();
        node* start = cur;
        while (cur->next != start)
        {
            cout << cur->elem << " ";
            cur = cur->next;
        }
        cout << cur->elem << endl;
    }
    void destroy_tree(node* leaf)
    {
        if (leaf->left)
        {
            destroy_tree(leaf->left);
        }
        if (leaf->right)
        {
            destroy_tree(leaf->right);
        }
        delete leaf;
    }
    void insert_balance(node* cur)
    {
        while (cur != root && cur->parent->typ == 1)
        {
            if (cur->parent == cur->parent->parent->left)
            {
                node* y = cur->parent->parent->right;
                if (y != nullptr && y->typ == 1)
                {
                    cur->parent->typ = 0;
                    y->typ = 0;
                    cur->parent->parent->typ = 1;
                    cur = cur->parent->parent;
                }
                else
                {
                    if (cur == cur->parent->right)
                    {
                        cur = cur->parent;
                        rotate_Left(cur);
                    }
                    cur->parent->typ = 0;
                    cur->parent->parent->typ = 1;
                    rotate_Right(cur->parent->parent);
                }
            }
            else
            {
                node* y = cur->parent->parent->left;
                if (y != nullptr && y->typ == 1)
                {
                    cur->parent->typ = 0;
                    y->typ = 0;
                    cur->parent->parent->typ = 1;
                    cur = cur->parent->parent;
                }
                else
                {
                    if (cur == cur->parent->left)
                    {
                        cur = cur->parent;
                        rotate_Right(cur);
                    }
                    cur->parent->typ = 0;
                    cur->parent->parent->typ = 1;
                    rotate_Left(cur->parent->parent);
                }
            }
        }
        root->typ = 0;
    }
    void rotate_Left(node* cur)
    {
        node* y = cur->right;
        cur->right = y->left;
        if (y->left != nullptr)
        {
            y->left->parent = cur;
        }
        if (y != nullptr)
        {
            y->parent = cur->parent;
        }
        if (cur->parent)
        {
            if (cur == cur->parent->left)
            {
                cur->parent->left = y;
            }
            else
            {
                cur->parent->right = y;
            }
        }
        else
        {
            root = y;
        }
        y->left = cur;
        if (cur != nullptr)
        {
            cur->parent = y;
        }
    }
    void rotate_Right(node* cur)
    {
        node* y = cur->left;
        cur->left = y->right;
        if (y->right != nullptr)
        {
            y->right->parent = cur;
        }
        if (y != nullptr)
        {
            y->parent = cur->parent;
        }
        if (cur->parent)
        {
            if (cur == cur->parent->right)
            {
                cur->parent->right = y;
            }
            else
            {
                cur->parent->left = y;
            }
        }
        else
        {
            root = y;
        }
        y->right = cur;
        if (cur != nullptr)
        {
            cur->parent = y;
        }
    }
    void delete_balanse(node* cur)
    {
        while (cur != root && cur->typ == 0)
        {
            if (cur == cur->parent->left)
            {
                node* w = cur->parent->right;
                if (w->typ == 1) {
                    w->typ = 0;
                    cur->parent->typ = 1;
                    rotate_Left(cur->parent);
                    w = cur->parent->right;
                }
                if (w->left->typ == 0 && w->right->typ == 0)
                {
                    w->typ = 1;
                    cur = cur->parent;
                }
                else
                {
                    if (w->right->typ == 0)
                    {
                        w->left->typ = 0;
                        w->typ = 1;
                        rotate_Right(w);
                        w = cur->parent->right;
                    }
                    w->typ = cur->parent->typ;
                    cur->parent->typ = 0;
                    w->right->typ = 0;
                    rotate_Left(cur->parent);
                    cur = root;
                }
            }
            else
            {
                node* w = cur->parent->left;
                if (w->typ == 1)
                {
                    w->typ = 0;
                    cur->parent->typ = 0;
                    rotate_Right(cur->parent);
                    w = cur->parent->left;
                }
                if (w->right->typ == 0 && w->left->typ == 0)
                {
                    w->typ = 1;
                    cur = cur->parent;
                }
                else
                {
                    if (w->left->typ == 0)
                    {
                        w->right->typ = 0;
                        w->typ = 1;
                        rotate_Left(w);
                        w = cur->parent->left;
                    }
                    w->typ = cur->parent->typ;
                    cur->parent->typ = 0;
                    w->left->typ = 0;
                    rotate_Right(cur->parent);
                    cur = root;
                }
            }
        }
        cur->typ = 0;
    }
    void delete_node(node* cur)
    {
        node* x;
        node* y;
        if (!cur || cur == nullptr)
        {
            return;
        }
        if (cur->left == nullptr || cur->right == nullptr)
        {
            y = cur;
        }
        else
        {
            y = cur->right;
            while (y->left != nullptr)
            {
                y = y->left;
            }
        }
        if (y->left != nullptr)
        {
            x = y->left;
        }
        else
        {
            x = y->right;
        }
        x->parent = y->parent;
        if (y->parent)
        {
            if (y == y->parent->left)
            {
                y->parent->left = x;
            }
            else
            {
                y->parent->right = x;
            }
        }
        else
        {
            root = x;
        }
        if (y != cur)
        {
            cur->elem = y->elem;
        }
        if (y->typ == 0)
        {
            delete_balanse(x);
        }
        delete y;
    }
};


int main()
{
    black_red_tree<int> a;
    set <int> q;
    vector <int>  arr = {2 ,1, 5, 3, 10, 20, 19, 7, 4, 9};
    for (int i = 0; i < arr.size(); ++i)
    {
        q.insert(arr[i]);
        a.insert(arr[i]);
    }
    a.Print();
    for (auto i : q)
    {
        cout << i << " ";
    }
    cout << endl;
    //a.~black_red_tree(); se?
    return 0;
}