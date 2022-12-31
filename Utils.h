#ifndef DAST_EX1_UTILS_H
#define DAST_EX1_UTILS_H
#include "AVLTree.h"
#include <sstream>
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
//std::string toString(int a){
//    return std::to_string(a);
//}
//template <typename T>
//std::string toString( const T& value )
//{
//    std::ostringstream ss;
//    ss << value;
//    return ss.str();
//}
//
template <typename K,typename V>
void printBT(const std::string& prefix, const std::shared_ptr<Node<K,V>> node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );
//        std::cout << (isLeft ? "+++" : "---" );

        // print the value of the node
        std::string parentkey = "None";
        std::stringstream ss;
        if (node->parent!= nullptr){
            ss<<node->parent->key;
            parentkey = ss.str();
        }
        std::string leftkey = "None";
        std::stringstream ss1;
        if (node->left!= nullptr){
//            leftkey = std::to_string(node->left->key);
            ss1<<node->left->key;
            leftkey = ss1.str();
        }
        std::string rightkey = "None";
        std::stringstream ss2;
        if (node->right!= nullptr){
//            rightkey =  std::to_string(node->right->key);
            ss2<<node->right->key;
            rightkey = ss2.str();
        }
        std::stringstream ss3;
        std::string height = "None";
        height =  std::to_string(node->height);


        std::stringstream ss4;
        std::string mykey = "None";
//        mykey =  std::to_string(node->key);
        ss4<<node->key;
        mykey = ss4.str();

        std::cout <<"(" <<mykey<<",p:"<<parentkey<<",l:"<<leftkey<<",r:"<<rightkey<<",h:"<<height<<")" << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

template <typename K,typename V>
void printBT(const std::shared_ptr<Node<K,V>> node)
{
    printBT("", node, false);
}


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
        std::stringstream ss;
        if (node->parent!= nullptr){
            ss<<node->parent->key;
            parentkey = ss.str();
        }
        std::string leftkey = "None";
        std::stringstream ss1;
        if (node->left!= nullptr){
//            leftkey = std::to_string(node->left->key);
            ss1<<node->left->key;
            leftkey = ss1.str();
        }
        std::string rightkey = "None";
        std::stringstream ss2;
        if (node->right!= nullptr){
//            rightkey =  std::to_string(node->right->key);
            ss2<<node->right->key;
            rightkey = ss2.str();
        }
        std::stringstream ss3;
        std::string height = "None";
        height =  std::to_string(node->height);


        std::stringstream ss4;
        std::string mykey = "None";
//        mykey =  std::to_string(node->key);
        ss4<<node->key;
        mykey = ss4.str();

        std::cout <<"(" <<mykey<<",p:"<<parentkey<<",l:"<<leftkey<<",r:"<<rightkey<<",h:"<<height<<")" << std::endl;

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
