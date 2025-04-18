# DSA_PROJECT
# DSA Final Project

This project implements a word suggestion and management system using **Trie** and **Red-Black Tree (RBT)** data structures. The system supports functionalities such as word insertion, deletion, prefix-based suggestions, and spelling corrections.

## Features

1. **Word Management**:
   - Insert new words into the `words.txt` file.
   - Delete existing words from the `words.txt` file.

2. **Word Suggestions**:
   - Suggest words based on a given prefix using both Trie and Red-Black Tree.
   - Compare the performance of Trie and Red-Black Tree for prefix-based suggestions.

3. **Spelling Correction**:
   - Suggest similar words using Levenshtein Distance if no exact matches are found.

4. **Data Persistence**:
   - All words are stored in a sorted text file (`words.txt`) for persistence.

---

## File Structure

### Source Files

1. **[main.cpp](c:\Users\bagdi\OneDrive\Desktop\dsa final porject\main.cpp)**:
   - Entry point of the program.
   - Handles user interaction for word insertion, deletion, and suggestions.
   - Implements Levenshtein Distance for spelling correction.
   - Loads words into both Trie and Red-Black Tree from `words.txt`.

2. **[Trie.h](c:\Users\bagdi\OneDrive\Desktop\dsa final porject\Trie.h)** and **[Trie.cpp](c:\Users\bagdi\OneDrive\Desktop\dsa final porject\Trie.cpp)**:
   - Implements the Trie data structure.
   - Supports word insertion, prefix-based suggestions, and retrieval of all words.

3. **[RBT.h](c:\Users\bagdi\OneDrive\Desktop\dsa final porject\RBT.h)** and **[RBT.cpp](c:\Users\bagdi\OneDrive\Desktop\dsa final porject\RBT.cpp)**:
   - Implements the Red-Black Tree data structure.
   - Supports word insertion and prefix-based suggestions.

### Data File

- **[words.txt](c:\Users\bagdi\OneDrive\Desktop\dsa final porject\words.txt)**:
  - Stores all words in sorted order.
  - Used for loading words into Trie and Red-Black Tree at program startup.

---

## How to Run

1. **Compile the Program**:
   Use a C++ compiler to compile the source files. For example:
   ```bash
   g++ main.cpp Trie.cpp RBT.cpp -o project
