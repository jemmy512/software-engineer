/*
 * Created by by on 2018/8/15.
 * Reference:
         https://www.geeksforgeeks.org/red-black-tree-set-2-insert/
 *       https://juejin.im/entry/58371f13a22b9d006882902d#%E7%BA%A2%E9%BB%91%E6%A0%91%E7%9A%84%E5
            %B9%B3%E8%A1%A1%E5%88%A0%E9%99%A4
 *       http://www.cnblogs.com/skywang12345/p/3245399.html#a1
 *       http://blog.csdn.net/weewqrer/article/details/51866488
 *       https://blog.csdn.net/v_JULY_v/article/details/6284050 */
#include <array>
#include <iomanip>
#include <iostream>
#include <algorithm>

template<typename T>
class RBTree {
public:
    enum Color {Red, Black};
    enum Order {PreOrder, InOrder, PostOrder};

    struct Node {
        T value;
        Color color;
        struct Node* left, *right, *parent;

        Node(T val, Node* nill)
        :   value(val), color(Red), left(nill), right(nill), parent(nill)
        { }
    };

    RBTree() {
        _Nil = new Node(0, nullptr);
        _Nil->color = Black;
        _Root = _Nil;
    }

    ~RBTree() {
        delete _Nil;
    }

    void insert(T value);
    void erase(T value);
    void print(Order order);

protected:
    Node* minNode(Node* node);
    void lRotate(Node* node);
    void rRotate(Node* node);
    Node* _insert(Node* node);
    Node* _erase(T value);
    void balanceInsertion(Node* node);
    void balanceErasion(Node* node);

    void preOrderPrint(Node* node);
    void inOrderPrint(Node* node);
    void postOrderPrint(Node* node);

    void setColor(Node* node, Color col) {
        if (node != _Nil)
            node->color = col;
    }

    Color getColor(Node* node) {
        return node->color;
    }

private:
    Node* _Root = nullptr, *_Nil = nullptr;
};

template<typename T>
void RBTree<T>::insert(T value) {
    Node* node = new Node(value, _Nil);
    balanceInsertion(_insert(node));
}

template<typename T>
typename RBTree<T>::Node* RBTree<T>::_insert(Node* node) {
    if (node == _Nil)
        return _Nil;

    Node* fast = _Root, *slow = _Root;
    while (fast != _Nil) {
        slow = fast;
        if (fast->value < node->value)
            fast = fast->right;
        else if (fast->value > node->value)
            fast = fast->left;
        else
            return _Nil;
    }

    if (slow == _Nil)
        _Root = node;
    else if (slow->value < node->value)
        slow->right = node;
    else
        slow->left = node;
    node->parent = slow;

    return node;
}

template<typename T>
void RBTree<T>::balanceInsertion(Node* node) {
    if (node == _Nil)
        return;

    Node* parent = _Nil, *grandpa = _Nil, *uncle = _Nil;
    while ((node != _Root) && (Red == getColor(node)) && (Red == getColor(node->parent))) {
        parent = node->parent;
        grandpa = parent->parent;

        if (parent == grandpa->left) {
            uncle = grandpa->right;         //          node - parent - uncle
            if (Red == getColor(uncle)) {   //  case 1. Red  - Red    - Red
                setColor(uncle, Black);
                setColor(parent, Black);
                setColor(grandpa, Red);
                node = grandpa;
            } else {
                if (node == parent->right) {// case 2. (right)Red - Red - Black
                    lRotate(parent);
                    node = parent;
                    parent = node->parent;
                }
                rRotate(grandpa);           // case 3. (left)Red - Red - Black
                std::swap(parent->color, grandpa->color);
                node = parent;
            }
        } else {
            uncle = grandpa->left;
            if (Red == getColor(uncle)) {
                setColor(uncle, Black);
                setColor(parent, Black);
                setColor(grandpa, Red);
                node = grandpa;
            } else {
                if (node == parent->left) {
                    rRotate(parent);
                    node = parent;
                    parent = node->parent;
                }
                lRotate(grandpa);
                std::swap(parent->color, grandpa->color);
                node = parent;
            }
        }
    }

    setColor(_Root, Black);                  // case 4. _Root insert
}

template<typename T>
void RBTree<T>::erase(T value) {
    balanceErasion(_erase(value));
}

template<typename T>
typename RBTree<T>::Node* RBTree<T>::_erase(T value) {
    Node* node = _Root;
    while (node != _Nil) {
        if (node->value < value)
            node = node->right;
        else if (node->value > value)
            node = node->left;
        else {
            Node* no = node;
            if (no->left != _Nil && no->right != _Nil) {
                no = minNode(node->right);
                node->value = no->value;
            }
            return no;
        }
    }

    return _Nil;
}

template<typename T>
void RBTree<T>::balanceErasion(Node* node) {
    if (node == _Nil)
        return;

    Node* child = node->left != _Nil ? node->left : node->right;
    if (node == _Root)
        _Root = child;
    else if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;
    child->parent = node->parent;   // child may be nullptr

    if (Black != getColor(node)) {
        delete node;
        return;
    }

    Node* parent = _Nil;
    Node* sibling = _Nil;
    while ((child != _Root) && (Black == getColor(child))) {
        parent = child->parent;
        if (child == parent->left) {
            sibling = parent->right;
            if (Red == getColor(sibling)) {     // Case 1. Red, change to case 2,3,4
                std::swap(sibling->color, parent->color);
                lRotate(parent);
            } else {                            // Case 2. Black - Black - Black
                if (Black == getColor(sibling->left) && Black == getColor(sibling->right)) {
                    setColor(sibling, Red);
                    if (Red == getColor(parent)) {
                        setColor(parent, Black);
                        break;
                    } else {
                        child = parent;
                    }
                } else {                        // Case 3. Black - Red - Black, to case 4
                    if (Black == getColor(sibling->right)) {
                        std::swap(sibling->color, sibling->left->color);
                        rRotate(sibling);
                        sibling = parent->right;
                    }                           // Case 4. Black - <> - Red
                    std::swap(parent->color, sibling->color);
                    setColor(sibling->right, Black);
                    lRotate(parent);
                    child = _Root;
                }
            }
        } else {
            sibling = parent->left;
            if (Red == getColor(sibling)) {
                std::swap(sibling->color, parent->color);
                rRotate(parent);
            } else {
                if (Black == getColor(sibling->left) && Black == getColor(sibling->right)) {
                    setColor(sibling, Red);
                    if (Red == getColor(parent)) {
                        setColor(parent, Black);
                        break;
                    } else {
                        child = parent;
                    }
                } else {
                    if (Black == getColor(sibling->left)) {
                        std::swap(sibling->color, sibling->right->color);
                        lRotate(sibling);
                        sibling = parent->left;
                    }
                    std::swap(sibling->color, parent->color);
                    setColor(sibling->left, Black);
                    rRotate(parent);
                    child = _Root;
                }
            }
        }
    }
    setColor(child, Black);

    delete node;
}

template<typename T>
typename RBTree<T>::Node* RBTree<T>::minNode(Node* node) {
    while (node->left != _Nil)
        node = node->left;
    return node;
}

template<typename T>
void RBTree<T>::lRotate(Node* node) {
    if (node == _Nil)
        return;

    Node* tmp = node->right;
    node->right = tmp->left;
    if (node->right != _Nil)
        node->right->parent = node;

    if (node == _Root)
        _Root = tmp;
    else if (node == node->parent->left)
        node->parent->left = tmp;
    else
        node->parent->right = tmp;

    tmp->left = node;
    tmp->parent = node->parent;

    node->parent = tmp;
}

template<typename T>
void RBTree<T>::rRotate(Node* node) {
    if (node == _Nil)
        return;

    Node* tmp = node->left;
    node->left = tmp->right;
    if (node->left != _Nil)
        node->left->parent = node;

    if (node == _Root)
        _Root = tmp;
    else if (node == node->parent->left)
        node->parent->left = tmp;
    else
        node->parent->right = tmp;

    tmp->right = node;
    tmp->parent = node->parent;

    node->parent = tmp;
}

template<typename T>
void RBTree<T>::print(Order order) {
    if (order == Order::PreOrder)
        preOrderPrint(_Root);
    else if (order == Order::InOrder)
        inOrderPrint(_Root);
    else if (order == Order::PostOrder)
        postOrderPrint(_Root);
}

template<typename T>
void RBTree<T>::preOrderPrint(Node* node) {
    if (node != _Nil) {
        std::cout << std::setw(2) << node->value << "[" << node->color << "] ";
        preOrderPrint(node->left);
        preOrderPrint(node->right);
    }
}

template<typename T>
void RBTree<T>::inOrderPrint(Node* node) {
    if (node != _Nil) {
        inOrderPrint(node->left);
        std::cout << std::setw(2) << node->value << "[" << node->color << "] ";
        inOrderPrint(node->right);
    }
}

template<typename T>
void RBTree<T>::postOrderPrint(Node* node) {
    if (node != _Nil) {
        postOrderPrint(node->left);
        postOrderPrint(node->right);
        std::cout << std::setw(2) << node->value << "[" << node->color << "] ";
    }
}

int main() {
    auto tree = std::make_shared<RBTree<int>>();

    std::array<int, 20> arr{12, 1, 9, 2, 0, 11, 7, 19, 4, 15, 18, 5, 14, 13, 10, 16, 6, 3, 8, 17};

    std::cout << "Ref: " << tree.use_count() << std::endl;

    std::for_each(arr.begin(), arr.end(), [tree](const auto& num) {
        tree->insert(num);
        tree->print(RBTree<int>::Order::InOrder);
        std::cout << std::endl << std::endl;
    });

    std::for_each(arr.begin(), arr.end(), [tree](const auto& num) {
        tree->erase(num);
        tree->print(RBTree<int>::Order::InOrder);
        std::cout << std::endl << std::endl;
    });

    return 0;
}

/**
 * 1. Each node is either red or black.
 * 2. The root is black. This rule is sometimes omitted.
 * 3. All leaves (NIL) are black.
 * 4. If a node is red, then both its children are black.
 * 5. Every path from a given node to any of its descendant NIL nodes
 *  goes through the same number of black nodes.
 *
 *
 * Insert:
 * 1. N is the root node, i.e., first node of red–black tree
 * 2. N-P-U: red-red-red
 * 3. N-P-U: red(L)-red-black
 * 4. N-P-U: red(R)-red-black
 *
 *
 * Remove:
 * 1. N is the new root.
 * 2. S is red.
 * 3. P, S, and S's children are black.
 * 4. S and S's children are black, but P is red.
 * 5. S is black, S's left child is red, S's right child is black, and N is the left child of its parent.
 * 6. S is black, S's right child is red, and N is the left child of its parent P*/