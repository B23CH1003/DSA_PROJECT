#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
#include <unordered_map>

class Trie {
private:
    struct Node {
        bool isEndOfWord;
        std::unordered_map<char, Node*> children;
    };
    
    Node* root;

    // Helper function for getAllWords
    void getAllWordsHelper(Node* node, const std::string& prefix, std::vector<std::string>& words) const;

    // Helper function for suggestWords
    Node* findNode(const std::string& prefix) const;

public:
    Trie();
    
    
    // Basic Trie functions
    void insert(const std::string& word);
    
    // Suggestion functions
    std::vector<std::string> suggestWords(const std::string& prefix);
    std::vector<std::string> getAllWords() const;
    ~Trie();
    // Destructor
    void deleteTrie(Node* node);
};

#endif
