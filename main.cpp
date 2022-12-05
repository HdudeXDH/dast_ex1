
// Created by User on 11/29/2022.
//
#include "AVLTree.h"
#include "Utils.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "test_maker/test_AVL_insertions_deletions.h"
#include "test_maker/test_AVL_memory_leaks.h"


int main() {

//    AVLTree<int,int> a;
//    a.add(1,2);
//    a.add(2,2);
//    a.add(3,2);
//    a.add(4,2);
////	a.remove_by_key(2);
//    a.add(-1,2);
//    int ix = 0;
//    Key_Value_block<int,int> *array[a.size];
////    a.add(-1,2);
    test_leakage();
//    std::cout<<res;

//test_insertion_deletion();

//    int n=5;
//    int dummies[n];
//    int dummies_keys[n];
//    for (int i=0;i<n;i++){ dummies[i]=0;}
//    for (int i=0;i<n;i++){ dummies_keys[i]=0;}
//    AVLTree<dummy,dummy> del_tree;
//    for (int i=0;i<n;i++){
//
//        del_tree.add(dummy(&dummies_keys[i], i),dummy(&dummies[i], i));
//    }
//    del_tree.remove_by_key(dummy(&dummies_keys[2], 2));
//    assert (dummies[2]==0);
////    dummy d(&dummies[2], 2);
//    del_tree.add(2,d);
//    for (int i=0;i<n;i++){
//        del_tree.remove_by_key(i);
//        assert (dummies[i]==true);
//    }

}
