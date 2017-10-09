//
// Created by cristian on 27/09/17.
//

#include "rmRef_h.h"
template<typename T>
rmRef_h<T>::rmRef_h() {
    key = NULL;
    data = NULL;
    next = NULL;
    data_size = 0;
}

/*
template<typename T>
rmRef_h<T>::rmRef_h(const char* key_,T data_,int data_size_) {
    key = key_;
    data = data_;
    data_size = data_size_;
    next = NULL;
}
 */
template<typename T>
rmRef_h<T>::~rmRef_h() {}
