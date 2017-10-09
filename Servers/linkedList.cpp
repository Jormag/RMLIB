#include "linkedList.h"

using namespace std;

// Constructor por defecto
template<typename T>
linkedList<T>::linkedList()
{
    size = 0;
    first = NULL;
}

// Insertar al final
template<typename T>
void linkedList<T>::add_end(char* key_,T data_,int data_size_)
{
    rmRef_h<T>* temp = first;
    rmRef_h<T>* new_node = new rmRef_h<T> ();
    new_node->data = data_;
    new_node->key = key_;
    new_node->data_size = data_size_;

    if (size==0) {
        first = new_node;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    size++;
}



// Eliminar por data del nodo
template<typename T>
void linkedList<T>::del_by_key(char *key_)
{
    rmRef_h<T>* temp = first;
    rmRef_h<T>* temp1 = first->next;

    int cont = 0;

    if (first->key == key_) {
        first = temp->next;
    } else {
        while (temp1) {
            if (temp1->key == key_) {
                rmRef_h<T>* aux_node = temp1;
                temp->next = temp1->next;
                delete aux_node;
                cont++;
                size--;
            }
            temp = temp->next;
            temp1 = temp1->next;
        }
    }

    if (cont == 0) {
        cout << "The key doesn't exist " << endl;
    }
}

// Imprimir la Lista
template<typename T>
void linkedList<T>::print()
{
    rmRef_h<T>* temp = first;

    if (first == NULL) {
        cout << "La Lista está vacía " << endl;
    } else {
        while (temp != NULL) {
            cout << temp->data << "-> ";
            if (temp->next == NULL){
                cout << "NULL";
            }
            temp = temp->next;
        }
    }
    cout << endl << endl;
}

// Buscar el dato de un nodo
template<typename T>
bool linkedList<T>::searchKey(char* key_)
{
    rmRef_h<T>* temp = first;
    bool entry;
    entry = false;

    while (temp!= NULL) {

        if (string(temp->key).compare(string(key_)) == 0){
            entry = true;
            temp = temp->next;
        }
        else{
            temp = temp->next;
        }
    }

    return entry;
}

template<typename T>
rmRef_h<T>* linkedList<T>::get_nodo(char* key_)
{
    rmRef_h<T>* temp = first;

    while (temp!= NULL) {
        if (string(temp->key).compare(string(key_)) == 0){
            break;
        }else if (temp->next == NULL){
            cout << "The key doesn't in use" << endl;
            temp = temp->next;
        }
        else{
            temp = temp->next;
        }
    }
    return temp;
}


template<typename T>
linkedList<T>::~linkedList() {}