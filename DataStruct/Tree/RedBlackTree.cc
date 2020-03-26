/*
 * Created by by on 2018/8/15.
 * Reference:
         https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
 *       https://juejin.im/entry/58371f13a22b9d006882902d#%E7%BA%A2%E9%BB%91%E6%A0%91%E7%9A%84%E5
            %B9%B3%E8%A1%A1%E5%88%A0%E9%99%A4
 *       http://www.cnblogs.com/skywang12345/p/3245399.html#a1
 *       http://blog.csdn.net/weewqrer/article/details/51866488
 *       https://blog.csdn.net/v_JULY_v/article/details/6284050
 */
#include <array>
#include<iomanip>
#include <iostream>
using namespace std;

enum Color {RED, BLACK};
class RBTree;

struct Node {
    int key;
    Color color;
    struct Node *left, *right, *parent;
    Node (int key_) {
        key = key_;
        color = RED;
    }
};

class RBTree {
public:
    Node *root, *nil;
    RBTree() {
        nil = new Node(0);
        nil->color = BLACK;
        nil->parent = nil->left = nil->right = nullptr;
        root = nil;
    }
    ~RBTree() {
        delete nil;
    }

    void RBInsert(int key);
    void RBDelete(int key);
protected:
    Node *minNode(Node *node);
    void lRotate(Node *node);
    void rRotate(Node *node);
    Node *BSTInsert(Node *node);
    Node *BSTDelete(int key);
    void fixInsertion(Node *node);
    void fixDeletion(Node *node);

    void setColor(Node *node, Color color_) {
        if (node != nil)
            node->color = color_;
    }
    Color getColor(Node *node) {
        return node->color;
    }
};


void preorder(RBTree *tree, Node *node) {
    if (node != tree->nil) {
        cout << setw(2) << node->key << "[" << node->color << "] ";
        preorder(tree, node->left);
        preorder(tree, node->right);
    }
}

void RBTree::RBInsert(int key) {
    Node *node = new Node(key);
    node->left = node->right = node->parent = nil;

    node = BSTInsert(node);
    fixInsertion(node);
}

Node *RBTree::BSTInsert(Node *node) {
    if (node == nil)
        return nil;

    Node *fast = root, *slow = root;
    while (fast != nil) {
        slow = fast;
        if (fast->key < node->key)
            fast = fast->right;
        else if (fast->key > node->key)
            fast = fast->left;
        else
            return nil;
    }

    if (slow == nil)
        root = node;
    else if (slow->key < node->key)
        slow->right = node;
    else
        slow->left = node;
    node->parent = slow;

    return node;
}


void RBTree::fixInsertion(Node *node) {
    if (node == nil)
        return;

    Node *parent, *parent_g, *uncle;
    parent = parent_g = uncle = nil;
    while ((node != root) && (RED == getColor(node)) && (RED == getColor(node->parent))) {
        parent = node->parent;
        parent_g = parent->parent;

        if (parent == parent_g->left) {
            uncle = parent_g->right;
            if (RED == getColor(uncle)) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(parent_g, RED);
                node = parent_g;
            } else {
                if (node == parent->right) { /* change inside insert to outside insert */
                    lRotate(parent);
                    node = parent;
                    parent = node->parent;
                }
                rRotate(parent_g);           /* outside insert */
                swap(parent->color, parent_g->color);
                node = parent;
            }
        } else {
            uncle = parent_g->left;
            if (RED == getColor(uncle)) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(parent_g, RED);
                node = parent_g;
            } else {
                if (node == parent->left) {
                    rRotate(parent);
                    node = parent;
                    parent = node->parent;
                }
                lRotate(parent_g);
                swap(parent->color, parent_g->color);
                node = parent;
            }
        }
    }
    setColor(root, BLACK);
}

void RBTree::RBDelete(int key) {
    Node *node = BSTDelete(key);
    fixDeletion(node);
}

Node *RBTree::BSTDelete(int key) {
    Node *tmp = root;
    while (tmp != nil) {
        if (tmp->key < key)
            tmp = tmp->right;
        else if (tmp->key > key)
            tmp = tmp->left;
        else {
            Node *no = tmp;
            if (no->left != nil && no->right != nil) {
                no = minNode(tmp->right);
                tmp->key =no->key;
            }
            return no;
        }
    }
    return nil;
}

void RBTree::fixDeletion(Node *node) {
    if (node == nil)
        return;

    Node *child = node->left != nil ? node->left : node->right;
    if (node == root)
        root = child;
    else if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;
    child->parent = node->parent;   // child may be nullptr
    if (BLACK == getColor(node)) {
        Node *parent = nil;
        Node *sibling = nil;
        while ((child != root) && (BLACK == getColor(child))) {
            parent = child->parent;
            if (child == parent->left) {
                sibling = parent->right;
                if (RED == getColor(sibling)) {     // Case 1. RED, change to case 2,3,4
                    swap(sibling->color, parent->color);
                    lRotate(parent);
                } else {                            // Case 2. BLACK - BLACK - BLACK
                    if (BLACK == getColor(sibling->left) && BLACK == getColor(sibling->right)) {
                        setColor(sibling, RED);
                        if (RED == getColor(parent)) {
                            setColor(parent, BLACK);
                            break;
                        } else {
                            child = parent;
                        }
                    } else {                        // Case 3. BLACK - RED - BLACK, to case 4
                        if (BLACK == getColor(sibling->right)) {
                            swap(sibling->color, sibling->left->color);
                            rRotate(sibling);
                            sibling = parent->right;
                        }                           // Case 4. BLACK - <> - RED
                        swap(parent->color, sibling->color);
                        setColor(sibling->right, BLACK);
                        lRotate(parent);
                        child = root;
                    }
                }
            } else {
                sibling = parent->left;
                if (RED == getColor(sibling)) {
                    swap(sibling->color, parent->color);
                    rRotate(parent);
                } else {
                    if (BLACK == getColor(sibling->left) && BLACK == getColor(sibling->right)) {
                        setColor(sibling, RED);
                        if (RED == getColor(parent)) {
                            setColor(parent, BLACK);
                            break;
                        } else {
                            child = parent;
                        }
                    } else {
                        if (BLACK == getColor(sibling->left)) {
                            swap(sibling->color, sibling->right->color);
                            lRotate(sibling);
                            sibling = parent->left;
                        }
                        swap(sibling->color, parent->color);
                        setColor(sibling->left, BLACK);
                        rRotate(parent);
                        child = root;
                    }
                }
            }
        }
        setColor(child, BLACK);
    }
    delete node;
}

Node *RBTree::minNode(Node *node) {
    while (node->left != nil)
        node = node->left;
    return node;
}

void RBTree::lRotate(Node *node) {
    if (node == nil)
        return;

    Node *tmp = node->right;
    node->right = tmp->left;
    if (node->right != nil)
        node->right->parent = node;

    if (node == root)
        root = tmp;
    else if (node == node->parent->left)
        node->parent->left = tmp;
    else
        node->parent->right = tmp;

    tmp->left = node;
    tmp->parent = node->parent;
    node->parent = tmp;
}

void RBTree::rRotate(Node *node) {
    if (node == nil)
        return;

    Node *tmp = node->left;
    node->left = tmp->right;
    if (node->left != nil)
        node->left->parent = node;

    if (node == root)
        root = tmp;
    else if (node == node->parent->left)
        node->parent->left = tmp;
    else
        node->parent->right = tmp;

    tmp->right = node;
    tmp->parent = node->parent;
    node->parent = tmp;
}

int main() {
    RBTree *tree = new RBTree();

    array<int, 20> arr = {12, 1, 9, 2, 0, 11, 7, 19, 4, 15, 18, 5, 14, 13, 10, 16, 6, 3, 8, 17};

    for (int i = 0; i < arr.size(); ++i) {
        tree->RBInsert(arr[i]);
//        preorder(tree, tree->root);
//        cout << endl << endl;
    }
    for (int i = 0; i < 20; ++i) {
        tree->RBDelete(arr[i]);
        preorder(tree, tree->root);
        cout << endl << endl;
    }

//    tree->RBInsert(4);
//    cout << "Insetion. Inorder traversal of RBTree:\n";
//    tree->inOrder();
//    cout << endl;
//    tree->preOrder();
//
//    // tree->RBDelete(9);
//    for (int i = 0; i < arr.size(); ++i) {
//        tree->RBDelete(arr[i]);
//        cout << "D<" << setw(2) << arr[i] << "> ";
//        tree->inOrder();
//        cout << endl;
//    }
//    cout << "\nDeletion. Inorder traversal of RBTree:\n";
//    tree->inOrder();

    return 0;
}

