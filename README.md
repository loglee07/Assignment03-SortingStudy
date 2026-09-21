# Assignment 03: isSorted and Sorting Study

This C++17 program implements and compares four sorting algorithms:

* Bubble sort
* Selection sort
* Insertion sort
* Quicksort

The program tests each algorithm using random, already-sorted, and reverse-sorted vectors. It uses input sizes of 100, 1,000, and 5,000 elements. Each result is checked with the `isSorted` function.

## Compile and Run

```bash
clang++ -std=c++17 main.cpp -o sorting_study
./sorting_study
```

## Files

* `main.cpp` — source code
* `results.txt` — timing and testing results

The program does not use `std::sort`.

## Acknowledgments

I used the assignment instructions, course material, and AI assistance for guidance and explanations while developing and reviewing the program.
