#include <stdio.h>
#include <stdlib.h>

// AVL Tree Node
typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int height;
}Node;

// Function to get maximum
int max(int a,int b){
    if(a>b){
        return a;
    }else{
        return b;
    }
}

// Function to get height
int height(Node *node)
{
    if (node == NULL)
        return 0;

    return node->height;
}

// Create new node
Node *createNode(int data)
{
    Node *newNode =
        (Node *)malloc(sizeof(Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 0;

    return newNode;
}

// Right Rotation
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;

    x->height = max(height(x->left),
                    height(x->right)) + 1;

    return x;
}

// Left Rotation
Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left),
                    height(x->right)) + 1;

    y->height = max(height(y->left),
                    height(y->right)) + 1;

    return y;
}

// Get Balance Factor
int getBalance(Node *node)
{
    if (node == NULL)
        return 0;

    return height(node->left) - height(node->right);
}

// Insert node
Node *insert(Node *node, int data)
{
    // Normal BST insertion
    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);

    else if (data > node->data)
        node->right = insert(node->right, data);

    else
        return node;

    // Update height
    node->height = 1 + max(height(node->left),
                           height(node->right));

    // Get balance factor
    int balance = getBalance(node);

    // LEFT LEFT CASE
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // RIGHT RIGHT CASE
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // LEFT RIGHT CASE
    if (balance > 1 && data > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RIGHT LEFT CASE
    if (balance < -1 && data < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Inorder Traversal
void inorder(struct Node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Search operation
struct Node *search(struct Node *root, int key)
{
    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);

    return search(root->right, key);
}

// Main Function
int main()
{
    struct Node *root = NULL;
    int choice, value;

    while (1)
    {
        printf("\n--- AVL TREE MENU ---\n");
        printf("1. Insert\n");
        printf("2. Display Inorder\n");
        printf("3. Search\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);

            root = insert(root, value);

            printf("Node inserted successfully.\n");
            break;

        case 2:
            printf("Inorder Traversal: ");
            inorder(root);
            printf("\n");
            break;

        case 3:
            printf("Enter value to search: ");
            scanf("%d", &value);

            if (search(root, value) != NULL)
                printf("Value found.\n");
            else
                printf("Value not found.\n");

            break;

        case 4:
            exit(0);

        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}