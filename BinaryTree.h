//
// Created by jimch on 18.04.2022.
//

#ifndef LAB3_BINARYTREE_H
#define LAB3_BINARYTREE_H
#include <string>

enum class Field
{
    WEIGHT,
    CODE
};

struct Node
{
    std::string surname;
    int ticket_code;
    double luggage_weight;
    Node* left;
    Node* right;
    bool operator>(Node& rhs)const {return this->surname>rhs.surname; }
    bool operator<(Node& rhs)const {return this->surname<rhs.surname; }
};

class BinaryTree {
private:
    Node* root;
    int count;
    void delete_leaf(Node* leaf);
    void print(Node* leaf, int space);
    void preorder_print(Node* leaf);
    void postorder_print(Node* leaf);
    void inorder_print(Node* leaf);
public:
    BinaryTree();
    ~BinaryTree();
    bool insert(Node&& new_node);
    bool remove(std::string& value);
    Node* search(std::string& value);
    Node* search(int value);
    Node* find_with_parent(std::string& value, Node*& parent);
    void print();
    void preorder_print();
    void postorder_print();
    void inorder_print();
    void delete_tree();
    void get_avarage();
};


#endif //LAB3_BINARYTREE_H
