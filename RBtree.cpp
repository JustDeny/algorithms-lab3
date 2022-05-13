//
// Created by denny on 04.05.2022.
//

#include "RBtree.h"

bool RBtree::insert(RBNode &&node) {
    // Ordinary Binary Search Insertion
    NodePtr new_node = new RBNode{node};
    new_node->parent = nullptr;
    new_node->left = TNULL;
    new_node->right = TNULL;
    new_node->color = Color::RED; // new node must be red

    NodePtr y = nullptr;
    NodePtr x = this->root;

    while (x != TNULL) {
        y = x;
        if (*new_node < *x) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    // y is parent of x
    new_node->parent = y;
    if (y == nullptr) {
        root = new_node;
    } else if (*new_node < *y) {
        y->left = new_node;
    } else {
        y->right = new_node;
    }

    // if new node is a root node, simply return
    if (new_node->parent == nullptr){
        new_node->color = Color::BLACK;
        return true;
    }

    // if the grandparent is null, simply return
    if (new_node->parent->parent == nullptr) {
        return true;
    }

    // Fix the tree
    fix_insert(new_node);
    return true;
}

RBtree::RBtree(): root{nullptr}, count{0}
{
    TNULL = new RBNode;
    TNULL->color = Color::BLACK;
    TNULL->left= nullptr;
    TNULL->right = nullptr;
    root = TNULL;
}

void RBtree::print() {
    print(root,0);
}

void RBtree::print(RBNode *leaf, int space) {
    if(leaf != TNULL)
    {
        space += 10;
        print(leaf->right,space);
        std::cout << std::endl;
        for (int i = 10; i < space; ++i) {
            std::cout << " ";
        }
        std::string color = leaf->color == Color::RED?"RED":"BLACK";
        std::cout <<leaf->surname << "|" << leaf->ticket_code << "|" << leaf->luggage_weight << "|" <<color <<std::endl;
        print(leaf->left,space);
    }
}

void RBtree::fix_insert(RBNode *k) {
    NodePtr u;
    while (k->parent->color == Color::RED) {
        if (k->parent == k->parent->parent->right) {
            u = k->parent->parent->left; // uncle
            if (u->color == Color::RED) {
                // case 3.1
                u->color = Color::BLACK;
                k->parent->color = Color::BLACK;
                k->parent->parent->color = Color::RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->left) {
                    // case 3.2.2
                    k = k->parent;
                    right_rotate(k);
                }
                // case 3.2.1
                k->parent->color = Color::BLACK;
                k->parent->parent->color = Color::RED;
                left_rotate(k->parent->parent);
            }
        } else {
            u = k->parent->parent->right; // uncle

            if (u->color == Color::RED) {
                // mirror case 3.1
                u->color = Color::BLACK;
                k->parent->color = Color::BLACK;
                k->parent->parent->color = Color::RED;
                k = k->parent->parent;
            } else {
                if (k == k->parent->right) {
                    // mirror case 3.2.2
                    k = k->parent;
                    left_rotate(k);
                }
                // mirror case 3.2.1
                k->parent->color = Color::BLACK;
                k->parent->parent->color =Color::RED;
                right_rotate(k->parent->parent);
            }
        }
        if (k == root) {
            break;
        }
    }
    root->color = Color::BLACK;
}

void RBtree::left_rotate(RBNode* x) {
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RBtree::right_rotate(RBNode *x) {
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        this->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

bool RBtree::remove(std::string &key) {
// find the node containing key
    NodePtr parent;
    NodePtr node = find_with_parent(key,parent);
    NodePtr z = TNULL;
    NodePtr x, y;
    while (node != TNULL){
        if (node->surname == key) {
            z = node;
        }

        if (node->surname <= key) {
            node = node->right;
        } else {
            node = node->left;
        }
    }

    if (z == TNULL) {
        std::cout<<"Couldn't find key in the tree"<<std::endl;
        return false;
    }

    y = z;
    Color y_original_color = y->color;
    if (z->left == TNULL) {
        x = z->right;
        rb_transplant(z, z->right);
    } else if (z->right == TNULL) {
        x = z->left;
        rb_transplant(z, z->left);
    } else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            rb_transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rb_transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (y_original_color == Color::BLACK){
        fix_removal(x);
    }
}


RBNode *RBtree::search(std::string &value) {
    return nullptr;
}

void RBtree::fix_removal(RBNode *x) {
    RBNode* s;
    while (x != root && x->color == Color::BLACK) {
        if (x == x->parent->left) {
            s = x->parent->right;
            if (s->color == Color::RED) {
                // case 3.1
                s->color = Color::BLACK;
                x->parent->color = Color::RED;
                left_rotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == Color::BLACK && s->right->color == Color::BLACK) {
                // case 3.2
                s->color = Color::RED;
                x = x->parent;
            } else {
                if (s->right->color == Color::BLACK) {
                    // case 3.3
                    s->left->color = Color::BLACK;
                    s->color = Color::RED;
                    right_rotate(s);
                    s = x->parent->right;
                }

                // case 3.4
                s->color = x->parent->color;
                x->parent->color = Color::BLACK;
                s->right->color = Color::BLACK;
                left_rotate(x->parent);
                x = root;
            }
        } else {
            s = x->parent->left;
            if (s->color == Color::RED) {
                // case 3.1
                s->color = Color::BLACK;
                x->parent->color = Color::RED;
                right_rotate(x->parent);
                s = x->parent->left;
            }

            if (s->left->color == Color::BLACK && s->right->color == Color::BLACK) {
                // case 3.2
                s->color = Color::RED;
                x = x->parent;
            } else {
                if (s->left->color == Color::BLACK) {
                    // case 3.3
                    s->right->color = Color::BLACK;
                    s->color = Color::RED;
                    left_rotate(s);
                    s = x->parent->left;
                }

                // case 3.4
                s->color = x->parent->color;
                x->parent->color = Color::BLACK;
                s->left->color = Color::BLACK;
                right_rotate(x->parent);
                x = root;
            }
        }
    }
    x->color = Color::BLACK;
}

void RBtree::rb_transplant(RBNode *u, RBNode *v) {
    if(u->parent== nullptr)
    {
        root = v;
    }
    else if(u == u->parent->left)
    {
        u->parent->left=v;
    }
    else
    {
        u->parent->right=v;
    }
        v->parent = u->parent;
}

RBNode *RBtree::find_with_parent(std::string &value, RBNode *&parent) {
    if(root->surname == value)
    {
        return root;
    }
    RBNode* current = root;
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

RBtree::NodePtr RBtree::minimum(RBtree::NodePtr node) {
    while (node->left != TNULL) {
        node = node->left;
    }
    return node;
}

RBtree::~RBtree() {
    delete_leaf(root);
    root = TNULL;
    count = 0;
}

void RBtree::delete_leaf(RBNode *leaf) {
    if(leaf != TNULL)
    {
        delete_leaf(leaf->right);
        delete_leaf(leaf->left);
        delete leaf;
    }
}
