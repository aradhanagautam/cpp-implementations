C++ Low-Level Implementations

This repository contains from-scratch implementations of below core C++ concepts:
1. Unique Pointer
2. LRU cache
3. Vector

The goal is to build a deep understanding of how things work under the hood.

Implementations
🔹 Smart Pointers
unique_ptr
Custom implementation of exclusive ownership smart pointer.

RAII-based automatic memory management
Move constructor and move assignment (transfers ownership)
Copy constructor and copy assignment deleted (no shared ownership)
Pointer-like access via operator* and operator->

shared_ptr
Custom implementation of shared ownership smart pointer.

Reference counting via shared int* counter
Copy constructor and copy assignment increment ref count
Move constructor and move assignment transfer ownership without incrementing
Resource deleted only when last owner is destroyed
Pointer-like access via operator* and operator->


🔹 Data Structures
LRU Cache
Least Recently Used cache with O(1) get and put operations.

Doubly linked list for ordering
unordered_map for O(1) lookup
Iterator-based design to avoid O(n) deletion
Operations: get(key), put(key, value)

Vector
Custom implementation similar to std::vector.

Dynamic resizing with capacity doubling
Contiguous memory allocation
Tracks size vs capacity separately
Supports push_back


🔹 Concurrency Primitives
Producer-Consumer
Bounded buffer implementation using mutex and condition variables.

Separate producer_cv and consumer_cv for correct signaling
Predicate-based cv.wait() to handle spurious wakeups
Thread-safe with unique_lock

Readers-Writers
Shared resource access with multiple concurrent readers, exclusive writers.

Manual implementation using read_count + two mutexes
First reader locks out writers, last reader unlocks
Also implemented using shared_mutex (C++17)

Read-Write Lock
ReadWriteLock class wrapping the readers-writers pattern.

lock_read() / unlock_read()
lock_write() / unlock_write()
Replicates std::shared_mutex behavior from scratch

Thread Pool
Fixed-size worker thread pool with a task queue.

Worker threads block on condition variable waiting for tasks
enqueue(function<void()>) adds tasks and wakes one worker
Clean shutdown via stop flag and notify_all in destructor
No thread created per task — reuses fixed pool

Print in Order
Enforces sequential execution across threads using condition variables.

stage variable tracks progress
Each thread waits on its precondition before executing


Concepts Covered

RAII and Memory Management
Move Semantics (C++11/14) — Rule of Five
Pointer Ownership Models
Reference Counting
Mutex, Condition Variable, Semaphore
Reader-Writer Synchronization
Thread Pool Design Pattern
Template Programming
STL Internals (vector, list, unordered_map)


⚙️ How to Run
bashg++ main.cpp -std=c++17 -pthread
./a.out
Each module contains its own main.cpp for demonstration.
