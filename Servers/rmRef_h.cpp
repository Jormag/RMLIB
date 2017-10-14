//
// Created by cristian on 27/09/17.
//

#include "rmRef_h.h"

rmRef_h::rmRef_h() {
    key = NULL;
    data = 0;
    next = NULL;
    data_size = 0;
}

void rmRef_h::printValues()
{
    cout << "Key " << key << endl;
    cout << "Data " << data << endl;
    cout << "Data_size " << data_size << endl;
}

rmRef_h::~rmRef_h() {}

bool rmRef_h::operator==(const rmRef_h& target){
    bool result = false;
    if (this == &target){
        if (this->data != target.data){
            result = true;
        }
    }
    return result;
}

bool rmRef_h::operator!=(const rmRef_h& target){
    bool result = false;
    if (this != &target){
        if (this->data != target.data){
            result = true;
        }
    }
    return result;
}


rmRef_h& rmRef_h::operator=(const rmRef_h& target){
    if (this != &target){
        data = target.data;
        data_size =target.data_size;
    }
    return *this;
}