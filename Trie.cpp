#include "RBT.h"
#include <iostream>

using namespace std;

RedBlackTree::RedBlackTree() {
    TNULL = new Node("");
    TNULL->color = BLACK;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
}

void RedBlackTree::leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != TNULL)
        y->left->parent = x;
    
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != TNULL)
        y->right->parent = x;
    
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    
    y->right = x;
    x->parent = y;
}

void RedBlackTree::fixInsert(Node* k) {
    Node* u;
    while (k->parent != nullptr && k->parent->color == RED) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left;
            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    k = k->parent;
                    rightRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->right;
            if (u->color == RED) {
                u->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    k = k->parent;
                    leftRotate(k);
                }
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        }
        if (k == root)
            break;
    }
    root->color = BLACK;
}

void RedBlackTree::insert(const string& word) {
    Node* node = new Node(word);
    node->parent = nullptr;
    node->left = TNULL;
    node->right = TNULL;
    node->color = RED;
    
    Node* y = nullptr;
    Node* x = root;
    
    while (x != TNULL) {
        y = x;
        if (node->word < x->word)
            x = x->left;
        else
            x = x->right;
    }
    
    node->parent = y;
    if (y == nullptr)
        root = node;
    else if (node->word < y->word)
        y->left = node;
    else
        y->right = node;
    
    if (node->parent == nullptr) {
        node->color = BLACK;
        return;
    }
    
    if (node->parent->parent == nullptr)
        return;
    
    fixInsert(node);
}

void RedBlackTree::prefixHelper(Node* node, const string& prefix, vector<string>& words) {
    if (node == TNULL || node == nullptr)
        return;
    
    // If the node's word starts with the prefix, add it.
    if (node->word.compare(0, prefix.size(), prefix) == 0)
        words.push_back(node->word);
    
    if (node->left != TNULL)
        prefixHelper(node->left, prefix, words);
    if (node->right != TNULL)
        prefixHelper(node->right, prefix, words);
}

vector<string> RedBlackTree::suggestWords(const string& prefix) {
    vector<string> suggestions;
    prefixHelper(root, prefix, suggestions);
    return suggestions;
}

RedBlackTree::~RedBlackTree() {
    // For simplicity, only the sentinel is deleted.
    // In a complete implementation, you’d traverse and delete all nodes.
    delete TNULL;
}
