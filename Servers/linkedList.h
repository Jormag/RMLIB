//
// Created by cristian on 20/09/17.
//

#ifndef RMLIB_LIST_H
#define RMLIB_LIST_H


#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "node.h"
#include "node.cpp"

using namespace std;

template <class T>
class linkedList {
public:
    linkedList();

    ~linkedList();

    Node<T> *first;
    int size;

    void add_end(T);

    void del_by_data(T);

    void del_by_position(int);

    void print();

    void search(T);
};


#endif //RMLIB_LIST_H
