#include <stdio.h>
#include <string.h>

#define MAX 100

// Job structure
typedef struct {
    char name[20];
    int priority;
} Job;

Job heap[MAX];
int size = 0;

//////////////////////////////////////////////////////
// Swap function
void swap(Job *a, Job *b) {
    Job temp = *a;
    *a = *b;
    *b = temp;
}

//////////////////////////////////////////////////////
// Heapify Up (for insertion)
void heapifyUp(int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;

        // Max Heap condition
        if (heap[i].priority > heap[parent].priority) {
            swap(&heap[i], &heap[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

//////////////////////////////////////////////////////
// Heapify Down (for deletion)
void heapifyDown(int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size &&
        heap[left].priority > heap[largest].priority) {
        largest = left;
    }

    if (right < size &&
        heap[right].priority > heap[largest].priority) {
        largest = right;
    }

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        heapifyDown(largest);
    }
}

//////////////////////////////////////////////////////
// Insert Job
void insertJob(char name[], int priority) {
    strcpy(heap[size].name, name);
    heap[size].priority = priority;

    heapifyUp(size);
    size++;

    printf("Job inserted successfully!\n");
}

//////////////////////////////////////////////////////
// Delete Highest Priority Job
void deleteJob() {
    if (size == 0) {
        printf("No jobs to execute!\n");
        return;
    }

    printf("Executing Job: %s (Priority %d)\n",
           heap[0].name, heap[0].priority);

    heap[0] = heap[size - 1];
    size--;

    heapifyDown(0);
}

//////////////////////////////////////////////////////
// Display Heap (not sorted, just structure)
void displayHeap() {
    if (size == 0) {
        printf("No jobs in queue!\n");
        return;
    }

    printf("\nCurrent Job Queue (Heap):\n");
    for (int i = 0; i < size; i++) {
        printf("%s (%d)  ", heap[i].name, heap[i].priority);
    }
    printf("\n");
}

//////////////////////////////////////////////////////
// Simulate full scheduling
void scheduleJobs() {
    printf("\n--- Job Execution Order ---\n");

    while (size > 0) {
        deleteJob();
    }
}

//////////////////////////////////////////////////////
// Main Menu
int main() {
    int choice;
    char name[20];
    int priority;

    while (1) {
        printf("\n===== PRIORITY QUEUE (MAX HEAP) =====\n");
        printf("1. Insert Job\n");
        printf("2. Execute Highest Priority Job\n");
        printf("3. Display Heap\n");
        printf("4. Run Full Scheduling\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter Job Name: ");
            scanf("%s", name);
            printf("Enter Priority: ");
            scanf("%d", &priority);
            insertJob(name, priority);
            break;

        case 2:
            deleteJob();
            break;

        case 3:
            displayHeap();
            break;

        case 4:
            scheduleJobs();
            break;

        case 5:
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
}











// 1. What is Priority Queue?

// A Priority Queue is a special type of queue where:

// 👉 Every element has a priority
// 👉 Higher priority element is served first (not FIFO like normal queue)

// 📌 Example (Job Scheduling)
// Job	Priority
// J1	3
// J2	1
// J3	5

// 👉 Higher number = higher priority (Max Heap case)

// Execution order:

// J3 → J1 → J2
// 🌳 2. Why Heap is used?

// Because Heap gives:

// ⏱️ Fast insertion → O(log n)
// ⏱️ Fast deletion (highest priority) → O(log n)
// 📌 Easy access to highest priority → O(1)
// 🔺 3. Types of Heap in Priority Queue
// 🔼 Max Heap (Most used in job scheduling)
// Highest priority job executes first
// 🔽 Min Heap
// Lowest priority job executes first (rare for scheduling)
// ⚙️ 4. Operations

// We will implement:

// ✔ Insert Job

// Add job in heap and fix structure

// ✔ Delete (Execute Job)

// Remove highest priority job (root)

// ✔ Display Execution Order

// Simulate scheduling

// 🧠 5. Working Example

// Jobs inserted:

// (J1, 3), (J2, 1), (J3, 5), (J4, 2)
// 🔺 Max Heap formed:
//         J3(5)
//        /     \
//    J1(3)     J2(1)
//    /
// J4(2)
// 🏁 Execution order:
// J3 → J1 → J4 → J2
// 💻 6. C Program (Priority Queue using Max Heap)
// #include <stdio.h>
// #include <stdlib.h>

// #define MAX 100

// // Job structure
// typedef struct {
//     char name[10];
//     int priority;
// } Job;

// Job heap[MAX];
// int size = 0;

// // Swap function
// void swap(Job *a, Job *b) {
//     Job temp = *a;
//     *a = *b;
//     *b = temp;
// }

// // Heapify (Max Heap)
// void heapifyDown(int i) {
//     int largest = i;
//     int left = 2 * i + 1;
//     int right = 2 * i + 2;

//     if (left < size && heap[left].priority > heap[largest].priority)
//         largest = left;

//     if (right < size && heap[right].priority > heap[largest].priority)
//         largest = right;

//     if (largest != i) {
//         swap(&heap[i], &heap[largest]);
//         heapifyDown(largest);
//     }
// }

// // Insert job
// void insertJob(char name[], int priority) {
//     int i = size++;

//     strcpy(heap[i].name, name);
//     heap[i].priority = priority;

//     // Heapify Up
//     while (i != 0 && heap[(i - 1) / 2].priority < heap[i].priority) {
//         swap(&heap[i], &heap[(i - 1) / 2]);
//         i = (i - 1) / 2;
//     }
// }

// // Execute highest priority job
// Job deleteJob() {
//     Job root = heap[0];

//     heap[0] = heap[--size];
//     heapifyDown(0);

//     return root;
// }

// // Display heap
// void displayHeap() {
//     printf("\nCurrent Priority Queue:\n");
//     for (int i = 0; i < size; i++) {
//         printf("%s(%d) ", heap[i].name, heap[i].priority);
//     }
//     printf("\n");
// }

// // Simulate job scheduling
// void scheduleJobs() {
//     printf("\n--- Job Execution Order ---\n");

//     while (size > 0) {
//         Job j = deleteJob();
//         printf("Executing Job: %s (Priority %d)\n", j.name, j.priority);
//     }
// }

// int main() {

//     // Insert jobs
//     insertJob("J1", 3);
//     insertJob("J2", 1);
//     insertJob("J3", 5);
//     insertJob("J4", 2);

//     displayHeap();

//     scheduleJobs();

//     return 0;
// }
// 🔁 7. How It Works (Simple Flow)
// Step 1: Insert jobs

// Each job goes into heap → placed based on priority

// Step 2: Heap structure maintained

// Highest priority always at root

// Step 3: Scheduling

// Repeatedly:

// Remove root → execute job → heapify again
// ⏱️ 8. Time Complexity
// Operation	Complexity
// Insert	O(log n)
// Delete	O(log n)
// Peek max	O(1)
// 📦 Space Complexity
// O(n) for storing jobs
// 👍 9. Advantages

// ✔ Very fast scheduling
// ✔ Efficient for dynamic job insertion
// ✔ Always gives highest priority job first
// ✔ Used in real operating systems

// 👎 10. Disadvantages

// ❌ Complex implementation
// ❌ Not stable (same priority order may change)
// ❌ Extra overhead of heap operations

// 🚀 11. Applications

// Priority Queue is used in:

// 🖥️ CPU scheduling (OS)
// 🌐 Network packet scheduling
// 🚑 Emergency systems (hospital priority cases)
// 🔎 Dijkstra’s shortest path algorithm
// 🎮 Game task scheduling
// 📩 Printer job scheduling