#include<iostream>
using namespace std;

struct Node {
    int val;
    Node* next;
};

Node* createList(int* args, int size) {
    Node *beg = nullptr, *end = nullptr;
    for (auto idx = 0; idx < size; ++idx) {
        Node* node = new Node;
        node->val = args[idx];
        node->next = nullptr;

        if (beg) {
            end->next = node;
            end = end->next;
        } else {
            beg = end = node;
        }
    }

    return beg;
}

void releaseList(Node* node) {
    while (node) {
        Node* cur = node;
        node = node->next;

        delete cur;
    }
}

void printList(Node* node) {
    while (node) {
        std::cout << node->val;
        if (node->next) 
            std::cout << " -> ";

        node = node->next;
    }

    std::cout << endl;
}

Node* reverseList(Node* head) {
    Node *mid, *tail = nullptr;
    while (head != nullptr) {
        mid = head;
        head = head->next;
        mid->next = tail;
        tail = mid;
        mid = head;
    }

    return tail;
}

int main() {
    int args[5]{1, 2, 3, 4, 5};
    Node* node = createList(args, 5);

    printList(node);

    node = reverseList(node);

    printList(node);

    releaseList(node);

    return 0;
}
