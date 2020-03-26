#include "List.h"

Node* deleteMaxNode(Node* node) {
    Node* cur{node->next};
    Node* prev{node};
    Node* max{node};
    Node* maxPrev{nullptr}; 

    for (; cur; prev = cur, cur = cur->next) {
        if (cur->val > max->val) {
            max = cur;
            maxPrev = prev;
        }
    }

    if (max == node)
        node = node->next;
    else
        maxPrev->next = max->next;

    std::cout << "Max: " << max->val << std::endl;
    delete max;

    return node;
}

int main() {
    int node1[1]{1};
    int node2[2]{1, 2};
    int node3[3]{1, 3, 2};
    int node4[4]{5, 3, 3, 1};
    int node5[5]{3, 2, 5, 4, 7};

    Node* begOne = createListHeadInsert(node1, 1);
    Node* begTwo = createListHeadInsert(node2, 2);
    Node* begThree = createListHeadInsert(node3, 3);
    Node* begFour = createListHeadInsert(node4, 4);
    Node* begFive = createListHeadInsert(node5, 5);

    Node* one = deleteMaxNode(begOne);
    Node* two = deleteMaxNode(begTwo);
    Node* three = deleteMaxNode(begThree);
    Node* four = deleteMaxNode(begFour);
    Node* five = deleteMaxNode(begFive);


    printList(one);
    printList(two);
    printList(three);
    printList(four);
    printList(five);

    releaseList(one);
    releaseList(two);
    releaseList(three);
    releaseList(four);
    releaseList(five);

    return 0;
}