C++ Low-Level Implementations

This repository contains from-scratch implementations of below core C++ concepts:
1. Unique Pointer
2. LRU cache
3. Vector

The goal is to build a deep understanding of how things work under the hood, rather than just using standard libraries.

Implementations
🔹 Smart Pointers
unique_ptr
Custom implementation of exclusive ownership smart pointer
Demonstrates RAII (Resource Acquisition Is Initialization)
Supports:
Move constructor
Move assignment
Deleted copy constructor
Pointer-like access (*, ->)

🔹 Data Structures
LRU Cache
Implements Least Recently Used (LRU) eviction policy
Designed for O(1) operations
Uses:
Doubly Linked List
Hash Map (unordered_map)

Operations:
get(key)
put(key, value)

🔹 Vector
Custom implementation similar to std::vector
Demonstrates dynamic array behavior

Features:
Dynamic resizing
Capacity vs size handling
Contiguous memory allocation
Push back operation



Concepts Covered
RAII and Memory Management
Move Semantics (C++11/14)
Rule of 5
Pointer Ownership Models
STL Internal Working

⚙️ How to Run

Compile using: g++ main.cpp -std=c++14
To run: ./a.out

(Each module contains its own main.cpp for demonstration)