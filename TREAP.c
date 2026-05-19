#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Treap Node
struct Node {
    int key;
    int priority;
    struct Node *left, *right;
};

//////////////////////////////////////////////////////
// Create new node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->priority = rand();   // random priority

    node->left = node->right = NULL;
    return node;
}

//////////////////////////////////////////////////////
// RIGHT ROTATION
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

//////////////////////////////////////////////////////
// LEFT ROTATION
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
}

//////////////////////////////////////////////////////
// INSERT
struct Node* insert(struct Node* root, int key) {

    if (root == NULL)
        return newNode(key);

    // BST property
    if (key < root->key)
        root->left = insert(root->left, key);

    else if (key > root->key)
        root->right = insert(root->right, key);

    else
        return root;

    // Heap property violation fix

    if (root->left != NULL && root->left->priority > root->priority)
        root = rightRotate(root);

    if (root->right != NULL && root->right->priority > root->priority)
        root = leftRotate(root);

    return root;
}

//////////////////////////////////////////////////////
// SEARCH
int search(struct Node* root, int key) {
    if (root == NULL)
        return 0;

    if (root->key == key)
        return 1;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

//////////////////////////////////////////////////////
// DELETE
struct Node* deleteNode(struct Node* root, int key) {

    if (root == NULL)
        return root;

    // BST move
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {
        // node found

        // leaf or single child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }

        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // two children
        if (root->left->priority > root->right->priority) {
            root = rightRotate(root);
            root->right = deleteNode(root->right, key);
        }
        else {
            root = leftRotate(root);
            root->left = deleteNode(root->left, key);
        }
    }

    return root;
}

//////////////////////////////////////////////////////
// INORDER DISPLAY
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("(%d,%d) ", root->key, root->priority);
        inorder(root->right);
    }
}

//////////////////////////////////////////////////////
// MAIN
int main() {
    struct Node* root = NULL;
    int choice, key;

    srand(time(0)); // for random priorities

    while (1) {
        printf("\n===== TREAP MENU =====\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Display (Inorder)\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter key: ");
            scanf("%d", &key);
            root = insert(root, key);
            printf("Inserted successfully!\n");
            break;

        case 2:
            printf("Enter key: ");
            scanf("%d", &key);
            root = deleteNode(root, key);
            printf("Deleted successfully!\n");
            break;

        case 3:
            printf("Enter key: ");
            scanf("%d", &key);

            if (search(root, key))
                printf("FOUND!\n");
            else
                printf("NOT FOUND!\n");
            break;

        case 4:
            printf("Inorder (key,priority): ");
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


















// What is a Treap?

// A Treap = Tree + Heap

// It combines:

// ✔ 1. Binary Search Tree (BST) property
// Left < Root < Right (based on KEY)
// ✔ 2. Heap property
// Parent has higher priority than children

// 👉 Each node stores:

// (key, priority)
// key → BST rule
// priority → Heap rule (random)
// 🔥 Why Treap is used?

// 👉 To keep tree balanced randomly
// 👉 Avoid worst-case BST (like linked list)

// 🔷 Example (We will build step-by-step)

// Insert keys:

// 10, 20, 30

// We assign random priorities:

// 10 → 40
// 20 → 90
// 30 → 30

// So nodes are:

// (10,40), (20,90), (30,30)
// 🔷 STEP 1: Insert (10,40)

// Tree is empty:

// (10,40)

// ✔ Root node

// 🔷 STEP 2: Insert (20,90)
// Step 2.1 BST insert
// (10,40)
//      \
//      (20,90)
// Step 2.2 Check heap property

// Parent priority = 40
// Child priority = 90 ❌ (violation)

// 👉 90 > 40 → rotate

// 🔥 LEFT ROTATION at 10

// Result:

//      (20,90)
//      /
//  (10,40)

// ✔ Heap + BST both satisfied

// 🔷 STEP 3: Insert (30,30)
// Step 3.1 BST insert
//      (20,90)
//      /     \
//  (10,40)  (30,30)
// Step 3.2 Check heap property
// 90 > 40 ✔
// 90 > 30 ✔

// ✔ No rotation needed

// 🔷 FINAL TREAP
//      (20,90)
//      /     \
//  (10,40)  (30,30)
// 🔥 Now understand operations
// 🔷 1. SEARCH

// Example: search 30

// 👉 Works like BST:

// 30 > 20 → go right
// found

// ✔ No change in structure (normally)

// 🔷 2. INSERT (important rule)

// Steps:

// Insert like BST
// Fix heap using rotations
// 🔷 3. DELETION (important)

// Example: delete 20

// Tree:

//      (20,90)
//      /     \
//  (10,40)  (30,30)
// Step 1: Rotate down (based on priority)

// We push 20 down:

// Compare children priorities
// swap with higher priority child if needed
// Step 2: After rotations
// (30,30)
// /
// (10,40)
// Step 3: remove node

// Final:

// (10,40)
//   \
//   (30,30)
// 🔥 KEY IDEA

// 👉 Treap behaves like:

// BST (by key)
// Heap (by priority)

// BUT balanced randomly

// 🔷 Why randomness helps?

// 👉 prevents worst-case skewed tree

// Example:
// Normal BST insertion:

// 10 → 20 → 30 → 40  (linked list ❌)

// Treap:

// balanced randomly ✔
// 🔷 TIME COMPLEXITY
// Operation	Complexity
// Search	O(log n) expected
// Insert	O(log n) expected
// Delete	O(log n) expected

// Worst case: O(n)

// 🔷 ADVANTAGES

// ✔ Easy to implement
// ✔ Automatically balanced (randomized)
// ✔ No strict balancing rules like AVL/Red-Black
// ✔ Fast average performance

// 🔷 DISADVANTAGES

// ❌ Worst case O(n)
// ❌ Depends on randomness
// ❌ Not strictly balanced like AVL

// 🔷 APPLICATIONS

// ✔ Database indexing
// ✔ Priority-based scheduling
// ✔ Memory management
// ✔ Competitive programming
// ✔ Fast dynamic sets (insert/delete/search)

// 🔥 FINAL EXAM PARAGRAPH

// A Treap is a randomized binary search tree that combines properties of a Binary Search Tree and a Heap. Each node contains a key and a randomly assigned priority. The tree maintains BST property based on keys and heap property based on priorities. When a node is inserted, it is first placed using BST rules, and then rotations are performed to maintain heap order. This randomization helps keep the tree balanced on average. The time complexity of search, insertion, and deletion operations is O(log n) on average, while worst-case complexity is O(n). Treaps are widely used in database systems, priority scheduling, memory management, and dynamic set operations due to their simplicity and efficiency.