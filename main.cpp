
// Created by User on 11/29/2022.
//
#include "AVLTree.h"
#include "Utils.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "test_maker/test_AVL_insertions_deletions.h"
class dummy{
    bool * result;
    int id;
public:
    dummy(bool * res, int id=0):result(res), id(id){
        std::cout<<"dummy["<<id<<"] Ctor used."<<std::endl;
        *result = false;}
    ~dummy(){
        std::cout<<"~dummy["<<id<<"] Dtor used."<<std::endl;
        *result=true;
    }
    bool operator!=(bool other){ return  *result!=other;}
    bool operator==(bool other){ return  *result==other;}
};



// pass the root node of your binary tree



int main() {
//    test_insertion_deletion();

    int n=5;
    bool dummies[n];
    AVLTree<int,dummy> del_tree;
    for (int i=0;i<n;i++){
        del_tree.add(i,dummy(&dummies[i], i));
    }
    del_tree.remove_by_key(2);
    assert (dummies[2]==true);
    del_tree.add(2,dummy(&dummies[2], 2));
    for (int i=0;i<n;i++){
        del_tree.remove_by_key(i);
        assert (dummies[i]==true);
    }





}
