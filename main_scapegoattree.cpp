#include <iostream>

#include "ScapegoatTree.h"


int main() {

    ScapegoatTree<int> tree;

    tree.printPretty();    
    tree.insert(10);
    tree.insert(15);
    tree.insert(20);
    tree.insert(25);
    tree.insert(30);
    std::cout <<  tree.getNext(10);
    // tree.insert(33);
    // tree.insert(12);
    // tree.insert(33);
    // tree.insert(58);
    // tree.balance();
    tree.printPretty();


    return 0;
}
