//
// Created by cristian on 27/09/17.
//

#ifndef RMLIB_RMREF_H_H
#define RMLIB_RMREF_H_H

#include <iostream>

using namespace std;


class rmRef_h {
public:
    rmRef_h();
    void printValues();
    ~rmRef_h();

    rmRef_h* next;
    int data;
    char* key;
    int data_size;

    bool operator==(const rmRef_h& target);
    bool operator!=(const rmRef_h& target);
    rmRef_h& operator=(const rmRef_h& target);
};


#endif //RMLIB_RMREF_H_H
