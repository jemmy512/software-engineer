#include <iostream>
#include <string>
#include <vector>
#include <string>

struct TrieNode {
    char data;
    TrieNode** children = nullptr;
    bool isEndingChar = false;

    TrieNode() = default;

    TrieNode(char data) {
        data = data;
        children = new TrieNode*[CharSize];
    }

    ~TrieNode() {
        for (auto i = 0; i < CharSize; ++i)
            delete children[i];

        if (children != nullptr)
            delete[] children;
    }

    constexpr static int CharSize = 26;
};


class Trie {
public:
    void insert(const std::string& text) {
        auto* p = root;
        for (int i = 0; i < text.size(); ++i) {
            int index = text[i] - 'a';

            if (p->children[index] == nullptr) {
                auto* newNode = new TrieNode(text[i]);
                p->children[index] = newNode;
            }

            p = p->children[index];
        }

        p->isEndingChar = true;
    }

    bool find(const std::string& pattern) {
        auto* p = root;
        for (int i = 0; i < pattern.size(); ++i) {
            int index = pattern[i] - 'a';

            if (p->children[index] == nullptr) {
                return false;
            }

            p = p->children[index];
        }

        return p->isEndingChar;
    }

private:
    TrieNode* root = new TrieNode('/');

};

int main() {
    std::vector<std::string> vec{"hello", "her", "hi", "how", "so", "se"};

    Trie trie;
    for (const auto& v : vec) {
        trie.insert(v);
    }

    vec.emplace_back("sk");
    vec.emplace_back("hkw");
    for (const auto& v : vec) {
        std::cout << "find: " << v <<  " | " << trie.find(v) << std::endl;;
    }

    return 0;
}