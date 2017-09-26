//
// Created by cristian on 25/09/17.
//

#ifndef RMLIB_MEMORY_H
#define RMLIB_MEMORY_H

#include <iostream>
#include "linkedList.cpp"

template <class T>

class Memory {
public:
    linkedList<T> cache;
    linkedList<T> ram;

    Memory();
    ~Memory();
};


#endif //RMLIB_MEMORY_H
