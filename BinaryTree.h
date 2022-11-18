#ifndef DAST_EX1_BINARYTREE_H
#define DAST_EX1_BINARYTREE_H

template <typename T, typename V>
class Node {
public:
    Node(const T& key, const V& value, Node<T, V>* parent= nullptr, int height=0):
    key(key), value(value),parent(parent),height(height)
     {
       left= nullptr;
       right= nullptr;
    }
    int key;
    V value;
	Node<T, V>* parent,left, right;
    int height;
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
    int height(){
        return root->height;
    };
    int bf(){
        return root->left.height-root->right.height;
    };

	void virtual add(const T& key, const V& value )= 0;
	void virtual remove(const T& key) = 0;
	bool friend operator>(const Node<T, V> & first, const Node<T, V> & second);

};
template<typename T, typename V>
bool operator>(const Node<T, V> & first, const Node<T, V> & second) {
	return first.key > second.key;
}


#endif //DAST_EX1_BINARYTREE_H
