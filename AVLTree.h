#ifndef DAST_EX1_BINARYTREE_H
#define DAST_EX1_BINARYTREE_H
#define BAD_BF 4
#include <assert.h>
#include <exception>
#include <memory>
#include <iostream>
//#include "Utils.h"
#define max(X, Y) (((X) > (Y)) ? (X) : (Y))

//template <typename K, typename V>
//class Node {
//public:
//	K key ;
//	V value ;
//	Node(const K& key, const V& value): key(key), value(value){};
////	void merge_arrays(Node<K, V>** src1, int size1, Node<K, V>** src2, int size2, Node<K, V>** dst);
//};

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
//    bool operator==(const Node& node);
//    bool operator>(const Node& node);
    void print();
};


template <typename K,typename V>
class AVLTree {
private:
	Node<K,V>* remove_leaf(Node<K, V> *leaf_to_remove);
	Node<K,V>* remove_link_from_chain(Node<K, V> *node_to_remove);
	Node<K,V>* min(Node<K,V>* start);

	void rotate(Node<K,V>* dest);
	void RR_rotate(Node<K,V>* dest);
	void LL_rotate(Node<K,V>* dest);
	void RL_rotate(Node<K,V>* dest);
	void LR_rotate(Node<K,V>* dest);
	void replace( Node<K, V> *target, Node<K, V> *replace_by, bool remove = true);
	void swap_keys_and_values(Node<K, V> *node1, Node<K, V> *node2);



public:
	// members
    Node<K, V> * root;
	int size;
	// constructor and destractor
	AVLTree() : root(nullptr), size(0){};
	~AVLTree(){
        if (root== nullptr) return;
        int n = size;
        int ix = 0;
        Node<K, V> * allNodes[n];
        Recursive_export_to_array(root,allNodes, &ix);
        std::cout<<ix<<", "<<n<<std::endl;
        for (int i =0; i<ix;i++){
            delete allNodes[i];
        }
    };

	//basic methods
	Node<K, V>* search(const K & target_key, bool return_parent= false, Node<K, V> *start_node = nullptr);
	Node<K,V>* add(const K& key, const V& value );
	Node<K,V>* remove_by_key(const K& key, Node<K, V> *start_node= nullptr);
	Node<K,V>* remove_Node(Node<K, V>* to_remove, Node<K, V> *start_node= nullptr);
//    Node<K,V>* remove_recursively(Node<K, V>* to_remove);
    Node<K,V>* max_node(Node<K,V>* start = nullptr);
    Node<K, V>** export_to_array();
    bool is_empty() {return (root == nullptr);}
	void merge_trees(AVLTree<K,V> & tree1, AVLTree<K,V> &tree2);
	void create_avl_from_array(Node<K, V>** array, int n);
    void update_parent(Node<K, V> *child,Node<K, V> *target);
    Node<K,V>* sortedArrayToBST(Node<K,V>* arr[], int start, int end, int height=1);
	int height() { return get_height(root);};
	class NodeAlreadyExists:public std::exception{};
	class NodeDoesntExists:public std::exception{};
    class AVLTreeNotEmpty:public std::exception{};
    Node<K,V>** merge_arrays(Node<K,V> * arr1[], Node<K,V> * arr2[], int m, int n, Node<K,V> * mergedArr[]);
	void Recursive_export_to_array(Node<K,V>* root, Node<K,V> **array, int *indexPtr);
    Node<K,V>* find_next_up(Node<K,V> * start);
//    Node<K,V>* find_next_down(Node<K,V> * start);


//	bool friend operator>(const Node<K, V> & first, const Node<K, V> & second);
};

/**
 *
 */

/**
 ----------------- AVL implementations ----------------------------
 */

//template <typename K,typename V>
//Node<K,V>* remove_recursively(Node<K, V>* to_remove){
//    if (to_remove== nullptr) return ;
//    if (to_remove->is_leaf()) {
//        update_parent(to_remove,nullptr);
//        delete to_remove;
//    }
//    else{
//        remove_recursively(to_remove->right);
//        remove_recursively(to_remove->left);
//    }
//};
template <typename K,typename V>
Node<K,V>* AVLTree<K, V>::find_next_up(Node<K,V> * start){
    if (start->right!= nullptr){
        return AVLTree<K, V>::min(start->right);
    }
    Node<K,V>* parent = start->parent;
    while (parent!= nullptr && start==parent->right){
        start=parent;
        parent=parent;
    }
    return parent;
};
//template <typename K,typename V>
//Node<K,V>* AVLTree<K, V>::find_next_down(Node<K,V> * start){
//    if (!start->is_leaf()){
//        return AVLTree<K, V>::max_node(start->left);
//    }
//    Node<K,V>* parent = start->parent;
//    while (parent!= nullptr && start==parent->left){
//        start=parent;
//        parent=parent;
//    }
//    return parent;
//};
template <typename K,typename V>
void AVLTree<K, V>::update_parent(Node<K, V> *child,Node<K, V> *target){
    if (child->parent== nullptr){
        return;
    }
    if (child->parent->right==child){
        child->parent->right=target;
    }
    else {
        child->parent->left=target;
    }
};

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
Node<K,V>*  AVLTree<K,V>::add(const K& key, const V& value ) {//(const K& key, const V& value ) {
    Node<K, V> *search_result = search(key, true);
	int size = this->size;

	// key doesn't exist - set the Node to the root of the tree
	if (search_result == nullptr) {
		Node<K, V> *new_node = new Node<K, V>(key, value);//std::shared_ptr<Node<K, V>>(new Node<K, V>(key, value));
		this->root = new_node;
		this->size = size + 1;
        return new_node;
    } else {
        // key exists
        if (search_result->key == key) {
            throw AVLTree<K,V>::NodeAlreadyExists();
        }
        // insert as is regular Binary tree
        Node<K, V> *new_node = new Node<K, V>(key, value);//std::shared_ptr<Node<K, V>>(new Node<K, V>(key, value), value);
        new_node->parent = search_result;
        if (search_result->key > new_node->key) {
            search_result->left = new_node;
        } else {
            search_result->right = new_node;
        }
		this->size = size + 1;
        // AvlTree stuff
        Node<K, V>* temp_node = new_node;
        while(temp_node != root) {
            Node<K, V>* p = temp_node->parent;
            // if the tree is AVL balanced
			int temp_node_height = get_height(temp_node);
            if (get_height(p) >= (temp_node_height+1)){
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
void AVLTree<K,V>::rotate(Node<K,V>* dest){
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
Node<K,V>* AVLTree<K,V>::max_node( Node<K,V>* start) {
	if (start == nullptr) {
		start = root;
	}
	while (start->right != nullptr){
		start = start->right;
	}
	return start;
}

template <typename K,typename V>
Node<K,V>* AVLTree<K,V>::remove_by_key(const K& key, Node<K, V> *start_node){
	Node<K, V> *target = search(key, false, start_node);
    if (target == nullptr){
        throw AVLTree<K,V>::NodeDoesntExists();
    }
    Node<K,V>* temp = remove_Node(target, start_node);
	this->size = this->size - 1;

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

template <typename K,typename V>
void AVLTree<K,V>::create_avl_from_array(Node<K, V>** array, int n){
//    if (!this->is_empty()){throw AVLTree<K,V>::AVLTreeNotEmpty();}
    root = sortedArrayToBST(array, 0, n); //todo maybe should be n-1
    size = n;
};


template <typename K,typename V>
Node<K,V>* AVLTree<K,V>::remove_Node(Node<K, V> *to_remove, Node<K, V> *start_node) {
    //todo: node is root?
    //todo: return?
	Node<K, V> * follower;
	bool has_two_sons = to_remove->has_two_sons();
//    size=size-1;
	// if node is leaf
	if (to_remove->is_leaf()) {
		AVLTree::remove_leaf(to_remove);
	}
	else if (!has_two_sons) {
		return AVLTree::remove_link_from_chain(to_remove);
	} else {
		follower = AVLTree<K,V>::min(to_remove->right);
		swap_keys_and_values(to_remove, follower); //todo: maybe better to use dummy, will be problem in player
		return remove_Node(follower, to_remove->right);
	}

	return nullptr;
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
Node<K,V>* AVLTree<K,V>::remove_leaf(Node<K, V> *leaf_to_remove){
	assert(leaf_to_remove->right == nullptr && leaf_to_remove->left == nullptr);
	Node<K,V> *parent = leaf_to_remove->parent;
	if (parent->left == leaf_to_remove) {
		parent->left = nullptr;
	} else {
		assert(parent->right == leaf_to_remove);
		parent->right = nullptr;
	}
	delete leaf_to_remove;
    return parent;
}

template<typename K, typename  V>
Node<K,V>* AVLTree<K,V>::remove_link_from_chain(Node<K, V> *node_to_remove){
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
    return son;
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
void AVLTree<K,V>::LL_rotate(Node<K,V>* b){
//    std::cout<<"LL_rotate ("<<b->key<<")"<<std::endl;
    Node<K,V> *a = b->left;
    Node<K,V> *a_r = a->right;
    Node<K,V> *b_p = b->parent;
    update_parent(b,a);
    a->right = b;
    b->left=a_r;
    if (a_r!= nullptr){
        a_r->parent=b;
    }
    a->parent=b_p;
    b->parent=a;

    if (b==root){
        root=a;
    }

    // Update heights
    a->height = max(get_height(a->left),
                    get_height(a->right)) + 1;
    b->height = max(get_height(b->left),
                    get_height(b->right)) + 1;

//    // Return new root
//    return x;
};
template <typename K,typename V>
void AVLTree<K,V>::RR_rotate(Node<K,V>* b){
//    std::cout<<"RR_rotate ("<<b->key<<")"<<std::endl;
    Node<K,V> *a = b->right;
    Node<K,V> *a_l = a->left;
    Node<K,V> *b_p = b->parent;
    update_parent(b,a);
    a->left = b;
    b->right=a_l;
    if (a_l!= nullptr){
        a_l->parent=b;
    }
    a->parent=b_p;
    b->parent=a;
    if (b==root){
        root=a;
    }

    // Update heights
    a->height = max(get_height(a->left),
                    get_height(a->right)) + 1;
    b->height = max(get_height(b->left),
                    get_height(b->right)) + 1;
//    Node<K,V> *y = dest->right;
//    Node<K,V> *T2 = y->left;
//
//    // Perform rotation
//    y->left = dest;
//    dest->right = T2;
//    if (dest==root){
//        root=y;
////        root->parent= nullptr;
//    }
//    y->parent=dest->parent;
//    dest->parent=y;
//
//    // Update heights
//    dest->height = max(get_height(dest->left),
//                    get_height(dest->right)) + 1;
//    y->height = max(get_height(y->left),
//                    get_height(y->right)) + 1;

};

template <typename K,typename V>
void AVLTree<K,V>::RL_rotate(Node<K,V>* dest){
    LL_rotate(dest->right);
    RR_rotate(dest);
};

template <typename K,typename V>
void AVLTree<K,V>::LR_rotate(Node<K,V>* dest){
    RR_rotate(dest->left);
    LL_rotate(dest);
};

template <typename K,typename V>
Node<K, V>** AVLTree<K,V>::export_to_array() {
	int size = this->size;
	Node<K,V>** array = new Node<K,V>*[size];
	// in order organize to array
	int index = 0;
	Recursive_export_to_array(root, array, &index);
	return array;

};
template <typename K,typename V>
void AVLTree<K,V>::Recursive_export_to_array(Node<K,V>* root, Node<K,V> **array, int *indexPtr){
	// recursion Base
	if(root->is_leaf()) {
		array[*indexPtr] = root;//new Node<K, V>(root->key, root->value);
		(*indexPtr)++;
		return ;
	}
	// handle right subtree
	if (root->left != nullptr) {
		Recursive_export_to_array(root->left , array, indexPtr);
	}

	// add root
	array[*indexPtr] = root;//new Node<K, V>(root->key, root->value);
	(*indexPtr)++;

	// handle left subtree
	if (root->right != nullptr) {
		Recursive_export_to_array(root->right , array, indexPtr);
	}
}

template <typename K,typename V>
void AVLTree<K,V>::merge_trees(AVLTree<K,V> & tree1, AVLTree<K,V> & tree2) {
//    if (!is_empty()) {throw AVLTreeNotEmpty();}
	int tree1_size = tree1.size, tree2_size = tree2.size;
	Node<K, V>** tree1_array = tree1.export_to_array();
	Node<K, V>** tree2_array = tree2.export_to_array();
    Node<K,V>* mergedArr[tree1.size + tree2.size];
	Node<K, V>** merged_array = merge_arrays(tree1_array, tree2_array, tree1_size, tree2_size,mergedArr);
	create_avl_from_array(merged_array,tree1_size+tree2_size);
}

/**
 * aids
 */
//template <typename K,typename V>
//void Node<K,V>::merge_arrays(Node<K, V>** src1, int size1, Node<K, V>** src2,int size2, Node<K, V>** dst) {
//	int index1 = 0, index2 = 0;
//	int dst_arr_size = size1 + size2;
//	while (index1 + index2 < dst_arr_size) {
//		if (index1 >= size1) {
//			dst[index1 + index2] = src2[index2];
//			index2++;
//		} else if (index2 >= size2) {
//			dst[index1 + index2] = src1[index1];
//			index1++;
//		} else {
//			Node<K, V>* block1 = src1[index1];
//			K key1 = block1->key;
//			Node<K, V>* block2 = src2[index2];
//			K key2 = block2->key;
//			if (key1 < key2) {
//				dst[index1 + index2] = src1[index1];
//				index1++;
//			} else {
//				dst[index1 + index2] = src1[index2];
//				index2++;
//			}
//		}
//	}
//}


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

//-----
//todo: cleanup
template <typename K, typename V>
Node<K,V> * AVLTree<K,V>::sortedArrayToBST(Node<K,V>* arr[], int start, int end, int height)
{
    /* Base Case */
    if (start > end)
        return nullptr;

    /* Get the middle element and make it root */
    int mid = (start + end)/2;
//    Node(const K& key, const V& value,,
    Node<K,V> *root = arr[mid]; //new Node<K,V>(arr[mid].key, arr[mid].value, height);
    root->height=height;

    /* Recursively construct the left subtree and make it
    left child of root */
    root->left = sortedArrayToBST(arr, start, mid-1,height+1);

    /* Recursively construct the right subtree and make it
    right child of root */
    root->right = sortedArrayToBST(arr, mid+1, end,height+1);

    return root;
}


//todo: clean up
template <typename K, typename V>
Node<K,V>** AVLTree<K,V>::merge_arrays(Node<K,V> * arr1[], Node<K,V> * arr2[], int m, int n, Node<K,V> * mergedArr[])
{
    // mergedArr[] is going to contain result

//    Node<K,V>* mergedArr[m + n];
    int i = 0, j = 0, k = 0;

    // Traverse through both arrays
    while (i < m && j < n)
    {
        // Pick the smaller element and put it in mergedArr
        if (arr1[i]->key < arr2[j]->key)
        {
            mergedArr[k] = arr1[i];
            i++;
        }
        else
        {
            mergedArr[k] = arr2[j];
            j++;
        }
        k++;
    }

    // If there are more elements in first array
    while (i < m)
    {
        mergedArr[k] = arr1[i];
        i++; k++;
    }

    // If there are more elements in second array
    while (j < n)
    {
        mergedArr[k] = arr2[j];
        j++; k++;
    }

    return mergedArr;
}


#endif //DAST_EX1_BINARYTREE_H
