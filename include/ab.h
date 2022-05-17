#pragma once
#include "nodoB.h"
#include "cola.h"
#include <vector>
#include <iostream>

using namespace std;

#ifndef AB
#define AB

template <class Clave>
class Arbol
{
private:
  NodoB<Clave> *raiz;

public:
  virtual bool Buscar(const Clave &x) = 0;
  virtual bool Insertar(const Clave &x) = 0;
  virtual void eliminar(Clave x)=0;
  virtual void write() = 0;
  void inOrden();
  void inOrden(NodoB<Clave> *&nodo);
  NodoB<Clave> *&get_raiz();
  void set_raiz(NodoB<Clave> *nodo);
};
template <class Clave>
void Arbol<Clave>::inOrden()
{
  inOrden(raiz);
}
template <class Clave>
void Arbol<Clave>::inOrden(NodoB<Clave> *&nodo)
{
  if (nodo == NULL)
  {
    return;
  }

  inOrden(nodo->get_izq());
  cout << nodo;
  inOrden(nodo->get_dcho());
}
template <class Clave>
NodoB<Clave> *&Arbol<Clave>::get_raiz()
{
  return raiz;
}
template <class Clave>
void Arbol<Clave>::set_raiz(NodoB<Clave> *nodo)
{
 raiz = nodo;
}
#endif