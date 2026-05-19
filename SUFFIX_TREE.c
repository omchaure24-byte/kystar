#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256

// Trie Node
struct Node {
    struct Node *children[MAX];
    int isEnd;
    int count; // for repeated substring
};

// Create new node
struct Node* createNode() {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->isEnd = 0;
    node->count = 0;

    for (int i = 0; i < MAX; i++)
        node->children[i] = NULL;

    return node;
}

//////////////////////////////////////////////////////
// INSERT SUFFIX
void insert(struct Node* root, char *suffix) {
    struct Node* temp = root;

    for (int i = 0; suffix[i] != '\0'; i++) {
        int index = suffix[i];

        if (temp->children[index] == NULL)
            temp->children[index] = createNode();

        temp = temp->children[index];
        temp->count++;
    }

    temp->isEnd = 1;
}

//////////////////////////////////////////////////////
// BUILD SUFFIX TREE (TRIE)
void buildSuffixTree(struct Node* root, char *str) {
    int n = strlen(str);

    for (int i = 0; i < n; i++) {
        insert(root, &str[i]);
    }
}

//////////////////////////////////////////////////////
// SEARCH PATTERN
int search(struct Node* root, char *pattern) {
    struct Node* temp = root;

    for (int i = 0; pattern[i] != '\0'; i++) {
        int index = pattern[i];

        if (temp->children[index] == NULL)
            return 0;

        temp = temp->children[index];
    }

    return 1;
}

//////////////////////////////////////////////////////
// DISPLAY ALL SUFFIXES (DFS)
void display(struct Node* root, char *path, int level) {
    if (root->isEnd) {
        path[level] = '\0';
        printf("%s\n", path);
    }

    for (int i = 0; i < MAX; i++) {
        if (root->children[i] != NULL) {
            path[level] = i;
            display(root->children[i], path, level + 1);
        }
    }
}

//////////////////////////////////////////////////////
// LONGEST REPEATED SUBSTRING
void longestRepeated(struct Node* root, char *path, int level, char *result, int *maxLen) {

    if (root->count < 2)
        return;

    if (level > *maxLen) {
        *maxLen = level;
        strncpy(result, path, level);
        result[level] = '\0';
    }

    for (int i = 0; i < MAX; i++) {
        if (root->children[i] != NULL) {
            path[level] = i;
            longestRepeated(root->children[i], path, level + 1, result, maxLen);
        }
    }
}

//////////////////////////////////////////////////////
// MAIN
int main() {
    struct Node* root = createNode();

    char str[100], pattern[100];
    int choice;

    printf("Enter string: ");
    scanf("%s", str);

    buildSuffixTree(root, str);

    while (1) {
        printf("\n===== SUFFIX TREE MENU =====\n");
        printf("1. Search Pattern\n");
        printf("2. Display All Suffixes\n");
        printf("3. Longest Repeated Substring\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter pattern: ");
            scanf("%s", pattern);

            if (search(root, pattern))
                printf("Pattern FOUND!\n");
            else
                printf("Pattern NOT FOUND!\n");
            break;

        case 2: {
            char path[100];
            printf("All suffixes:\n");
            display(root, path, 0);
            break;
        }

        case 3: {
            char path[100], result[100];
            int maxLen = 0;

            longestRepeated(root, path, 0, result, &maxLen);

            if (maxLen == 0)
                printf("No repeated substring found!\n");
            else
                printf("Longest Repeated Substring: %s\n", result);

            break;
        }

        case 4:
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }
}







// Operation	Complexity
// Build suffix structure	O(n²)
// Pattern search	O(m)
// Longest repeated substring	O(n²)










//What is a Suffix Tree?

// A Suffix Tree is a compressed tree that stores all suffixes of a string.

// 👉 It helps to:

// Search patterns fast
// Find repeated substrings
// Work with DNA, text processing, plagiarism tools
// 🔥 First: What is a suffix?

// A suffix is a substring that starts from some position to the end.

// Example string:

// banana

// All suffixes are:

// banana
// anana
// nana
// ana
// na
// a
// 🔷 Step 1: Add special character $

// We always add $ to mark end:

// banana$

// Why?
// 👉 To ensure every suffix is unique

// 🔷 Step 2: All suffixes of "banana$"
// banana$
// anana$
// nana$
// ana$
// na$
// a$
// $
// 🔷 Step 3: Build Suffix Tree (Concept)

// Instead of storing full words repeatedly, we share common prefixes.

// 🔥 Important idea:
// “ana” appears multiple times
// so we reuse same path
// 🔷 STEP-BY-STEP BUILDING (Simple view)

// We insert suffixes one by one:

// 🔹 Insert "banana$"
// banana$
// 🔹 Insert "anana$"

// Shares “ana”

// b → a → n → a → n → a$
//       ↘ a → n → a$
// 🔹 Insert "nana$"
// b
// a → n → a → n → a$
//       ↘ a → n → a$
// n → a → n → a$

// (Conceptually shared paths)

// 🔥 Final Idea of Suffix Tree

// Instead of many strings:

// 👉 We get a tree where:

// Each path = suffix
// Common parts are shared
// 🔷 Now understand your problem requirements
// 🔥 1. Construct suffix tree

// 👉 Insert all suffixes of string into tree

// Example:

// banana$
// 🔥 2. Pattern matching

// Suppose pattern = "ana"

// We traverse:

// a → n → a

// ✔ If path exists → pattern FOUND

// Example:

// Pattern = "nan"

// n → a → n

// ✔ FOUND in tree

// 🔥 3. Display all suffixes

// Just traverse tree DFS:

// Output:

// banana$
// anana$
// nana$
// ana$
// na$
// a$
// $
// 🔥 4. Longest repeated substring

// 👉 Find deepest path that occurs more than once

// Example:

// String:

// banana$

// Repeated substring:

// 👉 "ana"

// Because:

// appears in banana
// appears in anana part

// ✔ Longest repeated substring = ana

// 🔷 Why suffix tree is powerful?

// Because it reduces repeated work:

// Operation	Time
// Build	O(n²) (simple version)
// Search	O(m)
// Repeated substring	O(n)
// 🔥 Real Life Applications

// ✔ DNA sequence matching
// ✔ Plagiarism detection
// ✔ Text search engines
// ✔ Data compression
// ✔ Bioinformatics

// 🔷 Simple intuition

// 👉 Suffix Tree = “Tree of all endings of a string”

// 🔥 ONE-LINE EXAM DEFINITION

// A suffix tree is a compressed trie that contains all suffixes of a given string, allowing efficient pattern matching, substring search, and repeated substring detection.