//
// Created by jimch on 18.04.2022.
//

#include "BinaryTree.h"
#include <iostream>
#include <iomanip>

BinaryTree::BinaryTree():
    root{nullptr}, count{0}
{}

bool BinaryTree::insert(Node&& new_node) {
    if(!root)
    {
        root = new Node{new_node};
    }
    else
    {
        Node* curr = root;
        while(curr)
        {
            if(new_node < *curr)
            {
                if(curr->left == nullptr)
                {
                    curr->left = new Node{new_node};
                    break;
                }
                else
                {
                    curr = curr->left;
                }
            }
            else
            {
                if(curr->right == nullptr)
                {
                    curr->right = new Node{new_node};
                    break;
                }
                else
                {
                    curr = curr->right;
                }
            }
        }
    }
    ++count;
    return false;
}

BinaryTree::~BinaryTree() {
    delete_tree();
}

Node *BinaryTree::search(int value) {

    return nullptr;
}

Node *BinaryTree::search(std::string& value) {
    if(root->surname == value)
    {
        return root;
    }
    Node* current = root;
    while(current)
    {
        if(current->surname == value)
            return current;
        if(value < current->surname) {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return nullptr;
}

bool BinaryTree::remove(std::string& value) {
    Node* parent = nullptr;
    Node* target = find_with_parent(value, parent);
    if(target == nullptr)
        return false;
    if(!target->left && !target->right)
    {
        if(*target < *parent)
        {
            parent->left = nullptr;
        }
        else
        {
            parent->right = nullptr;
        }
    }
    else if(!target->right)
    {
        if(parent == nullptr)
        {
            root = target->left;
        }
        else
        {
            if(*target > *parent)
            {
                parent->right = target->left;
            }
            else
            {
                parent->left = target->left;
            }
        }
    }
    else if(target->right->left == nullptr)
    {
        if(parent == nullptr)
        {
            root = target->right;
        }
        else
        {
            if(*target > *parent)
            {
                parent->right = target->right;
            }
            else
            {
                parent->left = target->right;
            }
        }
    }
    else
    {
        Node* most_left = target->right->left;
        Node* most_left_parent = target->right;
        while(most_left->left)
        {
            most_left_parent = most_left; most_left = most_left->left;
        }
        most_left_parent->left = nullptr;
        most_left->right = target->right;
        most_left->left = target->left;
        if(parent == nullptr)
        {
            root = most_left;
        }
        else if(*target > *parent)
        {
            parent->right = most_left;
        }
        else
        {
            parent->left = most_left;
        }
    }
    delete target;
    count--;
    return true;
}

Node *BinaryTree::find_with_parent(std::string &value,Node*& parent) {
    if(root->surname == value)
    {
        return root;
    }
    Node* current = root;
    while(current)
    {
        if(current->surname == value)
            return current;
        parent = current;
        if(value < current->surname) {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }
    return nullptr;
}

void BinaryTree::delete_leaf(Node *leaf) {
    if(leaf != nullptr)
    {
        delete_leaf(leaf->right);
        delete_leaf(leaf->left);
        delete leaf;
    }
}

void BinaryTree::print(Node *leaf, int space) {
    if(leaf != nullptr)
    {
        space += 10;
        print(leaf->right,space);
        std::cout << std::endl;
        for (int i = 10; i < space; ++i) {
            std::cout << " ";
        }
        std::cout <<leaf->surname << "|" << leaf->ticket_code << "|" << leaf->luggage_weight << std::endl;
        print(leaf->left,space);
    }
}

void BinaryTree::preorder_print(Node *leaf) {
    if(leaf != nullptr)
    {
        std::cout <<leaf->surname << "|" << leaf->ticket_code << "|" << leaf->luggage_weight << std::endl;
        inorder_print(leaf->left);
        inorder_print(leaf->right);
    }
}

void BinaryTree::postorder_print(Node *leaf) {
    if(leaf != nullptr)
    {
        inorder_print(leaf->left);
        inorder_print(leaf->right);
        std::cout <<leaf->surname << "|" << leaf->ticket_code << "|" << leaf->luggage_weight << std::endl;
    }
}

void BinaryTree::print() {
    print(root, 0);
}

void BinaryTree::preorder_print() {
    preorder_print(root);
}

void BinaryTree::postorder_print() {
    postorder_print(root);
}

void BinaryTree::delete_tree() {
    delete_leaf(root);
    root = nullptr;
    count = 0;
}

double calc_avarage(Node* leaf, Field field)
{
    static int count = 0;
    static double sum = 0;
    if(leaf != nullptr) {
        count++;
        calc_avarage(leaf->right, field);
        switch (field) {
            case Field::WEIGHT:
                sum += leaf->luggage_weight;
                break;
            case Field::CODE:
                sum += leaf->ticket_code;
                break;
            default:
                break;
        }
        calc_avarage(leaf->left, field);
    }
    return sum;
}

void BinaryTree::get_avarage() {
    std::cout << "1 - average of luggage weight field, 2 - average of ticket code field:";
    int field;
    std::cin >> field;
    double sum;
    switch(field)
    {
        case 1:
            sum = calc_avarage(root,Field::WEIGHT);
            break;
        case 2:
            sum = calc_avarage(root, Field::CODE);
            break;
        default:
            break;
    }
    double avrg = sum / count;
    std::cout << avrg <<std::endl;
}

void BinaryTree::inorder_print(Node *leaf) {
    if(leaf != nullptr)
    {
        inorder_print(leaf->left);
        std::cout <<leaf->surname << "|" << leaf->ticket_code << "|" << leaf->luggage_weight << std::endl;
        inorder_print(leaf->right);
    }
}

void BinaryTree::inorder_print() {
    inorder_print(root);
}

void BinaryTree::delete_left_subtree() {
    delete_left_subtree(root);
    root->left = nullptr;
}

void BinaryTree::delete_left_subtree(Node *leaf) {
    if(leaf != nullptr)
    {
        delete_left_subtree(leaf->left);
        delete_left_subtree(leaf->right);
        if(leaf == root)
            return;
        delete leaf;
    }
}

void BinaryTree::delete_right_subtree(Node *leaf) {
    if(leaf != nullptr)
    {
        delete_left_subtree(leaf->right);
        delete_left_subtree(leaf->left);
        if(leaf == root)
            return;
        delete leaf;
    }
}

void BinaryTree::delete_right_subtree() {
    delete_right_subtree(root);
    root->right = nullptr;
}

BinaryTree::BinaryTree(BinaryTree &&other) noexcept {
    root = other.root;
    other.root = nullptr;
    count = other.count;
    other.count = 0;
}

BinaryTree &BinaryTree::operator=(BinaryTree &&other) {
    if(root)
    {
        delete_tree();
    }
    root = other.root;
    other.root = nullptr;
    count = other.count;
    other.count = 0;
    return *this;
}

void BinaryTree::move_tree(BinaryTree &other) {
    if(root)
    {
        if(count > 1)
        {
            Node* array = new Node[count];
            move_leaf(root, array);
            for (int i = 0; i < count; ++i) {
                other.insert(std::move(array[i]), [](Node& lhs, Node& rhs){return lhs.ticket_code<rhs.ticket_code;});
            }
            delete_tree();
        }
        else
        {
            other.root = root;
        }
        other.count=count;
        root = nullptr;
        count = 0;
    }
}

Node* BinaryTree::move_leaf(Node *origin, Node *array) {
    if(origin != nullptr)
    {
        array->surname = origin->surname;
        array->ticket_code = origin->ticket_code;
        array->luggage_weight = origin->luggage_weight;
        array++;
        array = move_leaf(origin->left, array);
        array = move_leaf(origin->right, array);
    }
    return array;
}

bool BinaryTree::insert(Node &&new_node, bool (*comp)(Node &, Node&)) {
    if(!root)
    {
        root = new Node{new_node};
    }
    else
    {
        Node* curr = root;
        while(curr)
        {
            if(comp(new_node,*curr))
            {
                if(curr->left == nullptr)
                {
                    curr->left = new Node{new_node};
                    break;
                }
                else
                {
                    curr = curr->left;
                }
            }
            else
            {
                if(curr->right == nullptr)
                {
                    curr->right = new Node{new_node};
                    break;
                }
                else
                {
                    curr = curr->right;
                }
            }
        }
    }
    ++count;
    return false;
}

