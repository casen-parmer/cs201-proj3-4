/*
Shelbe Yousey, Casen Parmer, Riley Herchert - Dr. Don Yessick - Lucas Hasting
Declares the templated maxHeap priority queue class.
*/

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