/*
 ============================================================================
 NOMBRE      : grimorio_colas_prioridad.cpp
 DESCRIPCIÓN : Grimorio de Colas de Prioridad utilizando estructura_CoP.h
               Implementación limpia 100% usando la sobrecarga pop(int&)
 ============================================================================
*/
#include <iostream>
#include "estructura_CoP.h"

using namespace std;

// --- Ejercicio 1 (Variante A): Inserción restringida en Arreglo de Colas ---
void insertarArregloUnico(ColaPrioridadArreglo<int>& ac, int idProceso, int prio, int maxPrio) {
    ColaPrioridadArreglo<int> aux(maxPrio);
    bool existe = false;

    // Vaciar y buscar duplicados extrayendo dato y prioridad simultáneamente
    while (!ac.estaVacia()) {
        int prioOriginal;
        int actual = ac.pop2(prioOriginal); 
        if (actual == idProceso) existe = true;
        aux.push(actual, prioOriginal);
    }

    if (!existe) {
        ac.push(idProceso, prio);
    }

    // Restaurar estructura original
    while (!aux.estaVacia()) {
        int prioOriginal;
        int temp = aux.pop2(prioOriginal);
        ac.push(temp, prioOriginal);
    }
}

// --- Ejercicio 1 (Variante B): Inserción restringida en Lista Enlazada ---
void insertarListaUnico(ColaPrioridadLista<int>& cl, int idProceso, int prio) {
    ColaPrioridadLista<int> aux;
    bool existe = false;

    while (!cl.estaVacia()) {
        int prioOriginal;
        int actual = cl.pop2(prioOriginal);
        if (actual == idProceso) existe = true;
        aux.push(actual, prioOriginal);
    }

    if (!existe) {
        cl.push(idProceso, prio);
    }

    while (!aux.estaVacia()) {
        int prioOriginal;
        int temp = aux.pop2(prioOriginal);
        cl.push(temp, prioOriginal);
    }
}

// --- Ejercicio 2: Atender/Extraer ---
// Nota: Resuelto de forma nativa e inmediata invocando el método .pop() de tus clases.

// --- Ejercicio 3 (Variante A): Invertir Criterio de Prioridad (Arreglo) ---
void invertirCriterioArreglo(ColaPrioridadArreglo<int>& ac, int maxPrio) {
    ColaPrioridadArreglo<int> aux(maxPrio);
    
    while (!ac.estaVacia()) {
        int prioOriginal;
        int actual = ac.pop2(prioOriginal);
        
        // Invertimos restando la prioridad actual al máximo permitido (ej. Prio 4 pasa a ser 0)
        int nuevaPrio = (maxPrio - 1) - prioOriginal;
        aux.push(actual, nuevaPrio);
    }
    
    while (!aux.estaVacia()) {
        int prioOriginal;
        int temp = aux.pop2(prioOriginal);
        ac.push(temp, prioOriginal);
    }
}

// --- Ejercicio 3 (Variante B): Invertir Criterio Reestructurando (Lista) ---
void invertirCriterioLista(ColaPrioridadLista<int>& cl) {
    ColaPrioridadLista<int> aux;
    
    while (!cl.estaVacia()) {
        int prioOriginal;
        int actual = cl.pop2(prioOriginal);
        
        // Como la lista opera como un Min-Heap (menor número = se atiende primero),
        // Invertimos convirtiendo la prioridad a su equivalente negativo.
        int nuevaPrio = -prioOriginal;
        aux.push(actual, nuevaPrio);
    }
    
    while (!aux.estaVacia()) {
        int prioOriginal;   
        int temp = aux.pop2(prioOriginal);
        cl.push(temp, prioOriginal);
    }
}

// --- Ejercicio 4: Fusión de Sistemas de Triage Hospitalario (Lista Enlazada) ---
void fusionarTriages(ColaPrioridadLista<int>& l1, ColaPrioridadLista<int>& l2) {
    while (!l2.estaVacia()) {
        int prioOriginal;
        int actual = l2.pop2(prioOriginal);
        insertarListaUnico(l1, actual, prioOriginal);
    }
}

// --- Ejercicio 5: Lógica Conceptual del Árbol de Frecuencias de Huffman ---
void simularHuffman(ColaPrioridadLista<int>& cl) {
    // El algoritmo de Huffman extrae siempre las frecuencias MÍNIMAS y las suma.
    while (cl.getSize() > 1) {
        int prio1, prio2;
        int frec1 = cl.pop2(prio1); 
        int frec2 = cl.pop2(prio2);
        
        int suma = prio1 + prio2;
        // Reinsertamos el nodo combinado, donde el dato y la prioridad son la suma de frecuencias
        insertarListaUnico(cl, suma, suma);
    }
}

// --- MAIN DE PRUEBAS ---
int main() {
    cout << "========= PRUEBAS GRIMORIO COLAS DE PRIORIDAD =========\n\n";

    // ----------------------------------------------------
    // PRUEBAS VARIANTE A: ARREGLO DE COLAS ESTÁTICAS
    // ----------------------------------------------------
    cout << "--- PRUEBAS VARIANTE A (Arreglo de Colas) ---\n";
    int maxPrio = 5;
    ColaPrioridadArreglo<int> ac(maxPrio);
    
    insertarArregloUnico(ac, 500, 1, maxPrio); // ID 500, Prio 1
    insertarArregloUnico(ac, 900, 4, maxPrio); // ID 900, Prio 4
    insertarArregloUnico(ac, 300, 4, maxPrio); // ID 300, Prio 4
    insertarArregloUnico(ac, 900, 4, maxPrio); // Duplicado omitido

    cout << "Estado Arreglo (Prio 0 es mas alta):\n";
    ac.mostrar();
    
    cout << "\nExtrayendo prioritarios (Menor indice sale primero):\n";
    int pRescatada;
    cout << "Atendido: ID " << ac.pop2(pRescatada) << " (Prioridad Original: " << pRescatada << ")\n";
    cout << "Atendido: ID " << ac.pop2(pRescatada) << " (Prioridad Original: " << pRescatada << ")\n";

    // Invertir criterio
    insertarArregloUnico(ac, 900, 4, maxPrio); // Re-insertamos para test
    invertirCriterioArreglo(ac, maxPrio);
    cout << "\nDespues de invertir criterio (Las prioridades se voltean):\n";
    ac.mostrar();
    cout << "Atendido: ID " << ac.pop2(pRescatada) << " (Nueva Prioridad: " << pRescatada << ")\n\n";

    // ----------------------------------------------------
    // PRUEBAS VARIANTE B: LISTA ENLAZADA ORDENADA
    // ----------------------------------------------------
    cout << "--- PRUEBAS VARIANTE B (Lista Enlazada Ordenada) ---\n";
    ColaPrioridadLista<int> cl;
    insertarListaUnico(cl, 10, 2);
    insertarListaUnico(cl, 20, 4);
    insertarListaUnico(cl, 30, 1);
    insertarListaUnico(cl, 20, 4); // Duplicado omitido
    
    cout << "Lista de Prioridad (Min Prioridad Primero nativo):\n";
    cl.mostrar();

    // Invertir Criterio
    cout << "Invirtiendo criterio fisicamente (Prioridades en negativo):\n";
    invertirCriterioLista(cl);
    cl.mostrar();
    cout << "\n";

    // Prueba Triage Hospitalario
    cout << "--- Prueba Fusion Triage Hospitalario ---\n";
    ColaPrioridadLista<int> triage1, triage2;
    insertarListaUnico(triage1, 101, 1); // Paciente Critico
    insertarListaUnico(triage1, 102, 5); // Paciente Leve
    insertarListaUnico(triage2, 201, 3); // Paciente Moderado
    
    cout << "Triage Isla 1:\n"; triage1.mostrar();
    cout << "Triage Isla 2:\n"; triage2.mostrar();
    fusionarTriages(triage1, triage2);
    cout << "Sistemas de Triage Unificados:\n"; triage1.mostrar();
    cout << "\n";

    // Prueba Simulación Huffman
    cout << "--- Prueba Conceptual Huffman ---\n";
    ColaPrioridadLista<int> huffmanList;
    insertarListaUnico(huffmanList, 5, 5);   // Frecuencia 5
    insertarListaUnico(huffmanList, 7, 7);   // Frecuencia 7
    insertarListaUnico(huffmanList, 10, 10); // Frecuencia 10
    
    cout << "Frecuencias iniciales:\n"; huffmanList.mostrar();
    simularHuffman(huffmanList);
    cout << "Despues de simular combinaciones de Huffman (Raiz acumulada):\n"; 
    huffmanList.mostrar();

    cout << "\n===========================================\n";
    return 0;
}