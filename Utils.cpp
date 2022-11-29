#include "Utils.h"
#include <iostream>
#define INDENT_SIZE 4
using namespace std;

template <typename K,typename V>
void Utils::printNode(Node<K, V> *node, int indent) {
    int counter = 0;
	for (int i = 0; i <= indent; i++) {
		cout << " "
	}
	if ( node != nullptr) {
		cout << "$$$" << endl
		return;
	}
	cout << node->value << endl;
	printNode(node->left, indent+INDENT_SIZE);
	printNode(node->right, indent+INDENT_SIZE);
}

template <typename K,typename V>
void Utils::printTree(AVLTree<K, V>* tree) {
	Utils::printNode(tree->root);
}