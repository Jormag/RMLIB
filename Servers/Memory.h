//
// Created by cristian on 25/09/17.
//

#ifndef RMLIB_MEMORY_H
#define RMLIB_MEMORY_H

#include <iostream>
#include "linkedList.cpp"
class Memory {
public:
    linkedList cache;
    linkedList ram;

    Memory();
    ~Memory();
};


#endif //RMLIB_MEMORY_H
