// header comment

#pragma once

#include <memory>
#include <vector>

namespace bTree
{
    template <typename T, typename Cmp>
    class bTree
    {
    public:
        bTree(int degree);
        ~bTree();
        bTree(const bTree &) = delete;
        bTree &operator=(const bTree &) = delete;

        T *insert(std::unique_ptr<T> item);
        T *search(T *probe);
        std::vector<T *> inorder();

        template <typename U>
        U *insert(std::unique_ptr<U> item)
        {
            return static_cast<U *>(insert(std::unique_ptr<T>(std::move(item))));
        }

        template <typename U>
        U *searchAs(T *probe)
        {
            return dynamic_cast<U *>(search(probe));
        }
    };
}