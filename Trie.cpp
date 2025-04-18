#include "Trie.h"
#include <iostream>

using namespace std;

// Constructor
Trie::Trie() {
    root = new Node();
}

// Destructor
Trie::~Trie() {
    deleteTrie(root);
}

// Helper function to delete the Trie
void Trie::deleteTrie(Node* node) {
    if (node == nullptr) return;
    for (auto& pair : node->children) {
        deleteTrie(pair.second);
    }
    delete node;
}

// Insert a word into the Trie
void Trie::insert(const string& word) {
    Node* currentNode = root;
    for (char ch : word) {
        if (currentNode->children.find(ch) == currentNode->children.end()) {
            currentNode->children[ch] = new Node();
        }
        currentNode = currentNode->children[ch];
    }
    currentNode->isEndOfWord = true;
}

// Helper function to find the node at the end of the prefix
Trie::Node* Trie::findNode(const string& prefix) const {
    Node* currentNode = root;
    for (char ch : prefix) {
        if (currentNode->children.find(ch) == currentNode->children.end()) {
            return nullptr;
        }
        currentNode = currentNode->children[ch];
    }
    return currentNode;
}

// Helper function to get all words from a node
void Trie::getAllWordsHelper(Node* node, const string& prefix, vector<string>& words) const {
    if (node == nullptr) return;
    if (node->isEndOfWord) words.push_back(prefix);
    for (auto& pair : node->children) {
        getAllWordsHelper(pair.second, prefix + pair.first, words);
    }
}

// Get all words from the Trie
vector<string> Trie::getAllWords() const {
    vector<string> words;
    getAllWordsHelper(root, "", words);
    return words;
}

// Suggest words with the given prefix
vector<string> Trie::suggestWords(const string& prefix) {
    vector<string> suggestions;
    Node* node = findNode(prefix);
    if (node != nullptr) {
        getAllWordsHelper(node, prefix, suggestions);
    }
    return suggestions;
}
