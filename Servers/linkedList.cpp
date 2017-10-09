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
void linkedList<T>::add_end(const char* key_,T data_,int data_size_)
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
void linkedList<T>::del_by_data(T data_)
{
    rmRef_h<T>* temp = first;
    rmRef_h<T>* temp1 = first->next;

    int cont = 0;

    if (first->data == data_) {
        first = temp->next;
    } else {
        while (temp1) {
            if (temp1->data == data_) {
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
        cout << "No existe el dato " << endl;
    }
}

// Eliminar por posición del nodo
template<typename T>
void linkedList<T>::del_by_position(int pos)
{
    rmRef_h<T> *temp = first;
    rmRef_h<T> *temp1 = temp->next;

    if (pos < 1 || pos > size) {
        cout << "Fuera de rango " << endl;
    } else if (pos == 1) {
        first = temp->next;
    } else {
        for (int i = 2; i <= pos; i++) {
            if (i == pos) {
                rmRef_h<T> *aux_node = temp1;
                temp->next = temp1->next;
                delete aux_node;
                size--;
            }
            temp = temp->next;
            temp1 = temp1->next;
        }
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
void linkedList<T>::search(T data_)
{
    rmRef_h<T> *temp = first;
    int cont = 1;
    int cont2 = 0;

    while (temp) {
        if (temp->data == data_) {
            cout << "El dato se encuentra en la posición: " << cont << endl;
            cont2++;
        }
        temp = temp->next;
        cont++;
    }

    if (cont2 == 0) {
        cout << "No existe el dato " << endl;
    }
    cout << endl << endl;
}


template<typename T>
linkedList<T>::~linkedList() {}