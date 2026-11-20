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

    Node* Tree::find(std::size_t value_id, int skill_rank) {
        Node *current = this->root;
        if (current == nullptr) {
            return nullptr; 
        }
        while (current && current->value->getID() != value_id) {
            if (current->value->getSkill() >= skill_rank) {
                current = current->right;
            } else {
                current = current->left;
            }
            
        }
        if (!current) {
            return nullptr;
        } else {
            return current;
        }
    }

    /*
    Deletes a node from the binary search tree

    Input: The reference to the node to be deleted
    Output: N/A
    */
    void Tree::remove(Node* node) {
        if (node == nullptr) { // Check if the node is null if so do nothing
            return;
        } 

        if (node->left == nullptr && node->right == nullptr) { // If the node has no children just remove it
            if (node->parent == nullptr) { //if it is the root node root becomes null
                this->root = nullptr;
            } else if (node == node->parent->left) { //if it is the left child of its parent set the left child of its parent to null
                node->parent->left = nullptr;
            } else { //if it is the right child of its parent set the right child of its parent to null
                node->parent->right = nullptr;
            }
            delete node; //delete the node
        } else if (node->left == nullptr || node->right == nullptr) { // If the node has one child
            Node* child = (node->left != nullptr) ? node->left : node->right; // Get the existing child

            if (node->parent == nullptr) { //if it is the root node set the root to the child
                this->root = child;
            } else if (node == node->parent->left) { //if node is the left child
                node->parent->left = child; //set the parent's left child to the replacement child
            } else { //if node is the right child
                node->parent->right = child; //set the parent's right child to the replacement child
            }

            child->parent = node->parent; //set the child's parent to the node's parent
            delete node; //delete the node
        } else { // If the node has two children, find the successor
            Node* successor = node->right; //go right once
            while (successor->left != nullptr) { //continuously go left until you reach the leftmost node
                successor = successor->left;
            }

            Doctor* tempValue = successor->value; //save the value of the successor
            deleteSubtree(successor); //remove the successor node
            node->value = tempValue; //set the node's value to the successor's value
        }

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
