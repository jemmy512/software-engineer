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

        void setColor(Color col) {
            this->color = col;
        }

        Color getColor() const {
            return this->color;
        }

        bool isRed() const {
            return this->color == Red;
        }

        bool isBlack() const {
            return this->color == Black;
        }
    };

    RBTree() {
        _Nil = new Node(0, nullptr);
        _Nil->color = Black;
        _Root = _Nil;
    }

    ~RBTree() {
        clear(_Root);
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

private:
    void clear(Node* node) {
        if (node != _Nil) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

private:
    friend struct Node;
    Node* _Root = nullptr, *_Nil = nullptr;
};

template<typename T>
void RBTree<T>::insert(T value) {
    Node* node = new Node(value, _Nil);
    balanceInsertion(_insert(node));
}

template<typename T>
typename RBTree<T>::Node* RBTree<T>::_insert(Node* node) {
    if (node == _Nil) {
        return _Nil;
    }

    Node* cur = _Root, *prev = _Root;
    while (cur != _Nil) {
        prev = cur;
        if (cur->value < node->value) {
            cur = cur->right;
        } else if (cur->value > node->value) {
            cur = cur->left;
        } else {
            return _Nil;
        }
    }

    if (prev == _Nil) {
        _Root = node;
    } else if (prev->value < node->value) {
        prev->right = node;
    } else {
        prev->left = node;
    }

    node->parent = prev;

    return node;
}

template<typename T>
void RBTree<T>::balanceInsertion(Node* node) {
    if (node == _Nil) {
        return;
    }

    Node* parent = _Nil, *grandpa = _Nil, *uncle = _Nil;

    while ((node != _Root) && node->isRed() && node->parent->isRed()) {
        parent = node->parent;
        grandpa = parent->parent;

        if (parent == grandpa->left) {
            uncle = grandpa->right;         //          node - parent - uncle
            if (uncle->isRed()) {           //  case 1. Red  - Red    - Red
                uncle->setColor(Black);
                parent->setColor(Black);
                grandpa->setColor(Red);
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
            if (uncle->isRed()) {
                uncle->setColor(Black);
                parent->setColor(Black);
                grandpa->setColor(Red);
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

    _Root->setColor(Black);                  // case 4. _Root insert
}

template<typename T>
void RBTree<T>::erase(T value) {
    auto* node = _erase(value);
    if (node != _Nil) {
        balanceErasion(node);
    }
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
            Node* min = node;
            if (min->left != _Nil && min->right != _Nil) {
                min = minNode(node->right);
                node->value = min->value;
            }
            return min;
        }
    }

    return _Nil;
}

template<typename T>
void RBTree<T>::balanceErasion(Node* node) {
    if (node == _Nil) {
        return;
    }

    Node* child = (node->left != _Nil) ? node->left : node->right;
    if (node == _Root) {
        _Root = child;
    } else if (node == node->parent->left) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }

    child->parent = node->parent;   // child may be _Nil(nullptr)

    if (node->isRed()) {
        delete node;
        return;
    }

    Node* parent = _Nil;
    Node* sibling = _Nil;

    while ((child != _Root) && child->isBlack()) {
        parent = child->parent;
        if (child == parent->left) {
            sibling = parent->right;
            if (sibling->isRed()) {             // Case 1. Red, change to case 2,3,4
                std::swap(sibling->color, parent->color);
                lRotate(parent);
            } else {                            // Case 2. Black - Black - Black
                if (sibling->left->isBlack() && sibling->right->isBlack()) {
                    sibling->setColor(Red);
                    if (parent->isRed()) {
                        parent->setColor(Black);
                        break;
                    } else {
                        child = parent;
                    }
                } else {                        // Case 3. Black - Red - Black, to case 4
                    if (sibling->right->isBlack()) {
                        std::swap(sibling->color, sibling->left->color);
                        rRotate(sibling);
                        sibling = parent->right;
                    }                           // Case 4. Black - <> - Red
                    std::swap(parent->color, sibling->color);
                    sibling->right->setColor(Black);
                    lRotate(parent);
                    child = _Root;
                }
            }
        } else {
            sibling = parent->left;
            if (sibling->isRed()) {
                std::swap(sibling->color, parent->color);
                rRotate(parent);
            } else {
                if (sibling->left->isBlack() && sibling->right->isBlack()) {
                    sibling->setColor(Red);
                    if (parent->isRed()) {
                        parent->setColor(Black);
                        break;
                    } else {
                        child = parent;
                    }
                } else {
                    if (sibling->left->isBlack()) {
                        sibling->setColor(sibling->right->getColor());
                        lRotate(sibling);
                        sibling = parent->left;
                    }
                    // sibling->setColor(parent->getColor()); // segment fault
                    std::swap(sibling->color, parent->color);
                    sibling->left->setColor(Black);
                    rRotate(parent);
                    child = _Root;
                }
            }
        }
    }
    child->setColor(Black);

    delete node;
}

template<typename T>
typename RBTree<T>::Node* RBTree<T>::minNode(Node* node) {
    while (node->left != _Nil) {
        node = node->left;
    }
    return node;
}

/*      G             G
 *     / \           / \
 *    p   U  -->    n   U
 *   / \           / \
 *      n         p
 *     /         / \
 *    c             c       */
template<typename T>
void RBTree<T>::lRotate(Node* p) {
    if (p == _Nil) {
        return;
    }

    Node* n = p->right;
    Node* gp = p->parent;

    // link p & c
    p->right = n->left;
    if (p->right != _Nil) {
        p->right->parent = p;
    }

    // link n & gp
    n->parent = gp;
    if (p == _Root) {
        _Root = n;
    } else if (p == gp->left) {
        gp->left = n;
    } else {
        gp->right = n;
    }

    // link p & n
    n->left = p;
    p->parent = n;
}

/*        G           G
 *       / \         / \
 *      u   p  -->  u   n
 *         /             \
 *        n               p
 *         \             /
 *          c           c   */
template<typename T>
void RBTree<T>::rRotate(Node* p) {
    if (p == _Nil) {
        return;
    }

    Node* n = p->left;
    Node* gp = p->parent;

    p->left = n->right;
    if (p->left) {
        p->left->parent = p;
    }

    n->parent = gp;
    if (p == _Root) {
        _Root = n;
    } else if (p == gp->left) {
        gp->left = n;
    } else {
        gp->right = n;
    }

    n->right = p;
    p->parent = n;
}

template<typename T>
void RBTree<T>::print(Order order) {
    if (order == Order::PreOrder) {
        preOrderPrint(_Root);
    } else if (order == Order::InOrder) {
        inOrderPrint(_Root);
    } else if (order == Order::PostOrder) {
        postOrderPrint(_Root);
    }
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
  * 4. No adjacent red nodes. If a node is red, then both its children are black.
  * 5. Every path from a given node to any of its descendant NIL nodes
  *  goes through the same number of black nodes.
  *
  *
  * Insert:
  * 1. N is the root node, i.e., first node of red–black tree
  * 2. N-P-U: red-red-red        just flip colors
  * 3. N-P-U: red(L)-red-black   LRorate(P) - RRotate(GP)
  * 4. N-P-U: red(R)-red-black   RRotate(GP)
  *
  *
  * Remove:
  * 1. N is the new root.
  * 2. S is red.
  * 3. P, S, and S's children are black.
  * 4. S and S's children are black, but P is red.
  * 5. S is black, S's left child is red, S's right child is black,
  *      and N is the left child of its parent.
  * 6. S is black, S's right child is red, and N is the left child of its parent P */