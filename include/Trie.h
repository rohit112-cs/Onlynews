#ifndef TRIE_H
#define TRIE_H

#include <memory>
#include <unordered_map>
#include <string>
#include <vector>

class TrieNode {
public:
    std::unordered_map<char,std::shared_ptr<TrieNode>> children;
    bool isEndOfWord;
    std::string value;
    TrieNode();
};

class Trie {
private:
    std::shared_ptr<TrieNode> root;
    void collectWords(const std::shared_ptr<TrieNode>& node, const std::string& prefix, std::vector<std::string>& results);
public:
    Trie();
    void insert(const std::string& word, const std::string& original = "");
    bool searchExact(const std::string& word);
    std::string getExactMatch(const std::string& word);
    std::vector<std::string> searchPrefix(const std::string& prefix);
};

#endif
