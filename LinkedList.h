//
// Created by noamk on 12/6/2022.
//

#ifndef DAST_EX1_LINKEDLIST_H
#define DAST_EX1_LINKEDLIST_H

template <typename K, typename V>
class LinkedList_Node {
public:
	// members
	K key;
	V value;
    std::shared_ptr<LinkedList_Node<K,V>> next;
    std::shared_ptr<LinkedList_Node<K,V>> prev;


	// Ctor & Dtor
	LinkedList_Node() = default;
	LinkedList_Node(K key,V value): key(key), value(value), next(nullptr), prev(nullptr){};

	// methods :
//	LinkedList_Node<K,V>* compare_and_unite_node_with_next(LinkedList_Node<K,V>* node);
};


template <typename K, typename V>
class LinkedList {
public:
	// members
	// Head is dummy, does not have a value
	int size;
    std::shared_ptr<LinkedList_Node<K,V>> head;
    std::shared_ptr<LinkedList_Node<K,V>> tail;

	// Ctor & Dtor
	LinkedList(): size(0), head(new LinkedList_Node<K,V>()), tail(head) {
		head->prev = nullptr;
		tail->next = nullptr;
	};
	~LinkedList() {
        std::shared_ptr<LinkedList_Node<K,V>> current = head;
        while (current->next!= nullptr){
            current->next=nullptr;
            current->prev=nullptr;
        }
//        std::shared_ptr<LinkedList_Node<K,V>> next = head->next;
//        std::shared_ptr<LinkedList_Node<K,V>> nextnext = head->next->next;

//		while (nextnext != tail &&nextnext != nullptr) {
//			delete next;
//			next = nextnext;
//			nextnext = next->next;
//		}
//		delete head;
//		delete tail;
	}

	// methods
	void add(K key, V value);
	bool remove_node(std::shared_ptr<LinkedList_Node<K,V>>to_remove);
};


template <typename K, typename V>
void LinkedList<K,V>::add(K key, V value) {
    std::shared_ptr<LinkedList_Node<K,V>> new_node = std::shared_ptr<LinkedList_Node<K,V>>(new LinkedList_Node<K,V>(key, value));
	new_node->prev = tail;
	tail->next = new_node;
	tail = new_node;
	size++;
}
template <typename K, typename V>
bool LinkedList<K,V>::remove_node(std::shared_ptr<LinkedList_Node<K,V>> to_remove) {
	if (size == 1 || to_remove == head) {
		return false;
	}
	if (to_remove == head) {
		head = head->next;
		head->prev = nullptr;
	} else if (to_remove == tail) {
		tail = tail->prev;
		tail->next = nullptr;
	} else {
        std::shared_ptr<LinkedList_Node<K,V>> before = to_remove->prev;
        std::shared_ptr<LinkedList_Node<K,V>> after = to_remove->next;
		before->next = after;
		after->prev = before;
	}
	size--;
//	delete to_remove;
	return true;
}

#endif //DAST_EX1_LINKEDLIST_H
