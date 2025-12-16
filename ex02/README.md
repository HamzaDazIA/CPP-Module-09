# PmergeMe - Ford-Johnson Merge-Insertion Sort

## Overview
This project implements the Ford-Johnson merge-insertion sort algorithm (also known as merge-insertion sort) for sorting positive integers using both `std::vector` and `std::deque` containers.

## Compilation Errors Fixed

### 1. Type Mismatch Error
**Error Message:**
```
error: conversion from 'vector<long unsigned int>' to non-scalar type 'vector<int>' requested
```

**Problem:**
The function `get_order_jacobsthal()` returns `std::vector<size_t>`, but it was being assigned to `std::vector<int>`.

**Solution:**
```cpp
// Before (WRONG):
std::vector<int> sequence_order = get_order_jacobsthal(pend_chain.size());

// After (CORRECT):
std::vector<size_t> sequence_order = get_order_jacobsthal(pend_chain.size());
```

### 2. Template Function Not Found
**Error Message:**
```
error: 'binarySearchLimited' was not declared in this scope
```

**Problem:**
`binarySearchLimited` was defined in the .cpp file but needed during template instantiation in the header file. Template functions must be visible at the point of instantiation.

**Solution:**
- Moved `binarySearchLimited` to the header file as a template function
- Removed the non-template version from the .cpp file
- Added template declaration in the class

```cpp
// In header file:
template <typename TG, typename T> 
size_t binarySearchLimited(const TG& main_chain, const T& target, size_t limit);

// Template implementation in header:
template <typename TG, typename T>
size_t PmergeMe::binarySearchLimited(const TG& main_chain, const T& target, size_t limit)
{
    // ... implementation
}
```

### 3. C++98 Nested Template Syntax
**Error Message:**
```
error: '>>' should be '> >' within a nested template argument list
```

**Problem:**
C++98 doesn't allow `>>` in nested templates.

**Solution:**
```cpp
// Before (WRONG in C++98):
std::vector<std::vector<int>> group_vector;

// After (CORRECT in C++98):
std::vector<std::vector<int> > group_vector;
```

## Sorting Algorithm Errors Fixed

### 4. Results Not Sorted - Missing Flattening
**Problem:**
The algorithm was sorting the `group` container but never updating the original `cont` container with sorted results.

**Solution:**
Added flattening logic after sorting:

```cpp
template <typename T, typename TG>
void PmergeMe::running_sorting_algorithm(T& cont, TG & group)
{
    // Create groups from individual elements
    for (typename T::iterator it = cont.begin(); it != cont.end(); it++)
    {
        T temp;
        temp.push_back(*it);
        group.push_back(temp);
    }

    // Sort the groups
    ford_Johson_algo(group, cont);
    
    // IMPORTANT: Flatten sorted groups back into container
    cont.clear();
    for (typename TG::iterator it = group.begin(); it != group.end(); ++it)
    {
        for (typename T::iterator elem = it->begin(); elem != it->end(); ++elem)
        {
            cont.push_back(*elem);
        }
    }
}
```

### 5. Incorrect Pair Ordering
**Problem:**
After swapping to ensure `a >= b`, the code was doing `b.insert(b.end(), a)` which created `[small, large]` instead of `[large, small]`.

**Solution:**
```cpp
// Before (WRONG):
if (a < b)
    std::swap(a, b);
b.insert(b.end(), a.begin(), a.end());  // Results in [small, large]

// After (CORRECT):
if (a < b)
    std::swap(a, b);
a.insert(a.end(), b.begin(), b.end());  // Results in [large, small]
```

### 6. Wrong Binary Search Comparison
**Problem:**
Binary search was comparing entire vectors lexicographically instead of comparing only the first element (the sorting key).

**Solution:**
```cpp
// Before (WRONG):
if (main_chain[mid] < target)

// After (CORRECT):
if (main_chain[mid][0] < target[0])
```

### 7. Incorrect Binary Search Limit
**Problem:**
The search limit calculation didn't account for previously inserted elements, causing elements to be inserted in wrong positions.

**Example:** When inserting element at index 2, if we've already inserted 1 element, the limit should be `2 + 1 + 1 = 4`, not `2 + 1 = 3`.

**Solution:**
```cpp
// Before (WRONG):
size_t main_idx = idx + 1;

// After (CORRECT):
size_t main_idx = idx + i + 1;  // i is the loop counter tracking insertions
```

### 8. Straggler Inserted Multiple Times
**Problem:**
Straggler element was inside the insertion loop, causing it to be inserted on every iteration.

**Solution:**
```cpp
// Move straggler insertion OUTSIDE the loop:
for (size_t i = 0; i < sequence_order.size(); i++)
{
    // Insert pend_chain elements
}

// Insert straggler ONCE after all other insertions
if (have_straggeler)
{
    size_t insert_pos = binarySearchLimited(main_chain, strageller, main_chain.size());
    main_chain.insert(main_chain.begin() + insert_pos, strageller);
}
```

## Testing

Test the implementation with various inputs:

```bash
# Compile
make

# Test cases
./PmergeMe 3 2 1                    # Should output: 1 2 3
./PmergeMe 9 8 7 6 5 4 3 2 1       # Should output: 1 2 3 4 5 6 7 8 9
./PmergeMe 3 5 9 7 4                # Should output: 3 4 5 7 9
./PmergeMe 1                        # Should output: 1
./PmergeMe 4 3 2 1                  # Should output: 1 2 3 4
```

## Common Issues

### Input with 'd' or invalid characters
```bash
./PmergeMe 3 5 9 7 4 5 111 11 0550 4 441 1 d
# Output: Invalid input: d
```
This is correct behavior - only positive integers are accepted.

### Leading zeros
Leading zeros like `0550` are accepted and converted to `550`.

## Algorithm Overview

The Ford-Johnson algorithm works as follows:

1. **Pairing**: Group elements into pairs
2. **Comparison**: Within each pair, ensure larger element comes first
3. **Recursive Sort**: Recursively sort pairs by their first (larger) element
4. **Splitting**: Separate into main_chain (larger elements) and pend_chain (smaller elements)
5. **Insertion**: Insert pend_chain elements into main_chain using Jacobsthal sequence order
6. **Binary Search**: Use limited binary search to find optimal insertion positions

The Jacobsthal sequence minimizes comparisons during insertion phase.

## Performance
The algorithm displays timing for both `std::vector` and `std::deque` implementations, allowing comparison of container performance.
