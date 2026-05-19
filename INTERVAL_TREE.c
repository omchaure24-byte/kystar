#include <stdio.h>
#include <stdlib.h>

// Interval Tree Node
struct Node {
    int low, high;      // interval [low, high]
    int max;            // maximum high in subtree
    struct Node *left, *right;
};

//////////////////////////////////////////////////////
// Create new node
struct Node* newNode(int low, int high) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->low = low;
    node->high = high;
    node->max = high;
    node->left = node->right = NULL;
    return node;
}

//////////////////////////////////////////////////////
// Utility to get max
int max(int a, int b) {
    return (a > b) ? a : b;
}

//////////////////////////////////////////////////////
// Update max value
int getMax(struct Node* root) {
    if (root == NULL)
        return -1;

    int m = root->high;

    if (root->left)
        m = max(m, root->left->max);

    if (root->right)
        m = max(m, root->right->max);

    return m;
}

//////////////////////////////////////////////////////
// INSERT
struct Node* insert(struct Node* root, int low, int high) {

    if (root == NULL)
        return newNode(low, high);

    if (low < root->low)
        root->left = insert(root->left, low, high);

    else
        root->right = insert(root->right, low, high);

    root->max = getMax(root);

    return root;
}

//////////////////////////////////////////////////////
// CHECK OVERLAP
int overlap(int l1, int h1, int l2, int h2) {
    return (l1 <= h2 && l2 <= h1);
}

//////////////////////////////////////////////////////
// SEARCH OVERLAP
void searchOverlap(struct Node* root, int low, int high) {

    if (root == NULL)
        return;

    if (overlap(root->low, root->high, low, high))
        printf("[%d,%d] overlaps with [%d,%d]\n",
               root->low, root->high, low, high);

    if (root->left != NULL && root->left->max >= low)
        searchOverlap(root->left, low, high);

    searchOverlap(root->right, low, high);
}

//////////////////////////////////////////////////////
// FIND MIN VALUE NODE
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    while (current && current->left != NULL)
        current = current->left;

    return current;
}

//////////////////////////////////////////////////////
// DELETE NODE
struct Node* deleteNode(struct Node* root, int low, int high) {

    if (root == NULL)
        return root;

    if (low < root->low)
        root->left = deleteNode(root->left, low, high);

    else if (low > root->low)
        root->right = deleteNode(root->right, low, high);

    else {

        // match interval
        if (root->high == high) {

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

            struct Node* temp = minValueNode(root->right);

            root->low = temp->low;
            root->high = temp->high;

            root->right = deleteNode(root->right,
                                     temp->low, temp->high);
        }
    }

    if (root != NULL)
        root->max = getMax(root);

    return root;
}

//////////////////////////////////////////////////////
// INORDER DISPLAY
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("[%d,%d] max=%d\n",
               root->low, root->high, root->max);
        inorder(root->right);
    }
}

//////////////////////////////////////////////////////
// MAIN
int main() {
    struct Node* root = NULL;
    int choice, l, h;

    while (1) {
        printf("\n===== INTERVAL TREE MENU =====\n");
        printf("1. Insert Interval\n");
        printf("2. Delete Interval\n");
        printf("3. Search Overlap\n");
        printf("4. Display (Inorder)\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter low and high: ");
            scanf("%d %d", &l, &h);
            root = insert(root, l, h);
            printf("Inserted!\n");
            break;

        case 2:
            printf("Enter low and high: ");
            scanf("%d %d", &l, &h);
            root = deleteNode(root, l, h);
            printf("Deleted!\n");
            break;

        case 3:
            printf("Enter interval to search (low high): ");
            scanf("%d %d", &l, &h);
            searchOverlap(root, l, h);
            break;

        case 4:
            inorder(root);
            break;

        case 5:
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }
}




// What is an Interval Tree?

// An Interval Tree is a special Binary Search Tree used to store intervals like:

// [low, high]

// 👉 It helps to quickly find overlapping intervals.

// 🔥 Why we need Interval Tree?

// Normal BST cannot efficiently answer:

// 👉 “Which intervals overlap with [x, y]?”

// So Interval Tree adds an extra value:

// 🔷 max value

// Each node stores:

// max = highest end value in its subtree
// 🔷 Example (We will build step-by-step)

// Insert intervals:

// [15,20], [10,30], [17,19], [5,20], [12,15], [30,40]
// 🔷 STEP 1: Insert [15,20]

// Tree:

// [15,20]
// max = 20
// 🔷 STEP 2: Insert [10,30]

// BST rule (10 < 15 → left):

//         [15,20]
//         /
//    [10,30]

// Now update max:

// [10,30] max = 30
// [15,20] max = 30 (because left subtree has 30)
// 🔷 STEP 3: Insert [17,19]

// 17 > 15 → right:

//         [15,20]
//         /     \
//    [10,30]   [17,19]

// Update max:

// right max = 19
// root max = 30 (still max of subtree)
// 🔷 STEP 4: Insert [5,20]

// 5 < 15 → left of 10:

//         [15,20]
//         /     \
//    [10,30]   [17,19]
//    /
// [5,20]

// Update max:

// [10,30] max = 30
// root max = 30
// 🔷 STEP 5: Insert [12,15]

// 12 > 10 → right of 10:

//         [15,20]
//         /     \
//    [10,30]   [17,19]
//    /    \
// [5,20] [12,15]

// Update max stays 30.

// 🔷 STEP 6: Insert [30,40]

// 30 > 15 → right side of 17:

//         [15,20]
//         /     \
//    [10,30]   [17,19]
//    /    \        \
// [5,20] [12,15]  [30,40]

// Now update max:

// right subtree max = 40
// root max = 40
// 🔥 FINAL TREE IDEA

// Each node stores:

// [interval] + max

// Example root:

// [15,20], max = 40
// 🔷 Now understand QUERY (MOST IMPORTANT)

// 👉 Find overlapping with [14,16]

// Check rule:

// Overlap condition:
// low1 ≤ high2 AND low2 ≤ high1
// 🔥 STEP-BY-STEP SEARCH

// Start at root [15,20]:

// Check overlap:
// [15,20] overlaps with [14,16]? ✔ YES
// Go left?

// Check:

// left.max = 30 ≥ 14 → YES go left
// At [10,30]:
// overlaps? YES ([10,30] overlaps [14,16])
// Continue traversal...

// ✔ We get all overlapping intervals efficiently

// 🔥 KEY IDEA (VERY IMPORTANT)

// We don’t check all nodes!

// We use:

// max value → to skip useless branches
// 🔷 Why max is important?

// Example:

// If:

// left.max < query.low

// 👉 we SKIP left subtree completely

// ✔ This makes search fast

// 🔷 TIME COMPLEXITY
// Operation	Complexity
// Insert	O(log n)
// Delete	O(log n)
// Overlap Search	O(log n + k)
// Worst case	O(n)

// (k = number of overlapping intervals)

// 🔷 ADVANTAGES

// ✔ Efficient interval searching
// ✔ Faster than linear search
// ✔ Good for range queries
// ✔ Uses BST structure + extra info

// 🔷 DISADVANTAGES

// ❌ Complex to implement
// ❌ Extra memory for max field
// ❌ Not self-balancing by default
// ❌ Worst case O(n) if unbalanced

// 🔷 APPLICATIONS

// ✔ Scheduling systems (CPU, jobs)
// ✔ Calendar applications
// ✔ Network bandwidth allocation
// ✔ Database range queries
// ✔ Collision detection (games, graphics)
// ✔ Genomics (DNA intervals)

// 🔥 FINAL EXAM PARAGRAPH

// An Interval Tree is a Binary Search Tree that stores intervals and supports efficient overlap queries. Each node stores an interval [low, high] along with an additional field called max, which represents the maximum high value in its subtree. This helps in pruning unnecessary branches during search operations. When searching for overlapping intervals, the tree avoids exploring subtrees whose max value is smaller than the query interval. The time complexity for insertion and deletion is O(log n), and overlap search takes O(log n + k), where k is the number of overlapping intervals. Interval Trees are widely used in scheduling systems, computational geometry, databases, and networking applications.