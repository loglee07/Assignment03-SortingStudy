#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <string>

// Returns true if the vector is sorted from smallest to largest.
bool isSorted(const std::vector<int>& values) {
    for (int i = 1; i < values.size(); i++) {
        if (values[i] < values[i - 1]) {
            return false;
        }
    }

    return true;
}

// Repeatedly swaps neighboring values that are out of order.
void bubbleSort(std::vector<int>& values) {
    for (int end = values.size() - 1; end > 0; end--) {
        bool swapped = false;

        for (int i = 0; i < end; i++) {
            if (values[i] > values[i + 1]) {
                int temp = values[i];
                values[i] = values[i + 1];
                values[i + 1] = temp;
                swapped = true;
            }
        }

        // The vector is already sorted if no swaps were needed.
        if (!swapped) {
            break;
        }
    }
}

// Finds the smallest remaining value and moves it into position.
void selectionSort(std::vector<int>& values) {
    for (int i = 0; i < values.size() - 1; i++) {
        int smallestIndex = i;

        for (int j = i + 1; j < values.size(); j++) {
            if (values[j] < values[smallestIndex]) {
                smallestIndex = j;
            }
        }

        int temp = values[i];
        values[i] = values[smallestIndex];
        values[smallestIndex] = temp;
    }
}

// Inserts each value into the correct position in the sorted section.
void insertionSort(std::vector<int>& values) {
    for (int i = 1; i < values.size(); i++) {
        int currentValue = values[i];
        int j = i - 1;

        while (j >= 0 && values[j] > currentValue) {
            values[j + 1] = values[j];
            j--;
        }

        values[j + 1] = currentValue;
    }
}

// Sorts sections of the vector around a pivot value.
void quickSortHelper(
    std::vector<int>& values,
    int left,
    int right) {

    if (left >= right) {
        return;
    }

    int i = left;
    int j = right;
    int pivot = values[left + (right - left) / 2];

    while (i <= j) {
        while (values[i] < pivot) {
            i++;
        }

        while (values[j] > pivot) {
            j--;
        }

        if (i <= j) {
            int temp = values[i];
            values[i] = values[j];
            values[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j) {
        quickSortHelper(values, left, j);
    }

    if (i < right) {
        quickSortHelper(values, i, right);
    }
}

void quickSort(std::vector<int>& values) {
    if (!values.empty()) {
        quickSortHelper(values, 0, values.size() - 1);
    }
}

// Creates random input.
std::vector<int> makeRandomData(int size) {
    std::vector<int> values;
    std::mt19937 generator(42);
    std::uniform_int_distribution<int> distribution(0, size * 10);

    for (int i = 0; i < size; i++) {
        values.push_back(distribution(generator));
    }

    return values;
}

// Creates already-sorted input.
std::vector<int> makeSortedData(int size) {
    std::vector<int> values;

    for (int i = 0; i < size; i++) {
        values.push_back(i);
    }

    return values;
}

// Creates reverse-sorted input.
std::vector<int> makeReverseData(int size) {
    std::vector<int> values;

    for (int i = size; i > 0; i--) {
        values.push_back(i);
    }

    return values;
}

// Runs and times all four sorting algorithms.
void runTest(
    const std::vector<int>& original,
    const std::string& inputType) {

    std::cout << "\nInput: " << inputType
              << " | Size: " << original.size() << '\n';

    // Bubble sort
    std::vector<int> bubbleValues = original;
    auto bubbleStart = std::chrono::high_resolution_clock::now();
    bubbleSort(bubbleValues);
    auto bubbleEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Bubble Sort: "
              << std::chrono::duration_cast<std::chrono::microseconds>(
                     bubbleEnd - bubbleStart).count()
              << " microseconds | Sorted: "
              << (isSorted(bubbleValues) ? "Yes" : "No") << '\n';

    // Selection sort
    std::vector<int> selectionValues = original;
    auto selectionStart = std::chrono::high_resolution_clock::now();
    selectionSort(selectionValues);
    auto selectionEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Selection Sort: "
              << std::chrono::duration_cast<std::chrono::microseconds>(
                     selectionEnd - selectionStart).count()
              << " microseconds | Sorted: "
              << (isSorted(selectionValues) ? "Yes" : "No") << '\n';

    // Insertion sort
    std::vector<int> insertionValues = original;
    auto insertionStart = std::chrono::high_resolution_clock::now();
    insertionSort(insertionValues);
    auto insertionEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Insertion Sort: "
              << std::chrono::duration_cast<std::chrono::microseconds>(
                     insertionEnd - insertionStart).count()
              << " microseconds | Sorted: "
              << (isSorted(insertionValues) ? "Yes" : "No") << '\n';

    // Quicksort
    std::vector<int> quickValues = original;
    auto quickStart = std::chrono::high_resolution_clock::now();
    quickSort(quickValues);
    auto quickEnd = std::chrono::high_resolution_clock::now();

    std::cout << "Quicksort: "
              << std::chrono::duration_cast<std::chrono::microseconds>(
                     quickEnd - quickStart).count()
              << " microseconds | Sorted: "
              << (isSorted(quickValues) ? "Yes" : "No") << '\n';
}

int main() {
    std::vector<int> sizes = {100, 1000, 5000};

    for (int size : sizes) {
        std::vector<int> randomValues = makeRandomData(size);
        std::vector<int> sortedValues = makeSortedData(size);
        std::vector<int> reverseValues = makeReverseData(size);

        runTest(randomValues, "Random");
        runTest(sortedValues, "Already Sorted");
        runTest(reverseValues, "Reverse Sorted");
    }

    return 0;
}