#ifndef DAST_EX1_BINARYTREE_H
#define DAST_EX1_BINARYTREE_H
#define BAD_BF 4
#include <assert.h>
#include <exception>
#include <memory>

int max(int a, int b){
    if (a>b) return a;
    else return b;
}

template <typename K, typename V>
class Node {
public:
    K key;
    V value;
    int height;
    Node<K,V> * parent;
    Node<K,V> * left;
    Node<K,V> * right;
    Node(const K& key, const V& value, int height=1, Node* parent= nullptr,Node* left= nullptr, Node* right= nullptr):
    key(key), value(value),height(height),parent(parent),left(left), right(right) {};
    Node() = delete;
    int BF();
    bool operator==(const Node& node);
    bool operator>(const Node& node);
    void print();
};


template <typename K,typename V>
class AVLTree {
public:
    Node<K, V> * root;
    AVLTree() : root(nullptr){};
    ~AVLTree(){ delete root;};
    Node<K, V>* search(const K & target_key, bool return_parent= false);
    virtual Node<K,V>* add(const K& key, const V& value );
    virtual Node<K,V>* remove(const K& key);
    void replace( Node<K, V> *target, Node<K, V> *replace_by, bool remove = true);
    void rotate(Node<V,K>* dest);
    void RR_rotate(Node<V,K>* dest);
    void LL_rotate(Node<V,K>* dest);
    void RL_rotate(Node<V,K>* dest);
    void LR_rotate(Node<V,K>* dest);
    Node<K,V>* min(Node<K,V>* start);
    int height() { return get_height(root);};
    class NodeAlreadyExists:public std::exception{};
    class NodeDoesntExists:public std::exception{};

//	bool friend operator>(const Node<K, V> & first, const Node<K, V> & second);
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
    Node<K,V> * temp = root;
    while(true) {
        if (temp->key == target_key) { return temp; }
        if (temp->key < target_key) {
            if (temp->right == nullptr) {
                if (return_parent) {return temp;}
                return nullptr;
            }
            else{
                temp=temp->right;
                continue;
            }

        } else {
            if (temp->left == nullptr) {
                if (return_parent) {return temp;}
                return nullptr;
            }
            else{
                temp=temp->left;
                continue;
            }
        }
    }
}

template <typename K,typename V>
// todo Alon - dont we want here v* value instead of const V& value ?
Node<K,V>*  AVLTree<K,V>::add(const K& key, const V& value ) {
    Node<K, V> *search_result = search(key, true);

    // key doesn't exist - set the Node to the root of the tree
    if (search_result == nullptr) {
        Node<K, V> *new_node = new Node<K, V>(key, value);//std::shared_ptr<Node<K, V>>(new Node<K, V>(key, value));
        this->root = new_node;
        return new_node;
    } else {
        // key exists
        if (search_result->key == key) {
            throw AVLTree<K,V>::NodeAlreadyExists();
        }
        // insert as is regular Binary tree
        Node<K, V> *new_node = new Node<K, V>(key, value);//std::shared_ptr<Node<K, V>>(new Node<K, V>(key, value), value);
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
            if (get_height(p) >= get_height(temp_node)+1){
                return new_node;
            } else {
                // check if rotation needed
                p->height = get_height(temp_node) + 1;
                int bf = p->BF();
                if (bf*bf == BAD_BF) {
                    rotate(p);
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
void AVLTree<K,V>::rotate(Node<V,K>* dest){
    int balance = dest->BF();
    if (balance > 1 && dest->left->BF()>=0)
        return LL_rotate(dest);
    if (balance > 1 && dest->left->BF()==-1)
        return LR_rotate(dest);
    if (balance <-1 && dest->right->BF()<=0)
        return RR_rotate(dest);
    if (balance <-1 && dest->right->BF()==1)
        return RL_rotate(dest);


};

template <typename K,typename V>
Node<K,V>* AVLTree<K,V>::min( Node<K,V>* start) {
    while (start->left != nullptr){
        start = start->left;
    }
    return start;
}

template <typename K,typename V>
Node<K,V>* AVLTree<K,V>::remove(const K& key){
    Node<K, V> *target = search(key);
    Node<K, V> * temp;
    if (target == nullptr){
        throw AVLTree<K,V>::NodeDoesntExists();
    }
    // there is a node, lets delete it
    Node<K,V>* p = target->parent;
//    if (p == nullptr) {
//        root= nullptr;
//        //todo check deletion
//    }
    // if node is leaf
    if (target->left == nullptr && target->right == nullptr) {
        replace(target, nullptr);
        delete target;
    }
    // Not root not leaf
    else if (target->left == nullptr) {
        temp = target->right;
        replace(target, target->right);
        //todo check deletion
    } else if (target->right == nullptr) {
        temp = target->right;
        replace(target, target->left);
        //todo check deletion
    } else {
        Node<K, V> *temp = AVLTree<K,V>::min(target->right);
        replace(target, temp);
        }
    //AVL_balancing
    if (temp== nullptr){return temp;}
    temp->height=1+max(get_height(temp->left),get_height(temp->right));
    while(temp != root) {
        Node<K, V>* p = temp->parent;
        // if the tree is AVL balanced
        if (get_height(p) >= get_height(temp)){
            return temp;
        } else {
            // check if rotation needed
            p->height = get_height(temp) + 1;
            int bf = p->BF();
            if (bf*bf == BAD_BF) {
                rotate(p);
                return temp;
            }
            temp = temp->parent;
        }
    }
    return nullptr;
}

template<typename K, typename  V>
void AVLTree<K,V>::replace(Node<K, V> *target, Node<K, V> *replace_by, bool remove) {
    Node<K, V> * by_parent= nullptr;
    Node<K, V> * by_right= nullptr;
    Node<K, V> * by_left= nullptr;
    if (replace_by!= nullptr){
        by_parent=replace_by->parent;
        by_left=replace_by->left;
        by_right=replace_by->right;
    }
    Node<K, V> * target_p= target->parent;
    Node<K, V> * target_right=target->right;
    Node<K, V> * target_left=target->left;

    if (target_right!= nullptr) target_right->parent=replace_by;
    if (target_left!= nullptr) target_left->parent=replace_by;
    if (target_p!= nullptr) {
        if(target_p->left==target){
            target_p->left= replace_by;
        }
        else target_p->right= replace_by;
    }
    else{
        root=replace_by;
        replace_by->parent= nullptr;
    }
    replace_by->right=target_right;
    replace_by->left=target_left;
    if (by_parent!= nullptr&&remove){
        if (by_parent->left==replace_by){
            by_parent->left= nullptr;
        }
        else {by_parent->right= nullptr;}
    }
    if (replace_by!= nullptr&&(!remove)){
        replace_by->right= target_right;
        replace_by->left=target_left;
        if (by_parent!= nullptr) {
            if(by_parent->left==replace_by){
                by_parent->left= target;
            }
            else by_parent->right= target;
        }
        else{root=target;}
    }



};

template <typename K,typename V>
void AVLTree<K,V>::LL_rotate(Node<V,K>* dest){
    //todo: validate
    Node<K,V> *x = dest->left;
    Node<K,V> *T2 = x->right;

    // Perform rotation
    x->right = dest;
    dest->left = T2;
    if (dest==root){
        root=x;
        root->parent= nullptr;
    }

    // Update heights
    dest->height = max(get_height(dest->left),
                    get_height(dest->right)) + 1;
    x->height = max(get_height(x->left),
                    get_height(x->right)) + 1;

//    // Return new root
//    return x;
};
template <typename K,typename V>
void AVLTree<K,V>::RR_rotate(Node<V,K>* dest){
    Node<K,V> *y = dest->right;
    Node<K,V> *T2 = y->left;

    // Perform rotation
    y->left = dest;
    dest->right = T2;
    if (dest==root){
        root=y;
        root->parent= nullptr;
    }

    // Update heights
    dest->height = max(get_height(dest->left),
                    get_height(dest->right)) + 1;
    y->height = max(get_height(y->left),
                    get_height(y->right)) + 1;

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



/**
 ----------------------------- Node methods ----------------------------
 */


template <typename K,typename V>
int get_height(Node<V,K>* target){
    if (target== nullptr) return 0;
    else return target->height;
}
//template <typename K,typename V>
//int getBalance( Node<K,V>* target){
//    if (target== nullptr) return 0;
//    else return target->BF();
//}

template <typename K,typename V>
int Node<K,V>::BF() {
    return (get_height(this->left) - get_height(this->right));
}
//
//
//template <typename K,typename V>
//bool Node<K,V>::operator==(const Node<K,V>& node) {
//    return node.key==this->key;
//};
//template <typename K,typename V>
//bool Node<K,V>::operator>(const Node<K,V>& node) {
//    return node.key>this->key;
//};
#endif //DAST_EX1_BINARYTREE_H
