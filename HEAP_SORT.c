#include <stdio.h>

#define MAX 100

int arr[MAX], n;

// Swap function
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//////////////////////////////////////////////////////
// Heapify (Max Heap)
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

//////////////////////////////////////////////////////
// Build Heap
void buildHeap(int arr[], int n) {
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

//////////////////////////////////////////////////////
// Heap Sort
void heapSort() {

    buildHeap(arr, n);

    printf("\nMax Heap Built:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");

    for (int i = n - 1; i > 0; i--) {

        swap(&arr[0], &arr[i]);

        printf("\nAfter placing max at end:\n");
        for (int j = 0; j < n; j++)
            printf("%d ", arr[j]);

        heapify(arr, i, 0);

        printf("\nAfter heapify:\n");
        for (int j = 0; j < n; j++)
            printf("%d ", arr[j]);

        printf("\n");
    }
}

//////////////////////////////////////////////////////
// Display Array
void display() {
    printf("\nArray:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

//////////////////////////////////////////////////////
// MAIN MENU
int main() {
    int choice;

    while (1) {
        printf("\n===== HEAP SORT MENU =====\n");
        printf("1. Input Elements\n");
        printf("2. Display Array\n");
        printf("3. Perform Heap Sort\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter number of elements: ");
            scanf("%d", &n);

            printf("Enter elements:\n");
            for (int i = 0; i < n; i++)
                scanf("%d", &arr[i]);
            break;

        case 2:
            display();
            break;

        case 3:
            heapSort();
            printf("\nFinal Sorted Array (Ascending Order):\n");
            for (int i = 0; i < n; i++)
                printf("%d ", arr[i]);
            printf("\n");
            break;

        case 4:
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
}

















// 1. What is Heap Sort?

// Heap Sort is a comparison-based sorting algorithm that uses a special tree structure called a Binary Heap.

// 👉 It sorts an array in two phases:

// Build a Heap (usually Max Heap for ascending order)
// Repeatedly extract the maximum element and rebuild heap
// 🌳 2. What is a Heap?

// A Binary Heap is a complete binary tree where:

// 🔺 Max Heap (used for ascending sort)
// Parent ≥ Children
// Largest element is at root

// Example:

//         50
//        /  \
//      30    40
//     /  \   /
//    10  20 35

// 👉 Root = maximum element

// 📌 Heap in Array Form

// Heap is stored in array:

// For index i:

// Left child = 2i + 1
// Right child = 2i + 2
// Parent = (i - 1) / 2
// ⚙️ 3. Heap Sort Steps

// We take example:

// Input:
// A = [4, 10, 3, 5, 1]
// 🧱 STEP 1: Build Max Heap

// We rearrange array into Max Heap.

// Initial array:

// [4, 10, 3, 5, 1]
// Build heap process:

// After heapify:

//         10
//        /  \
//       5    3
//      / \
//     4   1

// Array becomes:

// [10, 5, 3, 4, 1]
// 🔁 STEP 2: Extract Max & Sort

// Now we repeat:

// 🔹 Step 1:

// Swap root (10) with last element (1)

// [1, 5, 3, 4, 10]

// Heapify again:

// [5, 4, 3, 1, 10]
// 🔹 Step 2:

// Swap 5 and 1

// [1, 4, 3, 5, 10]

// Heapify:

// [4, 1, 3, 5, 10]
// 🔹 Step 3:

// Swap 4 and 3

// [3, 1, 4, 5, 10]

// Heapify:

// [3, 1, 4, 5, 10]
// 🔹 Step 4:

// Swap 3 and 1

// [1, 3, 4, 5, 10]
// 🎯 Final Sorted Array (Ascending):
// [1, 3, 4, 5, 10]
// 🔄 4. What is Heapify?

// Heapify is a process to maintain heap property.

// 👉 It checks parent and children and fixes order.

// Example:

// If parent < child → swap
// 💻 5. C Program for Heap Sort
// #include <stdio.h>

// void heapify(int arr[], int n, int i) {
//     int largest = i;
//     int left = 2 * i + 1;
//     int right = 2 * i + 2;

//     if (left < n && arr[left] > arr[largest])
//         largest = left;

//     if (right < n && arr[right] > arr[largest])
//         largest = right;

//     if (largest != i) {
//         int temp = arr[i];
//         arr[i] = arr[largest];
//         arr[largest] = temp;

//         heapify(arr, n, largest);
//     }
// }

// void heapSort(int arr[], int n) {

//     // Build max heap
//     for (int i = n / 2 - 1; i >= 0; i--)
//         heapify(arr, n, i);

//     // Extract elements
//     for (int i = n - 1; i > 0; i--) {

//         int temp = arr[0];
//         arr[0] = arr[i];
//         arr[i] = temp;

//         heapify(arr, i, 0);
//     }
// }

// void printArray(int arr[], int n) {
//     for (int i = 0; i < n; i++)
//         printf("%d ", arr[i]);
//     printf("\n");
// }

// int main() {
//     int arr[] = {4, 10, 3, 5, 1};
//     int n = sizeof(arr) / sizeof(arr[0]);

//     printf("Original array:\n");
//     printArray(arr, n);

//     heapSort(arr, n);

//     printf("Sorted array:\n");
//     printArray(arr, n);

//     return 0;
// }
// ⏱️ 6. Time Complexity Analysis
// 📌 Build Heap:
// O(n)
// 📌 Sorting (n elements × log n):
// O(n log n)
// 🎯 Final Time Complexity:
// Case	Complexity
// Best	O(n log n)
// Average	O(n log n)
// Worst	O(n log n)
// 📦 Space Complexity:
// O(1) (in-place sorting)
// 👍 7. Advantages of Heap Sort

// ✔ Very efficient for large datasets
// ✔ Always O(n log n) (no worst-case degradation like quicksort)
// ✔ In-place sorting (no extra array needed)
// ✔ Useful in priority scheduling systems

// 👎 8. Disadvantages

// ❌ Not stable (equal elements may change order)
// ❌ Slower than quicksort in real-world practice
// ❌ Poor cache performance
// ❌ Complex compared to simple sorts (bubble/insertion)

// 🚀 9. Applications

// Heap Sort is used in:

// Operating system scheduling (priority queues)
// Memory management systems
// Embedded systems
// Selection algorithms (finding k largest/smallest elements)
// Graph algorithms (like Dijkstra’s)
// 🧾 FINAL SUMMARY

// Heap Sort works by:

// Converting array → Max Heap
// Repeatedly extracting largest element
// Rebuilding heap after each extraction
// Producing sorted array in O(n log n)