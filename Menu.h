//
// Created by denny on 13.05.2022.
//

#ifndef LAB3_MENU_H
#define LAB3_MENU_H
#include "BinaryTree.h"
#include "RBtree.h"

class Menu {
private:
    BinaryTree btree;
    RBtree rbtree;
public:
    Menu() = default;
    void run();
    void manage_btree();
    void manage_rbtree();
};


#endif //LAB3_MENU_H
