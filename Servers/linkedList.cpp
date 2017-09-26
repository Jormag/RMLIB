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
void linkedList<T>::add_end(T data_)
{
    Node<T> *new_node = new Node<T> (data_);
    Node<T> *temp = first;

    if (!first) {
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
    Node<T> *temp = first;
    Node<T> *temp1 = first->next;

    int cont = 0;

    if (first->data == data_) {
        first = temp->next;
    } else {
        while (temp1) {
            if (temp1->data == data_) {
                Node<T> *aux_node = temp1;
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
    Node<T> *temp = first;
    Node<T> *temp1 = temp->next;

    if (pos < 1 || pos > size) {
        cout << "Fuera de rango " << endl;
    } else if (pos == 1) {
        first = temp->next;
    } else {
        for (int i = 2; i <= pos; i++) {
            if (i == pos) {
                Node<T> *aux_node = temp1;
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
    Node<T> *temp = first;
    if (!first) {
        cout << "La Lista está vacía " << endl;
    } else {
        while (temp) {
            temp->print();
            if (!temp->next) cout << "NULL";
            temp = temp->next;
        }
    }
    cout << endl << endl;
}

// Buscar el dato de un nodo
template<typename T>
void linkedList<T>::search(T data_)
{
    Node<T> *temp = first;
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