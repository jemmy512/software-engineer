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
#include <iomanip>
#include <iostream>

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
        nil = new Node(0, nullptr);
        nil->color = Black;
        root = nil;
    }
    ~RBTree() {
        delete nil;
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
        if (node != nil)
            node->color = col;
    }

    Color getColor(Node* node) {
        return node->color;
    }

private:
    Node* root = nullptr, *nil = nullptr;
};

template<typename T>
void RBTree<T>::insert(T value) {
    Node* node = new Node(value, nil);
    balanceInsertion(_insert(node));
}

template<typename T>
typename RBTree<T>::Node* RBTree<T>::_insert(Node* node) {
    if (node == nil)
        return nil;

    Node* fast = root, *slow = root;
    while (fast != nil) {
        slow = fast;
        if (fast->value < node->value)
            fast = fast->right;
        else if (fast->value > node->value)
            fast = fast->left;
        else
            return nil;
    }

    if (slow == nil)
        root = node;
    else if (slow->value < node->value)
        slow->right = node;
    else
        slow->left = node;
    node->parent = slow;

    return node;
}

template<typename T>
void RBTree<T>::balanceInsertion(Node* node) {
    if (node == nil)
        return;

    Node* parent = nil, *grandpa = nil, *uncle = nil;
    while ((node != root) && (Red == getColor(node)) && (Red == getColor(node->parent))) {
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

    setColor(root, Black);                  // case 4. root insert
}

template<typename T>
void RBTree<T>::erase(T value) {
    balanceErasion(_erase(value));
}

template<typename T>
typename RBTree<T>::Node* RBTree<T>::_erase(T value) {
    Node* node = root;
    while (node != nil) {
        if (node->value < value)
            node = node->right;
        else if (node->value > value)
            node = node->left;
        else {
            Node* no = node;
            if (no->left != nil && no->right != nil) {
                no = minNode(node->right);
                node->value = no->value;
            }
            return no;
        }
    }

    return nil;
}

template<typename T>
void RBTree<T>::balanceErasion(Node* node) {
    if (node == nil)
        return;

    Node* child = node->left != nil ? node->left : node->right;
    if (node == root)
        root = child;
    else if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;
    child->parent = node->parent;   // child may be nullptr

    if (Black == getColor(node)) {
        Node* parent = nil;
        Node* sibling = nil;
        while ((child != root) && (Black == getColor(child))) {
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
                        child = root;
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
                        child = root;
                    }
                }
            }
        }
        setColor(child, Black);
    }

    delete node;
}

template<typename T>
typename RBTree<T>::Node* RBTree<T>::minNode(Node* node) {
    while (node->left != nil)
        node = node->left;
    return node;
}

template<typename T>
void RBTree<T>::lRotate(Node* node) {
    if (node == nil)
        return;

    Node* tmp = node->right;
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

template<typename T>
void RBTree<T>::rRotate(Node* node) {
    if (node == nil)
        return;

    Node* tmp = node->left;
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

template<typename T>
void RBTree<T>::print(typename RBTree<T>::Order order) {
    if (order == Order::PreOrder)
        preOrderPrint(root);
    else if (order == Order::InOrder)
        inOrderPrint(root);
    else if (order == Order::PostOrder)
        postOrderPrint(root);
}

template<typename T>
void RBTree<T>::preOrderPrint(RBTree<T>::Node* node) {
    if (node != nil) {
        std::cout << std::setw(2) << node->value << "[" << node->color << "] ";
        preOrderPrint(node->left);
        preOrderPrint(node->right);
    }
}

template<typename T>
void RBTree<T>::inOrderPrint(RBTree<T>::Node* node) {
    if (node != nil) {
        inOrderPrint(node->left);
        std::cout << std::setw(2) << node->value << "[" << node->color << "] ";
        inOrderPrint(node->right);
    }
}

template<typename T>
void RBTree<T>::postOrderPrint(RBTree<T>::Node* node) {
    if (node != nil) {
        postOrderPrint(node->left);
        postOrderPrint(node->right);
        std::cout << std::setw(2) << node->value << "[" << node->color << "] ";
    }
}

int main() {
    RBTree<int> *tree = new RBTree<int>();

    std::array<int, 20> arr{12, 1, 9, 2, 0, 11, 7, 19, 4, 15, 18, 5, 14, 13, 10, 16, 6, 3, 8, 17};

    for (int i = 0; i < arr.size(); ++i) {
        tree->insert(arr[i]);
        tree->print(RBTree<int>::Order::InOrder);
        std::cout << std::endl << std::endl;
    }

    for (int i = 0; i < arr.size(); ++i) {
        tree->erase(arr[i]);
        tree->print(RBTree<int>::Order::InOrder);
        std::cout << std::endl << std::endl;
    }

    return 0;
}
