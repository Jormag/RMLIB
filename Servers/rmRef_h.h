//
// Created by cristian on 27/09/17.
//

#ifndef RMLIB_RMREF_H_H
#define RMLIB_RMREF_H_H

#include <iostream>

using namespace std;

template <class T>
class rmRef_h {
public:
    rmRef_h();
    void printValues();
    ~rmRef_h();

    rmRef_h* next;
    T data;
    const char* key;
    int data_size;
};


#endif //RMLIB_RMREF_H_H
