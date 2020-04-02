#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <queue>
#include <exception>

auto matchHandler = [](const std::string& text, int pos, int len) {
    std::cout << "Matched word:  " << std::string(text.begin() + pos, text.begin() + pos + len) << " | pos: " << pos << ", length: " << len << std::endl;
};


struct TrieNode {
    char data;
    TrieNode** children = nullptr;
    bool isEndingChar = false;
    TrieNode* fail = nullptr;   // Aho-Corasick search algorithm
    int length = 0;

    TrieNode(char chr) {
        data = chr;  // data = data;
        children = new TrieNode*[CharSize](); // value-initialization: children[i] is nullptr
    }

    ~TrieNode() {
        for (auto i = 0; i < CharSize; ++i) {
            delete children[i];
        }

        delete[] children;
    }

    constexpr static int CharSize = 26;
};


class Trie {
public:
    Trie(bool build = true) : isBuildFail(build) {}

    void insert(const std::string& text) {
        auto* cur = root;

        for (int i = 0; i < text.size(); ++i) {
            int idx = index(text[i]);

            if (cur->children[idx] == nullptr) {
                auto* newNode = new TrieNode(text[i]);
                cur->children[idx] = newNode;
                cur->children[idx]->length = cur->length + 1;

                if (isBuildFail)
                    buildFailurePointer(cur);
            }

            cur = cur->children[idx];
        }

        cur->isEndingChar = true;
    }

    bool find(const std::string& curattern) {
        auto* cur = root;

        for (int i = 0; i < curattern.size(); ++i) {
            int idx = index(curattern[i]);

            if (cur->children[idx] == nullptr) {
                return false;
            }

            cur = cur->children[idx];
        }

        return cur->isEndingChar;
    }

    void match(const std::string& text) {
        auto len = text.size();
        auto* cur = root;

        for (int i = 0; i < len; ++i) {
            auto idx = index(text[i]);

            while (cur->children[idx] == nullptr && cur != root) {
                cur = cur->fail;
            }

            cur = cur->children[idx];
            if (cur == nullptr)
                cur = root;

            auto* tmp = cur;
            while (tmp != root) {
                if (tmp->isEndingChar == true) {
                    auto pos = i - tmp->length + 1;
                    matchHandler(text, pos, tmp->length);
                }

                tmp = tmp->fail;
            }
        }

    }

void buildFailurePointer(const TrieNode* node = root) {
    auto queue = std::queue<TrieNode*>();
    if (node != nullptr)
        queue.push(root);

    while (!queue.empty()) {
        auto* cur = queue.front();
        queue.pop();

        for (int i = 0; i < 26; ++i) {
            auto* child = cur->children[i];
            if (child == nullptr)
                continue;

            if (cur == root) {
                child->fail = root;
            } else {
                auto* curFail = cur->fail;
                while (curFail != nullptr) {
                    auto* curFailChild = curFail->children[index(child)];
                    if (curFailChild != nullptr) {
                        child->fail = curFailChild;
                        break;
                    } else {
                        curFail = curFail->fail;
                    }
                }

                if (curFail == nullptr) {
                    child->fail = root;
                }
            }

            queue.push(child);
        }
    }
}

int index(const char& chr) {
    return chr - 'a';
}

int index(const TrieNode* node) {
    if (node != nullptr)
        return node->data - 'a';
    else
        throw std::out_of_range("TrieNode is null, can't get it's index!");
}

private:
    bool isBuildFail = true;
    inline static TrieNode* root = new TrieNode('/');
};

int main() {
    std::vector<std::string> vec{"hello", "her", "hi", "how", "so", "se"};

    Trie trie;

    for (const auto& v : vec) {
        trie.insert(v);
    }

    trie.match("howhellohihowsosejemmyjie");

    vec.emplace_back("sk");
    vec.emplace_back("hkw");
    for (const auto& v : vec) {
        std::cout << "find: " << v <<  " | " << trie.find(v) << std::endl;;
    }

    return 0;
}