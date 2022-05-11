#pragma once
#include "nodoB.h"
#include "cola.h"
#include <vector>
#include <iostream>

using namespace std;

#ifndef AB
#define AB

template <class Clave>
class ArbolB
{
private:
  NodoB<Clave> *raiz;
  vector<vector<NodoB<Clave>>> niveles;
  int izquierda = 0;
  int derecha = 0;
  int height = 0;

public:
  ArbolB();
  NodoB<Clave> *Buscar(Clave &x);
  NodoB<Clave> *BuscarRama(NodoB<Clave> *nodo, Clave dato);
  void Insertar(const Clave &x);
  void InsertarRama(NodoB<Clave> *&nodo, Clave dato);
  void inOrden();
  void inOrden(NodoB<Clave> *&nodo);
  void write();
};
template <class Clave>
bool checkHeightBalance(NodoB<Clave> *root, int *height, int lef, int rig)
{
  // Check for emptiness
  int izqHeight = 0, dchoHeight = 0;
  int l = 0;
  int r = 0;
  if (root == NULL)
  {
    *height = 0;
    return 1;
  }

  l = checkHeightBalance(root->get_izq(), &izqHeight, 0, 0);
  r = checkHeightBalance(root->get_dcho(), &dchoHeight, 0, 0);
  l = l + lef;
  r = r + rig;
  // cout<<"left: "<< l << endl;
  // cout<<"right : " <<r<< endl;

  *height = (izqHeight > dchoHeight ? izqHeight : dchoHeight) + 1;

  if (std::abs(izqHeight - dchoHeight >= 1))
    return 0;

  else
    return l && r;
}
template <class Clave>
ArbolB<Clave>::ArbolB(void) : raiz(nullptr)
{
}

template <class Clave>
NodoB<Clave> *ArbolB<Clave>::Buscar(Clave &x)
{
  return BuscarRama(raiz, x);
}

template <class Clave>
NodoB<Clave> *ArbolB<Clave>::BuscarRama(NodoB<Clave> *nodo, Clave dato)
{
  if (nodo == NULL)
  {
    return NULL;
  }
  if (dato == nodo->get_dato())
  {
    return nodo;
  }
  if (dato < nodo->get_dato())
  {
    return buscar_rama(nodo->get_izq(), dato);
  }
  if (dato > nodo->get_dato())
  {
    return buscar_rama(nodo->get_dch(), dato);
  }
}

template <class Clave>
void ArbolB<Clave>::Insertar(const Clave &x)
{
  InsertarRama(raiz, x);
}

template <class Clave>
void ArbolB<Clave>::InsertarRama(NodoB<Clave> *&nodo, Clave dato)
{
  nodo->write();
  if (nodo == NULL)
    nodo = new NodoB<Clave>(dato);
  else if (checkHeightBalance(nodo, &height, 1, 0))
  {
    cout << "entra en izquietda: " << endl;
    // cout<<"izquierda: " << izquierda << endl;
    InsertarRama(nodo->get_izq(), dato);
  }
  else
  {
    // cout<<"derecha: " << derecha << endl;
    InsertarRama(nodo->get_dcho(), dato);
  }
}
template <class Clave>
void ArbolB<Clave>::inOrden(){
inOrden(raiz);
}
template <class Clave>
void ArbolB<Clave>::inOrden(NodoB<Clave> *&nodo)
{
  if (nodo == NULL)
  {
    return;
  }

  inOrden(nodo->get_izq());
  cout << nodo->get_dato() << " - ";
  inOrden(nodo->get_dcho());
}
template <class Clave>
void ArbolB<Clave>::write()
{
  cola_ABB<Clave> cola;       // Cola para guardar los nodos por niveles
  NodoB<Clave> *nodo;         // Nodo auxiliar
  int nivel = 0;              // Nivel auxiliar
  int nivel_actual = 0;       // Nivel actual
  cola.insertar(raiz, nivel); // Se inserta el primer nodo y nivel (nodo raíz y nivel 0)
  cout << "\33[1;31m\t\tNivel 0: \033[0m";
  // Mientras la cola no esté vacía...
  while (!cola.vacia())
  {
    cola.extraer(nodo, nivel); // Se extrae un nodo y nivel
    // Si el nivel extraído es mayor que el nivel actual, se aumenta el nivel actual
    if (nivel > nivel_actual)
    {
      nivel_actual = nivel;
      cout << "\33[1;31m\n\t\tNivel " << nivel_actual << ": \033[0m";
    }
    nodo->write();
    // Si el nodo extraído no está vacío, se insertan sus dos hijos en la cola
    if (nodo != NULL)
    {
      cola.insertar(nodo->get_izq(), nivel + 1);
      cola.insertar(nodo->get_dcho(), nivel + 1);
    }
  }
}

#endif