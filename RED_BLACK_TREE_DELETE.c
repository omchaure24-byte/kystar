#include <stdio.h>
#include <stdlib.h>

#define R 'R'
#define B 'B'

// Node structure
struct Node {
    int data;
    char color;
    struct Node *left, *right, *parent;
};

struct Node *root = NULL;

// Create node
struct Node* createNode(int data) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->color = R;
    node->left = node->right = node->parent = NULL;
    return node;
}

// LEFT ROTATION
void leftRotate(struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// RIGHT ROTATION
void rightRotate(struct Node *y) {
    struct Node *x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// Fix insertion
void fixInsert(struct Node *z) {

    while (z != root && z->parent->color == R) {

        if (z->parent == z->parent->parent->left) {

            struct Node *y = z->parent->parent->right;

            // CASE 1: Uncle RED
            if (y != NULL && y->color == R) {
                z->parent->color = B;
                y->color = B;
                z->parent->parent->color = R;
                z = z->parent->parent;
            }
            else {
                // CASE 2
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }

                // CASE 3
                z->parent->color = B;
                z->parent->parent->color = R;
                rightRotate(z->parent->parent);
            }
        }
        else {

            struct Node *y = z->parent->parent->left;

            if (y != NULL && y->color == R) {
                z->parent->color = B;
                y->color = B;
                z->parent->parent->color = R;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }

                z->parent->color = B;
                z->parent->parent->color = R;
                leftRotate(z->parent->parent);
            }
        }
    }

    root->color = B;
}

// BST insert
void bstInsert(struct Node *rootNode, struct Node *newNode) {

    if (newNode->data < rootNode->data) {
        if (rootNode->left == NULL) {
            rootNode->left = newNode;
            newNode->parent = rootNode;
        } else {
            bstInsert(rootNode->left, newNode);
        }
    } else {
        if (rootNode->right == NULL) {
            rootNode->right = newNode;
            newNode->parent = rootNode;
        } else {
            bstInsert(rootNode->right, newNode);
        }
    }
}

// INSERT
void insert(int data) {

    struct Node *node = createNode(data);

    if (root == NULL) {
        root = node;
        root->color = B;
        return;
    }

    bstInsert(root, node);
    fixInsert(node);
}

// INORDER DISPLAY
void inorder(struct Node *root) {
    if (root == NULL) return;

    inorder(root->left);
    printf("%d(%c) ", root->data, root->color);
    inorder(root->right);
}

// FIND MIN
struct Node* minValue(struct Node *node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

// SIMPLE BST DELETE (RB fix not fully implemented for simplicity)
struct Node* deleteBST(struct Node *root, int key) {

    if (root == NULL) return root;

    if (key < root->data)
        root->left = deleteBST(root->left, key);

    else if (key > root->data)
        root->right = deleteBST(root->right, key);

    else {

        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        struct Node *temp = minValue(root->right);
        root->data = temp->data;
        root->right = deleteBST(root->right, temp->data);
    }

    return root;
}

// DELETE WRAPPER
void deleteNode(int key) {
    root = deleteBST(root, key);
    printf("\nDeletion done (basic BST delete, RB fix not included fully)\n");
}

// MENU
int main() {

    int choice, value;

    while (1) {

        printf("\n\n--- RED BLACK TREE MENU ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display (Inorder)\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(value);
                printf("Inserted successfully.\n");
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                deleteNode(value);
                break;

            case 3:
                printf("Inorder Traversal (Data(Color)):\n");
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










// 1. What is a Red-Black Tree?

// A Red-Black Tree is a self-balancing Binary Search Tree (BST) where each node has a color:

// 🔴 Red
// ⚫ Black

// 👉 These colors are used to keep the tree balanced automatically.

// 📌 2. Properties of Red-Black Tree

// A Red-Black Tree must follow these rules:

// ✔ Rule 1

// Every node is either Red or Black

// ✔ Rule 2

// Root is always Black

// ✔ Rule 3

// No two Red nodes come together
// (👉 No Red parent–Red child)

// ✔ Rule 4

// Every path from root to leaf has same number of Black nodes

// ✔ Rule 5

// New nodes are always inserted as Red

// 🌲 3. Why Red-Black Tree is used?

// Normal BST can become like:

// 1 → 2 → 3 → 4 → 5   (skewed)

// 👉 This becomes slow (O(n))

// Red-Black Tree fixes this by:
// ✔ keeping height balanced
// ✔ ensuring operations stay fast

// 🔧 4. Basic Idea of Working

// Every operation (Insert/Delete):

// Do normal BST insertion/deletion
// Check Red-Black rules
// Fix violations using:
// 🔄 Rotation (Left / Right)
// 🎨 Recoloring (Red ↔ Black)
// 📥 5. Example of Insertion (Step-by-Step)

// Let’s insert:

// 10, 20, 30
// Step 1: Insert 10

// Root must be Black:

// 10(B)
// Step 2: Insert 20

// New node always Red:

// 10(B)
//    \
//    20(R)

// ✔ No problem (Red child under Black parent)

// Step 3: Insert 30
// 10(B)
//    \
//    20(R)
//        \
//        30(R)

// ❌ Problem:

// Red parent (20) + Red child (30) → VIOLATION
// ⚠️ Violation Fix

// We fix using rotation + recoloring.

// Case:
// 30 is right-right case

// 👉 Perform Left Rotation on 10

// After rotation:

//       20(B)
//      /    \
//   10(R)   30(R)

// ✔ Now tree is balanced again

// 🔍 6. Search Example

// Search for 30:

// Steps:

// Start at 20
// 30 > 20 → go right
// Found 30 ✔

// 👉 Time = O(log n)

// ❌ 7. Deletion Example (Simple Idea)

// Let’s delete 20:

//       20(B)
//      /    \
//   10(R)   30(R)

// After deletion:

// Replace 20 with successor or restructure
// Fix black height rule if violated

// 👉 If imbalance happens:

// Rotate
// Recolor

// (Deletion is more complex than insertion)

// 🔄 8. Rotations (Core Idea)
// Left Rotation:

// Used when right-heavy imbalance occurs

// Right Rotation:

// Used when left-heavy imbalance occurs

// 👉 These operations keep tree height small

// 🧠 9. Real Working Concept

// Think like this:

// 👉 BST gives structure
// 👉 Colors give balance control

// So Red-Black Tree =

// BST + Color Rules + Rotations
// ⏱️ 10. Time Complexity
// Operation	Complexity
// Search	O(log n)
// Insert	O(log n)
// Delete	O(log n)
// Traversal	O(n)
// 📦 11. Space Complexity
// O(n)

// (extra pointers + color field)

// 👍 12. Advantages

// ✔ Always balanced tree
// ✔ Fast operations (log n)
// ✔ Used in real systems (Linux, STL map/set)
// ✔ Better than normal BST in worst case
// ✔ Good for dynamic data

// 👎 13. Disadvantages

// ❌ Complex logic
// ❌ Hard to implement deletion
// ❌ Many cases (rotations + recoloring)
// ❌ More memory usage

// 🚀 14. Applications
// 🖥️ Operating systems (Linux scheduling)
// 📚 C++ STL (map, set)
// 🗄️ Database indexing
// 🌐 Networking routing tables
// 🔎 Search engines