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
class Key_Value_block {
public:
	K key ;
	V value ;
	Key_Value_block(const K& key, const V& value): key(key), value(value){};
};

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
	bool has_two_sons();
	bool is_leaf();
    int BF();
    bool operator==(const Node& node);
    bool operator>(const Node& node);
    void print();
};


template <typename K,typename V>
class AVLTree {
public:
	// members
    Node<K, V> * root;
	int size;
	//methods
	AVLTree() : root(nullptr), size(0){};
	~AVLTree(){ delete root;};
	Node<K, V>* search(const K & target_key, bool return_parent= false, Node<K, V> *start_node = nullptr);
	Node<K,V>* add(const K& key, const V& value );
	Node<K,V>* remove_by_key(const K& key, Node<K, V> *start_node= nullptr);
	Node<K,V>* remove_Node(Node<K, V>* to_remove, Node<K, V> *start_node= nullptr);
	void replace( Node<K, V> *target, Node<K, V> *replace_by, bool remove = true);
	void swap_keys_and_values(Node<K, V> *node1, Node<K, V> *node2);
	void remove_leaf(Node<K, V> *leaf_to_remove);
	void remove_link_from_chain(Node<K, V> *node_to_remove);
	void rotate(Node<V,K>* dest);
	void RR_rotate(Node<V,K>* dest);
	void LL_rotate(Node<V,K>* dest);
	void RL_rotate(Node<V,K>* dest);
	void LR_rotate(Node<V,K>* dest);
	Node<K,V>* min(Node<K,V>* start);
	Key_Value_block<K, V>* export_to_array();
	void Recursive_export_to_array(Node<K,V>* root, Key_Value_block<K,V> *array, int *indexPtr);
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
Node<K, V>* AVLTree<K, V>::search(const K & target_key, bool return_parent, Node<K, V> *start_node) {
	if (start_node == nullptr){
		start_node = root;
	}
    if (start_node == nullptr) return nullptr;
    Node<K,V> * temp = start_node;
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
		this->size = this->size + 1;
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
		this->size = this->size + 1;
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
Node<K,V>* AVLTree<K,V>::remove_by_key(const K& key, Node<K, V> *start_node){
	Node<K, V> *target = search(key, false, start_node);
    if (target == nullptr){
        throw AVLTree<K,V>::NodeDoesntExists();
    }
	remove_Node(target, start_node);
	this->size = this->size - 1;
	/**
	 *
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
    } **/
    return nullptr;
}

template <typename K,typename V>
Node<K,V>* AVLTree<K,V>::remove_Node(Node<K, V> *to_remove, Node<K, V> *start_node) {
	Node<K, V> * follower;
	bool has_two_sons = to_remove->has_two_sons();
	// if node is leaf
	if (to_remove->is_leaf()) {
		AVLTree::remove_leaf(to_remove);
	}
	else if (!has_two_sons) {
		AVLTree::remove_link_from_chain(to_remove);
	} else {
		follower = AVLTree<K,V>::min(to_remove->right);
		swap_keys_and_values(to_remove, follower);
		remove_Node(follower, to_remove->right);
	}
}

template<typename K, typename  V>
void AVLTree<K,V>::swap_keys_and_values(Node<K, V> *node1, Node<K, V> *node2) {
	K temp_key = node1->key;
	node1->key = node2->key;
	node2->key = temp_key;

	V temp_value = node1->value;
	node1->value = node2->value;
	node2->value = temp_value;
}

template<typename K, typename  V>
void AVLTree<K,V>::remove_leaf(Node<K, V> *leaf_to_remove){
	assert(leaf_to_remove->right == nullptr && leaf_to_remove->left == nullptr);
	Node<K,V> *parent = leaf_to_remove->parent;
	if (parent->left == leaf_to_remove) {
		parent->left = nullptr;
	} else {
		assert(parent->right == leaf_to_remove);
		parent->right = nullptr;
	}
	delete leaf_to_remove;
}

template<typename K, typename  V>
void AVLTree<K,V>::remove_link_from_chain(Node<K, V> *node_to_remove){
	assert(!(node_to_remove->is_leaf())&& !(node_to_remove->has_two_sons()));
	Node<K,V> *son;
	Node<K,V> *parent = node_to_remove->parent;
	// handle son
	if(node_to_remove->right == nullptr) {
		assert(node_to_remove->left != nullptr);
		son = node_to_remove->left;
	} else {
		assert(node_to_remove->right != nullptr);
		son = node_to_remove->right;
	}
	son->parent = parent;

	// handle parent
	// if node_to_remove is not root
	if (parent != nullptr) {
		if (parent->left == node_to_remove) {
			parent->left = son;
		} else {
			assert(parent->right == node_to_remove);
			parent->right = son;
		}
	} else {
		this->root = son;
	}
	delete node_to_remove;
}

template<typename K, typename  V>
void AVLTree<K,V>::replace(Node<K, V> *target, Node<K, V> *replace_by, bool remove) {
	target->value = replace_by;

}

template<typename K, typename  V>
bool Node<K, V>::has_two_sons() {
	return !((this->right == nullptr) || (this->left == nullptr));
}

template<typename K, typename  V>
bool Node<K, V>::is_leaf() {
	return ((this->right == nullptr) && (this->left == nullptr));
}


//
//template<typename K, typename  V>
//void AVLTree<K,V>::replace(Node<K, V> *target, Node<K, V> *replace_by, bool remove_by_key) {
//    Node<K, V> * by_parent= nullptr;
//    Node<K, V> * by_right= nullptr;
//    Node<K, V> * by_left= nullptr;
//    if (replace_by!= nullptr){
//        by_parent=replace_by->parent;
//        by_left=replace_by->left;
//        by_right=replace_by->right;
//    }
//    Node<K, V> * target_p= target->parent;
//    Node<K, V> * target_right=target->right;
//    Node<K, V> * target_left=target->left;
//
//    if (target_right!= nullptr) target_right->parent=replace_by;
//    if (target_left!= nullptr) target_left->parent=replace_by;
//    if (target_p!= nullptr) {
//        if(target_p->left==target){
//            target_p->left= replace_by;
//        }
//        else target_p->right= replace_by;
//    }
//    else{
//        root=replace_by;
//        replace_by->parent= nullptr;
//    }
//    replace_by->right=target_right;
//    replace_by->left=target_left;
//    if (by_parent!= nullptr&&remove_by_key){
//        if (by_parent->left==replace_by){
//            by_parent->left= nullptr;
//        }
//        else {by_parent->right= nullptr;}
//    }
//    if (replace_by!= nullptr&&(!remove_by_key)){
//        replace_by->right= target_right;
//        replace_by->left=target_left;
//        if (by_parent!= nullptr) {
//            if(by_parent->left==replace_by){
//                by_parent->left= target;
//            }
//            else by_parent->right= target;
//        }
//        else{root=target;}
//    }
//
//
//
//};

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

template <typename K,typename V>
Key_Value_block<K, V>* AVLTree<K,V>::export_to_array() {
	Key_Value_block<K,V>* array[this->size];
	// in order organize to array
	int index = 0;
	Recursive_export_to_array(root, array, &index);
	return array;

};
template <typename K,typename V>
void AVLTree<K,V>::Recursive_export_to_array(Node<K,V>* root, Key_Value_block<K,V> *array, int *indexPtr){
	// recursion Base
	if(root->is_leaf()) {
		array[*indexPtr] = new Key_Value_block<K, V>(root->key, root->value);
		(*indexPtr)++;
		return ;
	}
	// handle right subtree
	if (root->left != nullptr) {
		Recursive_export_to_array(root->left , array, indexPtr);
	}

	// add root
	array[*indexPtr] = new Key_Value_block<K, V>(root->key, root->value);
	(*indexPtr)++;

	// handle left subtree
	if (root->right != nullptr) {
		Recursive_export_to_array(root->right , array, indexPtr);
	}
}

/**
 * aids
 */
//void


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
