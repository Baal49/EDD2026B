/*
 ============================================================================
 NOMBRE      : grimorio_pilas.cpp
 DESCRIPCIÓN : Grimorio de Pilas (LIFO) con funciones de prueba (main)
               Implementado desde cero sin librerías de la STL.
 ============================================================================
*/
#include <iostream>
#include "estructuras.h"

// --- Ejercicios del Grimorio ---

// Ejercicio 1: Insertar sin duplicados
void insertarSinDuplicados(Pila<int>& p, int valor) {
    Pila<int> aux;
    bool existe = false;
    while (!p.isEmpty()) {
        int actual = p.pop();
        if (actual == valor) existe = true;
        aux.push(actual);
    }
    if (!existe) p.push(valor);
    while (!aux.isEmpty()) {
        p.push(aux.pop());
    }
}

// Ejercicio 2: Eliminar todas las ocurrencias de X
void eliminarElemento(Pila<int>& p, int x) {
    Pila<int> aux;
    while (!p.isEmpty()) {
        int actual = p.pop();
        if (actual != x) aux.push(actual);
    }
    while (!aux.isEmpty()) {
        p.push(aux.pop());
    }
}

// Ejercicio 3: Combinar dos pilas ordenadas
void combinarOrdenado(Pila<int>& p1, Pila<int>& p2, Pila<int>& resultado) {
    Pila<int> temp;
    while (!p1.isEmpty() && !p2.isEmpty()) {
        if (p1.getTop() > p2.getTop()) temp.push(p1.pop());
        else temp.push(p2.pop());
    }
    while (!p1.isEmpty()) temp.push(p1.pop());
    while (!p2.isEmpty()) temp.push(p2.pop());
    while (!temp.isEmpty()) resultado.push(temp.pop());
}

// Ejercicio 4: Ordenar una pila (menor en el tope)
void ordenarPila(Pila<int>& p) {
    Pila<int> aux;
    while (!p.isEmpty()) {
        int actual = p.pop();
        while (!aux.isEmpty() && aux.getTop() > actual) {
            p.push(aux.pop());
        }
        aux.push(actual);
    }
    while (!aux.isEmpty()) {
        p.push(aux.pop());
    }
}

// Ejercicio 5: Invertir con inserción en el fondo (Recursivo)
void insertarEnFondo(Pila<int>& p, int valor) {
    if (p.isEmpty()) {
        p.push(valor);
        return;
    }
    int temp = p.pop();
    insertarEnFondo(p, valor);
    p.push(temp);
}

void invertirConPila(Pila<int>& p) {
    if (!p.isEmpty()) {
        int actual = p.pop();
        invertirConPila(p);
        insertarEnFondo(p, actual);
    }
}

// Ejercicio 6: Invertir usando Cola auxiliar
void invertirConColaAux(Pila<int>& p, Cola<int>& c) {
    while (!p.isEmpty()) c.push(p.pop());
    while (!c.isEmpty()) p.push(c.pop());
}

// Ejercicio 7: Intercalar Pila y Cola
void intercalarPilaCola(Pila<int>& p, Cola<int>& c, Pila<int>& resultado) {
    while (!p.isEmpty() || !c.isEmpty()) {
        if (!p.isEmpty()) resultado.push(p.pop());
        if (!c.isEmpty()) resultado.push(c.pop());
    }
}

// Ejercicio 8: Verificar balanceo de símbolos
bool verificarBalanceo(const char* expresion) {
    Pila<char> p;
    for (int i = 0; expresion[i] != '\0'; i++) {
        char c = expresion[i];
        if (c == '(' || c == '[' || c == '{') {
            p.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (p.isEmpty()) return false;
            char topeC = p.pop();
            if ((c == ')' && topeC != '(') ||
                (c == ']' && topeC != '[') ||
                (c == '}' && topeC != '{')) return false;
        }
    }
    return p.isEmpty();
}

// Ejercicio 9: Evaluar expresión Postfija
int evaluarPostfija(const char* expresion) {
    Pila<int> p;
    for (int i = 0; expresion[i] != '\0'; i++) {
        char c = expresion[i];
        if (c >= '0' && c <= '9') {
            p.push(c - '0');
        } else {
            int op2 = p.pop();
            int op1 = p.pop();
            if (c == '+') p.push(op1 + op2);
            else if (c == '-') p.push(op1 - op2);
            else if (c == '*') p.push(op1 * op2);
            else if (c == '/') p.push(op1 / op2);
        }
    }
    return p.pop();
}

// Ejercicio 10: Historial web con límite
void insertarHistorial(Pila<int>& p, int urlID, int limite) {
    if (p.getSize() >= limite) {
        Pila<int> aux;
        while (p.getSize() > 1) aux.push(p.pop());
        p.pop(); // Borra el fondo
        while (!aux.isEmpty()) p.push(aux.pop());
    }
    p.push(urlID);
}

// Ejercicio 11: Búsqueda Binaria sobre Pila
bool busquedaBinariaPila(Pila<int>& p, int buscado, int limiteInferior, int limiteSuperior) {
    if (limiteInferior > limiteSuperior) return false;
    int mitad = limiteInferior + (limiteSuperior - limiteInferior) / 2;
    Pila<int> aux;
    int valorMitad = -1;
    for (int i = limiteInferior; i <= mitad && !p.isEmpty(); i++) {
        valorMitad = p.pop();
        aux.push(valorMitad);
    }
    bool encontrado = false;
    if (valorMitad == buscado) {
        encontrado = true;
    } else {
        while (!aux.isEmpty()) p.push(aux.pop());
        if (buscado < valorMitad) encontrado = busquedaBinariaPila(p, buscado, limiteInferior, mitad - 1);
        else encontrado = busquedaBinariaPila(p, buscado, mitad + 1, limiteSuperior);
        return encontrado;
    }
    while (!aux.isEmpty()) p.push(aux.pop());
    return encontrado;
}

// --- Función para imprimir Pila de prueba ---
void imprimirPila(Pila<int>& p) {
    std::cout << "[Tope] -> ";
    Pila<int> aux;
    while (!p.isEmpty()) {
        int val = p.pop();
        std::cout << val << " -> ";
        aux.push(val);
    }
    std::cout << "NULL\n";
    while(!aux.isEmpty()){
        p.push(aux.pop());
    }
}

// --- MAIN DE PRUEBAS ---
int main() {
    std::cout << "========= PRUEBAS GRIMORIO PILAS =========\n\n";

    // Prueba 1: Insertar sin duplicados
    Pila<int> p1;
    p1.push(1); p1.push(2); p1.push(3);
    std::cout << "P1 Original: "; imprimirPila(p1);
    insertarSinDuplicados(p1, 2);
    std::cout << "Intentando insertar 2 duplicado: "; imprimirPila(p1);
    insertarSinDuplicados(p1, 4);
    std::cout << "Intentando insertar 4 unico:     "; imprimirPila(p1);
    std::cout << "\n";

    // Prueba 2: Eliminar elemento
    std::cout << "Eliminando el elemento 2 de P1:\n";
    eliminarElemento(p1, 2);
    imprimirPila(p1);
    std::cout << "\n";

    // Prueba 3: Combinar ordenado
    Pila<int> po1, po2, resCombinado;
    po1.push(5); po1.push(3); // po1: [3, 5]
    po2.push(6); po2.push(2); // po2: [2, 6]
    std::cout << "PO1 Ordenada: "; imprimirPila(po1);
    std::cout << "PO2 Ordenada: "; imprimirPila(po2);
    combinarOrdenado(po1, po2, resCombinado);
    std::cout << "Resultado Combinado Ascendente: "; imprimirPila(resCombinado);
    std::cout << "\n";

    // Prueba 4: Ordenar Pila
    Pila<int> pDesordenada;
    pDesordenada.push(4); pDesordenada.push(1); pDesordenada.push(5);
    std::cout << "Pila Desordenada: "; imprimirPila(pDesordenada);
    ordenarPila(pDesordenada);
    std::cout << "Pila Ordenada (Menor en Tope): "; imprimirPila(pDesordenada);
    std::cout << "\n";

    // Prueba 5: Invertir Recursivo
    std::cout << "Invirtiendo Pila ordenada de forma recursiva:\n";
    invertirConPila(pDesordenada);
    imprimirPila(pDesordenada);
    std::cout << "\n";

    // Prueba 8: Balanceo de símbolos
    const char* expValida = "{[()]}";
    const char* expInvalida = "{[(])}";
    std::cout << "Verificar '" << expValida << "': " << (verificarBalanceo(expValida) ? "BALANCEADO" : "ERROR") << "\n";
    std::cout << "Verificar '" << expInvalida << "': " << (verificarBalanceo(expInvalida) ? "BALANCEADO" : "ERROR") << "\n";
    std::cout << "\n";

    // Prueba 9: Evaluar Postfija
    const char* postfija = "34+2*";
    std::cout << "Evaluar postfija '34+2*' ((3+4)*2): " << evaluarPostfija(postfija) << "\n\n";

    // Prueba 10: Historial con límite
    Pila<int> hist;
    std::cout << "Insertando en historial con limite 3:\n";
    insertarHistorial(hist, 10, 3);
    insertarHistorial(hist, 20, 3);
    insertarHistorial(hist, 30, 3);
    imprimirPila(hist);
    std::cout << "Insertando URL 40 (debe borrar el fondo '10'):\n";
    insertarHistorial(hist, 40, 3);
    imprimirPila(hist);
    std::cout << "\n";

    // Prueba 11: Busqueda Binaria en Pila
    Pila<int> pBusqueda;
    pBusqueda.push(50); pBusqueda.push(40); pBusqueda.push(30); pBusqueda.push(20); pBusqueda.push(10);
    std::cout << "Pila para Busqueda Binaria: "; imprimirPila(pBusqueda);
    std::cout << "Buscando 40: " << (busquedaBinariaPila(pBusqueda, 40, 0, 4) ? "ENCONTRADO" : "NO ENCONTRADO") << "\n";
    std::cout << "Buscando 15: " << (busquedaBinariaPila(pBusqueda, 15, 0, 4) ? "ENCONTRADO" : "NO ENCONTRADO") << "\n";

    std::cout << "\n===========================================\n";
    return 0;
}
