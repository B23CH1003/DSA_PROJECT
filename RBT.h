#ifndef RBT_H
#define RBT_H

#include <string>
#include <vector>
using namespace std;

class RedBlackTree {
private:
    enum Color { RED, BLACK };
    
    struct Node {
        string word;
        Node* left;
        Node* right;
        Node* parent;
        Color color;
        Node(const string &w) : word(w), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
    };
    
    Node* root;
    Node* TNULL; // Sentinel node to represent null leaves
    
    // Helper functions for rotations and balancing.
    void fixInsert(Node* k);
    void leftRotate(Node* x);
    void rightRotate(Node* x);
    // Recursive helper to collect words with matching prefix.
    void prefixHelper(Node* node, const string& prefix, vector<string>& words);
    
public:
    RedBlackTree();
    // Insert a word into the Red-Black Tree.
    void insert(const string& word);
    // Returns all words with the given prefix.
    vector<string> suggestWords(const string& prefix);
    ~RedBlackTree();
};

#endif  // RBT_H
