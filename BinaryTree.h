#ifndef DAST_EX1_BINARYTREE_H
#define DAST_EX1_BINARYTREE_H

template <typename T>
class Node<T> {
public:
	T data;
	Node<T>* left;
	Node<T>* right;
	Node<T>* parent;
};


template <typename T>
class BinaryTree<T> {

protected:
	Node<T> root

public:
	BinaryTree();
	~BinaryTree();
	search(const T& object);
	virtual add(const T& object)= 0;
	virtual remove(const T& object) = 0;
	operator>(BinaryTree<T> other)

};
template<typename T>
public operator>(BinaryTree<T> first, BinaryTree<T> second) {
	return first.key > second.key;
}
//
//public operator>(BinaryTree<T> other) {
//
//}

#endif //DAST_EX1_BINARYTREE_H
