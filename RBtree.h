//
// Created by denny on 04.05.2022.
//

#ifndef LAB3_RBTREE_H
#define LAB3_RBTREE_H
#include <iostream>

enum class Color: bool
{
    RED,
    BLACK
};

struct RBNode
{
    std::string surname;
    int ticket_code;
    double luggage_weight;
    RBNode* left;
    RBNode* right;
    RBNode* parent;
    Color color;
    bool operator>(RBNode& rhs)const {return this->surname>rhs.surname; }
    bool operator<(RBNode& rhs)const {return this->surname<rhs.surname; }
};

class RBtree {
private:
    using NodePtr = RBNode*;
    NodePtr TNULL;
    RBNode* root;
    int count;
    void print(RBNode* leaf, int space);
    void fix_insert(RBNode* node);
    void fix_removal(RBNode* node);
    void left_rotate(RBNode* node);
    void right_rotate(RBNode* node);
    void rb_transplant(RBNode* u, RBNode* v);
    NodePtr minimum(NodePtr node);
    void delete_leaf(RBNode* leaf);
public:
    RBtree();
    ~RBtree();
    bool insert(RBNode&& new_node);
    bool remove(std::string& value);
    RBNode* search(std::string& value);
    //RBNode* search(int value);
    RBNode* find_with_parent(std::string& value, RBNode*& parent);
    void print();
};


#endif //LAB3_RBTREE_H
