//
// Created by noamk on 12/6/2022.
//

#ifndef DAST_EX1_LINKEDLIST_H
#define DAST_EX1_LINKEDLIST_H

template <typename K, typename V>
class LinkedList {
public:
	LinkedList(): head(LinkedList_Node<K,V>()) {};
	LinkedList_Node<K,V> head;
};

template <typename K, typename V>
class LinkedList_Node {
public:
	// members
	K key;
	V value;
	LinkedList_Node<K,V>* next;
	LinkedList_Node<K,V>* prev;

	// big 3
	LinkedList_Node();

	// methods :

};


template <typename K, typename V>
LinkedList_Node<K,V>::LinkedList_Node() {
	LinkedList_Node<K,V>* next = this;
}
#endif //DAST_EX1_LINKEDLIST_H
