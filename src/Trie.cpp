#include "Trie.h"

TrieNode::TrieNode(): isEndOfWord(false) {}

Trie::Trie(): root(std::make_shared<TrieNode>()) {}

void Trie::insert(const std::string& word, const std::string& original) {
    auto node = root;
    for (char c : word) {
        if (node->children.find(c) == node->children.end()) {
            node->children[c] = std::make_shared<TrieNode>();
        }
        node = node->children[c];
    }
    node->isEndOfWord = true;
    node->value = original.empty() ? word : original;
}

bool Trie::searchExact(const std::string& word) {
    auto node = root;
    for (char c : word) {
        if (node->children.find(c) == node->children.end()) return false;
        node = node->children[c];
    }
    return node->isEndOfWord;
}

std::string Trie::getExactMatch(const std::string& word) {
    auto node = root;
    for (char c : word) {
        if (node->children.find(c) == node->children.end()) return "";
        node = node->children[c];
    }
    return node->isEndOfWord ? node->value : "";
}

std::vector<std::string> Trie::searchPrefix(const std::string& prefix) {
    std::vector<std::string> results;
    auto node = root;
    for (char c : prefix) {
        if (node->children.find(c) == node->children.end()) return results;
        node = node->children[c];
    }
    collectWords(node, prefix, results);
    return results;
}

void Trie::collectWords(const std::shared_ptr<TrieNode>& node, const std::string& prefix, std::vector<std::string>& results) {
    if (node->isEndOfWord) results.push_back(node->value);
    for (const auto &p : node->children) collectWords(p.second, prefix + p.first, results);
}
