//
// Created by cristian on 20/09/17.
//

#ifndef RMLIB_NODE_H
#define RMLIB_NODE_H

#include <iostream>

using namespace std;

template <class T>

class Node
{
public:
    Node();
    Node(T);
    ~Node();

    Node *next;
    T data;

    void delete_all();
    void print();
};


#endif //RMLIB_NODE_H
