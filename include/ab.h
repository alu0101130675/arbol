#pragma once
#include "nodoB.h"
#include "cola.h"
#include <vector>
#include <iostream>

using namespace std;

#ifndef AB
#define AB

template <class Clave>
class Arbol {
  private:
    NodoB<Clave>* raiz;
  public:
    Arbol();
    NodoB<Clave>* Buscar(Clave& x)=0
    NodoB<Clave>* BuscarRama(NodoB<Clave>* nodo, Clave dato)=0
    void Insertar(const Clave& x)=0;
    void InsertarRama(NodoB<Clave>* &nodo, Clave dato)=0;
    void write()=0;
};
#endif