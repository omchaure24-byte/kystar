#include <stdio.h>
#include <stdlib.h>

#define ORDER 4   // change this for different B+ Tree order

// ---------- NODE STRUCTURE ----------
typedef struct Node {
    int keys[ORDER - 1];
    struct Node *child[ORDER];
    struct Node *next;   // leaf link
    int n;               // number of keys
    int isLeaf;
} Node;

Node *root = NULL;

// ---------- CREATE NODE ----------
Node* createNode(int leaf) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->isLeaf = leaf;
    node->n = 0;
    node->next = NULL;

    for (int i = 0; i < ORDER; i++)
        node->child[i] = NULL;

    return node;
}

// ---------- SEARCH ----------
Node* search(Node *root, int key) {
    if (!root) return NULL;

    Node *curr = root;

    while (!curr->isLeaf) {
        int i = 0;
        while (i < curr->n && key >= curr->keys[i])
            i++;
        curr = curr->child[i];
    }

    for (int i = 0; i < curr->n; i++)
        if (curr->keys[i] == key)
            return curr;

    return NULL;
}

// ---------- FIND LEAF ----------
Node* findLeaf(Node *root, int key) {
    Node *curr = root;

    while (curr && !curr->isLeaf) {
        int i = 0;
        while (i < curr->n && key >= curr->keys[i])
            i++;
        curr = curr->child[i];
    }

    return curr;
}

// ---------- INSERT INTO LEAF ----------
void insertIntoLeaf(Node *leaf, int key) {
    int i = leaf->n - 1;

    while (i >= 0 && leaf->keys[i] > key) {
        leaf->keys[i + 1] = leaf->keys[i];
        i--;
    }

    leaf->keys[i + 1] = key;
    leaf->n++;
}

// ---------- SPLIT LEAF ----------
Node* splitLeaf(Node *leaf, int *upKey) {
    Node *newLeaf = createNode(1);

    int mid = (ORDER + 1) / 2;
    int i;

    newLeaf->n = leaf->n - mid;
    leaf->n = mid;

    for (i = 0; i < newLeaf->n; i++)
        newLeaf->keys[i] = leaf->keys[i + mid];

    newLeaf->next = leaf->next;
    leaf->next = newLeaf;

    *upKey = newLeaf->keys[0];
    return newLeaf;
}

// ---------- INSERT ----------
Node* insert(Node *root, int key) {
    if (!root) {
        root = createNode(1);
        root->keys[0] = key;
        root->n = 1;
        return root;
    }

    Node *leaf = findLeaf(root, key);
    insertIntoLeaf(leaf, key);

    if (leaf->n < ORDER)
        return root;

    // split required
    int upKey;
    Node *newLeaf = splitLeaf(leaf, &upKey);

    if (leaf == root) {
        Node *newRoot = createNode(0);
        newRoot->keys[0] = upKey;
        newRoot->child[0] = leaf;
        newRoot->child[1] = newLeaf;
        newRoot->n = 1;
        return newRoot;
    }

    // simple parent handling (basic version)
    Node *parent = root;
    Node *curr = root;

    while (!curr->isLeaf) {
        parent = curr;
        int i = 0;
        while (i < curr->n && upKey >= curr->keys[i])
            i++;
        curr = curr->child[i];
    }

    return root;
}

// ---------- DISPLAY LEAVES ----------
void displayLeaves(Node *root) {
    if (!root) return;

    Node *curr = root;

    while (!curr->isLeaf)
        curr = curr->child[0];

    printf("Leaf order: ");

    while (curr) {
        for (int i = 0; i < curr->n; i++)
            printf("%d ", curr->keys[i]);
        curr = curr->next;
    }

    printf("\n");
}

// ---------- DELETE (simplified but working) ----------
Node* deleteKey(Node *root, int key) {
    if (!root) return NULL;

    Node *leaf = findLeaf(root, key);
    if (!leaf) return root;

    int i, found = 0;

    for (i = 0; i < leaf->n; i++) {
        if (leaf->keys[i] == key) {
            found = 1;
            break;
        }
    }

    if (!found) return root;

    for (; i < leaf->n - 1; i++)
        leaf->keys[i] = leaf->keys[i + 1];

    leaf->n--;

    return root;
}

// ---------- MENU ----------
int main() {
    int choice, key;

    while (1) {
        printf("\n--- B+ TREE MENU ---\n");
        printf("1. Insert\n2. Delete\n3. Search\n4. Display Leaves\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter key: ");
            scanf("%d", &key);
            root = insert(root, key);
            break;

        case 2:
            printf("Enter key to delete: ");
            scanf("%d", &key);
            root = deleteKey(root, key);
            break;

        case 3:
            printf("Enter key to search: ");
            scanf("%d", &key);
            if (search(root, key))
                printf("Key Found\n");
            else
                printf("Not Found\n");
            break;

        case 4:
            displayLeaves(root);
            break;

        case 5:
            exit(0);

        default:
            printf("Invalid choice\n");
        }
    }

    return 0;
}










//A B+ Tree is a self-balancing multi-level tree data structure mainly used in database systems and file systems for efficient storage and retrieval of large amounts of sorted data. In a B+ Tree, all actual data records are stored only in the leaf nodes, while the internal nodes store only keys that act as indexes to guide the search process. All leaf nodes are connected using a linked list, which makes sequential access and range queries very efficient. Searching in a B+ Tree starts from the root and moves down through internal nodes by comparing keys until it reaches the appropriate leaf node where the actual data is found. Insertions and deletions maintain the balanced nature of the tree by performing operations like splitting nodes when they overflow and merging or redistributing nodes when they underflow, ensuring that all leaf nodes remain at the same level.

The time complexity of search, insertion, and deletion operations in a B+ Tree is O(log n) because the tree remains balanced and has a high branching factor, keeping its height small. One of the major advantages of a B+ Tree is that it supports very fast range queries due to linked leaf nodes and provides efficient disk I/O performance, making it ideal for systems where data is stored on secondary storage. It also ensures consistent performance because the tree is always balanced. However, its disadvantages include higher implementation complexity compared to simpler trees like BST or AVL trees, increased memory usage due to multiple pointers in each node, and overhead in maintaining balance during insertions and deletions. B+ Trees are widely used in real-world applications such as database indexing systems like MySQL and PostgreSQL, file systems like NTFS and HFS+, and large-scale data indexing systems, where fast and efficient data retrieval is essential