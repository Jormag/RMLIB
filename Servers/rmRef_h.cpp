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

template<typename T>
void rmRef_h<T>::printValues()
{
    cout << "Key " << key << endl;
    cout << "Data " << data << endl;
    cout << "Data_size " << data_size << endl;
}


template<typename T>
rmRef_h<T>::~rmRef_h() {}
