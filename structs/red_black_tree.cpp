#include <bits/stdc++.h>

template <class T>
struct Node {
    Node *left;
    Node *right;
    Node *parent;
    Node *next;
    Node *prev;
    int color;
    T data;
};

template <class T>
class RedBlackTree {
 private:
    Node<T> *root;
    Node<T> *TNULL;

    Node<T> *_search_tree(Node<T> *node, T key) {
        if (node == TNULL) {
            return nullptr;
        }
        if (key == node->data) {
            return node;
        }
        if (key < node->data) {
            return this->_search_tree(node->left, key);
        }
        return this->_search_tree(node->right, key);
    }

    void _initialize_null_node(Node<T> *node, Node<T> *parent) {
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = 0;
    }
    void _preorder(Node<T> *node) {
        if (node != TNULL) {
            // cout << node->data << " ";
            this->_preorder(node->left);
            this->_preerder(node->right);
        }
    }
    void _inorder(Node<T> *node) {
        if (node != TNULL) {
            this->_inorder(node->left);
            // cout << node->data << " ";
            this->_inorder(node->right);
        }
    }
    void _postorder(Node<T> *node) {
        if (node != TNULL) {
            this->_postorder(node->left);
            this->_postorder(node->right);
            // cout << node->data << " ";
        }
    }
    void _inorder(Node<T>* cur, std::vector<Node<T>*> &tmp) {
        if (cur == TNULL) {
            return;
        }
        this->_inorder(cur->left, tmp);
        tmp.push_back(cur);
        this->_inorder(cur->right, tmp);
    }
    void _sew_tree() {
        std::vector<Node<T>*> tmp;
        this->_inorder(root, tmp);
        if (tmp.size() == 1) {
            tmp[0]->next = tmp[0];
            tmp[0]->prev = tmp[0];
        }
        tmp[0]->prev = tmp[tmp.size() - 1];
        for (int i = 1; i < tmp.size(); ++i) {
            tmp[i - 1]->next = tmp[i];
            tmp[i]->prev = tmp[i - 1];
        }
        tmp.back()->next = tmp[0];
    }
    void _delete(Node<T> *x) {
        Node<T> *s;
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    this->_left_rotate(x->parent);
                    s = x->parent->right;
                }
                if (s->left->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->right->color == 0) {
                        s->left->color = 0;
                        s->color = 1;
                        this->_right_rotate(s);
                        s = x->parent->right;
                    }
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    this->_left_rotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    this->_right_rotate(x->parent);
                    s = x->parent->left;
                }
                if (s->right->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->left->color == 0) {
                        s->right->color = 0;
                        s->color = 1;
                        this->_left_rotate(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    this->_right_rotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }
    void _rb_transplant(Node<T> *u, Node<T> *v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }
    void _delete_node(Node<T> *node, T key) {
        Node<T> *z = TNULL;
        Node<T> *x;
        Node<T> *y;
        while (node != TNULL) {
            if (node->data == key) {
                z = node;
            }
            if (node->data <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }
        if (z == TNULL) {
            return;
        }
        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            this->_rb_transplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            this->_rb_transplant(z, z->left);
        } else {
            y = this->minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                this->_rb_transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            this->_rb_transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0) {
            this->_delete(x);
        }
    }
    void _insert(Node<T> *k) {
        Node<T> *u;
        while (k->parent->color == 1) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        this->_right_rotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    this->_left_rotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;
                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        this->_left_rotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    this->_right_rotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }
    void _print(Node<T> *root) {
        if (root != TNULL) {
            this->_print(root->left);
            std::cout << root->data << " ";
            this->_print(root->right);
        }
    }
    void _left_rotate(Node<T> *x) {
        Node<T> *y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
    void _right_rotate(Node<T> *x) {
        Node<T> *y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    bool _is_bst(Node<T> *node, T minKey, T maxKey) {
        if (node == TNULL) {
            return true;
        }
        if (node->data < minKey || node->data > maxKey) {
            return false;
        }
        return this->_is_bst(node->left, minKey, node->data - 1) &&
               this->_is_bst(node->right, node->data + 1, maxKey);
    }

 public:
    RedBlackTree() {
        TNULL = new Node<T>;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        TNULL->next = nullptr;
        TNULL->prev = nullptr;
        root = TNULL;
    }
    ~RedBlackTree<T>() {
        this->_sew_tree();
        Node<T> *min = this->minimum(this->get_root());
        Node<T> *max = this->maximum(this->get_root());
        Node<T> *tmp;
        while (min != max) {
            tmp = min;
            min = min->next;
            delete tmp;
        }
        delete max;
        delete TNULL;
    }
    Node<T> *search_tree(T k) {
        return this->_search_tree(this->root, k);
    }
    Node<T> *minimum(Node<T> *node) {
        while (node->left != TNULL) {
            node = node->left;
        }
        return node;
    }
    Node<T> *maximum(Node<T> *node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }
    Node<T> *successor(Node<T> *x) {
        if (x->right != TNULL) {
            return this->minimum(x->right);
        }
        Node<T> *y = x->parent;
        while (y != TNULL && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }
    Node<T> *predecessor(Node<T> *x) {
        if (x->left != TNULL) {
            return this->maximum(x->left);
        }
        Node<T> *y = x->parent;
        while (y != TNULL && x == y->left) {
            x = y;
            y = y->parent;
        }
        return y;
    }
    Node<T> *get_root() {
        return this->root;
    }

    void preorder() {
        this->_preorder(this->root);
    }
    void inorder() {
        this->_inorder(this->root);
    }
    void postorder() {
        this->_postorder(this->root);
    }
    void insert(T key) {
        Node<T> *node = new Node<T>;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;

        Node<T> *y = nullptr;
        Node<T> *x = this->root;
        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }
        if (node->parent == nullptr) {
            node->color = 0;
            return;
        }
        if (node->parent->parent == nullptr) {
            return;
        }
        this->_insert(node);
    }
    void sew() {
        this->_sew_tree();
    }
    void delete_node(T data) {
        this->_delete_node(this->root, data);
    }
    void print_tree() {
        this->_print(this->root);
    }

    bool is_bst() {
        return _is_bst(
            this->root,
            this->minimum(root)->data,
            this->maximum(root)->data);
    }
};

/*int main()
{
    RedBlackTree<int> bst = RedBlackTree<int>();
    vector<int> tmp = {55, 40, 65, 60, 75, 57};
    for (auto i : tmp) {
        bst.insert(i);
    }
    bst.Sew();
    bst.printTree();
    Node<int> *start = bst.minimum(bst.getRoot());
    Node<int> *finish = start->prev;
    while (start != finish)
    {
        cout << start->data << " ";
        start = start->next;
    }
}*/
