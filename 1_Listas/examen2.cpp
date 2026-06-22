/*
Realizar una funcion que devuelva el head de una lista simple invertida
(el algoritmo debe inveritr la lista de una sola pasada)
*/

#include <iostream>
# include "listas.h"

using namespace std;

template <typename T>
void reverse_simple(ListaEnlazada<T>& lista) {
    NodoSimple<T>* prev = nullptr;
    NodoSimple<T>* current = lista.head;
    NodoSimple<T>* next = nullptr;
    
    while (current != nullptr) {
        next = current->getSiguiente();
        current->setSiguiente(prev);    
        prev = current;                 
        current = next;                 
    }
    lista.head = prev;
}

int main(){
ListaEnlazada<int> original;
    original.agregar(5);
    original.agregar(3);
    original.agregar(8);
    original.agregar(1);
    original.agregar(7);

    cout << "Lista Original: ";
    original.imprimir();

    reverse_simple(original);
    cout << "invertir lista original: ";
    original.imprimir();
    return 0;
}