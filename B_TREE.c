#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 1

typedef struct Node {

    int keys[MAX + 1];
    struct Node *child[MAX + 2];

    int count;
    int leaf;

} Node;

Node *root = NULL;

// Create Node
Node* createNode(int leaf) {

    Node *newNode = (Node*)malloc(sizeof(Node));

    newNode->count = 0;
    newNode->leaf = leaf;

    for(int i = 0; i < MAX + 2; i++)
        newNode->child[i] = NULL;

    return newNode;
}

// Display
void display(Node *ptr, int level) {

    if(ptr != NULL) {

        printf("Level %d : ", level);

        for(int i = 0; i < ptr->count; i++)
            printf("%d ", ptr->keys[i]);

        printf("\n");

        for(int i = 0; i <= ptr->count; i++)
            display(ptr->child[i], level + 1);
    }
}

// Search
int search(Node *ptr, int key) {

    if(ptr == NULL)
        return 0;

    int i = 0;

    while(i < ptr->count && key > ptr->keys[i])
        i++;

    if(i < ptr->count && key == ptr->keys[i])
        return 1;

    return search(ptr->child[i], key);
}

// Split Child
void splitChild(Node *parent, int index, Node *child) {

    Node *newChild = createNode(child->leaf);

    newChild->count = MIN;

    // Move keys
    for(int i = 0; i < MIN; i++)
        newChild->keys[i] = child->keys[i + MIN + 1];

    // Move children
    if(!child->leaf) {

        for(int i = 0; i <= MIN; i++)
            newChild->child[i] = child->child[i + MIN + 1];
    }

    child->count = MIN;

    // Shift children
    for(int i = parent->count; i >= index + 1; i--)
        parent->child[i + 1] = parent->child[i];

    parent->child[index + 1] = newChild;

    // Shift keys
    for(int i = parent->count - 1; i >= index; i--)
        parent->keys[i + 1] = parent->keys[i];

    // Middle key goes up
    parent->keys[index] = child->keys[MIN];

    parent->count++;
}

// Insert Non Full
void insertNonFull(Node *ptr, int key) {

    int i = ptr->count - 1;

    // Leaf
    if(ptr->leaf) {

        while(i >= 0 && key < ptr->keys[i]) {

            ptr->keys[i + 1] = ptr->keys[i];
            i--;
        }

        ptr->keys[i + 1] = key;
        ptr->count++;
    }
    else {

        while(i >= 0 && key < ptr->keys[i])
            i--;

        i++;

        // Child full
        if(ptr->child[i]->count == MAX) {

            splitChild(ptr, i, ptr->child[i]);

            if(key > ptr->keys[i])
                i++;
        }

        insertNonFull(ptr->child[i], key);
    }
}

// Insert
void insert(int key) {

    if(root == NULL) {

        root = createNode(1);

        root->keys[0] = key;
        root->count = 1;

        return;
    }

    // Root full
    if(root->count == MAX) {

        Node *newRoot = createNode(0);

        newRoot->child[0] = root;

        splitChild(newRoot, 0, root);

        int i = 0;

        if(key > newRoot->keys[0])
            i++;

        insertNonFull(newRoot->child[i], key);

        root = newRoot;
    }
    else {

        insertNonFull(root, key);
    }
}

// Simple Delete from Leaf
void deleteKey(Node *ptr, int key) {

    if(ptr == NULL)
        return;

    int i = 0;

    while(i < ptr->count && key > ptr->keys[i])
        i++;

    // Found in leaf
    if(i < ptr->count && ptr->keys[i] == key && ptr->leaf) {

        for(int j = i; j < ptr->count - 1; j++)
            ptr->keys[j] = ptr->keys[j + 1];

        ptr->count--;

        printf("Key Deleted\n");

        return;
    }

    // Go child
    if(!ptr->leaf)
        deleteKey(ptr->child[i], key);
}

// Main
int main() {

    int choice, key;

    while(1) {

        printf("\n--- B-TREE MENU ---\n");

        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Display\n");
        printf("5. Exit\n");

        printf("Enter choice : ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:

                printf("Enter key : ");
                scanf("%d", &key);

                insert(key);

                break;

            case 2:

                printf("Enter key : ");
                scanf("%d", &key);

                deleteKey(root, key);

                break;

            case 3:

                printf("Enter key : ");
                scanf("%d", &key);

                if(search(root, key))
                    printf("Key Found\n");
                else
                    printf("Key Not Found\n");

                break;

            case 4:

                printf("\nB-Tree Structure:\n");

                display(root, 0);

                break;

            case 5:

                exit(0);

            default:

                printf("Invalid Choice\n");
        }
    }

    return 0;
}








// 🌳 1. What is a B-Tree?

// A B-Tree is a self-balancing multi-way search tree where:

// 👉 One node can contain multiple keys
// 👉 One node can have multiple children
// 👉 It stays always balanced

// It is mainly used in:

// 🗄️ Databases
// 💾 File systems
// 📚 Indexing systems
// ⭐ 2. Why B-Tree is needed?

// Normal BST (Binary Search Tree):

// Can become skewed (like a linked list)
// Search becomes slow → O(n)

// 👉 B-Tree solves this by:

// Keeping tree balanced
// Reducing height
// Storing multiple keys per node
// 📌 3. Properties of B-Tree (VERY IMPORTANT)

// Let order = m

// Each node:

// Can have at most m children
// Can have at most m − 1 keys
// Minimum children = ⌈m/2⌉
// Minimum keys = ⌈m/2⌉ − 1

// Other rules:

// Keys inside node are sorted
// All leaf nodes are at same level
// Tree is always balanced
// 🌲 4. Example of B-Tree (Order = 3)

// Let’s insert:

// 10, 20, 5, 6, 12, 30, 7, 17
// Step 1: Insert 10, 20, 5
// [5 10 20]

// Node is full (order 3 → max 2 keys allowed), so split:

//       [10]
//      /    \
//   [5]     [20]
// Step 2: Insert 6
//       [10]
//      /    \
//   [5 6]   [20]
// Step 3: Insert 12
//       [10]
//      /    \
//   [5 6]  [12 20]
// Step 4: Insert 30
//       [10]
//      /        \
//   [5 6]    [12 20 30]

// Split again:

//         [10 20]
//        /   |   \
//    [5 6] [12] [30]
// Step 5: Insert 7

// Goes to left side:

//         [10 20]
//        /   |   \
//  [5 6 7] [12] [30]

// Split left node:

//         [6 10 20]
//        /   |   |   \
//     [5]   [7] [12] [30]

// Split again (root overflow):

//           [10]
//         /      \
//      [6]       [20]
//     /   \      /   \
//  [5 7] [12]  [30]

// 👉 This shows how B-Tree grows but always stays balanced.

// 🔍 5. SEARCH Operation

// Example: Search 12

// Steps:

// Start at root [10]
// 12 > 10 → go right
// At [20], 12 < 20 → go left child
// Found [12] ✔

// 👉 Time = O(log n)

// ➕ 6. INSERT Operation

// Steps:

// Find correct leaf node
// Insert in sorted order
// If node overflows:
// Split node
// Move middle key to parent
// Repeat if needed

// 👉 Tree remains balanced automatically

// ❌ 7. DELETE Operation

// Steps:

// Find key
// If in leaf → remove directly
// If in internal node:
// Replace with predecessor/successor
// Fix underflow:
// Borrow from sibling OR
// Merge nodes
// Adjust parent

// 👉 Ensures balance always maintained

// 🌐 8. Traversal (In-order)

// B-Tree traversal gives sorted order:

// Example:

// 5 7 10 12 20 30
// 💻 9. Simple Concept of Working

// Think like this:

// 👉 Instead of storing 1 key per node (BST)
// 👉 B-Tree stores multiple keys per node

// So:

// Tree height becomes very small
// Disk reads become fewer
// Search becomes faster
// ⏱️ 10. Time Complexity

// Let:

// n = number of keys
// m = order of tree
// Operation	Complexity
// Search	O(log n)
// Insert	O(log n)
// Delete	O(log n)
// Traverse	O(n)

// 👉 Because height of B-Tree = log n

// 📦 11. Space Complexity
// O(n) for storing all keys
// Extra space for pointers
// 👍 12. Advantages of B-Tree

// ✔ Always balanced
// ✔ Fast search, insert, delete
// ✔ Good for large data
// ✔ Reduces disk I/O operations
// ✔ Efficient for databases

// 👎 13. Disadvantages

// ❌ Complex implementation
// ❌ Memory overhead due to multiple pointers
// ❌ Not efficient for small datasets
// ❌ Splitting and merging is costly

// 🚀 14. Applications

// B-Tree is widely used in:

// 🗄️ Database indexing (MySQL, Oracle)
// 💾 File systems (NTFS, HFS+)
// 🔎 Large search indexes
// 📚 Multi-level indexing systems
// 📊 Big data storage systems
// 🧾 FINAL SUMMARY

// A B-Tree is:

// A balanced multi-way search tree
// Stores multiple keys per node
// Keeps height small
// Ensures fast search, insert, delete
// Used in databases for indexing

















// A B-Tree is a self-balancing multi-level data structure used for storing large amounts of sorted data efficiently. It is mainly used in databases, file systems, and indexing systems because it keeps the height of the tree very small. Unlike a Binary Search Tree where one node stores only one key, a B-Tree stores multiple keys in one node, reducing the number of levels and making searching faster. The time complexity of searching, insertion, and deletion in a B-Tree is O(log n) because the tree always remains balanced, while traversal or display takes O(n) time because every node must be visited once. The main advantage of a B-Tree is that it minimizes disk accesses and provides very fast searching for huge datasets. It also keeps all leaf nodes at the same level, ensuring balanced performance. Another advantage is that insertion and deletion automatically maintain balance through splitting and merging operations. However, B-Trees are more complex to implement compared to simple trees like BST, and deletion operations are especially difficult because they require handling underflow conditions using borrowing and merging. B-Trees also use extra memory because each node stores multiple keys and child pointers. B-Trees are widely used in database management systems such as MySQL, Oracle, and SQLite, as well as in file systems like NTFS and Ext4 for efficient indexing and storage management.