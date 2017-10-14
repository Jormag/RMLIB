#include "linkedList.h"

using namespace std;

// Constructor por defecto

linkedList::linkedList()
{
    size = 0;
    first = NULL;
}

// Insertar al final
void linkedList::add_end(char* key_,int data_,int data_size_)
{
    rmRef_h* temp = first;
    rmRef_h* new_node = new rmRef_h ();
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
void linkedList::del_by_key(char *key_)
{
    rmRef_h* temp = first;
    rmRef_h* temp1 = first->next;

    int cont = 0;

    if (first->key == key_) {
        first = temp->next;
    } else {
        while (temp1 != NULL) {
            if (temp1->key == key_) {
                rmRef_h* aux_node = temp1;
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
void linkedList::print()
{
    rmRef_h* temp = first;

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
bool linkedList::searchKey(char* key_)
{
    rmRef_h* temp = first;
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

rmRef_h& linkedList::get_rmRef(char *key_)
{
    rmRef_h* temp = first;

    while (temp!= NULL) {
        if (string(temp->key).compare(string(key_)) == 0){
            break;
        }
        else{
            temp = temp->next;
        }
    }
    return *temp;
}

linkedList::~linkedList() {}