/* Medium
A linked list of length n is given such that each node contains an additional random pointer,
which could point to any node in the list, or null.

Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes,
where each new node has its value set to the value of its corresponding original node.
Both the next and random pointer of the new nodes should point to new nodes
in the copied list such that the pointers in the original list and copied list represent
the same list state. None of the pointers in the new list should point to nodes in the original list.

For example, if there are two nodes X and Y in the original list, where X.random --> Y,
then for the corresponding two nodes x and y in the copied list, x.random --> y.

Return the head of the copied linked list.

The linked list is represented in the input/output as a list of n nodes.
Each node is represented as a pair of [val, random_index] where:

val: an integer representing Node.val
random_index: the index of the node (range from 0 to n-1) that the random pointer points to,
or null if it does not point to any node.
Your code will only be given the head of the original linked list.

Constraints:
0 <= n <= 1000
-10000 <= Node.val <= 10000
Node.random is null or is pointing to some node in the linked list. */

/* The idea as below:
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
 *    3) After we take out all of the "NEW" node to finish the copy. */

struct Node {
    int val;
    Node* next;
    Node* random;
    Node(int _val) : val(_val), next(nullptr), random(nullptr) {}
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) {
            return nullptr;
        }

        Node *cur, *hd, *tail;

        cur = head;
        while (cur) {
            auto* node = new Node(cur->val);
            node->next = cur->next;
            cur->next = node;
            cur = node->next;
        }

        cur = head;
        while (cur) {
            if (cur->random) {
                cur->next->random = cur->random->next;
            }
            cur = cur->next->next;
        }

        cur = head;
        hd = tail = head->next;
        while (cur) {
            cur->next = tail->next;
            if (tail->next) {
                tail = tail->next = tail->next->next;
            }
            cur = cur->next;
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
 *      new->random = v [ map[node->random] ] */
