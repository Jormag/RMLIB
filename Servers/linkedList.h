//
// Created by cristian on 20/09/17.
//

#ifndef RMLIB_LIST_H
#define RMLIB_LIST_H


#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include "rmRef_h.cpp"

using namespace std;

class linkedList {
public:
    linkedList();

    ~linkedList();

    rmRef_h* first;

    int size;

    void add_end(char*,int,int);

    void del_by_key(char *);

    void print();

    bool searchKey(char *);

    rmRef_h& get_rmRef(char *);
};


#endif //RMLIB_LIST_H
