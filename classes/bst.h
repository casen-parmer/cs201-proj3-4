#ifndef BST_H_FILE
#define BST_H_FILE

#include "doctor.h"

namespace bst {

    /*
    Class representing a node in a binary search tree. 
     */
    class Node {
        public:
            Doctor* value;
            int key;
            Node* left;
            Node* right;
            Node* parent;

            /*
            Initializes a new node with the given value

            Input: value of node
            Output: N/A
            */
            Node(Doctor* value, int key) {
                this->value = value;
                this->key = key;
                this->left = nullptr;
                this->right = nullptr;
                this->parent = nullptr;
            }
    };

    /*
    Class representing a tree that is a binary search tree. 
     */
    class Tree {
        public:
            Node* root;

            /*
            Initializes a tree with a null root

            Input: N/A
            Output: N/A
            */
            Tree() {
                this->root = nullptr;
            }

            /*
            Inserts a new node into the binary search tree

            Input: The reference to the new node to be inserted
            Output: N/A
            */
            void insert(Node* newNode) {
                Node* x = this->root; //start at the root of the tree
                Node* y = nullptr;

                while (x != nullptr) { //go until you reach a null node
                    y = x; //save your previous position
                    if (newNode->key == x->key) {
                        delete newNode; //Value exists don't waste memory
                        return; // Value already exists, do nothing
                    }

                    if (newNode->key < x->key) { //determine whether it goes left or right and move in that direction
                        x = x->left;
                    } else {
                        x = x->right;
                    }
                }

                newNode->parent = y; //set the parent of the new node to the last non-null node

                if (y == nullptr) { //if the tree was empty, set the root to the new node
                    this->root = newNode;
                } else if (newNode->key < y->key) { //if the new node is less than the last non-null node, set it as the left child
                    y->left = newNode;
                } else { //if the new node is greater than the last non-null node, set it as the right child
                    y->right = newNode;
                }

            }

            /*
            Find lowest rank available doctor
            */
            Node* find_lowest_available_doctor(int rank, int time) {
                Node* current = this->root;
                Node* valid_rank = nullptr;
                while (current != nullptr) {
                    if (current->key >= rank) {
                        valid_rank = current;
                        current = current->left;
                    }
                    else {
                        current = current->right;
                    }
                }


                while (valid_rank != nullptr) {
                    if (valid_rank->value->isAvailable() && valid_rank->value->getStartTime() <= time && valid_rank->value->getEndTime() > time) {
                        return valid_rank; // Return the lowest valid rank found
                    }

                    if (valid_rank->right != nullptr) {
                        valid_rank = valid_rank->right;
                        while (valid_rank->left != nullptr) {
                            valid_rank = valid_rank->left;
                        }
                    } else {
                        Node* parent = valid_rank->parent;
                        while (parent != nullptr && valid_rank == parent->right) {
                            valid_rank = parent;
                            parent = parent->parent;
                        }
                        valid_rank = parent;
                    }

                }

                return nullptr; // Return the lowest valid rank found
            }
            
            /*
            Recursively explore the tree and then delete each node

            Input: Node to start deleting from
            Output: N/A
            */
            void deleteSubtree(Node* node) {
                if (node == nullptr) { // check if at the bottom
                    return;
                }

                deleteSubtree(node->left); // explore left subtree
                deleteSubtree(node->right); // explore right subtree
                delete node; //delete node
            }

            /*
            Used to free memory of the binary search tree by deleting all nodes in the tree.
            Input: N/A
            Output: N/A
            */
            ~Tree() {
                // Destructor to free memory
                deleteSubtree(this->root);
            }
    };

}

#endif