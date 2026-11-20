#include "btree.h"

namespace b_tree {

    Node::Node(Person* value, std::size_t key) {
        values.push_back(value);
        keys.push_back(key);
        leaf = true;
    }

    Node::Node(bool isLeaf) {
        this->leaf = isLeaf;
    }

    void Node::insertValueKeyPair(Person* value, std::size_t key, int i) {
        keys.insert(keys.begin()+i, key);
        values.insert(values.begin()+i, value);
    }

    void Node::fillWithValues(Node* fullNode, int t) {
        this->keys.assign(fullNode->keys.begin() + t,fullNode->keys.end());
        this->values.assign(fullNode->values.begin() + t, fullNode->values.end());
    }

    void Node::shrinkNode(int t) {
        this->keys.resize(t - 1);
        this->values.resize(t - 1);
    }


    BTree::BTree(int degree) {
        this->root = nullptr;
        this->t = degree;
    }

    BTree::~BTree() {
        deleteTree(root);
    }

    void BTree::splitChild(Node* parent, int index) {
        //define the full node descending into
        Node* full_node = parent->children[index];
        //define the new right node that will take on values, and define if is a leaf based on if is a leaf value
        Node* right_empty = new Node(full_node->leaf);

        //define the middle key and value based on the fact that each grouping must have at least t-1 elements
        std::size_t middleKey = full_node->keys[t-1];
        Person* middleValue = full_node->values[t-1];

        //move all the right values into the empty node
        right_empty->fillWithValues(full_node, t);

        //shrink current node
        full_node->shrinkNode(t);

        //if full node is not a leaf move children to right node
        if (!full_node->leaf) {
            right_empty->children.assign(full_node->children.begin() + t, full_node->children.end());
            full_node->children.resize(t);
        }

        //add the new right child to parent
        parent->children.insert(parent->children.begin()+index+1, right_empty);

        //promote middle key and value to parent in appropriate index
        parent->keys.insert(parent->keys.begin()+index,middleKey);
        parent->values.insert(parent->values.begin()+index,middleValue);
    }


    void BTree::insertNonFull(Node* node, Person* value, std::size_t key) {
        //set i to last index of keys
        int i = node->keys.size() - 1;

        if (node->leaf) {
            //if node is a leaf find the index it belongs at
            while (i >= 0 && key < node->keys[i]) {
                i -= 1;
            }
            i += 1;

            //insert the key value
            node->insertValueKeyPair(value, key, i);
        } else {
            //if node is not leaf find appropriate insertion point to descend into
            while (i >= 0 && key < node->keys[i]) {
                i -= 1;
            }
            i += 1;

            //if the child that would be descended into is full
            if ((int)node->children[i]->keys.size() >= 2*t-1) {
                //split the child so it isnt full
                splitChild(node, i);

                //if the key is too big because of the split go into the new right child
                if (key > node->keys[i]) {
                    i += 1;
                }
            }

            //recursively call until at a leaf
            insertNonFull(node->children[i], value, key);
        }
    }


    void BTree::insert(Person* value, std::size_t key) {
        if (root == nullptr) {
            root = new Node(value, key);
            return;
        }

        //if top is full make the root empty and then split the child which is the old root
        if ((int)root->values.size() >= 2*t-1) {
            Node* newRoot = new Node(false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0);
            root = newRoot;
        }

        //descend into non full
        insertNonFull(root, value, key);

    }

    Person* BTree::searchHelper(Node* node, std::size_t key){
        int i = 0;
        //search for position by going until key is greater than key in node
        while (i < (int)node->keys.size() && key > node->keys[i]) {
            i++;
        }
        //if the key matches return the value
        if (i < (int)node->keys.size() && key == node->keys[i]) {
            return node->values[i];
        }
        //if it is a leaf search failed
        if (node->leaf) {
            return nullptr;
        }
        //recursively search the next level
        return searchHelper(node->children[i], key);
    }

    Person* BTree::search(std::size_t key) {
        return root ? searchHelper(root, key) : nullptr;
    }

    void BTree::inorderHelper(Node* node, vector<Person*> &out) {
        int size = node->values.size();
        for (int i = 0; i < size; i++) {
            if (!node->leaf) {
                inorderHelper(node->children[i], out);
            }
            out.push_back(node->values[i]);
        }

        if (!node->leaf) {
            inorderHelper(node->children[size], out);
        }
    }

    vector<Person*> BTree::inorder() {
        vector<Person*> out;
        if (root != nullptr) {
            inorderHelper(root, out);
        }
        return out;
    }

    void BTree::deleteTree(Node* node) {
        if (node == nullptr) {
            return;
        }
        for (int i = 0; i < (int)node->children.size(); i++) {
            deleteTree(node->children[i]);
        }

        for (int i = 0; i < (int)node->values.size(); i++) {
            delete node->values[i];
        }
        delete node;
    }

    BTree::~BTree() {
        deleteTree(root);
    }

}
