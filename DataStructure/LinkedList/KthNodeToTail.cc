#include "List.h"

Node* findKthNodeToTail(Node* node, int kth) {
    if (node == nullptr || kth < 0)
        return nullptr;

    Node* fast = node;
    Node* slow = node;

    for (; kth > 0 && fast != nullptr; --kth) {
        fast = fast->next;
    }
    if (kth != 0)
        return nullptr;

    while (fast != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }

    return slow;
}

void printNode(Node* node) {
    if (node != nullptr) {
        std::cout << node->val << std::endl;
    }
}

int main() {
    int node5[5]{1, 2, 3, 4, 5};

    Node* begFive = createListHeadInsert(node5, 5);

    Node* zero = findKthNodeToTail(begFive, -1);
    Node* one = findKthNodeToTail(begFive, 1);
    Node* two = findKthNodeToTail(begFive, 2);
    Node* three = findKthNodeToTail(begFive, 3);
    Node* four = findKthNodeToTail(begFive, 4);
    Node* five = findKthNodeToTail(begFive, 5);
    Node* six = findKthNodeToTail(begFive, 6);




    printNode(six);
    printNode(five);
    printNode(four);
    printNode(three);
    printNode(two);
    printNode(one);
    printNode(zero);

    releaseList(begFive);

    return 0;
}