//
// Created by cristian on 25/09/17.
//

#include "Memory.h"
// Constructor por defecto
template<typename T>
Memory<T>::Memory(){
    cache = linkedList<T>();
    ram = linkedList<T>();
}
template<typename T>
Memory<T>::~Memory(){}
