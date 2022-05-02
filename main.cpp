#include <iostream>
#include <array>
#include <algorithm>
#include "BinaryTree.h"

int main() {
    BinaryTree bt;
    std::string arg;
    arg = "a";
    bt.insert({"Denis", 12, 20.4});
    bt.insert({"Alexey", 15, 20.4});
    bt.insert({"Sergey", 17, 20.4});
    bt.insert({"Mascha", 18, 20.4});
    bt.insert({"Valya", 13, 20.4});
    bt.insert({"Jhon", 22, 20.4});
    bt.insert({"Harry", 14, 20.4});
    //bt.insert({"a", 12, 20.4});
    //bt.insert({"g", 12, 20.4});
    arg = "d";
    bt.print();
    bt.preorder_print();
    std::cout << "-----" << std::endl;
    bt.postorder_print();
    std::cout << "-----" << std::endl;
    bt.inorder_print();
    //bt.get_avarage();
/*    std::array<std::string, 7> arr{"a", "b", "c","d","e", "f","g"};
    std::sort(arr.begin(), arr.end());*/
    return 0;
}
