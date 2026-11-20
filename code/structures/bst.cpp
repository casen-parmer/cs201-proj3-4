#include "bst.h"

namespace bst
{
    /*
    Initializes a new node with the given value

    Input: value of node
    Output: N/A
    */
    Node::Node(Doctor *value, int key)
    {
        this->value = value;
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    }

    /*
    Initializes a tree with a null root

    Input: N/A
    Output: N/A
    */
    Tree::Tree()
    {
        this->root = nullptr;
    }

    /*
    Inserts a new node into the binary search tree

    Input: The reference to the new node to be inserted
    Output: N/A
    */
    void Tree::insert(Node *newNode)
    {
        Node *x = this->root; // start at the root of the tree
        Node *y = nullptr;

        while (x != nullptr)
        {          // go until you reach a null node
            y = x; // save your previous position

            if (newNode->key < x->key)
            { // determine whether it goes left or right and move in that direction
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        newNode->parent = y; // set the parent of the new node to the last non-null node

        if (y == nullptr)
        { // if the tree was empty, set the root to the new node
            this->root = newNode;
        }
        else if (newNode->key < y->key)
        { // if the new node is less than the last non-null node, set it as the left child
            y->left = newNode;
        }
        else
        { // if the new node is greater than the last non-null node, set it as the right child
            y->right = newNode;
        }
    }

    /*
    Recursively explore the tree and then delete each node

    Input: Node to start deleting from
    Output: N/A
    */
    void Tree::deleteSubtree(Node *node)
    {
        if (node == nullptr)
        { // check if at the bottom
            return;
        }

        deleteSubtree(node->left);  // explore left subtree
        deleteSubtree(node->right); // explore right subtree
        delete node;                // delete node
    }

    bool Tree::empty() {
        return this->root == nullptr;
    }

    Doctor* Tree::max() {
        Node *current = this->root;
        if (current == nullptr) {
            return nullptr; 
        }
        while (current->right != nullptr) {
            current = current->right;
        }
        return current->value;
    }

    /*
    Used to free memory of the binary search tree by deleting all nodes in the tree.
    Input: N/A
    Output: N/A
    */
    Tree::~Tree()
    {
        // Destructor to free memory
        deleteSubtree(this->root);
    }
}
