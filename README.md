# Red-Black Tree Implementation

## Overview
This project contains an implementation of a **Red-Black Tree** data structure in C++. It includes the core class for the Red-Black Tree, a testing suite for validating functionality, and a makefile for running tests efficiently.

## Project Structure
- **RBTree.cpp**: Contains the implementation of the **Red-Black Tree** class, including insertion, deletion, balancing, and other fundamental operations.
- **TestingSuite.cpp**: Includes a set of test cases to verify the correctness of the Red-Black Tree implementation, covering edge cases and ensuring robustness.
- **Makefile**: Provides commands to compile the project and run the test suite.

## Features
- **Balanced Tree Operations**: Implements all core Red-Black Tree operations, such as insertion, deletion, search, and self-balancing.
- **Self-Balancing Mechanism**: Ensures that the tree maintains balanced properties after each operation for optimal performance.
- **Testing Suite**: Comprehensive tests included to ensure correctness and efficiency.

## Usage
1. **Compile the Project**: Use the provided makefile to compile and run **TestingSuite.cpp**:
   ```sh
   make
   ```
2. **Run Tests**: After compiling, use the following command to execute the test suite and verify the implementation:
   ```sh
   ./test
   ```

## How It Works
A **Red-Black Tree** is a type of self-balancing binary search tree. The implementation ensures logarithmic time complexity for key operations like insertion, deletion, and search by maintaining a set of balancing rules. The core features include:
- Nodes are either **red** or **black**.
- The tree is always roughly balanced, which guarantees efficient performance.
- The **TestingSuite.cpp** verifies key properties, such as the maintenance of balancing rules, proper color assignments, and overall correctness of operations.
