#ifndef B_H_FILE
#define B_H_FILE

#include <vector>
using std::vector;


namespace b_tree {

    /*
    Class representing a node in a B tree. 
     */
    template <typename T, typename T2>
    class Node {
        public:
            vector<T*> values;
            vector<T2> keys;
            vector<Node<T, T2>*> children;
            bool leaf;

            Node(T* value, T2 key) {
                values.push_back(value);
                keys.push_back(key);
                leaf = true;
            }

            Node(bool isLeaf) {
                this->leaf = isLeaf;
            }

            void insertValueKeyPair(T* value, T2 key, int i) {
                keys.insert(keys.begin()+i, key);
                values.insert(values.begin()+i, value);
            }

            void fillWithValues(Node<T, T2>* fullNode, int t) {
                this->keys.assign(fullNode->keys.begin() + t,fullNode->keys.end());
                this->values.assign(fullNode->values.begin() + t, fullNode->values.end());
            }

            void shrinkNode(int t) {
                this->keys.resize(t - 1);
                this->values.resize(t - 1);
            }
    };

    /*
    Class representing a tree that is a B tree. 
     */
    template <typename T, typename T2>
    class BTree {
        public:
            Node<T, T2>* root;
            int t;

         
            BTree(int degree) {
                this->root = nullptr;
                this->t = degree;
            }

            void splitChild(Node<T, T2>* parent, int index) {
                //define the full node descending into
                Node<T, T2>* full_node = parent->children[index];
                //define the new right node that will take on values, and define if is a leaf based on if is a leaf value
                Node<T, T2>* right_empty = new Node<T, T2>(full_node->leaf);

                //define the middle key and value based on the fact that each grouping must have at least t-1 elements
                T2 middleKey = full_node->keys[t-1];
                T* middleValue = full_node->values[t-1];

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


            void insertNonFull(Node<T, T2>* node, T* value, T2 key) {
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
                    if (node->children[i]->keys.size() >= 2*t-1) {
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

          
            void insert(T* value, T2 key) {
                if (root == nullptr) {
                    root = new Node<T, T2>(value, key);
                    return;
                }

                //if top is full make the root empty and then split the child which is the old root
                if (root->values.size() >= 2*t-1) {
                    Node<T, T2>* newRoot = new Node<T, T2>(false);
                    newRoot->children.push_back(root);
                    splitChild(newRoot, 0);
                    root = newRoot;
                }
                
                //descend into non full
                insertNonFull(root, value, key);

            }

            T* searchHelper(Node<T, T2>* node, T2 key){
                int i = 0;
                //search for position by going until key is greater than key in node
                while (i < node->keys.size() && key > node->keys[i]) {
                    i++;
                }
                //if the key matches return the value
                if (i < node->keys.size() && key == node->keys[i]) {
                    return node->values[i];
                }
                //if it is a leaf search failed
                if (node->leaf) {
                    return nullptr;
                }
                //recursively search the next level
                return searchHelper(node->children[i], key);
            }

            T* search(T2 key) {
                return searchHelper(root, key);
            }

            void deleteTree(Node<T, T2>* node) {
                if (node == nullptr) {
                    return;
                }
                for (int i = 0; i < node->children.size(); i++) {
                    deleteTree(node->children[i]);
                }
                delete node;
            }

            ~BTree() {
                deleteTree(root);
            }

    };

}

#endif