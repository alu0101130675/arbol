#pragma once
#include "nodoB.h"
#include "cola.h"
#include <vector>
#include <iostream>
#include <ab.h>

using namespace std;

#ifndef ABE
#define ABE

template <class Clave>
class ArbolB : public Arbol<Clave>
{
private:
  vector<vector<NodoB<Clave>>> niveles;
  int height = 0;

public:
  ArbolB();
  bool Buscar(const Clave &x);
  void BuscarRama(NodoB<Clave> *nodo, Clave dato, bool &flag);
  bool Insertar(const Clave &x);
  bool InsertarRama(NodoB<Clave> *&nodo, Clave dato);
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

  *height = (izqHeight > dchoHeight ? izqHeight : dchoHeight) + 1;

  if (std::abs(izqHeight - dchoHeight >= 1))
    return 0;

  else
    return l && r;
}
template <class Clave>
ArbolB<Clave>::ArbolB(void)
{
  NodoB<Clave> *nodo = new NodoB<Clave>();
  this->set_raiz(nodo);
}

template <class Clave>
bool ArbolB<Clave>::Buscar(const Clave &x)
{
  bool flag = false;
  BuscarRama(this->get_raiz(), x, flag);
  return flag;
}

template <class Clave>
void ArbolB<Clave>::BuscarRama(NodoB<Clave> *nodo, Clave dato, bool &flag)
{
  if (nodo == NULL)
  {
    return;
  }
  if (dato == nodo->get_dato())
  {
    flag = true;
  }
  BuscarRama(nodo->get_izq(), dato, flag);
  BuscarRama(nodo->get_dcho(), dato, flag);
}

template <class Clave>
bool ArbolB<Clave>::Insertar(const Clave &x)
{
  if (Buscar(x))
  {
    return false;
  }
  else
  {
    if (this->get_raiz()->get_dato() == NULL)
    {
      NodoB<Clave> *nodo = new NodoB<Clave>(x);
      this->set_raiz(nodo);
      return true;
    }
    InsertarRama(this->get_raiz(), x);
  }
}

template <class Clave>
bool ArbolB<Clave>::InsertarRama(NodoB<Clave> *&nodo, Clave dato)
{
  if (nodo == NULL)
  {
    nodo = new NodoB<Clave>(dato);
    return true;
  }
  else if (checkHeightBalance(nodo, &height, 1, 0))
  {
    InsertarRama(nodo->get_izq(), dato);
  }
  else
  {
    InsertarRama(nodo->get_dcho(), dato);
  }
}

template <class Clave>
void ArbolB<Clave>::write()
{
  cola_ABB<Clave> cola;                   // Cola para guardar los nodos por niveles
  NodoB<Clave> *nodo;                     // Nodo auxiliar
  int nivel = 0;                          // Nivel auxiliar
  int nivel_actual = 0;                   // Nivel actual
  cola.insertar(this->get_raiz(), nivel); // Se inserta el primer nodo y nivel (nodo raíz y nivel 0)
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
   cout << nodo;
    // Si el nodo extraído no está vacío, se insertan sus dos hijos en la cola
    if (nodo != NULL)
    {
      cola.insertar(nodo->get_izq(), nivel + 1);
      cola.insertar(nodo->get_dcho(), nivel + 1);
    }
  }
}

#endif