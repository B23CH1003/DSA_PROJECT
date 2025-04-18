#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <string>
#include "Trie.h"
#include "RBT.h"
#include <algorithm> // For std::binary_search and std::lower_bound

using namespace std;
using namespace std::chrono;

// Trim whitespace from the string
string trim(const string &s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    if (start == string::npos)
        return "";
    return s.substr(start, end - start + 1);
}

// Function to calculate Levenshtein distance
int levenshteinDistance(const string& a, const string& b) {
    int m = a.size(), n = b.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (int i = 0; i <= m; ++i) dp[i][0] = i;
    for (int j = 0; j <= n; ++j) dp[0][j] = j;

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else {
                int minVal = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1]));
                dp[i][j] = 1 + minVal;
            }
        }
    }

    return dp[m][n];
}

// Function to suggest spelling corrections using Levenshtein Distance
vector<string> suggestSpelling(const Trie& trie, const string& word, int maxDistance = 2) {
    vector<string> suggestions;
    vector<string> allWords = trie.getAllWords();  // Assuming Trie has a function to get all words

    for (const string& w : allWords) {
        if (levenshteinDistance(word, w) <= maxDistance) {
            suggestions.push_back(w);
        }
    }

    return suggestions;
}

// Function to load words into both the Trie and Red-Black Tree
void loadWords(Trie& trie, RedBlackTree& rbt, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }
    
    string line;
    while (getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;
        
        // Directly insert the line (word) into the Trie and RBT.
        trie.insert(line);
        rbt.insert(line);
    }
    file.close();
}

// Function to insert a word into the words.txt file (used only for inserting new words)
void insertWordInFile(const string& filename, const string& word) {
    // Read the file into a vector of strings
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    vector<string> words;
    string line;
    while (getline(file, line)) {
        line = trim(line);
        if (!line.empty()) {
            words.push_back(line);
        }
    }
    file.close();

    // Check if the word already exists in the vector (binary search for efficiency)
    if (binary_search(words.begin(), words.end(), word)) {
        cout << "The word \"" << word << "\" is already present in the file.\n";
        return;
    }

    // Find the correct position to insert the word (using lower_bound for binary insertion)
    auto pos = lower_bound(words.begin(), words.end(), word);
    words.insert(pos, word);

    // Write the updated list of words back to the file
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    for (const string& w : words) {
        outFile << w << "\n";
    }

    outFile.close();
    cout << "The word \"" << word << "\" has been inserted into the file.\n";
}

// Function to delete a word from the words.txt file
void deleteWordFromFile(const string& filename, const string& word) {
    // Read the file into a vector of strings
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    vector<string> words;
    string line;
    while (getline(file, line)) {
        line = trim(line);
        if (!line.empty()) {
            words.push_back(line);
        }
    }
    file.close();

    // Use binary search to find the word
    auto it = lower_bound(words.begin(), words.end(), word);
    
    // Check if the word exists at the position returned by lower_bound
    if (it != words.end() && *it == word) {
        // Word is found, erase it from the vector
        words.erase(it);
        cout << "The word \"" << word << "\" has been deleted from the file.\n";
    } else {
        // Word is not found, print a message
        cout << "The word \"" << word << "\" was not found in the file.\n";
        return;  // No need to rewrite the file if the word was not found
    }

    // Write the updated list of words back to the file
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    // Write each word in the sorted list to the file
    for (const string& w : words) {
        outFile << w << "\n";
    }

    outFile.close();
}

int main() {
    cout << "Starting the program..." << endl;

    Trie trie;
    RedBlackTree rbt;

    loadWords(trie, rbt, "words.txt");

    string prefix;
    cout << "Program started successfully." << endl;

    while (true) {
        cout << "Enter a prefix to get suggestions (or type 'exit' to quit): ";
        cin >> prefix;

        if (prefix == "exit") break;

        // --- Trie suggestions ---
        auto start = high_resolution_clock::now();
        vector<string> trieSuggestions = trie.suggestWords(prefix);
        auto end = high_resolution_clock::now();
        auto durationTrie = duration_cast<microseconds>(end - start);

        // --- RBT suggestions ---
        start = high_resolution_clock::now();
        vector<string> rbtSuggestions = rbt.suggestWords(prefix);
        end = high_resolution_clock::now();
        auto durationRBT = duration_cast<microseconds>(end - start);

        // --- Output Trie results ---
        cout << "\nSuggestions from Trie:\n";
        if (trieSuggestions.empty()) {
            cout << " No suggestions found in Trie.\n";
        } else {
            for (const string& word : trieSuggestions)
                cout << "  - " << word << endl;
        }
        cout << "Trie time: " << durationTrie.count() << " microsecond\n";

        // --- Output RBT results ---
        cout << "\nSuggestions from Red-Black Tree:\n";
        if (rbtSuggestions.empty()) {
            cout << " No suggestions found in RBT.\n";
        } else {
            for (const string& word : rbtSuggestions)
                cout << "  - " << word << endl;
        }
        cout << "RBT time: " << durationRBT.count() << " microsecond\n";

        // --- Comparison ---
        if (durationTrie < durationRBT)
            cout << "\n Trie was faster by " << (durationRBT - durationTrie).count() << " microsecond\n";
        else if (durationRBT < durationTrie)
            cout << "\n RBT was faster by " << (durationTrie - durationRBT).count() << " microsecond\n";
        else
            cout << "\n Both performed equally.\n";

        // --- Spell Correction (if both failed) ---
        if (trieSuggestions.empty() && rbtSuggestions.empty()) {
            cout << "\n Did you mean:\n";
            vector<string> corrections = suggestSpelling(trie, prefix);
            if (corrections.empty()) {
                cout << "  (No similar words found.)\n";
            } else {
                for (const string& word : corrections)
                    cout << "  - " << word << endl;
            }
        }

        cout << "\n---------------------------\n";

        // Prompt user to insert or delete a word
        string action;
        cout << "Would you like to insert or delete a word? (insert/delete/skip): ";
        cin >> action;

        if (action == "insert") {
            string newWord;
            cout << "Enter a word to insert into the file: ";
            cin >> newWord;
            insertWordInFile("words.txt", newWord);
        } else if (action == "delete") {
            string wordToDelete;
            cout << "Enter a word to delete from the file: ";
            cin >> wordToDelete;
            deleteWordFromFile("words.txt", wordToDelete);
        } else if (action == "skip") {
            continue;
        }
    }

    return 0;
}
