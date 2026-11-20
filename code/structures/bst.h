// header comment

#pragma once

namespace BST
{
    template <typename T, typename compare>
    class BST
    {
    public:
        BST();
        ~BST();

        void insert(T *item);
        T *max();
        void remove(T *item);
        bool empty();
    };
}