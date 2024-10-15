#include <iostream>
using namespace std;

template <typename Key, typename Value>
class Node
{
public:
    Key key;
    Value value;
    Node *left;
    Node *right;
    Node *p;
    int size;
    int color; // red=1, black=0

    Node()
    {
        color = 0;
        size = 1;
        left = NULL;
        right = NULL;
    }

    Node(Key k, Value v, int col)
    {
        key = k;
        value = v;
        color = col;
        size = 1;
        right = nullptr;
        left = nullptr;
        p = nullptr;
    }
};

template <typename K, typename V>
class RBTree
{
public:
    Node<K, V> *nil;
    Node<K, V> *root;
    int s;
    int count;

    RBTree()
    {
        nil = new Node<K, V>();
        nil->size = 0;
        root = nil;
        s = 0;
        count = 0; // for printk()
    }

    RBTree(K k[], V v[], int size)
    {
        count = 0;
        nil = new Node<K, V>();
        nil->size = 0;
        root = nil;
        for (int i = 0; i < size; i++)
        {
            insert(k[i], v[i]);
        }
    }

    ~RBTree()
    {
        deleteTree(root);
        delete nil;
    }

    RBTree(const RBTree &oldObj)
    {
        this->nil = new Node<K, V>();
        this->nil->size = 0;
        this->root = this->nil;
        this->root = copyHelper(oldObj.root, this->nil, this->nil);
        this->s = oldObj.s;
    }

    Node<K, V> *copyHelper(const Node<K, V> *x, Node<K, V> *nilNew, Node<K, V> *parent)
    {
        if (x->size == 0)
        {
            return nilNew;
        }
        Node<K, V> *copyNode = new Node<K, V>();
        copyNode->color = x->color;
        copyNode->size = x->size;
        copyNode->key = x->key;
        copyNode->value = x->value;
        copyNode->p = parent;
        copyNode->left = copyHelper(x->left, nilNew, copyNode);
        copyNode->right = copyHelper(x->right, nilNew, copyNode);
        return copyNode;
    }

    RBTree &operator=(const RBTree &oldObj)
    {
        this->nil = new Node<K, V>();
        this->nil->size = 0;
        this->root = this->nil;
        this->root = copyHelper(oldObj.root, this->nil, this->nil);
        this->s = oldObj.s;
        return *this;
    }

    void deleteTree(Node<K, V> *node)
    {
        if (node != nil)
        {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    void inorder()
    {
        printInorder(root);
        cout << endl;
    }
    void printInorder(Node<K, V> *node)
    {
        // if nil node
        if (node->left == NULL)
            return;

        /* first recur on left child */
        printInorder(node->left);

        /* then print the data of node */
        cout << node->key << " ";

        /* now recur on right child */
        printInorder(node->right);
    }

    void preorder()
    {
        printPreorder(root);
        cout << endl;
    }

    void printPreorder(Node<K, V> *node)
    {
        if (node->left == NULL)
            return;

        /* first print data of node */
        cout << node->key << " ";

        /* then recur on left subtree */
        printPreorder(node->left);

        /* now recur on right subtree */
        printPreorder(node->right);
    }

    void postorder()
    {
        printPostorder(root);
        cout << endl;
    }

    void printPostorder(Node<K, V> *node)
    {
        if (node->left == NULL)
            return;

        // first recur on left subtree
        printPostorder(node->left);

        // then recur on right subtree
        printPostorder(node->right);

        // now deal with the node
        cout << node->key << " ";
    }

    void insert(K k, V v)
    {
        Node<K, V> *z = new Node<K, V>(k, v, 1);
        Node<K, V> *y = nil;
        Node<K, V> *x = root;
        while (x != nil)
        {
            y = x;
            if (z->key < x->key)
            {
                x->size++;
                x = x->left;
            }
            else
            {
                x->size++;
                x = x->right;
            }
        }
        z->p = y;
        if (y == nil)
        {
            root = z;
        }
        else if (z->key < y->key)
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }
        z->left = nil;
        z->right = nil;
        z->color = 1;
        s++;
        insertFixup(z);
    }

    void insertFixup(Node<K, V> *z)
    {
        while (z->p->color == 1)
        {
            if (z->p == z->p->p->left)
            {
                Node<K, V> *y = z->p->p->right;
                if (y->color == 1)
                {
                    z->p->color = 0;
                    y->color = 0;
                    z->p->p->color = 1;
                    z = z->p->p;
                    continue;
                }
                else if (z == z->p->right)
                {
                    z = z->p;
                    leftRotate(z);
                }
                z->p->color = 0;
                z->p->p->color = 1;
                rightRotate(z->p->p);
            }
            else
            {
                // right
                Node<K, V> *y = z->p->p->left;
                if (y->color == 1)
                {
                    z->p->color = 0;
                    y->color = 0;
                    z->p->p->color = 1;
                    z = z->p->p;
                    continue;
                }
                else if (z == z->p->left)
                {
                    z = z->p;
                    rightRotate(z);
                }
                z->p->color = 0;
                z->p->p->color = 1;
                leftRotate(z->p->p);
            }
        }
        root->color = 0;
    }

    void leftRotate(Node<K, V> *z)
    {
        Node<K, V> *y = z->right;
        z->right = y->left;

        if (y->left != nil)
            y->left->p = z;
        y->p = z->p;
        if (z->p == nil)
        {
            root = y;
        }
        else if (z == z->p->left)
        {
            z->p->left = y;
        }
        else
        {
            z->p->right = y;
        }
        y->left = z;
        z->p = y;

        y->size = z->size;
        z->size = z->right->size + z->left->size + 1;
    }

    void rightRotate(Node<K, V> *z)
    {
        Node<K, V> *y = z->left;
        z->left = y->right;

        if (y->right != nil)
            y->right->p = z;
        y->p = z->p;
        if (z->p == nil)
        {
            root = y;
        }
        else if (z == z->p->right)
            z->p->right = y;
        else
            z->p->left = y;
        y->right = z;
        z->p = y;

        y->size = z->size;
        z->size = z->right->size + z->left->size + 1;
    }

    int size()
    {
        return s;
    }

    V *search(K k)
    {
        Node<K, V> *x = root;
        while (x != nil)
        {
            if (x->key == k)
                return &(x->value);
            else if (x->key < k)
                x = x->right;
            else
                x = x->left;
        }
        return NULL;
    }

    int rank(K k)
    {
        Node<K, V> *x = root;
        while (x != nil)
        {
            if (x->key > k)
            {
                x = x->left;
            }
            else if (x->key < k)
            {
                x = x->right;
            }
            else
                break;
        }

        if (x == nil)
            return 0;

        int r = x->left->size + 1;
        Node<K, V> *y = x;
        while (y != root)
        {
            if (y == y->p->right)
                r = r + y->p->left->size + 1;
            y = y->p;
        }
        return r;
    }

    K select(int pos)
    {
        return osSelect(root, pos);
    }

    K osSelect(Node<K, V> *x, int pos)
    {
        int r = x->left->size + 1;
        if (pos == r)
            return x->key;
        else if (pos < r)
            return osSelect(x->left, pos);
        else
            return osSelect(x->right, pos - r);
    }

    K *predecessor(K k)
    {
        K *suc = NULL;
        Node<K, V> *x = root;

        while (x != nil)
        {
            if (x->key > k)
            {
                x = x->left;
            }
            else if (x->key < k)
            {
                x = x->right;
            }
            else
                break;
        }

        if (x == nil)
            return NULL;

        if (x->left != nil)
            return &((treeMax(x->left))->key);

        Node<K, V> *y = x->p;
        while (y != nil && x == y->left)
        {
            x = y;
            y = y->p;
        }

        if (y == nil)
            return NULL;

        return &(y->key);
    }

    K *successor(K k)
    {
        K *suc = NULL;
        Node<K, V> *x = root;

        while (x != nil)
        {
            if (x->key > k)
            {
                x = x->left;
            }
            else if (x->key < k)
            {
                x = x->right;
            }
            else
                break;
        }

        if (x == nil)
            return NULL;

        if (x->right != nil)
            return &((treeMin(x->right))->key);

        Node<K, V> *y = x->p;
        while (y != nil && x == y->right)
        {
            x = y;
            y = y->p;
        }

        if (y == nil)
            return NULL;

        return &(y->key);
    }

    void printk(int k)
    {
        printkInorder(k, root);
        cout << endl;
        count = 0;
    }

    void printkInorder(int k, Node<K, V> *node)
    {
        // if nil node
        if (node->left == NULL)
            return;

        /* first recur on left child */
        printkInorder(k, node->left);

        /* then print the data of node */
        if (count < k)
        {
            cout << node->key << " ";
            count++;
        }
        else
            return;

        /* now recur on right child */

        printkInorder(k, node->right);
    }

    int remove(K k)
    {
        Node<K, V> *z = root;
        while (z != nil)
        {
            if (z->key > k)
            {
                z->size--;
                z = z->left;
            }
            else if (z->key < k)
            {
                z->size--;
                z = z->right;
            }
            else
                break;
        }

        if (z == nil)
            return 0; // if node does not exist

        Node<K, V> *y = z;
        Node<K, V> *x = nil;
        Node<K, V> *cur;

        int originalColor = y->color;

        if (z->right == nil)
        {
            x = z->left;
            transplant(z, z->left);
        }
        else if (z->left == nil)
        {
            x = z->right;
            transplant(z, z->right);
        }
        else
        {
            y = treeMax(z->left);
            originalColor = y->color;
            x = y->left;

            // size updates
            cur = y;
            while (cur != z)
            {
                cur = cur->p;
                cur->size--;
            }

            if (y->p == z)
                x->p = y;
            else
            {
                transplant(y, y->left);
                y->left = z->left;
                y->left->p = y;
            }
            transplant(z, y);
            y->size = z->size;
            y->right = z->right;
            y->right->p = y;
            y->color = z->color;
        }
        if (originalColor == 0)
            deleteFixup(x);

        s--;
        return 1;
    }

    Node<K, V> *treeMin(Node<K, V> *x)
    {
        while (x->left != nil)
        {
            x = x->left;
        }
        return x;
    }
    Node<K, V> *treeMax(Node<K, V> *x)
    {
        while (x->right != nil)
        {
            x = x->right;
        }
        return x;
    }

    void transplant(Node<K, V> *u, Node<K, V> *v)
    {
        if (u->p == nil)
            root = v;
        else if (u == u->p->left)
            u->p->left = v;
        else
        {
            u->p->right = v;
        }
        v->p = u->p;
    }

    void deleteFixup(Node<K, V> *x)
    {
        while (x != root && x->color == 0)
        {
            if (x == x->p->left)
            {
                Node<K, V> *w = x->p->right;
                if (w->color == 1)
                {
                    w->color = 0;
                    x->p->color = 1;
                    leftRotate(x->p);
                    w = x->p->right;
                }
                if (w->left->color == 0 && w->right->color == 0)
                {
                    w->color = 1;
                    x = x->p;
                }
                else
                {
                    if (w->right->color == 0)
                    {
                        w->left->color = 0;
                        w->color = 1;
                        rightRotate(w);
                        w = x->p->right;
                    }
                    w->color = x->p->color;
                    x->p->color = 0;
                    w->right->color = 0;
                    leftRotate(x->p);
                    x = root;
                }
            }
            else
            {
                Node<K, V> *w = x->p->left;
                if (w->color == 1)
                {
                    w->color = 0;
                    x->p->color = 1;
                    rightRotate(x->p);
                    w = x->p->left;
                }
                if (w->right->color == 0 && w->left->color == 0)
                {
                    w->color = 1;
                    x = x->p;
                }
                else
                {
                    if (w->left->color == 0)
                    {
                        w->right->color = 0;
                        w->color = 1;
                        leftRotate(w);
                        w = x->p->left;
                    }
                    w->color = x->p->color;
                    x->p->color = 0;
                    w->left->color = 0;
                    rightRotate(x->p);
                    x = root;
                }
            }
        }
        x->color = 0;
    }
};
