#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;

    int lthread;
    int rthread;

}node;



// create node
node* createNode(int key)
{
    node *newnode;

    newnode = (node*)malloc(sizeof(node));

    newnode->data = key;

    newnode->left = NULL;
    newnode->right = NULL;

    newnode->lthread = 0;
    newnode->rthread = 0;

    return newnode;
}



// insert node
node* insert(node *root, int key)
{
    node *ptr;
    node *parent;
    node *newnode;

    ptr = root;
    parent = NULL;

    // empty tree
    if(root == NULL)
    {
        root = createNode(key);
        return root;
    }

    // search position
    while(ptr != NULL)
    {
        parent = ptr;

        // move left
        if(key < ptr->data)
        {
            if(ptr->lthread == 1)
            {
                ptr = ptr->left;
            }
            else
            {
                break;
            }
        }

        // move right
        else
        {
            if(ptr->rthread == 1)
            {
                ptr = ptr->right;
            }
            else
            {
                break;
            }
        }
    }

    // create new node
    newnode = createNode(key);

    // insert left
    if(key < parent->data)
    {
        newnode->left = parent->left;
        newnode->right = parent;

        parent->lthread = 1;
        parent->left = newnode;
    }

    // insert right
    else
    {
        newnode->right = parent->right;
        newnode->left = parent;

        parent->rthread = 1;
        parent->right = newnode;
    }

    return root;
}



// inorder successor
node* inorderSuccessor(node *ptr)
{
    // if right pointer is thread
    if(ptr->rthread == 0)
    {
        return ptr->right;
    }

    // move right child
    ptr = ptr->right;

    // move leftmost
    while(ptr->lthread == 1)
    {
        ptr = ptr->left;
    }

    return ptr;
}



// inorder traversal
void inorder(node *root)
{
    node *ptr;

    if(root == NULL)
    {
        return;
    }

    ptr = root;

    // move leftmost
    while(ptr->lthread == 1)
    {
        ptr = ptr->left;
    }

    // traversal
    while(ptr != NULL)
    {
        printf("%d ", ptr->data);

        ptr = inorderSuccessor(ptr);
    }
}



// preorder traversal
void preorder(node *root)
{
    node *ptr;

    if(root == NULL)
    {
        return;
    }

    ptr = root;

    while(ptr != NULL)
    {
        printf("%d ", ptr->data);

        // move left
        if(ptr->lthread == 1)
        {
            ptr = ptr->left;
        }

        else
        {
            // follow threads
            while(ptr != NULL && ptr->rthread == 0)
            {
                ptr = ptr->right;
            }

            // move right child
            if(ptr != NULL)
            {
                ptr = ptr->right;
            }
        }
    }
}



// main function
int main()
{
    node *root = NULL;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);

    printf("Inorder Traversal:\n");
    inorder(root);

    printf("\n");

    printf("Preorder Traversal:\n");
    preorder(root);

    return 0;
}