#include <queue>
#include <vector>

#include "patient.h"

// Compare the priority levels of two paitents to determine their position in the heap
inline constexpr auto lowerPriority = [](Patient* a, Patient* b) {
    return a->getCondition() < b->getCondition();
};

using PatientHeap = std::priority_queue<Patient*, std::vector<Patient*>, decltype(lowerPriority)>;

