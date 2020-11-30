/*
Difficulty: Medium

A linked list is given such that each node contains an additional random pointer
which could point to any node in the list or null.

Return a deep copy of the list.
*/

/*
 *  The idea as below:
 *
 *  Consider we have a linked list as below:
 *
 *    node1->random = node2;
 *    node2->random = node1;
 *    node3->random = node1;
 *
 *       +-------------+
 *       |             v
 *    +-------+    +-------+    +-------+
 *    | node1 |----> node2 |----> node3 |--->NULL
 *    +-------+    +-------+    +-------+
 *      ^  ^           |           |
 *      |  +-----------+           |
 *      +--------------------------+
 *
 *
 *  To copy the list,
 *
 *    1) We insert a new node for each node's next position
 *
 *
 *       +-------------------------+
 *       |                         v
 *    +--+----+     +-----+    +-------+     +-----+    +-------+     +-----+
 *    | node1 |---> | NEW |----> node2 |---> | NEW |----> node3 |---> | NEW | ---> NULL
 *    +-------+     +-----+    +---+---+     +-----+    +--+----+     +-----+
 *      ^  ^                       |                       |
 *      |  +-----------------------+                       |
 *      +--------------------------------------------------+
 *
 *    2) Then, we can construt the new node's random pointer:
 *
 *        (node1->next) -> random  = (node1->random) -> next;
 *
 *    3) After we take out all of the "NEW" node to finish the copy.
 *
 */

struct Node {
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head)
            return head;

        Node* cur, *hd, *tail;

        cur = head;
        while (cur) {
            auto* node = new Node(cur->val);
            node->next = cur->next;
            cur->next = node;
            cur = node->next;
        }

        cur = head;
        while (cur) {
            if (cur->random)
                cur->next->random = cur->random->next;
            cur = cur->next->next;
        }

        cur = head;
        hd = tail = head->next;
        while (cur) {
            cur->next = cur->next->next;
            if (tail->next)
                tail->next = tail->next->next;
            cur = cur->next;
            tail = tail->next;
        }

        return hd;
    }
};

/* Second Solution:
 *
 *       +-------------+
 *       |             v
 *    +-------+    +-------+    +-------+
 *    | node1 |----> node2 |----> node3 |--->NULL
 *    +-------+    +-------+    +-------+
 *      ^  ^           |           |
 *      |  +-----------+           |
 *      +--------------------------+
 *
 *  1) Using a map to store each node's random pointer's position
 *
 *      map[node1->random] = 1;
 *      map[node2->random] = 0;
 *      map[node3->random] = 0;
 *
 *  2) Clone the linked list (only consider the next pointer)
 *
 *      new1 --> new2 --> new3 --> NULL
 *
 *  3) Using an array to strore the order of the cloned linked-list
 *
 *      v[0] = &new1
 *      v[1] = &new2
 *      v[2] = &new3
 *
 *  4) Then we can clone the random pointers.
 *
 *      new->random = v [ map[node->random] ]
 *
 */
