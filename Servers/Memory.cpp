//
// Created by cristian on 25/09/17.
//

#include "Memory.h"
// Constructor por defecto

Memory::Memory(){
    cache = linkedList();
    ram = linkedList();
}
Memory::~Memory(){}
