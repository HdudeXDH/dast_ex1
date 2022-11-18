#ifndef DAST_EX1_BINARYTREE_H
#define DAST_EX1_BINARYTREE_H
#define RETURN_PARENT=true
#include <assert.h>
#include <exception>

template <typename K, typename V>
class Node {
public:
    K key;
    V value;
    int height;
    Node<K, V>* parent,left, right;
    Node() = 0;
    Node(const K& key, const V& value, int height=0, Node<K, V>* parent= nullptr,Node<K, V>* left= nullptr,Node<K
         , V>* right= nullptr):  key(key), value(value),height(height),parent(parent), right(right), left(left){};


    /**
     * aids
     */
     bool operator==(const Node& node);
};


template <typename K,typename V>
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

/**
 *
 */


/**
 ----------------- Node implementations ----------------------------
 */
template <typename K,typename V>
bool Node<K,V>::operator==(const Node<K,V>& node) {
    return node.key==this->key;
};

/**
 ----------------- BinaryTree implementations ----------------------------
 */
template <typename K,typename V>
Node<K, V>* BinaryTree<K, V>::search(const K & target_key, bool return_parent) {
    if (root== nullptr) return nullptr;
    if (root->key==target_key){ return this; }
    if (root->key<target_key) {
        if (root->right== nullptr)
            if (return_parent){
                return root;
            }
        return nullptr;}
    else{
        if (root->left== nullptr)
            if (return_parent){
                return root;
            }
        return nullptr;
    }

};

template <typename K,typename V>
Node<K,V>*  BinaryTree<K,V>::add(const K& key, const V& value ) {
    Node<K, V> *search_result = search(key, true);
    if (search_result->key == key) {
        throw BinaryTree<K,V>::NodeAlreadyExists();
    }
    if (search_result == nullptr) {
        Node<K, V> *new_node = shared_ptr<Node<K, V>>(new Node<K, V>(key, value), value);
        this->root = new_node;
        return new_node;
    } else {
        Node<K, V> *new_node = shared_ptr<Node<K, V>>(new Node<K, V>(key, value), value);
        new_node->
                parent = search_result;
        if (search_result > new_node) { // todo Noam implement > operator
            search_result->left = new_node;
        } else {
            search_result->right = new_node;
        }
    }
}

template <typename K,typename V>
Node<K,V>* BinaryTree<K,V>::remove(const K& key){
    Node<K, V> *search_result = search(key);
    if (search_result== nullptr){throw BinaryTree<K,V>::NodeDoesntExists();}
};


//template< typename K, typename V>
//Node<T,V>::Node(const T& key, const V& value, int height, Node<T, V>* parent ,Node<T, V>* left ,Node<T
//        , V>* right):  key(key), value(value),height(height),parent(parent), right(right), left(left){};

//template<typename K, typename V>
//bool operator>(const Node<T, V> & first, const Node<T, V> & second) {
//	return first.key > second.key;
//}


#endif //DAST_EX1_BINARYTREE_H
