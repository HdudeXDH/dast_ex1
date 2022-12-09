#ifndef DAST_EX1_BINARYTREE_H
#define DAST_EX1_BINARYTREE_H
#define BAD_BF 4
#include <assert.h>
#include <exception>
#include <memory>
#include <iostream>

template <typename K, typename V>
class Node {
public:
    K key;
    V value;
    int height;
    std::shared_ptr<Node<K, V>> parent;
    std::shared_ptr<Node<K, V>> left;
    std::shared_ptr<Node<K, V>> right;
    Node(const K& key, const V& value, int height=1, Node* parent= nullptr,Node* left= nullptr, Node* right= nullptr):
    key(key), value(value),height(height),parent(parent),left(left), right(right) {};
    Node() = delete;
	bool has_two_sons();
	bool is_leaf();
    int BF();
};


template <typename K,typename V>
class AVLTree {
private:
	std::shared_ptr<Node<K, V>> remove_leaf(std::shared_ptr<Node<K, V>>leaf_to_remove);
	std::shared_ptr<Node<K, V>> remove_link_from_chain(std::shared_ptr<Node<K, V>>node_to_remove);
	std::shared_ptr<Node<K, V>> min(std::shared_ptr<Node<K, V>> start);

	void rotate(std::shared_ptr<Node<K, V>> dest);
	void RR_rotate(std::shared_ptr<Node<K, V>> dest);
	void LL_rotate(std::shared_ptr<Node<K, V>> dest);
	void RL_rotate(std::shared_ptr<Node<K, V>> dest);
	void LR_rotate(std::shared_ptr<Node<K, V>>dest);
public:
    // members
    std::shared_ptr<Node<K, V>> root;
    int size;

	// constructor and destractor
	AVLTree() : root(nullptr), size(0){};
    ~AVLTree(){
        if (root== nullptr) return;
        int ix = 0;
        std::shared_ptr<Node<K, V>>* allNodes = new std::shared_ptr<Node<K, V>>[size];
        Recursive_export_to_array(root,allNodes, &ix);
        for (int i =0; i<ix;i++){
            allNodes[i]->parent = nullptr;
            allNodes[i]->left = nullptr;
            allNodes[i]->right = nullptr;
        }
		delete[] allNodes;
    };

	//basic methods
	std::shared_ptr<Node<K, V>> search(const K & target_key, bool return_parent= false, std::shared_ptr<Node<K, V>> start_node = nullptr);
    void swap_nodes(std::shared_ptr<Node<K, V>>node1, std::shared_ptr<Node<K, V>>node2);
    std::shared_ptr<Node<K, V>> add(const K& key, const V& value );
    std::shared_ptr<Node<K, V>> remove_by_key(const K& key, std::shared_ptr<Node<K, V>>start_node= nullptr);
	std::shared_ptr<Node<K, V>> remove_Node(std::shared_ptr<Node<K, V>> to_remove, std::shared_ptr<Node<K, V>>start_node= nullptr);
    std::shared_ptr<Node<K, V>> max_node(std::shared_ptr<Node<K, V>> start = nullptr);
    std::shared_ptr<Node<K, V>>* export_to_array();
    bool is_empty() {return (root == nullptr);}
	void merge_trees(AVLTree<K,V> & tree1, AVLTree<K,V> &tree2);
	void create_avl_from_array(std::shared_ptr<Node<K, V>>* array, int n);
    void update_parent(std::shared_ptr<Node<K, V>>child,std::shared_ptr<Node<K, V>>target);
    std::shared_ptr<Node<K, V>> Recursive_sorted_array_to_tree(std::shared_ptr<Node<K, V>> arr[], int start, int end, int height=1);
	class NodeAlreadyExists:public std::exception{};
	class NodeDoesntExists:public std::exception{};
    std::shared_ptr<Node<K, V>>* merge_arrays(std::shared_ptr<Node<K, V>> array1[], std::shared_ptr<Node<K, V>> array2[], int array1_size, int array2_size, std::shared_ptr<Node<K, V>> merged_Array[]);
	void Recursive_export_to_array(std::shared_ptr<Node<K, V>> root, std::shared_ptr<Node<K, V>>*array, int *indexPtr);
    std::shared_ptr<Node<K, V>> find_next_up(std::shared_ptr<Node<K, V>> start);
    int max(int a, int b){
        if (a>b){
            return a;
        }
        else return b;
    }
};

/**
 *
 */

/**
 ----------------- AVL implementations ----------------------------
 */

template <typename K,typename V>
std::shared_ptr<Node<K, V>> AVLTree<K, V>::find_next_up(std::shared_ptr<Node<K, V>> start){
    if (start->right!= nullptr){
        return AVLTree<K, V>::min(start->right);
    }
    std::shared_ptr<Node<K, V>> current = start;
    std::shared_ptr<Node<K, V>> parent = start->parent;
    while (parent!= nullptr && current==parent->right){

        current=parent;
        parent=current->parent;
    }
    return parent;
}


template <typename K,typename V>
void AVLTree<K, V>::update_parent(std::shared_ptr<Node<K, V>>child,std::shared_ptr<Node<K, V>>target){
    if (child->parent== nullptr){
        return;
    }
    if (child->parent->right==child){
        child->parent->right=target;
    }
    else {
        child->parent->left=target;
    }
}


template <typename K,typename V>
std::shared_ptr<Node<K, V>> AVLTree<K, V>::search(const K & target_key, bool return_parent, std::shared_ptr<Node<K, V>>start_node) {
	if (start_node == nullptr){
		start_node = root;
	}
    if (start_node == nullptr) return nullptr;
    std::shared_ptr<Node<K, V>> temp = start_node;
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
std::shared_ptr<Node<K, V>>  AVLTree<K,V>::add(const K& key, const V& value ) {
    std::shared_ptr<Node<K, V>>search_result = search(key, true);
	int size = this->size;
	if (search_result == nullptr) {
		std::shared_ptr<Node<K, V>>new_node = std::shared_ptr<Node<K, V>>(new Node<K, V>(key, value));
		this->root = new_node;
		this->size = size + 1;
        return new_node;
    } else {
        // key exists
        if (search_result->key == key) {
            throw AVLTree<K,V>::NodeAlreadyExists();
        }
        // insert as is regular Binary tree
        std::shared_ptr<Node<K, V>> new_node(new Node<K, V>(key, value));
        new_node->parent = search_result;
        if (search_result->key > new_node->key) {
            search_result->left = new_node;
        } else {
            search_result->right = new_node;
        }
		this->size = size + 1;
        std::shared_ptr<Node<K, V>> temp_node = new_node;
        while(temp_node != root) {
            std::shared_ptr<Node<K, V>> p = temp_node->parent;
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
void AVLTree<K,V>::rotate(std::shared_ptr<Node<K, V>> dest){
    int balance = dest->BF();
    if (balance > 1 && dest->left->BF()>=0)
        return LL_rotate(dest);
    if (balance > 1 && dest->left->BF()==-1)
        return LR_rotate(dest);
    if (balance <-1 && dest->right->BF()<=0)
        return RR_rotate(dest);
    if (balance <-1 && dest->right->BF()==1)
        return RL_rotate(dest);
}


template <typename K,typename V>
std::shared_ptr<Node<K, V>> AVLTree<K,V>::min( std::shared_ptr<Node<K, V>> start) {
    while (start->left != nullptr){
        start = start->left;
    }
    return start;
}


template <typename K,typename V>
std::shared_ptr<Node<K, V>> AVLTree<K,V>::max_node( std::shared_ptr<Node<K, V>> start) {
	if (root== nullptr){
        return nullptr;
    }
    if (start == nullptr) {
		start = root;
	}
	while (start->right != nullptr){
		start = start->right;
	}
	return start;
}


template <typename K,typename V>
std::shared_ptr<Node<K, V>> AVLTree<K,V>::remove_by_key(const K& key, std::shared_ptr<Node<K, V>>start_node){
	if (start_node == nullptr) {
		start_node = root;
	}
	std::shared_ptr<Node<K, V>>target = search(key, false, start_node);
    if (target == nullptr){
        throw AVLTree<K,V>::NodeDoesntExists();
    }
    std::shared_ptr<Node<K, V>> temp = remove_Node(target, start_node);
	this->size = this->size - 1;

    //AVL_balancing
    if (temp== nullptr){return temp;}
    temp->height=1+max(get_height(temp->left),get_height(temp->right));
    while(temp != root) {
        std::shared_ptr<Node<K, V>> p = temp->parent;
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
//    printBT(root);
    return nullptr;
}


template <typename K,typename V>
void AVLTree<K,V>::create_avl_from_array(std::shared_ptr<Node<K, V>>* array, int n){
    root = Recursive_sorted_array_to_tree(array, 0, n - 1);
    if (root != nullptr){
        root->parent= nullptr;
    }
    size = n;
}


template <typename K,typename V>
std::shared_ptr<Node<K, V>> AVLTree<K,V>::remove_Node(std::shared_ptr<Node<K, V>>to_remove, std::shared_ptr<Node<K, V>>start_node) {
	std::shared_ptr<Node<K, V>> follower;
	bool has_two_sons = to_remove->has_two_sons();
	if (to_remove->is_leaf()) {
		AVLTree::remove_leaf(to_remove);
	}
	else if (!has_two_sons) {
		return AVLTree::remove_link_from_chain(to_remove);
	} else {
		follower = AVLTree<K,V>::min(to_remove->right);
		swap_nodes(to_remove, follower);
		return remove_Node(to_remove, to_remove->right);
	}

	return nullptr;
}


template<typename K, typename  V>
void AVLTree<K,V>::swap_nodes(std::shared_ptr<Node<K, V>>node1, std::shared_ptr<Node<K, V>>node2) {
	//handle root
    if (node2 == root) {
        swap_nodes(node2, node1);
        return;
    }
	if (node1 == root) {
		root = node2;
	}

    if (node2==node1->parent){
        swap_nodes(node2, node1);
        return;
    }
    std::shared_ptr<Node<K, V>> temp_right_ptr, temp_left_ptr, temp_parent_ptr;
	// set temp values for later
	temp_left_ptr = node1->left;
	temp_right_ptr = node1->right;
	temp_parent_ptr = node1->parent;
    int temp_height = node1->height;
    node1->height =node2->height;
    node2->height=temp_height;
    if (node1==node2->parent){
        if (temp_left_ptr==node2){
            node1->right=node2->right;
            node1->left=node2->left;
            node2->right=temp_right_ptr;
            node2->left=node1;
            node2->parent=temp_parent_ptr;
            node1->parent=node2;
            if (temp_right_ptr != nullptr) {temp_right_ptr->parent=node2;}
        } else {
            node1->right=node2->right;
            node1->left=node2->left;
            node2->left=temp_left_ptr;
            node2->right=node1;
            node2->parent=temp_parent_ptr;
            node1->parent=node2;
            if (temp_left_ptr != nullptr) {temp_left_ptr->parent=node2;}
        }
        if (node1->left != nullptr) {node1->left->parent=node1;}
        if (node1->right != nullptr) {node1->right->parent=node1;}
        if (temp_parent_ptr != nullptr) {
            if (temp_parent_ptr->right==node1) temp_parent_ptr->right=node2;
            else  temp_parent_ptr->left=node2;
        }

    } else {
        // set parent and sons for node1
        node1->right = node2->right;
        if (node2->right != nullptr) {
            node1->right->parent = node1;
        }
        node1->left = node2->left;
        if (node2->left != nullptr) {
            node1->left->parent = node1;
        }
        node1->parent = node2->parent;
        if (node2->parent != nullptr) {
            if (node2->parent->right == node2) {
                node2->parent->right = node1;
            } else {
                node2->parent->left = node1;
            }
        }

        // set parent and sons for node2
        node2->right = temp_right_ptr;
        if (temp_right_ptr != nullptr) {
            temp_right_ptr->parent = node2;
        }
        node2->left = temp_left_ptr;
        if (temp_left_ptr != nullptr) {
            temp_left_ptr->parent = node2;
        }
        node2->parent = temp_parent_ptr;
        if (temp_parent_ptr != nullptr) {
            if (temp_parent_ptr->right == node1) {
                temp_parent_ptr->right = node2;
            } else {
                temp_parent_ptr->left = node2;
            }
        }
    }
}


template<typename K, typename  V>
std::shared_ptr<Node<K, V>> AVLTree<K,V>::remove_leaf(std::shared_ptr<Node<K, V>>leaf_to_remove){
	assert(leaf_to_remove->right == nullptr && leaf_to_remove->left == nullptr);
    std::shared_ptr<Node<K, V>>parent = leaf_to_remove->parent;
    if (leaf_to_remove==root){
        root= nullptr;
    }
	else if (parent->left == leaf_to_remove) {
		parent->left = nullptr;
	} else {
		assert(parent->right == leaf_to_remove);
		parent->right = nullptr;
	}
    leaf_to_remove.reset();
    return parent;
}


template<typename K, typename  V>
std::shared_ptr<Node<K, V>> AVLTree<K,V>::remove_link_from_chain(std::shared_ptr<Node<K, V>>node_to_remove){
	assert(!(node_to_remove->is_leaf())&& !(node_to_remove->has_two_sons()));
    std::shared_ptr<Node<K, V>>son;
    std::shared_ptr<Node<K, V>>parent = node_to_remove->parent;
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
    node_to_remove.reset();
//	delete node_to_remove;
    return son;
}


template<typename K, typename  V>
bool Node<K, V>::has_two_sons() {
	return !((this->right == nullptr) || (this->left == nullptr));
}

template<typename K, typename  V>
bool Node<K, V>::is_leaf() {
	return ((this->right == nullptr) && (this->left == nullptr));
}


template <typename K,typename V>
void AVLTree<K,V>::LL_rotate(std::shared_ptr<Node<K, V>> b){
    std::shared_ptr<Node<K, V>>a = b->left;
    std::shared_ptr<Node<K, V>>a_r = a->right;
    std::shared_ptr<Node<K, V>>b_p = b->parent;
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
}


template <typename K,typename V>
void AVLTree<K,V>::RR_rotate(std::shared_ptr<Node<K, V>> b){
    std::shared_ptr<Node<K, V>>a = b->right;
    std::shared_ptr<Node<K, V>>a_l = a->left;
    std::shared_ptr<Node<K, V>>b_p = b->parent;
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

    b->height = max(get_height(b->left),
                    get_height(b->right)) + 1;
    a->height = max(get_height(a->left),
                    get_height(a->right)) + 1;

}

template <typename K,typename V>
void AVLTree<K,V>::RL_rotate(std::shared_ptr<Node<K, V>> dest){
    LL_rotate(dest->right);
    RR_rotate(dest);
}

template <typename K,typename V>
void AVLTree<K,V>::LR_rotate(std::shared_ptr<Node<K, V>> dest){
    RR_rotate(dest->left);
    LL_rotate(dest);
}

template <typename K,typename V>
std::shared_ptr<Node<K, V>>* AVLTree<K,V>::export_to_array() {
	int size = this->size;
	std::shared_ptr<Node<K, V>>* array = new std::shared_ptr<Node<K, V>>[size];
	int index = 0;
	Recursive_export_to_array(root, array, &index);
	return array;

}
template <typename K,typename V>
void AVLTree<K,V>::Recursive_export_to_array(std::shared_ptr<Node<K, V>> root, std::shared_ptr<Node<K, V>>*array, int *indexPtr){
	if(root->is_leaf()) {
		array[*indexPtr] = root;
		(*indexPtr)++;
		return ;
	}
	if (root->left != nullptr) {
		Recursive_export_to_array(root->left , array, indexPtr);
	}
	array[*indexPtr] = root;
	(*indexPtr)++;

	if (root->right != nullptr) {
		Recursive_export_to_array(root->right , array, indexPtr);
	}
}

template <typename K,typename V>
void AVLTree<K,V>::merge_trees(AVLTree<K,V> & tree1, AVLTree<K,V> & tree2) {
	int tree1_size = tree1.size, tree2_size = tree2.size;
	std::shared_ptr<Node<K, V>>* tree1_array = tree1.export_to_array();
	std::shared_ptr<Node<K, V>>* tree2_array = tree2.export_to_array();
    if (this != &tree1){
        tree1.root= nullptr;
        tree1.size=0;
    }
    if (this != &tree2){
        tree2.root= nullptr;
        tree2.size=0;
    }
    std::shared_ptr<Node<K, V>>* mergedArr = new std::shared_ptr<Node<K, V>>[tree1_size + tree2_size];
	std::shared_ptr<Node<K, V>>* merged_array = merge_arrays(tree1_array, tree2_array, tree1_size, tree2_size,mergedArr);
	create_avl_from_array(merged_array,tree1_size+tree2_size);
    this->size=tree1_size+tree2_size;
	delete[] merged_array;
	delete[] tree1_array;
	delete[] tree2_array;
}


/**
 ----------------------------- Node methods ----------------------------
 */


template <typename K,typename V>
int get_height(std::shared_ptr<Node<K, V>> target){
    if (target== nullptr) return 0;
    else return target->height;
}

template <typename K,typename V>
int Node<K,V>::BF() {
    return (get_height(this->left) - get_height(this->right));
}


template <typename K, typename V>
std::shared_ptr<Node<K, V>> AVLTree<K,V>::Recursive_sorted_array_to_tree(std::shared_ptr<Node<K, V>> arr[], int start, int end, int height)
{
    if (start > end)
        return nullptr;

    int mid = (start + end)/2;
    std::shared_ptr<Node<K, V>>root = arr[mid];
    root->height=height;
    root->left = Recursive_sorted_array_to_tree(arr, start, mid - 1, height + 1);
	if (root->left != nullptr) {
		root->left->parent = root;
	}
    root->right = Recursive_sorted_array_to_tree(arr, mid + 1, end, height + 1);
	if (root->right != nullptr) {
		root->right->parent = root;
	}
    return root;
}


template <typename K, typename V>
std::shared_ptr<Node<K, V>>* AVLTree<K,V>::merge_arrays(std::shared_ptr<Node<K,V>>  array1[], std::shared_ptr<Node<K,V>> array2[], int array1_size, int array2_size, std::shared_ptr<Node<K, V>> merged_Array[])
{
    int array_1_index = 0, array_2_index = 0, new_array_index = 0;
    while (array_1_index < array1_size && array_2_index < array2_size)
    {
        if (array1[array_1_index]->key < array2[array_2_index]->key)
        {
			merged_Array[new_array_index] = array1[array_1_index];
            array_1_index+=1;
        }
        else
        {
			merged_Array[new_array_index] = array2[array_2_index];
            array_2_index+=1;
        }
        new_array_index+=1;
    }

    while (array_1_index < array1_size)
    {
		merged_Array[new_array_index] = array1[array_1_index];
		new_array_index+=1;
		array_1_index+=1;
    }

    while (array_2_index < array2_size)
    {
		merged_Array[new_array_index] = array2[array_2_index];
		new_array_index+=1;
		array_2_index+=1;
	}
    return merged_Array;
}


#endif //DAST_EX1_BINARYTREE_H
