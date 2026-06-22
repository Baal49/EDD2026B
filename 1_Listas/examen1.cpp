/*Programar una funcion que reciba dos heads de diferentes listas
doble enlazadas y devuelva el head de la fusion de ambas listas en 
orden de  menor a mayor eliminando duplicados
*/

#include <iostream>
#include "listas.h"

using namespace std;

template <typename T>
Nododoble<T>* fusion_heads(ListaDobleEnlazada<T>* head, ListaDobleEnlazada<T>* head2){
    
    Nododoble<T>* actual = head;
    Nododoble<T>* nodoactual = head;
    Nododoble<T>* tail1 = nullptr;
    T cambio = nullptr;
    T cambio2 = nullptr;

    while(nodoactual->getSiguiente() != nullptr){
        nodoactual = nodoactual->getSiguiente();
    }
    nodoactual->setSiguiente(head2);

    while(actual != nullptr){
        Nododoble<T>* siguientetemp = actual->getSiguiente();

        if(actual->getDato() > siguientetemp->getDato()){
            cambio = siguientetemp->getDato();
            cambio2 = actual->getdato();
            actual->setdato(cambio);
            siguientetemp->setDato(cambio2);
        }else if(actual->getDato() == siguientetemp->getdato()){
            siguientetemp->setAnterior(nullptr);
            siguientetemp->setSiguiente(nullptr);
        }
        
    }
    return head;
}
