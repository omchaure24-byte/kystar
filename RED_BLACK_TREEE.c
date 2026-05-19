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
    node->color = R;   // new node always RED
    node->left = node->right = node->parent = NULL;
    return node;
}

/* ================= ROTATIONS ================= */

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

/* ================= FIX INSERT ================= */

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

            // CASE 2 & 3
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }

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

/* ================= INSERT ================= */

void bstInsert(struct Node *rootNode, struct Node *newNode) {

    if (newNode->data < rootNode->data) {
        if (rootNode->left == NULL) {
            rootNode->left = newNode;
            newNode->parent = rootNode;
        } else {
            bstInsert(rootNode->left, newNode);
        }
    }
    else {
        if (rootNode->right == NULL) {
            rootNode->right = newNode;
            newNode->parent = rootNode;
        } else {
            bstInsert(rootNode->right, newNode);
        }
    }
}

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

    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d(%c) ", root->data, root->color);
    inorder(root->right);
}

/* ================= MAIN MENU ================= */

int main() {

    int choice, value;

    while (1) {

        printf("\n\n--- RED BLACK TREE MENU ---\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Display (Inorder)\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insert(value);
                printf("Inserted successfully.\n");
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);

                if (search(root, value))
                    printf("Key FOUND\n");
                else
                    printf("Key NOT FOUND\n");
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






// What is this program?

// This program implements a Red-Black Tree, which is a:

// 👉 Self-balancing Binary Search Tree
// 👉 Ensures height is always O(log n)
// 👉 Uses colors (Red & Black) to maintain balance

// ⚙️ OPERATIONS IMPLEMENTED
// ✔ 1. INSERTION

// Steps:

// Insert like normal BST
// New node is always RED
// Check Red-Black rules
// If violation occurs:
// Recolor nodes
// Perform rotations (Left / Right)

// 👉 This keeps tree balanced automatically

// ✔ 2. SEARCH
// Works like BST search
// Compare key:
// If smaller → left subtree
// If larger → right subtree

// 👉 Time = O(log n)

// ✔ 3. DISPLAY (INORDER)
// Left → Root → Right
// Prints sorted order
// Shows color also:

// Example:

// 10(B) 20(R) 30(B)
// 🔄 3. WHY ROTATIONS ARE USED?

// When tree becomes unbalanced:

// ✔ Left Rotation

// Fixes right-heavy tree

// ✔ Right Rotation

// Fixes left-heavy tree

// 👉 These keep tree height balanced

// 🎨 4. WHY RECOLORING IS USED?

// Rules:

// Red node cannot have red parent
// Black height must remain same

// So we:
// ✔ Change Red → Black
// ✔ Change Black → Red

// to fix violations

// ⏱️ 5. TIME COMPLEXITY
// Operation	Complexity
// Insert	O(log n)
// Search	O(log n)
// Display	O(n)
// 👍 6. ADVANTAGES

// ✔ Always balanced tree
// ✔ Fast search and insert
// ✔ Used in real systems (Linux, C++ STL)
// ✔ Better than normal BST

// 👎 7. DISADVANTAGES

// ❌ Complex logic
// ❌ Difficult to implement
// ❌ Many special cases
// ❌ Extra memory for color + pointers

// 🚀 8. APPLICATIONS
// 🖥️ Operating Systems
// 📚 C++ STL (map, set)
// 🗄️ Database indexing
// 🌐 Networking systems
// 🔎 Search engines