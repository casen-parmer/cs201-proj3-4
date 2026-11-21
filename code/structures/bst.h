/*
Shelbe Yousey, Casen Parmer, Riley Herchert - Dr. Don Yessick - Lucas Hasting
Defines the binary search tree Node and Tree classes for on-shift doctors.
*/

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
        void remove(Node*);
        Node* find(std::size_t value_id, int skill_rank);
    };
}
