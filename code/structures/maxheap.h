// header comment

#pragma once

namespace maxHeap
{
    template <typename T, typename Cmp>
    class maxHeap
    {
    public:
        void push(T *item);
        T *top();
        void pop();
        bool empty();
    };
}