/*
Shelbe Yousey, Casen Parmer, Riley Herchert - Dr. Don Yessick - Lucas Hasting
Defines the BTree and Node classes for storing Person records by ID.
*/

#ifndef B_H_FILE
#define B_H_FILE

#include <cstddef>
#include <vector>
#include "person.h"
using std::vector;


namespace b_tree {

    /*
    Class representing a node in a B tree.
     */
    class Node {
        public:
            vector<Person*> values;
            vector<std::size_t> keys;
            vector<Node*> children;
            bool leaf;

            Node(Person* value, std::size_t key);
            Node(bool isLeaf);
            void insertValueKeyPair(Person* value, std::size_t key, int i);
            void fillWithValues(Node* fullNode, int t);
            void shrinkNode(int t);
    };

    /*
    This class is a BTree implementation.
     */
    class BTree {
        public:
            Node* root;
            int t;

            BTree(int degree);
            ~BTree();

            void splitChild(Node* parent, int index);
            void insertNonFull(Node* node, Person* value, std::size_t key);
            void insert(Person* value, std::size_t key);
            Person* searchHelper(Node* node, std::size_t key);
            Person* search(std::size_t key);
            void inorderHelper(Node* node, vector<Person*> &out);
            vector<Person*> inorder();
            void deleteTree(Node* node);
    };

}

#endif
