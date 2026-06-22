#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <iostream>

using namespace std;

template <typename T>
class NodoSimple{
    private:
        T dato;
        NodoSimple<T>* siguiente;
    public:
        NodoSimple(T valor){
            dato = valor;
            siguiente = nullptr;
        }
        T getDato(){
            return dato;
        }
        NodoSimple<T>* getSiguiente(){
            return siguiente;
        }
        void setSiguiente(NodoSimple<T>* nodo){
            siguiente = nodo;
        }
};

template <typename T>
class Pila{
    private:
        NodoSimple<T>* top;
        int size;
    public:
        Pila(){
            top = nullptr;
            size = 0;
        }
        void push(T valor){
            NodoSimple<T>* nuevoNodo = new NodoSimple<T>(valor);
            nuevoNodo->setSiguiente(top);
            top = nuevoNodo;
            size++;
        }
        T pop(){
            if(top == nullptr){
                cout << "Pila vacia" << endl;
                return T();
            }
            T valor = top->getDato();
            NodoSimple<T>* temp = top;
            top = top->getSiguiente();
            delete temp;
            size--;
            return valor;
        }
        int getSize(){
            return size;
        }
        ~Pila(){
            while(top != nullptr){
                NodoSimple<T>* temp = top;
                top = top->getSiguiente();
                delete temp;
            }
        }
};

template<typename T>
class Cola{
    private:
    NodoSimple<T>* head;
    NodoSimple<T>* tail;
    int size;
    public:
    Cola(){
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    void push(T valor){
        NodoSimple<T>* nuevonodo = new NodoSimple<T>(valor);
        if(head == nullptr){
            head = nuevonodo;
            tail = nuevonodo;
        } else {
            tail->setSiguiente(nuevonodo);
            tail = nuevonodo;
        }
        size++;
    }
    T pop(){
        if(head == nullptr){
            cout << "Cola vacia" << endl;
            return T(); 
        }
        T valor = head->getDato();
        NodoSimple<T>* temp = head;
        head = head->getSiguiente();
        delete temp;
        size--;
        return valor;
    }
    int getSize(){
        return size;
    }

    ~Cola(){
        while(head != nullptr){
            NodoSimple<T>* temp = head;
            head = head->getSiguiente();
            delete temp;
        }
    }
};

#endif // ESTRUCTURAS_H