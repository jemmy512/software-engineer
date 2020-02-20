#include <iostream>

struct Node {
	int val;
	Node* next;
};

#define Pln(x) std::cout << x << std::endl;

Node* createList(const int* nodes, int size) {
	if (nodes == nullptr || size < 0)
		return nullptr;

	Node* beg = nullptr;
	Node* end = nullptr;
	for (auto idx = 0; idx < size; ++idx) {
		Node* node = new Node;
		node->val = nodes[idx];
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

Node* findMiddleNode(Node* node) {
	if (node == nullptr)
		return nullptr;

	Node* slow = node;
	Node* fast = node;
	while (fast != nullptr && fast->next != nullptr) {
		fast = fast->next->next;
		slow = slow->next;
	}

	return slow;
}

int main() {
	int node1[1]{1};
	int node2[2]{1, 2};
	int node3[3]{1, 2, 3};
	int node4[4]{1, 2, 3, 4};
	int node5[5]{1, 2, 3, 4, 5};

	Node* begOne = createList(node1, 1);
	Node* begTwo = createList(node2, 2);
	Node* begThree = createList(node3, 3);
	Node* begFour = createList(node4, 4);
	Node* begFive = createList(node5, 5);

	Node* one = findMiddleNode(begOne);
	Node* two = findMiddleNode(begTwo);
	Node* three = findMiddleNode(begThree);
	Node* four = findMiddleNode(begFour);
	Node* five = findMiddleNode(begFive);

	Pln(one->val);
	Pln(two->val);
	Pln(three->val);
	Pln(four->val);
	Pln(five->val);

	releaseList(one);
	releaseList(two);
	releaseList(three);
	releaseList(four);
	releaseList(five);

	return 0;
}
