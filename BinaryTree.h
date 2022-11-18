#ifndef DAST_EX1_BINARYTREE_H
#define DAST_EX1_BINARYTREE_H

template <typename T, typename V>
class Node {
public:
    T key;
    V value;
    int height;
    Node<T, V>* parent,left, right;
    Node(const T& key, const V& value, int height=0, Node<T, V>* parent= nullptr,Node<T, V>* left= nullptr,Node<T
         , V>* right= nullptr):  key(key), value(value),height(height),parent(parent), right(right), left(left){};
};


template <typename T,typename V>
class BinaryTree {
//protected:
public:
    Node<T, V> * root;

    BinaryTree();
    ~BinaryTree();
    Node<T, V>& search(const T & target_key) {
        if (root== nullptr) return nullptr;
        if (root->key==target_key){ return this; }
        if (root->key<target_key) {
            if (root->right== nullptr) return nullptr;}
    };
    int height() { return root->height;};

	void virtual add(const T& key, const V& value )= 0;
	void virtual remove(const T& key) = 0;
//	bool friend operator>(const Node<T, V> & first, const Node<T, V> & second);

};

//template<typename T, typename V>
//bool operator>(const Node<T, V> & first, const Node<T, V> & second) {
//	return first.key > second.key;
//}


#endif //DAST_EX1_BINARYTREE_H
