

#ifndef LAB3_BINARYTREE_H
#define LAB3_BINARYTREE_H
#include <iostream>

enum class Field
{
    WEIGHT,
    CODE
};
//linux
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
    void delete_left_subtree(Node* leaf);
    void delete_right_subtree(Node* leaf);
    Node* move_leaf(Node* origin, Node* array);
    void write(Node* leaf, int space, std::ostream& out);

public:
    BinaryTree();
    ~BinaryTree();
    BinaryTree(BinaryTree&& other) noexcept;
    BinaryTree& operator=(BinaryTree&& other);
    bool insert(Node&& new_node);
    bool insert(Node&& new_node, bool(*comp)(Node&, Node&));
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
    void delete_left_subtree();
    void delete_right_subtree();
    void move_tree(BinaryTree& other);
    void read_file(std::istream& in);
    void write_file(std::ostream& out);
};


#endif //LAB3_BINARYTREE_H
