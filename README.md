# mishaaskarov@gmail.com
# MyContainer Assignment

## Overview

This project implements `MyContainer<T>`, a generic container supporting comparable types (e.g., `int`, `double`, `std::string`). It provides:

 **Dynamic insertion** via `addElement(const T& val)` and **removal** via `removeElement(const T& val)`. Removal uses a loop-based erase to remove all matching values and throws if no element is found.

 **Six custom iteration orders** through nested iterator classes and corresponding `begin_...` / `end_...` methods:

  1. **Insertion Order** (`OrderIterator`): traverse elements in the order they were added.
    * `begin_order()` / `end_order()`

  2. **Ascending Order** (`AscendingOrderIterator`): traverse elements from smallest to largest.
     * `begin_ascending_order()` / `end_ascending_order()`

  3. **Descending Order** (`DescendingOrderIterator`): traverse elements from largest to smallest.
     * `begin_descending_order()` / `end_descending_order()`

  4. **Reverse Insertion Order** (`ReverseOrderIterator`): traverse elements from most recently added back to the first.
     * `begin_reverse_order()` / `end_reverse_order()`

  5. **Side-Cross Order** (`SideCrossOrderIterator`): alternate between smallest, largest, next smallest, next largest, etc.
     * `begin_side_cross_order()` / `end_side_cross_order()`

  6. **Middle-Out Order** (`MiddleOutOrderIterator`): start at the middle element (floor of size/2) of the insertion sequence, then alternate left/right outward.
     * `begin_middle_out_order()` / `end_middle_out_order()`

## Repository Structure

* `MyContainer.hpp`   – Container implementation (header-only)
* `Demo.cpp`          – Example usage; build with `make main`
* `Test.cpp`          – doctest test suite; build and run with `make test`
* `Makefile`          – build, test, valgrind, and clean automation
* `README.md`         – this file

## Build & Run

* Build the demo executable:
    make main


## Run the Demo
    ./main


## Testing
    make test


## Memory Leak Check
    make valgrind


## Clean-Up
    make clean

