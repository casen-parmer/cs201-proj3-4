#include <queue>
#include <vector>

#include "patient.h"
#include "maxheap.h"

// Compare the priority levels of two paitents to determine their position in the heap
inline constexpr auto lowerPriority = [](Patient* a, Patient* b) {
    return a->getCondition() < b->getCondition();
};

using PatientHeap = std::priority_queue<Patient*, std::vector<Patient*>, decltype(lowerPriority)>;

namespace maxHeap
{
    
    template <typename T, typename Cmp>
    void maxHeap<T, Cmp>::push(T* person) {
        this->push(person);
    }

    template <typename T, typename Cmp>
    T* maxHeap<T, Cmp>::top() {
        return this->top();
    }

    template <typename T, typename Cmp>
    void maxHeap<T, Cmp>::pop() {
        this->pop();
    }

    template <typename T, typename Cmp>
    bool maxHeap<T, Cmp>::empty() {
        return this->empty();
    }

}

