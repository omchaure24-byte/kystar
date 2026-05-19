#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie Node
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int isEnd;
};

// Create new node
struct TrieNode *createNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    node->isEnd = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;

    return node;
}

//////////////////////////////////////////////////////
// INSERT WORD
void insert(struct TrieNode *root, char *word) {
    struct TrieNode *temp = root;

    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';

        if (temp->children[index] == NULL) {
            temp->children[index] = createNode();
        }

        temp = temp->children[index];
    }

    temp->isEnd = 1;
}

//////////////////////////////////////////////////////
// SEARCH WORD
int search(struct TrieNode *root, char *word) {
    struct TrieNode *temp = root;

    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';

        if (temp->children[index] == NULL)
            return 0;

        temp = temp->children[index];
    }

    return (temp != NULL && temp->isEnd);
}

//////////////////////////////////////////////////////
// CHECK IF NODE HAS CHILDREN
int isEmpty(struct TrieNode *node) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL)
            return 0;
    }
    return 1;
}

//////////////////////////////////////////////////////
// DISPLAY WORDS FROM NODE
void display(struct TrieNode *root, char *prefix, int level) {
    if (root->isEnd) {
        prefix[level] = '\0';
        printf("%s\n", prefix);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            prefix[level] = i + 'a';
            display(root->children[i], prefix, level + 1);
        }
    }
}

//////////////////////////////////////////////////////
// PREFIX MATCHING
void prefixSearch(struct TrieNode *root, char *prefix) {
    struct TrieNode *temp = root;

    for (int i = 0; prefix[i] != '\0'; i++) {
        int index = prefix[i] - 'a';

        if (temp->children[index] == NULL) {
            printf("No words found with this prefix.\n");
            return;
        }

        temp = temp->children[index];
    }

    printf("Words with prefix '%s':\n", prefix);

    char buffer[100];
    strcpy(buffer, prefix);

    display(temp, buffer, strlen(prefix));
}

//////////////////////////////////////////////////////
// MAIN FUNCTION
int main() {
    struct TrieNode *root = createNode();

    int choice;
    char word[100];

    while (1) {
        printf("\n===== TRIE MENU =====\n");
        printf("1. Insert Word\n");
        printf("2. Search Word\n");
        printf("3. Prefix Search\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter word: ");
            scanf("%s", word);
            insert(root, word);
            printf("Inserted successfully!\n");
            break;

        case 2:
            printf("Enter word to search: ");
            scanf("%s", word);

            if (search(root, word))
                printf("Word FOUND!\n");
            else
                printf("Word NOT FOUND!\n");
            break;

        case 3:
            printf("Enter prefix: ");
            scanf("%s", word);
            prefixSearch(root, word);
            break;

        case 4:
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }
}





// 1. What is a Trie?

// A Trie is a tree-like data structure used to store strings (words) in a way that makes:

// 🔍 Searching fast
// ✏️ Prefix matching efficient
// 📚 Dictionary operations easy

// 👉 It is mainly used for string-based problems

// 🧠 2. Why Trie is useful?

// Instead of storing words separately like:

// cat, car, card, dog

// Trie stores them in shared prefix form:

// 🌲 3. Trie Structure Example

// Words:

// cat, car, card, dog

// Trie looks like:

// (root)
//  ├── c
//  │    ├── a
//  │    │    ├── t (end)
//  │    │    └── r
//  │    │         └── d (end)
//  │
//  └── d
//       └── o
//            └── g (end)

// 👉 Same prefix “ca” is shared → saves time and space

// ⚙️ 4. Operations in Trie

// We implement 4 main operations:

// ✍️ (A) Insert Word

// Example: Insert "car"

// Steps:

// c → create node
// a → create node
// r → create node
// mark end of word
// 🔍 (B) Search Word

// Example: Search "car"

// We check:

// c exists ✔
// a exists ✔
// r exists ✔
// end marker ✔ → FOUND

// If any missing → NOT FOUND

// 📌 (C) Prefix Search

// Example: "ca"

// We check:

// c ✔
// a ✔

// 👉 prefix exists, so words start with "ca" exist

// 📚 (D) Display Words with Prefix

// If prefix = "ca"
// We collect all words starting from that node:

// cat
// car
// card
// 💻 5. C Implementation of Trie
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define ALPHABET_SIZE 26

// // Trie Node
// struct TrieNode {
//     struct TrieNode *children[ALPHABET_SIZE];
//     int isEnd;
// };

// // Create new node
// struct TrieNode* getNode() {
//     struct TrieNode *node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
//     node->isEnd = 0;

//     for (int i = 0; i < ALPHABET_SIZE; i++)
//         node->children[i] = NULL;

//     return node;
// }

// // Insert word
// void insert(struct TrieNode *root, char *word) {
//     struct TrieNode *curr = root;

//     for (int i = 0; word[i] != '\0'; i++) {
//         int index = word[i] - 'a';

//         if (curr->children[index] == NULL)
//             curr->children[index] = getNode();

//         curr = curr->children[index];
//     }

//     curr->isEnd = 1;
// }

// // Search word
// int search(struct TrieNode *root, char *word) {
//     struct TrieNode *curr = root;

//     for (int i = 0; word[i] != '\0'; i++) {
//         int index = word[i] - 'a';

//         if (curr->children[index] == NULL)
//             return 0;

//         curr = curr->children[index];
//     }

//     return (curr != NULL && curr->isEnd);
// }

// // Check prefix exists
// int startsWith(struct TrieNode *root, char *prefix) {
//     struct TrieNode *curr = root;

//     for (int i = 0; prefix[i] != '\0'; i++) {
//         int index = prefix[i] - 'a';

//         if (curr->children[index] == NULL)
//             return 0;

//         curr = curr->children[index];
//     }

//     return 1;
// }

// // Print all words from a node
// void printAll(struct TrieNode *root, char *prefix, int level) {
//     if (root->isEnd) {
//         prefix[level] = '\0';
//         printf("%s\n", prefix);
//     }

//     for (int i = 0; i < 26; i++) {
//         if (root->children[i]) {
//             prefix[level] = i + 'a';
//             printAll(root->children[i], prefix, level + 1);
//         }
//     }
// }

// // Display words with prefix
// void displayPrefix(struct TrieNode *root, char *prefix) {
//     struct TrieNode *curr = root;

//     for (int i = 0; prefix[i] != '\0'; i++) {
//         int index = prefix[i] - 'a';

//         if (curr->children[index] == NULL) {
//             printf("No words found\n");
//             return;
//         }

//         curr = curr->children[index];
//     }

//     char word[100];
//     strcpy(word, prefix);

//     printAll(curr, word, strlen(prefix));
// }

// int main() {
//     struct TrieNode *root = getNode();

//     // Dictionary insert
//     insert(root, "cat");
//     insert(root, "car");
//     insert(root, "card");
//     insert(root, "dog");
//     insert(root, "door");

//     printf("Search car: %d\n", search(root, "car"));
//     printf("Search cap: %d\n", search(root, "cap"));

//     printf("\nWords with prefix 'ca':\n");
//     displayPrefix(root, "ca");

//     return 0;
// }
// ⏱️ 6. Time Complexity

// Let:

// n = number of words
// m = length of word
// 📌 Insert:
// O(m)
// 📌 Search:
// O(m)
// 📌 Prefix search:
// O(m)
// 📌 Display words:
// O(number of characters in subtree)
// 📦 Space Complexity
// O(ALPHABET_SIZE × N × M)
// 👉 Can be high due to pointers
// 👍 7. Advantages of Trie

// ✔ Very fast search (better than BST/Hash for prefixes)
// ✔ Efficient prefix matching
// ✔ Used in autocomplete systems
// ✔ No need to compare full strings repeatedly

// 👎 8. Disadvantages

// ❌ High memory usage
// ❌ Complex implementation
// ❌ Not suitable for small datasets
// ❌ Fixed alphabet makes it inefficient for large character sets

// 🚀 9. Applications

// Trie is used in:

// 🔎 Google search autocomplete
// 📱 Keyboard suggestions
// 📚 Dictionary implementation
// 🧠 Spell checkers
// 🌐 IP routing (longest prefix match)
// 🧾 Contact search apps
// 🧾 FINAL SUMMARY

// Trie is a tree for strings where:

// Each node = character
// Words share prefixes
// Fast search + fast prefix matching