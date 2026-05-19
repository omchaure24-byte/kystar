#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int key;
    struct Node *left, *right;
};

// Create new node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

//////////////////////////////////////////////////////
// RIGHT ROTATION (Zig / LL fix)
struct Node* rightRotate(struct Node* x) {
    struct Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

//////////////////////////////////////////////////////
// LEFT ROTATION (Zag / RR fix)
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

//////////////////////////////////////////////////////
// SPLAY FUNCTION (main logic)
struct Node* splay(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    // KEY lies in LEFT subtree
    if (key < root->key) {

        if (root->left == NULL)
            return root;

        // Zig-Zig (LL case)
        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }

        // Zig-Zag (LR case)
        else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        return (root->left == NULL) ? root : rightRotate(root);
    }

    // KEY lies in RIGHT subtree
    else {

        if (root->right == NULL)
            return root;

        // Zag-Zag (RR case)
        if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }

        // Zag-Zig (RL case)
        else if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }

        return (root->right == NULL) ? root : leftRotate(root);
    }
}

//////////////////////////////////////////////////////
// INSERT
struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return newNode(key);

    root = splay(root, key);

    if (root->key == key)
        return root;

    struct Node* newnode = newNode(key);

    if (key < root->key) {
        newnode->right = root;
        newnode->left = root->left;
        root->left = NULL;
    }
    else {
        newnode->left = root;
        newnode->right = root->right;
        root->right = NULL;
    }

    return newnode;
}

//////////////////////////////////////////////////////
// SEARCH
struct Node* search(struct Node* root, int key) {
    return splay(root, key);
}

//////////////////////////////////////////////////////
// DELETE
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return NULL;

    root = splay(root, key);

    if (root->key != key)
        return root;

    struct Node* temp;

    if (root->left == NULL) {
        temp = root;
        root = root->right;
    }
    else {
        temp = root;

        root = splay(root->left, key);
        root->right = temp->right;
    }

    free(temp);
    return root;
}

//////////////////////////////////////////////////////
// INORDER DISPLAY
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

//////////////////////////////////////////////////////
// MAIN
int main() {
    struct Node* root = NULL;
    int choice, key;

    while (1) {
        printf("\n===== SPLAY TREE MENU =====\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display (Inorder)\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter key: ");
            scanf("%d", &key);
            root = insert(root, key);
            printf("Inserted and Splayed to Root!\n");
            break;

        case 2:
            printf("Enter key to search: ");
            scanf("%d", &key);
            root = search(root, key);
            printf("Search completed (Splayed to Root if found)!\n");
            break;

        case 3:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            root = deleteNode(root, key);
            printf("Deletion completed!\n");
            break;

        case 4:
            printf("Inorder Traversal: ");
            inorder(root);
            printf("\n");
            break;

        case 5:
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }
}


// 40, 20, 60, 10

// Zig (Right Rotation)

// Case: Node is left child of root

//     20
//    /
//  10   (access 10)

// After right rotation:

//   10
//     \
//      20
// 👉 Zag (Left Rotation)

// Case: Node is right child of root

// 10
//   \
//    20   (access 20)

// After left rotation:

//   20
//  /
// 10
// 🔹 2. Zig-Zig (Same Side Double Rotation)
// 👉 Zig-Zig (LL case → Right + Right rotation)
//       30
//      /
//    20
//   /
// 10   (access 10)

// After:

//   10
//     \
//      20
//        \
//         30
// 👉 Zag-Zag (RR case → Left + Left rotation)
// 10
//   \
//    20
//      \
//       30   (access 30)

// After:

//    30
//   /
//  20
// /
// 10
// 🔹 3. Zig-Zag (Opposite Side Double Rotation)
// 👉 Zig-Zag (LR case → Left + Right rotation)
//     30
//    /
//  10
//    \
//     20   (access 20)

// After:

//    20
//   /  \
// 10    30
// 👉 Zag-Zig (RL case → Right + Left rotation)
// 10
//   \
//    30
//   /
//  20   (access 20)

// After:

//    20
//   /  \
// 10    30
// 🔥 Summary of 6 Rotations
// Case	Pattern	Rotations
// Zig	Single step	Left or Right
// Zag	Single step	Right or Left
// Zig-Zig	LL	Right + Right
// Zag-Zag	RR	Left + Left
// Zig-Zag	LR	Left + Right
// Zag-Zig	RL	Right + Left


// Advantages of Splay Tree

// ✔ Self-adjusting structure

// Frequently accessed elements move closer to the root automatically.

// ✔ Fast access for repeated operations

// Recently used nodes become quicker to access.

// ✔ No extra balancing factor needed

// Unlike AVL or Red-Black trees, no height balancing rules.

// ✔ Simple implementation (compared to AVL/Red-Black)

// Only uses rotations (zig, zig-zig, zig-zag).

// ✔ Good cache performance in practice

// Frequently used data stays near top → faster real-world performance.
// 🔷 Applications of Splay Tree

// ✔ Cache systems

// Recently used data is accessed faster.

// ✔ Memory management systems

// Frequently accessed memory blocks are kept near root.

// ✔ Compiler design

// Used in symbol tables.

// ✔ Database systems

// Fast access to recently queried records.

// ✔ Network routers / routing tables

// Frequently used routes are optimized.

// ✔ Text editors / browsers

// Recently opened files or pages accessed quickly.
// 🔷 Time Complexity of Splay Tree
// ✔ Individual operations:
// Operation	Time Complexity
// Search	O(log n) amortized
// Insert	O(log n) amortized
// Delete	O(log n) amortized
// ⚠ Worst case:
// O(n) (when tree becomes skewed)
// 🔥 Amortized meaning (important viva point):

// Even if one operation is slow, average performance over many operations is O(log n).

// 🔷 Final Exam Paragraph (ready to write)

// A Splay Tree is a self-adjusting binary search tree in which every operation moves the accessed node to the root using rotations called splaying. It provides efficient access to frequently used elements by keeping them near the root. The main advantage of a splay tree is that it improves access time for repeated operations without requiring complex balancing like AVL or Red-Black trees. It is simple to implement and provides good cache performance. However, its disadvantage is that individual operations can take O(n) time in the worst case. Splay trees are widely used in cache systems, memory management, compiler symbol tables, database query optimization, and routing systems. The time complexity of search, insertion, and deletion is O(log n) amortized, while the worst-case complexity is O(n).