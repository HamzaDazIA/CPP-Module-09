#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

class PmergeMe {
private:
    // Generate Jacobsthal sequence
    std::vector<size_t> generateJacobsthal(size_t n) {
        std::vector<size_t> jacobsthal;
        
        if (n == 0) return jacobsthal;
        
        jacobsthal.push_back(0);
        if (n == 1) return jacobsthal;
        
        jacobsthal.push_back(1);
        
        size_t j_prev = 0;
        size_t j_curr = 1;
        
        while (true) {
            size_t j_next = j_curr + 2 * j_prev;
            if (j_next >= n) break;
            jacobsthal.push_back(j_next);
            j_prev = j_curr;
            j_curr = j_next;
        }
        
        return jacobsthal;
    }
    
    // Generate insertion order from Jacobsthal sequence
    std::vector<size_t> generateInsertionOrder(size_t pend_size) {
        if (pend_size == 0) return std::vector<size_t>();
        
        std::vector<size_t> jacobsthal = generateJacobsthal(pend_size + 1);
        std::vector<size_t> order;
        
        size_t prev = 0;
        for (size_t i = 2; i < jacobsthal.size(); i++) {
            size_t current = jacobsthal[i];
            
            // Insert indices from current down to prev+1
            for (size_t j = std::min(current, pend_size); j > prev; j--) {
                order.push_back(j - 1); // -1 because we use 0-based indexing
            }
            
            prev = current;
            if (prev >= pend_size) break;
        }
        
        // Add remaining indices if any
        for (size_t j = pend_size; j > prev; j--) {
            order.push_back(j - 1);
        }
        
        return order;
    }
    
    // Binary search with limited range (only search up to 'end' position)
    size_t binarySearchLimited(const std::vector<std::vector<int>>& chain, 
                               const std::vector<int>& value, 
                               size_t end) {
        size_t left = 0;
        size_t right = end;
        
        while (left < right) {
            size_t mid = left + (right - left) / 2;
            
            if (chain[mid].front() < value.front()) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return left;
    }
    
    // Main recursive sorting function
    void mergeInsertionSortRecursive(std::vector<std::vector<int>>& container) {
        // Base case: if 1 or 0 elements, already sorted
        if (container.size() <= 1) {
            return;
        }
        
        // Handle odd element (straggler)
        std::vector<int> straggler;
        bool has_straggler = false;
        
        if (container.size() % 2 == 1) {
            straggler = container.back();
            container.pop_back();
            has_straggler = true;
        }
        
        // ===== PAIRING & COMPARISON PHASE =====
        std::vector<std::vector<int>> paired;
        
        for (size_t i = 0; i + 1 < container.size(); i += 2) {
            std::vector<int> a = container[i];
            std::vector<int> b = container[i + 1];
            
            // Compare front elements - ensure 'a' has the larger front
            if (a.front() < b.front()) {
                std::swap(a, b);
            }
            
            // Merge: append loser 'b' to winner 'a'
            a.insert(a.end(), b.begin(), b.end());
            
            paired.push_back(a);
        }
        
        container = paired;
        
        // ===== RECURSIVE CALL =====
        mergeInsertionSortRecursive(container);
        
        // ===== UNWINDING PHASE =====
        
        // Calculate pair_size to know where to split
        size_t pair_size = container.front().size() / 2;
        
        // Split winners and losers
        std::vector<std::vector<int>> main_chain;
        std::vector<std::vector<int>> pend_chain;
        
        for (size_t i = 0; i < container.size(); i++) {
            std::vector<int>& group = container[i];
            
            // Winner: first pair_size elements
            std::vector<int> winner(group.begin(), group.begin() + pair_size);
            main_chain.push_back(winner);
            
            // Loser: remaining elements
            std::vector<int> loser(group.begin() + pair_size, group.end());
            pend_chain.push_back(loser);
        }
        
        // Insert first loser manually at the front
        if (!pend_chain.empty()) {
            main_chain.insert(main_chain.begin(), pend_chain[0]);
        }
        
        // Generate Jacobsthal insertion order
        std::vector<size_t> insertion_order = generateInsertionOrder(pend_chain.size());
        
        // Insert remaining losers in Jacobsthal order
        for (size_t idx : insertion_order) {
            if (idx == 0 || idx >= pend_chain.size()) continue;
            
            // The winner for pend_chain[idx] is at position idx+1 in main_chain
            // (because we already inserted pend_chain[0] at the beginning)
            size_t winner_pos = idx + 1;
            if (winner_pos > main_chain.size()) {
                winner_pos = main_chain.size();
            }
            
            // Binary search only up to winner's position
            size_t insert_pos = binarySearchLimited(main_chain, pend_chain[idx], winner_pos);
            
            main_chain.insert(main_chain.begin() + insert_pos, pend_chain[idx]);
        }
        
        // Insert straggler if exists
        if (has_straggler) {
            size_t insert_pos = binarySearchLimited(main_chain, straggler, main_chain.size());
            main_chain.insert(main_chain.begin() + insert_pos, straggler);
        }
        
        // Update container with sorted result
        container = main_chain;
    }

public:
    // Public interface: sort a vector of integers
    std::vector<int> sort(const std::vector<int>& input) {
        if (input.size() <= 1) {
            return input;
        }
        
        // Convert to nested container format
        std::vector<std::vector<int>> container;
        for (int num : input) {
            std::vector<int> group;
            group.push_back(num);
            container.push_back(group);
        }
        
        // Perform merge-insertion sort
        mergeInsertionSortRecursive(container);
        
        // Flatten back to regular vector
        std::vector<int> result;
        for (const auto& group : container) {
            result.push_back(group.front());
        }
        
        return result;
    }
    
    // Helper function to print vector
    void printVector(const std::vector<int>& vec, const std::string& label) {
        std::cout << label;
        for (int num : vec) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
};

// ===== MAIN FUNCTION =====
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: No input provided" << std::endl;
        std::cerr << "Usage: ./PmergeMe <positive integers...>" << std::endl;
        return 1;
    }
    
    // Parse input
    std::vector<int> input;
    for (int i = 1; i < argc; i++) {
        try {
            int num = std::stoi(argv[i]);
            if (num < 0) {
                std::cerr << "Error: negative number not allowed" << std::endl;
                return 1;
            }
            input.push_back(num);
        } catch (...) {
            std::cerr << "Error: invalid input" << std::endl;
            return 1;
        }
    }
    
    PmergeMe sorter;
    
    // Print before
    sorter.printVector(input, "Before: ");
    
    // Sort
    std::vector<int> sorted = sorter.sort(input);
    
    // Print after
    sorter.printVector(sorted, "After:  ");
    
    return 0;
}