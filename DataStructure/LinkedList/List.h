#include<iostream>
using namespace std;

struct Node {
    int val;
    Node* next;
};

Node* createListHeadInsert(int* args, int size) {
    Node* head = nullptr;
    if (args == nullptr ||  size < 0)
        return head;

    for (; size > 0; --size) {
        head = new Node{args[size-1], head};
    }

    return head;
}

Node* createListTailInsert(int* args, int size) {
    if (args == nullptr || size < 0)
        return nullptr;

    Node *beg = nullptr, *end = nullptr;
    for (int idx = 0; idx < size; ++idx) {
        Node* node = new Node{args[idx], nullptr};

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

Node* deleteNode(Node* node, int val) {
    Node *beg = node, *end = nullptr;
    while (beg != nullptr && beg->val != val) {
        end = beg;
        beg = beg->next;
    }

    if (beg == node) {
        node = beg->next;
    } else if (beg != nullptr) {
        end->next = beg->next;
    } else {
        // not found
    }

    if (beg) {
        delete beg;
    }

    return node;
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

Node* mergeSortedList(Node* head1,Node* head2)
{
    if(head1 == nullptr && head2 == nullptr)
        return nullptr;
    else if (head1 == nullptr)
        return head2;
    else if(head2 == nullptr)
        return head1;

    Node* newHead = nullptr;

    if (head1->val < head2->val) {
        newHead = head1;
        newHead->next = mergeSortedList(head1->next, head2);
    } else {
        newHead = head2;
        newHead->next = mergeSortedList(head1, head2->next);
    }

    return newHead;
}

/*
int main() {
    int node1[1]{1};
    int node2[2]{1, 2};
    int node3[3]{1, 2, 3};
    int node4[4]{1, 2, 3, 4};
    int node5[5]{1, 2, 3, 4, 5};

    Node* begOne = createListHeadInsert(node1, 1);
    Node* begTwo = createListHeadInsert(node2, 2);
    Node* begThree = createListHeadInsert(node3, 3);
    Node* begFour = createListHeadInsert(node4, 4);
    Node* begFive = createListHeadInsert(node5, 5);

    printList(begOne);
    printList(begTwo);
    printList(begThree);
    printList(begFour);
    printList(begFive);

    Node* one = deleteNode(begOne, 1);
    Node* two = deleteNode(begTwo, 1);
    Node* three = deleteNode(begThree, 2);
    Node* four = deleteNode(begFour,3 );
    Node* five = deleteNode(begFive, 6);


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
*/