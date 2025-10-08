#include <iostream>
#include <unordered_map>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEnd = false;
};

class Trie {
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }

    void insert(const string &word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c])
                node->children[c] = new TrieNode();
            node = node->children[c];
        }
        node->isEnd = true;
    }

    bool search(const string &word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->children[c])
                return false;
            node = node->children[c];
        }
        return node->isEnd;
    }
};