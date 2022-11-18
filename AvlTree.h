
#ifndef DAST_EX1_AVLTREE_H
#define DAST_EX1_AVLTREE_H
#include BinaryTree.h

template<typename T>
class AvlTree() : public BinaryTree<T>{
public :


	int height();

	// rotations
	void RR_rotate(AvlTree<T>*);
	void RL_rotate(AvlTree<T>*);
	void LR_rotate(AvlTree<T>*);
	void LL_rotate(AvlTree<T>*);

}

#endif //DAST_EX1_AVLTREE_H
