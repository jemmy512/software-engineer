/*
Given a singly linked list, determine if it is a palindrome.

Follow up:
Could you do it in O(n) time and O(1) space?
*/

#include<iostream>
#include<stack>
#include<vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    explicit ListNode(int x) : val(x), next(NULL) {}
};

ListNode *findMiddle(ListNode *head) {
    ListNode *m = head, *n = head;
    while (m && m->next) {
        n = n->next;
        m = m->next->next;
    }
    return n;
}

ListNode *reverseList(ListNode *head) {
    ListNode *p = NULL;
    ListNode *m = NULL;
    while (head) {
       m = head->next;
       head->next = p;
       p = head;
       head = m;
    }
    return p;
}

// 26 test cases, 20ms, beat 96.66%
bool isPalindrome(ListNode* head) {
    ListNode *middle = findMiddle(head);
    ListNode *right = reverseList(middle);
    // head != middle not head != right [head has one more node than right]
    for (; head != middle; head = head->next, right = right->next) {
        if (head->val != right->val)
            return false;
    }
    return true;
}

int main() {
    ListNode a(1);
    ListNode b(0);
    ListNode c(0);
    ListNode d(1);
    a.next = &b;
    b.next = &c;
    c.next = &d;
    d.next = NULL;

    cout << isPalindrome(&a) << endl;
}
