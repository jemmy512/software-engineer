/* Hard
Serialization is the process of converting a data structure or object into a sequence of bits
so that it can be stored in a file or memory buffer,
or transmitted across a network connection link to be reconstructed later
in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary tree.
There is no restriction on how your serialization/deserialization algorithm should work.
You just need to ensure that a binary tree can be serialized to a string
and this string can be deserialized to the original tree structure.

Clarification: The input/output format is the same as how LeetCode serializes
a binary tree. You do not necessarily need to follow this format,
so please be creative and come up with different approaches yourself.



Example 1:
Input: root = [1,2,3,null,null,4,5]
Output: [1,2,3,null,null,4,5]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [1]
Output: [1]

Example 4:
Input: root = [1,2]
Output: [1,2]


Constraints:
The number of nodes in the tree is in the range [0, 10^4].
-1000 <= Node.val <= 1000 */

#include <string>
#include <queue>
#include <sstream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string str;
        serialize(root, str);
        return str;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        auto que = split(data, ',');
        return deserialize(que);
    }

private:
    void serialize(TreeNode* node, string& str) {
        if (!node) {
            str += "#";
            str += ",";
            return;
        }

        str += std::to_string(node->val) + ",";

        serialize(node->left, str);
        serialize(node->right, str);
    }

    TreeNode* deserialize(queue<string>& que) {
        if (que.empty())
            return nullptr;

        const auto val = std::move(que.front());
        que.pop();

        if (val == "#") {
            return nullptr;
        }

        auto* node = new TreeNode(std::stoi(val));
        node->left = deserialize(que);
        node->right = deserialize(que);

        return node;
    }

    queue<string> split(const string& str, char delimiter ) {
        queue<string> que;
        string token;
        stringstream ss(str);

        while (getline(ss, token, delimiter)) {
            if (!token.empty()) {
                que.emplace(token);
            }
        }

        return que;
    }
};