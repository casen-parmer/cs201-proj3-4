/*
Shelbe Yousey, Casen Parmer, Riley Herchert - Dr. Don Yessick - Lucas Hasting
Implements the templated maxHeap push, top, pop, and empty methods.
*/

// Template definitions for maxHeap, included at the bottom of maxheap.h
// cmp(a, b) is true when a has lower priority than b, so the highest priority item stays at items[0]

#include <utility>

namespace maxHeap
{
    // Inserts an item and sifts up to preserve heap order. Input: item pointer. Output: N/A.
    template <typename T, typename Cmp>
    void maxHeap<T, Cmp>::push(T *item) {
        items.push_back(item);
        int i = items.size()-1;
        while (i > 0 && cmp(items[(i-1)/2], items[i])) {
            std::swap(items[(i-1)/2], items[i]);
            i = (i - 1) / 2;
        }
    }

    // Returns the highest-priority item without removing it. Input: N/A. Output: top pointer or nullptr if empty.
    template <typename T, typename Cmp>
    T *maxHeap<T, Cmp>::top() {
        if (items.empty()) {
            return nullptr;
        }
        return items[0];
    }

    // Removes the top item and sifts down to restore heap order. Input: N/A. Output: N/A.
    template <typename T, typename Cmp>
    void maxHeap<T, Cmp>::pop()
    {
        if (items.empty()) {
            return;
        }
        items[0] = items.back();
        items.pop_back();

        int n = items.size();
        int i = 0;
        while (true) {
            int left = 2*i+1;
            int right = 2*i+2;
            int largest = i;
            if (left < n && cmp(items[largest], items[left])) {
                largest = left;
            }
            if (right < n && cmp(items[largest], items[right])) {
                largest = right;
            }
            if (largest == i) {
                break;
            }
            std::swap(items[i], items[largest]);
            i = largest;
        }
    }

    // Checks whether the heap contains no items. Input: N/A. Output: true if empty, false otherwise.
    template <typename T, typename Cmp>
    bool maxHeap<T, Cmp>::empty() {
        return items.empty();
    }
}
