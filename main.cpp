#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <climits>

class PmergeMe
{
private:
    std::vector<size_t> generateJacobsthal(size_t n)
    {
        std::vector<size_t> jacobsthal;

        if (n == 0)
            return jacobsthal;

        jacobsthal.push_back(0);
        if (n == 1)
            return jacobsthal;

        jacobsthal.push_back(1);

        size_t j_prev = 0;
        size_t j_curr = 1;

        while (true)
        {
            size_t j_next = j_curr + 2 * j_prev;
            if (j_next >= n)
                break;
            jacobsthal.push_back(j_next);
            j_prev = j_curr;
            j_curr = j_next;
        }

        return jacobsthal;
    }

    std::vector<size_t> generateInsertionOrder(size_t pend_size)
    {
        if (pend_size == 0)
            return std::vector<size_t>();

        std::vector<size_t> jacobsthal = generateJacobsthal(pend_size + 1);
        std::vector<size_t> order;

        size_t prev = 0;
        for (size_t i = 2; i < jacobsthal.size(); i++)
        {
            size_t current = jacobsthal[i];

            for (size_t j = std::min(current, pend_size); j > prev; j--)
            {
                order.push_back(j - 1);
            }

            prev = current;
            if (prev >= pend_size)
                break;
        }

        for (size_t j = pend_size; j > prev; j--)
        {
            order.push_back(j - 1);
        }

        return order;
    }

    size_t binarySearchLimited(const std::vector<std::vector<int> > &chain,
                               const std::vector<int> &value,
                               size_t end)
    {
        size_t left = 0;
        size_t right = end;

        while (left < right)
        {
            size_t mid = left + (right - left) / 2;

            if (chain[mid].front() < value.front())
            {
                left = mid + 1;
            }
            else
            {
                right = mid;
            }
        }

        return left;
    }

    void mergeInsertionSortRecursive(std::vector<std::vector<int> > &container)
    {
        if (container.size() <= 1)
        {
            return;
        }

        std::vector<int> straggler;
        bool has_straggler = false;

        if (container.size() % 2 == 1)
        {
            straggler = container.back();
            container.pop_back();
            has_straggler = true;
        }

        std::vector<std::vector<int> > paired;

        for (size_t i = 0; i + 1 < container.size(); i += 2)
        {
            std::vector<int> a = container[i];
            std::vector<int> b = container[i + 1];

            if (a.front() < b.front())
            {
                std::swap(a, b);
            }

            a.insert(a.end(), b.begin(), b.end());

            paired.push_back(a);
        }

        container = paired;

        mergeInsertionSortRecursive(container);

        size_t pair_size = container.front().size() / 2;

        std::vector<std::vector<int> > main_chain;
        std::vector<std::vector<int> > pend_chain;

        for (size_t i = 0; i < container.size(); i++)
        {
            std::vector<int> &group = container[i];

            std::vector<int> winner(group.begin(), group.begin() + pair_size);
            main_chain.push_back(winner);

            std::vector<int> loser(group.begin() + pair_size, group.end());
            pend_chain.push_back(loser);
        }

        if (!pend_chain.empty())
        {
            main_chain.insert(main_chain.begin(), pend_chain[0]);
        }

        std::vector<size_t> insertion_order = generateInsertionOrder(pend_chain.size());

        for (std::vector<size_t>::iterator it = insertion_order.begin(); it != insertion_order.end(); ++it)
        {

            size_t idx = *it;

            if (idx == 0 || idx >= pend_chain.size())
                continue;

            size_t winner_pos = idx + 1;
            if (winner_pos > main_chain.size())
            {
                winner_pos = main_chain.size();
            }

            size_t insert_pos = binarySearchLimited(main_chain, pend_chain[idx], winner_pos);

            main_chain.insert(main_chain.begin() + insert_pos, pend_chain[idx]);
        }

        if (has_straggler)
        {
            size_t insert_pos = binarySearchLimited(main_chain, straggler, main_chain.size());
            main_chain.insert(main_chain.begin() + insert_pos, straggler);
        }

        container = main_chain;
    }

public:
    std::vector<int> sort(const std::vector<int> &input)
    {
        if (input.size() <= 1)
        {
            return input;
        }

        std::vector<std::vector<int> > container;
        for (std::vector<int>::const_iterator it = input.begin(); it != input.end(); ++it)
        {
            std::vector<int> group;
            group.push_back(*it);
            container.push_back(group);
        }

        mergeInsertionSortRecursive(container);

        std::vector<int> result;
        for (std::vector<std::vector<int> >::iterator it = container.begin(); it != container.end(); ++it)
        {
            result.push_back(it->front());
        }

        return result;
    }

    void printVector(const std::vector<int> &vec, const std::string &label)
    {
        std::cout << label;
        for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
};

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error: No input provided" << std::endl;
        std::cerr << "Usage: ./PmergeMe <positive integers...>" << std::endl;
        return 1;
    }

    std::vector<int> input;
    for (int i = 1; i < argc; i++)
    {
        char *endptr;
        long num = std::strtol(argv[i], &endptr, 10);

        if (argv[i] == endptr || *endptr != '\0')
        {
            std::cerr << "Error: invalid input" << std::endl;
            return 1;
        }

        if (num < 0 || num > INT_MAX)
        {
            std::cerr << "Error: negative number or overflow not allowed" << std::endl;
            return 1;
        }

        input.push_back(static_cast<int>(num));
    }

    PmergeMe sorter;

    sorter.printVector(input, "Before: ");

    std::vector<int> sorted = sorter.sort(input);

    sorter.printVector(sorted, "After:  ");

    return 0;
}