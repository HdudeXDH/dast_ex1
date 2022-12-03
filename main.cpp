
// Created by User on 11/29/2022.
//
#include "AVLTree.h"
#include "Utils.h"
int main() {
    AVLTree<int,int> a;
    a.add(1,2);
    a.add(2,2);
    a.add(3,2);
    a.add(4,2);
//	a.remove_by_key(2);
    a.add(-1,2);
    int ix = 0;
    Key_Value_block<int,int> *array[a.size];
    a.Recursive_export_to_array(a.root, array, &ix);
    a.add(-1,2);



}
