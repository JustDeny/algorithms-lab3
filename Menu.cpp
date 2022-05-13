//
// Created by denny on 13.05.2022.
//

#include "Menu.h"

void Menu::run() {
    while(true)
    {
        std::cout << "1 - manage binary tree, 2 - manage rb tree" << std::endl;
        int type_tree;
        std::cin >> type_tree;
        switch(type_tree)
        {
            case 1:
                manage_btree();
                break;
            case 2:
                manage_rbtree();
                break;
            default:
                break;
        }
    }
}

void Menu::manage_btree() {
    std::cout << "1 - to initialize tree" << std::endl;
    std::cout << "2 - to calculate average" << std::endl;
    std::cout << "3 - to print tree" << std::endl;
    std::cout << "4 - to delete subtree" << std::endl;
    std::cout << "5 - to move nodes into another tree" << std::endl;
    std::cout << "6 - to write to file" << std::endl;
    int option;
    std::cin >> option;
    switch (option){
        case 1:
            std::cout << "1 - manual, 2 - from file: " << std::endl;
            std::cin >> option;
            std::cin.ignore(1);
            switch (option) {
                case 1:
                    while(true)
                    {
                        std::cout << "Surname: ";
                        std::string name;
                        getline(std::cin, name);
                        std::cout << "Ticket code: ";
                        int ticket;
                        std::cin >> ticket;
                        std::cout << "Weight of luggage: ";
                        double luggage;
                        std::cin>>luggage;
                        btree.insert({name, ticket,luggage});
                        std::cin.ignore(1);
                        std::cout << "Press X to exit or anything else to continue";
                        std::cin.clear();
                        char c = std::cin.get();
                        if(c == 'x')
                            break;
                    }
                    break;
                case 2:
                    break;
            }
            break;
        case 2:

            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
    }
}

void Menu::manage_rbtree() {

}
