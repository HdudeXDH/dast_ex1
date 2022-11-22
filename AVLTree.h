#ifndef DAST_EX1_BINARYTREE_H
#define DAST_EX1_BINARYTREE_H
#define BAD_BF 4
#define RETURN_PARENT=true
#include <assert.h>
#include <exception>

template <typename K, typename V>
class Node {
public:
    K key;
    V value;
    int height;
    Node<K, V>* parent,left, right; //, nextup, nextdown;
    int BF();
    Node() = delete;
    Node(const K& key, const V& value, int height=0, Node<K, V>* parent= nullptr,Node<K, V>* left= nullptr,
         Node<K, V>* right= nullptr): //,Node<K, V>* nextup= nullptr,Node<K, V>* nextdown=nullptr
         key(key), value(value),height(height),parent(parent), right(right), left(left) { //, nextup(nextup),nextdown(nextdown)
    };


     bool operator==(const Node& node);
     bool operator>(const Node& node);
};


template <typename K,typename V>
class AVLTree {
public:
    Node<K, V> * root;

    AVLTree();
    ~AVLTree();
    int height() { return root->height;};
    Node<K, V>* search(const K & target_key, bool return_parent= false);
    virtual Node<K,V>* add(const K& key, const V& value );
    virtual Node<K,V>* remove(const K& key);
    class NodeAlreadyExists:public std::exception{};
    class NodeDoesntExists:public std::exception{};
    void rotate(Node<V,K>* dest);
    void RR_rotate(Node<V,K>* dest);
    void LL_rotate(Node<V,K>* dest);
    void RL_rotate(Node<V,K>* dest);
    void LR_rotate(Node<V,K>* dest);

//	bool friend operator>(const Node<K, V> & first, const Node<K, V> & second);

    void replace( Node<K, V> *target, Node<K, V> *replace_by);
};

/**
 *
 */

/**
 ----------------- AVL implementations ----------------------------
 */
template <typename K,typename V>
Node<K, V>* AVLTree<K, V>::search(const K & target_key, bool return_parent) {
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
Node<K,V>*  AVLTree<K,V>::add(const K& key, const V& value ) {
    Node<K, V> *search_result = search(key, true);
    // key exists
    if (search_result->key == key) {
        throw AVLTree<K,V>::NodeAlreadyExists();
    }
    // key doesn't exist - set the Node to the root of the tree
    if (search_result == nullptr) {
        Node<K, V> *new_node = shared_ptr<Node<K, V>>(new Node<K, V>(key, value), value);
        this->root = new_node;
        return new_node;
    } else {
        // insert as is regular Binary tree
        Node<K, V> *new_node = shared_ptr<Node<K, V>>(new Node<K, V>(key, value), value);
        new_node->parent = search_result;
        if (search_result > new_node) {
            search_result->left = new_node;
        } else {
            search_result->right = new_node;
        }
        // AvlTree stuff
        Node<K, V>* temp_node = new_node;
        while(temp_node != root) {
            Node<K, V>* p = temp_node->parent;
            // if the tree is AVL balanced
            if (p->height >= temp_node->height){
                return new_node;
            } else {
                // check if rotation needed
                p->height = temp_node->height + 1;
                int bf = p->BF();
                if (bf*bf == BAD_BF) {
                    rotate(temp_node);
                    return new_node;
                }
                temp_node = temp_node->parent;
            }
        }
        // in case the new node is the root
        return new_node;
    }
}

template <typename K,typename V>
Node<K,V>* AVLTree<K,V>::remove(const K& key){
    Node<K, V> *target = search(key);
    if (target == nullptr){
        throw AVLTree<K,V>::NodeDoesntExists();
    }
    // there is a node, lets delete it
    Node<K,V>* p = target->parent;
    if (p == nullptr) {
        // todo delete root
    }
    // if node is leaf
//    if (target->left == nullptr && target->right == nullptr) {
//        replace(target, nullptr);
//        delete target;
//    }
    // Not root not leaf
    else if (target->left == nullptr) {
        replace(target, target->right);
    } else if (target->right == nullptr) {
        replace(target, target->left);
    } else {
            // target has 2 sons
        }
}

template<typename K, typename  V>
void AVLTree<K,V>::replace(Node<K, V> *target, Node<K, V> *replace_by) {
    Node<K, V> * p = target->parent;
    if (target == target->parent->right) {
        p->right = nullptr;
    } else {
        p->left = nullptr;
    }
};

template <typename K,typename V>
void AVLTree<K,V>::RL_rotate(Node<V,K>* dest){
    LL_rotate(dest);
    RR_rotate(dest->parent);
};

template <typename K,typename V>
void AVLTree<K,V>::LR_rotate(Node<V,K>* dest){
    RR_rotate(dest);
    LL_rotate(dest->parent);
};
//template< typename K, typename V>
//Node<T,V>::Node(const T& key, const V& value, int height, Node<T, V>* parent ,Node<T, V>* left ,Node<T
//        , V>* right):  key(key), value(value),height(height),parent(parent), right(right), left(left){};

//template<typename K, typename V>
//bool operator>(const Node<T, V> & first, const Node<T, V> & second) {
//	return first.key > second.key;
//}


/**
 ----------------------------- Node methods ----------------------------
 */

template <typename K,typename V>
int Node<K,V>::BF() {
    return (this->left.height - this->right.hight);
}


template <typename K,typename V>
bool Node<K,V>::operator==(const Node<K,V>& node) {
    return node.key==this->key;
};
template <typename K,typename V>
bool Node<K,V>::operator>(const Node<K,V>& node) {
    return node.key>this->key;
};
#endif //DAST_EX1_BINARYTREE_H
