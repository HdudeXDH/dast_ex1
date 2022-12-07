#ifndef DAST_EX1_UTILS_H
#define DAST_EX1_UTILS_H
#include "AVLTree.h"

//class Utils {
//public:
//
//    template <typename K,typename V>
//    void printNode(Node<K, V>* node, int indent=0);
//
//    template <typename K,typename V>
//    void printTree(AVLTree<K, V>* tree);
//};

//
template <typename K,typename V>
void printBT(const std::string& prefix, const Node<K,V> * node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );
//        std::cout << (isLeft ? "+++" : "---" );

        // print the value of the node
        std::string parentkey = "None";
        if (node->parent!= nullptr){
            parentkey = std::to_string(node->parent->key);
        }
        std::string leftkey = "None";
        if (node->left!= nullptr){
            leftkey = std::to_string(node->left->key);
        }
        std::string rightkey = "None";
        if (node->right!= nullptr){
            rightkey = std::to_string(node->right->key);
        }
        std::string height = "None";
        height = std::to_string(node->height);

        std::cout <<"(" <<node->key<<",p:"<<parentkey<<",l:"<<leftkey<<",r:"<<rightkey<<",h:"<<height<<")" << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

template <typename K,typename V>
void printBT(const Node<K,V> * node)
{
    printBT("", node, false);
}

//int max(int a, int b){
//    if (a>b) return a;
//    else return b;
//}

#endif //DAST_EX1_UTILS_H
