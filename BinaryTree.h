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


    /**
     * aids
     */
     bool operator==(const Node& node);
};


template <typename T,typename V>
class BinaryTree {
//protected:
public:
    Node<K, V> * root;

    BinaryTree();
    ~BinaryTree();
    Node<K, V>* search(const K & target_key, bool return_parent= false);
    int height() { return root->height;};

    virtual Node<K,V>*  add(const K& key, const V& value );
    virtual Node<K,V>* remove(const K& key);
    class NodeAlreadyExists:public std::exception{};
    class NodeDoesntExists:public std::exception{};
//	bool friend operator>(const Node<K, V> & first, const Node<K, V> & second);

};

//template<typename T, typename V>
//bool operator>(const Node<T, V> & first, const Node<T, V> & second) {
//	return first.key > second.key;
//}


#endif //DAST_EX1_BINARYTREE_H
