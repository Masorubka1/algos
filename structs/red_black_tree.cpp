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

    Node<T> *searchTreeHelper(Node<T> *node, T key) {
        if (node == TNULL) {
            return nullptr;
        }
        if (key == node->data) {
            return node;
        }
        if (key < node->data) {
            return this->searchTreeHelper(node->left, key);
        }
        return this->searchTreeHelper(node->right, key);
    }

    void initializeNULLNode(Node<T> *node, Node<T> *parent) {
        node->data = 0;
        node->parent = parent;
        node->left = nullptr;
        node->right = nullptr;
        node->color = 0;
    }
    void preOrderHelper(Node<T> *node) {
        if (node != TNULL) {
            // cout << node->data << " ";
            this->preOrderHelper(node->left);
            this->preOrderHelper(node->right);
        }
    }
    void inOrderHelper(Node<T> *node) {
        if (node != TNULL) {
            this->inOrderHelper(node->left);
            // cout << node->data << " ";
            this->inOrderHelper(node->right);
        }
    }
    void postOrderHelper(Node<T> *node) {
        if (node != TNULL) {
            this->postOrderHelper(node->left);
            this->postOrderHelper(node->right);
            // cout << node->data << " ";
        }
    }
    void inorder(Node<T>* cur, std::vector<Node<T>*> &tmp) {
        if (cur == TNULL) {
            return;
        }
        this->inorder(cur->left, tmp);
        tmp.push_back(cur);
        this->inorder(cur->right, tmp);
    }
    void sew_tree() {
        std::vector<Node<T>*> tmp;
        this->inorder(root, tmp);
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
    void deleteFix(Node<T> *x) {
        Node<T> *s;
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    this->leftRotate(x->parent);
                    s = x->parent->right;
                }
                if (s->left->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->right->color == 0) {
                        s->left->color = 0;
                        s->color = 1;
                        this->rightRotate(s);
                        s = x->parent->right;
                    }
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    this->leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    this->rightRotate(x->parent);
                    s = x->parent->left;
                }
                if (s->right->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->left->color == 0) {
                        s->right->color = 0;
                        s->color = 1;
                        this->leftRotate(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    this->rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }
    void rbTransplant(Node<T> *u, Node<T> *v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }
    void deleteNodeHelper(Node<T> *node, T key) {
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
            this->rbTransplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            this->rbTransplant(z, z->left);
        } else {
            y = this->minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                this->rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            this->rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0) {
            this->deleteFix(x);
        }
    }
    void insertFix(Node<T> *k) {
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
                        this->rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    this->leftRotate(k->parent->parent);
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
                        this->leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    this->rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }
    void printHelper(Node<T> *root) {
        if (root != TNULL) {
            this->printHelper(root->left);
            std::cout << root->data << " ";
            this->printHelper(root->right);
        }
    }

    bool is_bst(Node<T> *node, T minKey, T maxKey) {
        if (node == TNULL) {
            return true;
        }
        if (node->data < minKey || node->data > maxKey) {
            return false;
        }
        return this->is_bst(node->left, minKey, node->data - 1) &&
               this->is_bst(node->right, node->data + 1, maxKey);
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
        this->sew_tree();
        Node<T> *min = this->minimum(this->getRoot());
        Node<T> *max = this->maximum(this->getRoot());
        Node<T> *tmp;
        while (min != max) {
            tmp = min;
            min = min->next;
            delete tmp;
        }
        delete max;
        delete TNULL;
    }
    Node<T> *searchTree(T k) {
        return this->searchTreeHelper(this->root, k);
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
    Node<T> *getRoot() {
        return this->root;
    }

    void preorder() {
        this->preOrderHelper(this->root);
    }
    void inorder() {
        this->inOrderHelper(this->root);
    }
    void postorder() {
        this->postOrderHelper(this->root);
    }
    void leftRotate(Node<T> *x) {
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
    void rightRotate(Node<T> *x) {
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
        this->insertFix(node);
    }
    void Sew() {
        this->sew_tree();
    }
    void deleteNode(T data) {
        this->deleteNodeHelper(this->root, data);
    }
    void printTree() {
        this->printHelper(this->root);
    }

    bool isBST() {
        return is_bst(
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
