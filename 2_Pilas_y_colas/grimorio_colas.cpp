/*
 ============================================================================
 NOMBRE      : grimorio_colas.cpp
 DESCRIPCIÓN : Grimorio de Colas (FIFO) con funciones de prueba (main)
               Temática: Fila de Gasolineras. Sin librerías STL.
 ============================================================================
*/
#include <iostream>
#include "estructuras.h"

// --- Ejercicios del Grimorio ---

// Ejercicio 1: Insertar vehículo único (Gasolinera)
void insertarVehiculoUnico(Cola<int>& c, int matricula) {
    bool existe = false;
    int size = c.getSize();
    for (int i = 0; i < size; i++) {
        int actual = c.pop();
        if (actual == matricula) existe = true;
        c.push(actual);
    }
    if (!existe) c.push(matricula);
}

// Ejercicio 2: Salida por emergencia
void salidaEmergencia(Cola<int>& c, int matriculaBuscada) {
    int size = c.getSize();
    for (int i = 0; i < size; i++) {
        int actual = c.pop();
        if (actual != matriculaBuscada) c.push(actual);
    }
}

// Ejercicio 3: Combinar/fusionar dos islas ordenadas por año
void fusionarIslas(Cola<int>& c1, Cola<int>& c2, Cola<int>& resultado) {
    while (!c1.isEmpty() && !c2.isEmpty()) {
        if (c1.getFront() < c2.getFront()) resultado.push(c1.pop());
        else resultado.push(c2.pop());
    }
    while (!c1.isEmpty()) resultado.push(c1.pop());
    while (!c2.isEmpty()) resultado.push(c2.pop());
}

// Ejercicio 4: Ordenar cola por Selección (Año del modelo)
void ordenarColaGasolina(Cola<int>& c) {
    int size = c.getSize();
    for (int i = 0; i < size; i++) {
        int min_val = c.getFront();
        for (int j = 0; j < size - i; j++) {
            int actual = c.pop();
            if (actual < min_val) min_val = actual;
            c.push(actual);
        }
        int limite = size - i;
        for (int j = 0; j < limite; j++) {
            int actual = c.pop();
            if (actual != min_val) c.push(actual);
            else min_val = -1; // Bandera para no duplicar eliminaciones
        }
        c.push(min_val);
    }
}

// Ejercicio 5: Invertir orden usando Pila auxiliar
void invertirCola(Cola<int>& c, Pila<int>& auxPila) {
    while (!c.isEmpty()) auxPila.push(c.pop());
    while (!auxPila.isEmpty()) c.push(auxPila.pop());
}

// Ejercicio 6: Despacho Circular con límite de litros
void despachoCircular(Cola<int>& c, int litrosPorTurno) {
    int size = c.getSize();
    for (int i = 0; i < size; i++) {
        int necesidad = c.pop();
        if (necesidad > litrosPorTurno) {
            c.push(necesidad - litrosPorTurno);
        }
    }
}

// Ejercicio 7: Planificación Round-Robin
void roundRobin(Cola<int>& procesos, int quantum) {
    while (!procesos.isEmpty()) {
        int tiempo = procesos.pop();
        tiempo -= quantum;
        if (tiempo > 0) procesos.push(tiempo);
    }
}

// Ejercicio 8: Validar Palíndromo con Pila y Cola
bool esPalindromo(const char* palabra) {
    Pila<char> p; Cola<char> c;
    for (int i = 0; palabra[i] != '\0'; i++) {
        p.push(palabra[i]);
        c.push(palabra[i]);
    }
    while (!p.isEmpty() && !c.isEmpty()) {
        if (p.pop() != c.pop()) return false;
    }
    return true;
}

// --- Función para imprimir Cola de prueba ---
void imprimirCola(Cola<int>& c) {
    std::cout << "[Frente] -> ";
    int size = c.getSize();
    for(int i=0; i<size; i++){
        int val = c.pop();
        std::cout << val << " -> ";
        c.push(val);
    }
    std::cout << "[Final]\n";
}

// --- MAIN DE PRUEBAS ---
int main() {
    std::cout << "========= PRUEBAS GRIMORIO COLAS =========\n\n";

    // Prueba 1: Insertar único (Matrículas de autos)
    Cola<int> gasolinera;
    insertarVehiculoUnico(gasolinera, 101);
    insertarVehiculoUnico(gasolinera, 202);
    insertarVehiculoUnico(gasolinera, 101); // Duplicado intencional
    std::cout << "Fila de vehiculos (Evitando Placa 101 duplicada):\n";
    imprimirCola(gasolinera);
    std::cout << "\n";

    // Prueba 2: Salida por emergencia
    gasolinera.push(303);
    std::cout << "Antes de emergencia del 202: "; imprimirCola(gasolinera);
    salidaEmergencia(gasolinera, 202);
    std::cout << "Despues de emergencia:       "; imprimirCola(gasolinera);
    std::cout << "\n";

    // Prueba 3: Fusionar islas ordenadas (por año del carro)
    Cola<int> isla1, isla2, fusion;
    isla1.push(2010); isla1.push(2015);
    isla2.push(2012); isla2.push(2018);
    std::cout << "Isla 1: "; imprimirCola(isla1);
    std::cout << "Isla 2: "; imprimirCola(isla2);
    fusionarIslas(isla1, isla2, fusion);
    std::cout << "Islas Fusionadas de forma ordenada: "; imprimirCola(fusion);
    std::cout << "\n";

    // Prueba 4: Ordenar Cola Desordenada
    Cola<int> desordenada;
    desordenada.push(2016); desordenada.push(1998); desordenada.push(2023);
    std::cout << "Fila Desordenada: "; imprimirCola(desordenada);
    ordenarColaGasolina(desordenada);
    std::cout << "Fila Ordenada por Seleccion: "; imprimirCola(desordenada);
    std::cout << "\n";

    // Prueba 5: Invertir Cola
    Pila<int> pAux;
    std::cout << "Invirtiendo el orden de atencion de la fila ordenada:\n";
    invertirCola(desordenada, pAux);
    imprimirCola(desordenada);
    std::cout << "\n";

    // Prueba 6: Despacho circular con límite de litros
    Cola<int> necesidades;
    necesidades.push(40); // Auto 1 quiere 40L
    necesidades.push(15); // Auto 2 quiere 15L
    std::cout << "Necesidades iniciales de combustible (Litros): "; imprimirCola(necesidades);
    despachoCircular(necesidades, 20); // Turno max de 20 litros
    std::cout << "Despues de una ronda circular de maximo 20L:   "; imprimirCola(necesidades);
    std::cout << "\n";

    // Prueba 8: Validar Palíndromo
    const char* p1 = "reconocer";
    const char* p2 = "gasolina";
    std::cout << "Es palindromo '" << p1 << "': " << (esPalindromo(p1) ? "SI" : "NO") << "\n";
    std::cout << "Es palindromo '" << p2 << "': " << (esPalindromo(p2) ? "SI" : "NO") << "\n";

    std::cout << "\n===========================================\n";
    return 0;
}
