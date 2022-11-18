
#ifndef DAST_EX1_AVLTREE_H
#define DAST_EX1_AVLTREE_H
#include "BinaryTree.h"

template<typename V,typename T>
class AvlTree : public BinaryTree<V,T> {
public :
    int bf(){
        return (this->root->left.height) - (this->root->right.height);
    };
	// rotations
    void add(const T& key, const V& value ) override {
    };
    void remove(const T& key) override {

    };
    void RR_rotate(Node<V,T>* dest) {

    };
    void LL_rotate(Node<V,T>* dest);
    void RL_rotate(Node<V,T>* dest){
        LL_rotate(dest);
        RR_rotate(dest);
    };
    void LR_rotate(Node<V,T>* dest){
        RR_rotate(dest);
        LL_rotate(dest);
    };


};

#endif //DAST_EX1_AVLTREE_H

