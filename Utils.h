#ifndef DAST_EX1_UTILS_H
#define DAST_EX1_UTILS_H
#include "AVLTree.h"

class Utils {
public:

    template <typename K,typename V>
    void printNode(Node<K, V>* node, int indent=0);

    template <typename K,typename V>
    void printTree(AVLTree<K, V>* tree);
};



#endif //DAST_EX1_UTILS_H
