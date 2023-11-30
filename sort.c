#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a Student
struct Student {
    char student_name[50];
    int student_roll_no;
    int total_marks;
};

// Function to swap two Student structures
void swap(struct Student* a, struct Student* b) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform heapify for Heap Sort
void heapify(struct Student arr[], int n, int i, int* swapCount) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].student_roll_no > arr[largest].student_roll_no) {
        largest = left;
    }

    if (right < n && arr[right].student_roll_no > arr[largest].student_roll_no) {
        largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        (*swapCount)++;
        heapify(arr, n, largest, swapCount);
    }
}

// Function to perform Heap Sort
void heapSort(struct Student arr[], int n, int* swapCount) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, swapCount);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        (*swapCount)++;
        heapify(arr, i, 0, swapCount);
    }
}

// Function to merge two subarrays for Merge Sort
void merge(struct Student arr[], int l, int m, int r, int* swapCount) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    struct Student L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    // Merge the temporary arrays back into arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i].student_roll_no <= R[j].student_roll_no) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
            (*swapCount)++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Function to perform Merge Sort
void mergeSort(struct Student arr[], int l, int r, int* swapCount) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m, swapCount);
        mergeSort(arr, m + 1, r, swapCount);

        // Merge the sorted halves
        merge(arr, l, m, r, swapCount);
    }
}

// Function to partition the array for Quick Sort
int partition(struct Student arr[], int low, int high, int* swapCount) {
    struct Student pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].student_roll_no <= pivot.student_roll_no) {
            i++;
            swap(&arr[i], &arr[j]);
            (*swapCount)++;
        }
    }

    swap(&arr[i + 1], &arr[high]);
    (*swapCount)++;
    return (i + 1);
}

// Function to perform Quick Sort
void quickSort(struct Student arr[], int low, int high, int* swapCount) {
    if (low < high) {
        int pi = partition(arr, low, high, swapCount);

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1, swapCount);
        quickSort(arr, pi + 1, high, swapCount);
    }
}

// Function to print the array of Students
void printArray(struct Student arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Roll No: %d, Name: %s, Marks: %d\n", arr[i].student_roll_no, arr[i].student_name, arr[i].total_marks);
    }
}

// Example usage
int main() {
    struct Student students[] = {
        {"Alice", 3, 80},
        {"Bob", 1, 95},
        {"Charlie", 4, 60},
        {"David", 2, 75},
        {"Eve", 5, 90}
    };

    int n = sizeof(students) / sizeof(students[0]);

    // Heap Sort
    int heapSwapCount = 0;
    heapSort(students, n, &heapSwapCount);
    printf("Heap Sorted Array:\n");
    printArray(students, n);
    printf("Number of swaps in Heap Sort: %d\n\n", heapSwapCount);

    // Merge Sort
    int mergeSwapCount = 0;
    mergeSort(students, 0, n - 1, &mergeSwapCount);
    printf("Merge Sorted Array:\n");
    printArray(students, n);
    printf("Number of swaps in Merge Sort: %d\n\n", mergeSwapCount);

    // Quick Sort
    int quickSwapCount = 0;
    quickSort(students, 0, n - 1, &quickSwapCount);
    printf("Quick Sorted Array:\n");
    printArray(students, n);
    printf("Number of swaps in Quick Sort: %d\n\n", quickSwapCount);

    return 0;
}
