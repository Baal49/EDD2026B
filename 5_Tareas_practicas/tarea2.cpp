/*crear una cola de prioridad donde los datos se procesan de la siguiente forma:
0-> prioridad maxima
5->prioridad minima
crear implementacion con listas y arreglos
*/

#include <iostream>

using namespace std;

#include "estructuras.h"
#include <iostream>

using namespace std;

template <typename T>
class ColaPrioridadLista {
private:
    struct Elemento {
        T dato;
        int prioridad;
        Elemento() : prioridad(0) {}
        Elemento(T d, int p) : dato(d), prioridad(p) {}
    };

    NodoSimple<Elemento>* cabeza;
    int sizeTotal;

public:
    ColaPrioridadLista() {
        cabeza = nullptr;
        sizeTotal = 0;
    }

    void push(T dato, int prioridad) {
        Elemento nuevoElemento(dato, prioridad);
        NodoSimple<Elemento>* nuevoNodo = new NodoSimple<Elemento>(nuevoElemento);

        if (cabeza == nullptr || prioridad < cabeza->getDato().prioridad) {
            nuevoNodo->setSiguiente(cabeza);
            cabeza = nuevoNodo;
        } else {
            NodoSimple<Elemento>* actual = cabeza;
            while (actual->getSiguiente() != nullptr && 
                   actual->getSiguiente()->getDato().prioridad <= prioridad) {
                actual = actual->getSiguiente();
            }
            nuevoNodo->setSiguiente(actual->getSiguiente());
            actual->setSiguiente(nuevoNodo);
        }
        sizeTotal++;
    }

    T pop() {
        if (cabeza == nullptr) {
            cout << "Cola de prioridad vacia" << endl;
            return T();
        }
        NodoSimple<Elemento>* temp = cabeza;
        T valor = temp->getDato().dato;
        
        cabeza = cabeza->getSiguiente();
        delete temp;
        sizeTotal--;
        return valor;
    }

    int getSize() const { return sizeTotal; }
    bool estaVacia() const { return cabeza == nullptr; }

    void mostrar() const {
        NodoSimple<Elemento>* actual = cabeza;
        while (actual != nullptr) {
            cout << "[Dato: " << actual->getDato().dato 
                 << " | Prioridad: " << actual->getDato().prioridad << "] -> ";
            actual = actual->getSiguiente();
        }
        cout << "NULL\n";
    }

    ~ColaPrioridadLista() {
        while (cabeza != nullptr) {
            NodoSimple<Elemento>* temp = cabeza;
            cabeza = cabeza->getSiguiente();
            delete temp;
        }
    }
};



template <typename T>
class ColaPrioridadArreglo {
private:
    Cola<T>** tabla;      // Doble puntero: apunta a un arreglo de punteros a Cola
    int maxPrioridades;   // Cantidad de niveles definidos por ti en el ejercicio
    int sizeTotal;

public:
    // El constructor reserva el arreglo de punteros e inicializa cada uno con 'new'
    ColaPrioridadArreglo(int nivelesPrioridad) {
        maxPrioridades = nivelesPrioridad;
        sizeTotal = 0;
        
        // 1. Creamos el arreglo dinámico que contendrá punteros (Cola<T>*)
        tabla = new Cola<T>*[maxPrioridades]; 
        
        // 2. Inicializamos cada puntero creando el objeto real de la Cola en el Heap
        for (int i = 0; i < maxPrioridades; i++) {
            tabla[i] = new Cola<T>(); 
        }
    }

    // Inserta usando el operador flecha (->) ya que accedemos mediante un puntero en la celda
    void push(T dato, int prioridad) {
        if (prioridad < 0 || prioridad >= maxPrioridades) {
            cout << "Error: Prioridad " << prioridad << " fuera del rango configurado.\n";
            return;
        }
        tabla[prioridad]->push(dato); // Usa el método push() de tu clase Cola
        sizeTotal++;
    }

    // Extrae buscando secuencialmente desde el índice 0 en adelante
    T pop() {
        for (int i = 0; i < maxPrioridades; i++) {
            if (tabla[i]->getSize() > 0) { // Usa el método getSize() de tu clase Cola
                sizeTotal--;
                return tabla[i]->pop();    // Usa el método pop() de tu clase Cola
            }
        }
        cout << "Cola de prioridad vacia" << endl;
        return T();
    }

    int getSize() const { return sizeTotal; }
    bool estaVacia() const { return sizeTotal == 0; }

    void mostrar() const {
        for (int i = 0; i < maxPrioridades; i++) {
            cout << "Prioridad [" << i << "] -> ";
            int sizeActual = tabla[i]->getSize();
            for (int j = 0; j < sizeActual; j++) {
                T temp = tabla[i]->pop();
                cout << temp << "->";
                tabla[i]->push(temp);
            }
            cout << "NULL\n";
        }
    }

    // Destructor: Al usar doble puntero, liberar la memoria requiere el proceso inverso al constructor
    ~ColaPrioridadArreglo() {
        // 1. Eliminamos primero cada objeto Cola creado individualmente
        for (int i = 0; i < maxPrioridades; i++) {
            delete tabla[i]; 
        }
        // 2. Eliminamos finalmente el arreglo contenedor de punteros
        delete[] tabla; 
    }
};

int main() {
    ColaPrioridadLista<int> copLista;
    copLista.push(10, 2);
    copLista.push(20, 1);
    copLista.push(30, 3);
    copLista.push(40, 0);
    copLista.push(50, 4);
    copLista.push(60, 2);
    cout << "Cola de Prioridad como Lista:\n";
    copLista.mostrar();
    cout << "Pop: " << copLista.pop() << endl;
    ColaPrioridadArreglo<int> copArreglo(5);
    copArreglo.push(10, 2);
    copArreglo.push(20, 1);
    copArreglo.push(30, 3);
    copArreglo.push(40, 0);
    copArreglo.push(50, 4);
    copArreglo.push(60, 2);
    cout << "\nCola de Prioridad como Arreglo:\n";
    copArreglo.mostrar();
    cout << "Pop: " << copArreglo.pop() << endl;
    return 0;
}