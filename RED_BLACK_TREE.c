#include <stdio.h>
#include <stdlib.h>

// ---------------- RED BLACK TREE ----------------

typedef struct Node {
    int data;
    char color; 

    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

Node *root = NULL;

// ---------- Utility Functions ----------

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));

    newNode->data = data;
    newNode->color = 'R';

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    return newNode;
}

// ---------- Left Rotation ----------

Node* leftRotate(Node *x) {

    Node *y = x->right;     // y
    Node *T2 = y->left;     // T2

    // rotation (AVL-style thinking)
    y->left = x;
    x->right = T2;

    // IMPORTANT: fix parents (RBT requirement)
    if (T2 != NULL)
        T2->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;

    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    x->parent = y;

    return y;   // optional but clean
}

// ---------- Right Rotation ----------

Node* rightRotate(Node *y) {

    Node *x = y->left;     // x
    Node *T2 = x->right;   // T2

    // step 1: rotation (AVL-style thinking)
    x->right = y;
    y->left = T2;

    // step 2: fix parent of T2
    if (T2 != NULL)
        T2->parent = y;

    // step 3: connect x to upper tree
    x->parent = y->parent;

    if (y->parent == NULL)
        root = x;

    else if (y == y->parent->left)
        y->parent->left = x;

    else
        y->parent->right = x;

    // step 4: fix parent of y
    y->parent = x;

    return x;
}

// ---------- Fix Insertion ----------

void fixInsert(Node *z) {

    while (z != root && z->parent->color == 'R') {

        // Parent is left child
        if (z->parent == z->parent->parent->left) {

            Node *y = z->parent->parent->right;

            // Case 1 : Uncle is Red
            if (y != NULL && y->color == 'R') {

                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';

                z = z->parent->parent;
            }

            else {

                // Case 2 : Left Right
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }

                // Case 3 : Left Left
                z->parent->color = 'B';
                z->parent->parent->color = 'R';

                rightRotate(z->parent->parent);
            }
        }

        // Parent is right child
        else {

            Node *y = z->parent->parent->left;

            // Case 1 : Uncle is Red
            if (y != NULL && y->color == 'R') {

                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';

                z = z->parent->parent;
            }

            else {

                // Case 2 : Right Left
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }

                // Case 3 : Right Right
                z->parent->color = 'B';
                z->parent->parent->color = 'R';

                leftRotate(z->parent->parent);
            }
        }
    }

    root->color = 'B';
}

// ---------- Insert ----------

void insert(int data) {

    Node *z = createNode(data);

    Node *y = NULL;
    Node *x = root;

    while (x != NULL) {

        y = x;

        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == NULL)
        root = z;

    else if (z->data < y->data)
        y->left = z;

    else
        y->right = z;

    fixInsert(z);
}

// ---------- Search ----------

Node* search(Node *root, int key) {

    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);

    return search(root->right, key);
}

// ---------- Inorder Traversal ----------

void inorder(Node *root) {

    if (root != NULL) {

        inorder(root->left);

        printf("%d(%c) ", root->data, root->color);

        inorder(root->right);
    }
}

// ---------- Minimum ----------

Node* minimum(Node *node) {

    while (node->left != NULL)
        node = node->left;

    return node;
}

// ---------- Transplant ----------

void transplant(Node *u, Node *v) {

    if (u->parent == NULL)
        root = v;

    else if (u == u->parent->left)
        u->parent->left = v;

    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}

// ---------- Fix Delete ----------

void fixDelete(Node *x) {

    while (x != root && (x == NULL || x->color == 'B')) {

        // x is left child
        if (x == x->parent->left) {

            Node *w = x->parent->right;

            // Case 1
            if (w != NULL && w->color == 'R') {

                w->color = 'B';
                x->parent->color = 'R';

                leftRotate(x->parent);

                w = x->parent->right;
            }

            // Case 2
            if ((w->left == NULL || w->left->color == 'B') &&
                (w->right == NULL || w->right->color == 'B')) {

                w->color = 'R';

                x = x->parent;
            }

            else {

                // Case 3
                if (w->right == NULL || w->right->color == 'B') {

                    if (w->left != NULL)
                        w->left->color = 'B';

                    w->color = 'R';

                    rightRotate(w);

                    w = x->parent->right;
                }

                // Case 4
                w->color = x->parent->color;

                x->parent->color = 'B';

                if (w->right != NULL)
                    w->right->color = 'B';

                leftRotate(x->parent);

                x = root;
            }
        }

        // x is right child
        else {

            Node *w = x->parent->left;

            // Case 1
            if (w != NULL && w->color == 'R') {

                w->color = 'B';
                x->parent->color = 'R';

                rightRotate(x->parent);

                w = x->parent->left;
            }

            // Case 2
            if ((w->right == NULL || w->right->color == 'B') &&
                (w->left == NULL || w->left->color == 'B')) {

                w->color = 'R';

                x = x->parent;
            }

            else {

                // Case 3
                if (w->left == NULL || w->left->color == 'B') {

                    if (w->right != NULL)
                        w->right->color = 'B';

                    w->color = 'R';

                    leftRotate(w);

                    w = x->parent->left;
                }

                // Case 4
                w->color = x->parent->color;

                x->parent->color = 'B';

                if (w->left != NULL)
                    w->left->color = 'B';

                rightRotate(x->parent);

                x = root;
            }
        }
    }

    if (x != NULL)
        x->color = 'B';
}

// ---------- Delete ----------

void deleteNode(int key) {

    Node *z = search(root, key);

    if (z == NULL) {
        printf("Node not found!\n");
        return;
    }

    Node *y = z;
    Node *x;

    char yOriginalColor = y->color;

    // Case 1 : No left child
    if (z->left == NULL) {

        x = z->right;

        transplant(z, z->right);
    }

    // Case 2 : No right child
    else if (z->right == NULL) {

        x = z->left;

        transplant(z, z->left);
    }

    // Case 3 : Two children
    else {

        y = minimum(z->right);

        yOriginalColor = y->color;

        x = y->right;

        if (y->parent == z) {

            if (x != NULL)
                x->parent = y;
        }

        else {

            transplant(y, y->right);

            y->right = z->right;

            y->right->parent = y;
        }

        transplant(z, y);

        y->left = z->left;

        y->left->parent = y;

        y->color = z->color;
    }

    free(z);

    if (yOriginalColor == 'B' && x != NULL)
        fixDelete(x);
}

// ---------- Main ----------

int main() {

    int choice, value;

    while (1) {

        printf("\n===== RED BLACK TREE =====\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Display Inorder\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:

                printf("Enter value to insert: ");
                scanf("%d", &value);

                insert(value);

                break;

            case 2:

                printf("Enter value to delete: ");
                scanf("%d", &value);

                deleteNode(value);

                break;

            case 3:

                printf("Enter value to search: ");
                scanf("%d", &value);

                if (search(root, value) != NULL)
                    printf("Node Found!\n");
                else
                    printf("Node Not Found!\n");

                break;

            case 4:

                printf("Inorder Traversal:\n");

                inorder(root);

                printf("\n");

                break;

            case 5:

                exit(0);

            default:

                printf("Invalid Choice!\n");
        }
    }

    return 0;
}