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

// Get balance factor
int getBalance(struct Node *n) {
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}

// INSERT
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

// MIN VALUE NODE
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// DELETE
struct Node* deleteNode(struct Node* root, int data) {

    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);

    else if (data > root->data)
        root->right = deleteNode(root->right, data);

    else {

        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        }
        else {
            struct Node* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // LL
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// INORDER DISPLAY
void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// MAIN MENU
int main() {

    struct Node *root = NULL;
    int choice, value;

    while (1) {

        printf("\n\n--- AVL TREE MENU ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display (Inorder)\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                root = insert(root, value);
                printf("Inserted successfully.\n");
                break;

            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                printf("Deleted successfully.\n");
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




// 5. EXPLANATION (VERY IMPORTANT)
// 📌 What happens in AVL Tree?

// Every time you:
// ✔ Insert
// ✔ Delete

// 👉 Tree checks balance factor
// 👉 If unbalanced → rotations happen automatically

// 🔄 6. ROTATION LOGIC
// ✔ LL Case

// Left-heavy → Right rotate

// ✔ RR Case

// Right-heavy → Left rotate

// ✔ LR Case

// Left + Right rotation

// ✔ RL Case

// Right + Left rotation

// 📥 7. INSERTION EXAMPLE

// Insert:

// 10, 20, 30
// Step:
// 10
//   \
//    20
//      \
//       30

// ❌ imbalance (RR case)

// ✔ Fix → Left rotation

// Result:

//    20
//   /  \
// 10   30
// ❌ 8. DELETION EXAMPLE

// Delete 20:

// Tree rebalances automatically using:
// ✔ rotations
// ✔ height updates

// ⏱️ 9. TIME COMPLEXITY
// Operation	Complexity
// Insert	O(log n)
// Delete	O(log n)
// Search	O(log n)
// Display	O(n)
// 👍 10. ADVANTAGES

// ✔ Always balanced
// ✔ Fast operations (log n)
// ✔ Better search than BST
// ✔ No skewed tree problem

// 👎 11. DISADVANTAGES

// ❌ Complex rotations
// ❌ Extra memory for height
// ❌ Slower insertion than BST in practice
// ❌ Hard to implement

// 🚀 12. APPLICATIONS
// Database indexing
// File systems
// Memory management
// Search engines
// Autocomplete systems
// 🧾 FINAL SUMMARY

// AVL Tree is:

// A self-balancing BST
// Uses balance factor (-1,0,1)
// Fixes imbalance using rotations
// Guarantees O(log n) performance