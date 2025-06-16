// mishaaskarov@gmail.com

#pragma once

#include <iostream>   
#include <vector>    
#include <stdexcept>   
#include <algorithm>   

namespace ariel {

// MyContainer
template<typename T = int>
class MyContainer {
private:
    std::vector<T> elements;  // Stores elements

public:
    // Adds a new element to the end of the container
    void addElement(const T& val) {
        elements.push_back(val);
    }

    // Removes all instances of `val` from the container.
    // Uses erase in a loop(while not at end) and throws if no elements were removed.
    void removeElement(const T& val) {
        bool found = false;
        typename std::vector<T>::iterator it = elements.begin();
        while (it != elements.end()) {
            if (*it == val) {
                it = elements.erase(it);
                found = true;
            } else {
                ++it;
            }
        }
        if (!found) {
            throw std::runtime_error("Element not found.");
        }
    }

    // Returns the number of elements currently in the container
    size_t size() const {
        return elements.size();
    }

    // Prints container contents in the format [e1, e2, ...]
    friend std::ostream& operator<<(std::ostream& os, const MyContainer<T>& c) {
        os << "[";
        for (size_t i = 0; i < c.elements.size(); ++i) {
            os << c.elements[i];
            if (i + 1 < c.elements.size()) os << ", ";
        }
        os << "]";
        return os;
    }



    // --- 1. Insertion-order iterator ---
    // Iterates elements in the order they were added.
    class OrderIterator {
    private:
        const MyContainer<T>& cont;  // Reference to container
        size_t idx; // Current index in elements
    public:
        // Constructor
        OrderIterator(const MyContainer<T>& c, size_t start) : cont(c), idx(start) {}

        // Get current element
        const T& operator*() const {
            if (idx >= cont.elements.size())
                throw std::out_of_range("OrderIterator out of range");
            return cont.elements[idx];
        }

        // Move to next element
        OrderIterator& operator++() {
            ++idx;
            return *this;
        }

        // Comparison -> equal if same container and same position
        bool operator==(const OrderIterator& o) const {
            return &cont == &o.cont && idx == o.idx;
        }
        bool operator!=(const OrderIterator& o) const {
            return !(*this == o);
        }
    };

    // begin_order -> first element in insertion order
    OrderIterator begin_order() const { return OrderIterator(*this, 0); }
    // end_order -> one past the last element
    OrderIterator end_order()   const { return OrderIterator(*this, elements.size()); }



    // --- 2. Ascending-order iterator ---
    // Iterates elements from smallest to largest.
    class AscendingOrderIterator {
    private:
        std::vector<T> sorted;  
        size_t idx;            
    public:
        // Constructor -> sort sorted and set start index
        AscendingOrderIterator(const MyContainer<T>& c, size_t start) : sorted(c.elements), idx(start) {
            std::sort(sorted.begin(), sorted.end());
        }

        // Get current element
        const T& operator*() const {
            if (idx >= sorted.size())
                throw std::out_of_range("AscendingOrderIterator out of range");
            return sorted[idx];
        }

        // Move to next sorted element
        AscendingOrderIterator& operator++() {
            ++idx;
            return *this;
        }

        // Comparison -> equal if same position
        bool operator==(const AscendingOrderIterator& o) const {
            return idx == o.idx;
        }
        bool operator!=(const AscendingOrderIterator& o) const {
            return idx != o.idx;
        }
    };

    // Smallest element
    AscendingOrderIterator begin_ascending_order() const {return AscendingOrderIterator(*this, 0); }
    
    // One past largest element
    AscendingOrderIterator end_ascending_order() const { return AscendingOrderIterator(*this, elements.size()); }



    // --- 3. Descending-order iterator ---
    // Iterates elements from largest to smallest.
    class DescendingOrderIterator {
    private:
        std::vector<T> sorted;  
        size_t idx;        
    public:
        // Constructor
        DescendingOrderIterator(const MyContainer<T>& c, size_t start) : sorted(c.elements), idx(start) {
            std::sort(sorted.begin(), sorted.end(), std::greater<T>());
        }

        // Get current element
        const T& operator*() const {
            if (idx >= sorted.size())
                throw std::out_of_range("DescendingOrderIterator out of range");
            return sorted[idx];
        }

        // Move to next sorted element
        DescendingOrderIterator& operator++() {
            ++idx;
            return *this;
        }

        // Comparison -> equal if same position
        bool operator==(const DescendingOrderIterator& o) const {
            return idx == o.idx;
        }
        bool operator!=(const DescendingOrderIterator& o) const {
            return idx != o.idx;
        }
    };

    // begin_descending_order -> largest element
    DescendingOrderIterator begin_descending_order() const { return DescendingOrderIterator(*this, 0); }

    // end_descending_order -> one past smallest element
    DescendingOrderIterator end_descending_order() const { return DescendingOrderIterator(*this, elements.size()); }



    // --- 4. Reverse-order iterator ---
    // Iterates elements from last added to first added.
    class ReverseOrderIterator {
    private:
        std::vector<T> reversed;  // Reversed copy of elements
        size_t idx; // Current index in reversed
    public:
        // Constructor
        ReverseOrderIterator(const MyContainer<T>& c, size_t start) : reversed(c.elements), idx(start) {
            std::reverse(reversed.begin(), reversed.end());
        }

        // Get current element
        const T& operator*() const {
            if (idx >= reversed.size())
                throw std::out_of_range("ReverseOrderIterator out of range");
            return reversed[idx];
        }

        // Move to next element
        ReverseOrderIterator& operator++() {
            ++idx;
            return *this;
        }

        // Comparison -> equal if same position
        bool operator==(const ReverseOrderIterator& o) const {
            return idx == o.idx;
        }
        bool operator!=(const ReverseOrderIterator& o) const {
            return idx != o.idx;
        }
    };

    // begin_reverse_order -> most recently added
    ReverseOrderIterator begin_reverse_order() const { return ReverseOrderIterator(*this, 0); }
    
    // end_reverse_order: one past oldest added
    ReverseOrderIterator end_reverse_order() const { return ReverseOrderIterator(*this, elements.size()); }



    // --- 5. Side-cross iterator ---
    // Iterates: smallest, largest, second-smallest, second-largest, etc.
    class SideCrossOrderIterator {
    private:
        std::vector<T> crossed;  // Side-cross ordered copy
        size_t idx;  // Current index in crossed
    public:
        // Constructor
        SideCrossOrderIterator(const MyContainer<T>& c, size_t start) : idx(start) {
            std::vector<T> s = c.elements;
            std::sort(s.begin(), s.end());
            size_t i = 0, j = s.size();  //point to start and end
            if (j > 0) --j;
            while (i < j) {  //add accordingly and i++ & j--
                crossed.push_back(s[i++]);
                crossed.push_back(s[j--]);
            }
            if (i == j) {
                crossed.push_back(s[i]);
            }
        }

        // Get current element
        const T& operator*() const {
            if (idx >= crossed.size())
                throw std::out_of_range("SideCrossOrderIterator out of range");
            return crossed[idx];
        }

        // Move to next element
        SideCrossOrderIterator& operator++() {
            ++idx;
            return *this;
        }

        // Comparison -> equal if same position
        bool operator==(const SideCrossOrderIterator& o) const {
            return idx == o.idx;
        }
        bool operator!=(const SideCrossOrderIterator& o) const {
            return idx != o.idx;
        }
    };

    // begin_side_cross_order -> first in side-cross pattern
    SideCrossOrderIterator begin_side_cross_order() const { return SideCrossOrderIterator(*this, 0); }
    // end_side_cross_order -> one past last in pattern
    SideCrossOrderIterator end_side_cross_order() const { return SideCrossOrderIterator(*this, elements.size()); }



    // --- 6. Middle-out iterator ---
    // Iterates: center element, then alternate left and right (on original insertion order).
    class MiddleOutOrderIterator {
    private:
        std::vector<T> middled;  // Middle-out ordered copy
        size_t idx;// Current index in middled
    public:
        // Constructor
        MiddleOutOrderIterator(const MyContainer<T>& c, size_t start)
            : idx(start) {
            std::vector<T> s = c.elements;  // use original order, no sort
            size_t n = s.size();
            if (n == 0) {
                return;
            }
            size_t mid = n / 2;  // middle index (floor)
            int left = int(mid) - 1;  // one left of middle
            size_t right = mid + 1;  // one right of middle
            middled.push_back(s[mid]);  // start with middle element
            bool takeLeft = true;
            // alternate left/right until all are added
            while (middled.size() < n) {
                if (takeLeft && left >= 0) {
                    middled.push_back(s[left--]);
                } else if (!takeLeft && right < n) {
                    middled.push_back(s[right++]);
                }
                takeLeft = !takeLeft;
            }
        }

        // Get current element
        const T& operator*() const {
            if (idx >= middled.size())
                throw std::out_of_range("MiddleOutOrderIterator out of range");
            return middled[idx];
        }

        // Move to next element
        MiddleOutOrderIterator& operator++() {
            ++idx;
            return *this;
        }

        // Comparison -> equal if same position
        bool operator==(const MiddleOutOrderIterator& o) const {
            return idx == o.idx;
        }
        bool operator!=(const MiddleOutOrderIterator& o) const {
            return idx != o.idx;
        }
    };

    // begin_middle_out_order -> start at center element
    MiddleOutOrderIterator begin_middle_out_order() const { return MiddleOutOrderIterator(*this, 0); }
    
    // end_middle_out_order: one past last in middle-out order
    MiddleOutOrderIterator end_middle_out_order() const { return MiddleOutOrderIterator(*this, elements.size()); }
};

} // namespace ariel

