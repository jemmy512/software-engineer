#include<iostream>

#include "List.h"

Node* findFirstCommentNode(Node* lhs, Node* rhs)
{
    Node* left = lhs;
    Node* rigt = rhs;
    while (left != rigt) {
        left = (left == nullptr ? rhs : left = left->next);
        rigt = (rigt == nullptr ? lhs: rigt = rigt->next);
    }
    return left;
}

int main(void)
{

    return 0;
}
