// header comment

#pragma once
#include "maxheap.tpp"
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
            maxHeap(Cmp cmp);
            void push(T *item);
            T *top();
            void pop();
            bool empty();
    };
}