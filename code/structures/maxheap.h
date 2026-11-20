// header comment

#pragma once
#include <vector>
namespace maxHeap
{
    template <typename T, typename Cmp>
    class maxHeap
    {
        private:
            std::vector<T *> items;
            Cmp cmp;
        public:
            void push(T *item);
            T *top();
            void pop();
            bool empty();
    };
}

#include "maxheap.tpp"