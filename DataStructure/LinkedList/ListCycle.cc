#include "List.h"

Node* detectCycle(Node* head) {
    auto* fast = head;
    auto* slow = head;

    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;

        if (fast == slow)
            return fast;
    }

    return nullptr;
}

Node* getCycleEntry(Node* head) {
    Node* meet = detectCycle(head);
    if (meet) {
        auto* left = head;
        while (left != meet) {
            left = left->next;
            meet = meet->next;
        }
    }

    return meet;
}