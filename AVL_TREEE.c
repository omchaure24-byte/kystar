#include <stdio.h>
#include <stdlib.h>

// AVL Node
struct Node {
    int data;
    struct Node *left, *right;
    int height;
};

// Get height
int height(struct Node *n) {
    if (n == NULL)
        return 0;
    return n->height;
}

// Max function
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create node
struct Node* createNode(int data) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// Right Rotation
struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left Rotation
struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Balance Factor
int getBalance(struct Node *n) {
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

/* ================= INSERT ================= */

struct Node* insert(struct Node* node, int data) {

    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // LL Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // RR Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // LR Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

/* ================= SEARCH ================= */

int search(struct Node *root, int key) {

    if (root == NULL)
        return 0;

    if (root->data == key)
        return 1;

    if (key < root->data)
        return search(root->left, key);

    return search(root->right, key);
}

/* ================= DISPLAY ================= */

void inorder(struct Node *root) {

    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

/* ================= MAIN ================= */

int main() {

    struct Node *root = NULL;
    int choice, value;

    while (1) {

        printf("\n\n--- AVL TREE MENU ---\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Display (Inorder)\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("Inserted successfully.\n");
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);

                if (search(root, value))
                    printf("Key FOUND in AVL Tree\n");
                else
                    printf("Key NOT FOUND\n");
                break;

            case 3:
                printf("Inorder Traversal:\n");
                inorder(root);
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}







// AVL TREE EXPLANATION (SIMPLE + CLEAR)
// 📌 What is AVL Tree?

// An AVL Tree is a:

// 👉 Self-balancing Binary Search Tree
// 👉 It keeps tree height balanced after every operation

// ⚙️ MAIN IDEA

// For every node:

// Balance Factor = Height(Left) - Height(Right)

// ✔ Allowed values:

// -1
// 0
// +1

// If balance factor goes outside this range → rotation happens.

// 🔄 ROTATIONS USED
// 1. LL Case → Right Rotation

// Left-heavy imbalance

// 2. RR Case → Left Rotation

// Right-heavy imbalance

// 3. LR Case → Left + Right Rotation
// 4. RL Case → Right + Left Rotation
// 📥 INSERTION EXAMPLE

// Insert:

// 10 → 20 → 30

// Tree becomes:

// 10
//   \
//    20
//      \
//       30

// ❌ Unbalanced (RR case)

// ✔ Fix → Left Rotation

// Final tree:

//    20
//   /  \
// 10   30
// 🔍 SEARCH EXAMPLE

// Search 30:

// Steps:

// Start at root
// Compare values
// Move left or right
// Found or not found

// 👉 Time: O(log n)

// 🌿 INORDER DISPLAY

// Traversal:

// Left → Root → Right

// Output is always sorted order

// Example:

// 10 20 30 40
// ⏱️ TIME COMPLEXITY
// Operation	Complexity
// Insert	O(log n)
// Search	O(log n)
// Display	O(n)
// 👍 ADVANTAGES

// ✔ Always balanced tree
// ✔ Fast search and insert
// ✔ Better than BST
// ✔ No skewed structure

// 👎 DISADVANTAGES

// ❌ Complex rotations
// ❌ More overhead than BST
// ❌ Hard to implement deletion
// ❌ Extra memory for height

// 🚀 APPLICATIONS
// Database indexing
// File systems
// Memory management
// Search engines
// Autocomplete systems
// 🧾 FINAL SUMMARY

// AVL Tree is:

// A self-balancing BST
// Uses balance factor (-1,0,1)
// Maintains balance using rotations
// Guarantees O(log n) operations