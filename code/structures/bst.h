// header comment

#pragma once

#include "doctor.h"

namespace bst
{
    // Class representing a node in a binary search tree.
    class Node
    {
    public:
        Doctor *value;
        int key;
        Node *left;
        Node *right;
        Node *parent;

        Node(Doctor *value, int key);
    };

    // Class representing a tree that is a binary search tree.
    class Tree
    {
    public:
        Node *root;

        Tree();
        ~Tree();

        void insert(Node *newNode);
        void deleteSubtree(Node *node);
        bool empty();
        Doctor* max();
    };
}
