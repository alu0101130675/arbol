#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include "nodoB.h"
#include "cola.h"
#include <ab.h>

using namespace std;
#ifndef ABi
#define ABi
template <class Clave>
class ABB : public Arbol<Clave>
{
private:
  // Operaciones iniciales
  void podar(NodoB<Clave> *&nodo);

  // Tamano y altura
  const int size_rama(NodoB<Clave> *nodo);
  const int altura_nodo(NodoB<Clave> *nodo);

  // Métodos ABB
  // Buscar(const Clave &x);        // sin IMplementar
  bool Insertar(const Clave &x); // sin IMplementar
  bool Buscar_rama(NodoB<Clave> *nodo, Clave x);
  void insertar_rama(NodoB<Clave> *&nodo, Clave x);
  void sustituir(NodoB<Clave> *&eliminado, NodoB<Clave> *&sustituto); // COMENTAR
  void eliminar_rama(NodoB<Clave> *&nodo, Clave x);

public:
  // Operaciones Iniciales + Podar

  ABB();
  ~ABB();
  bool hoja(NodoB<Clave> *nodo);
  bool vacio(NodoB<Clave> *nodo);

  // Tamano y altura
  const int size();
  const int altura();

  // Métodos ABB
  bool Buscar(const Clave &x);
  void eliminar(Clave x);

  // Recorridos
  void preorden(NodoB<Clave> *nodo);
  void inorden(NodoB<Clave> *nodo);
  void postorden(NodoB<Clave> *nodo);
  void niveles(NodoB<Clave> *nodo);
  void write(/*int recorrido*/);
};

template <class Clave>
ABB<Clave>::ABB()
{
  NodoB<Clave> *nodo = nullptr;
  this->set_raiz(nodo);
}

template <class Clave>
ABB<Clave>::~ABB()
{
  podar(this->get_raiz());
}

template <class Clave>
void ABB<Clave>::podar(NodoB<Clave> *&nodo)
{
  if (nodo == nullptr)
    return;

  podar(nodo->get_izq());
  podar(nodo->get_dcho());
  delete nodo;
  nodo = nullptr;
}

template <class Clave>
bool ABB<Clave>::hoja(NodoB<Clave> *nodo)
{
  return (!nodo->get_dcho() && !nodo->get_izq());
}

template <class Clave>
bool ABB<Clave>::vacio(NodoB<Clave> *nodo)
{
  return (nodo == nullptr);
}

template <class Clave>
const int ABB<Clave>::size()
{
  return size_rama(this->get_raiz());
}

template <class Clave>
const int ABB<Clave>::size_rama(NodoB<Clave> *nodo)
{
  if (nodo == nullptr)
    return 0;

  return (1 + size_rama(nodo->get_izq()) + size_rama(nodo->get_dcho()));
}

template <class Clave>
const int ABB<Clave>::altura()
{
  return altura_nodo(this->get_raiz());
}

template <class Clave>
const int ABB<Clave>::altura_nodo(NodoB<Clave> *nodo)
{
  if (nodo == nullptr)
    return 0;

  int alt_izquierda = altura_nodo(nodo->get_izq());
  int alt_derecha = altura_nodo(nodo->get_dcho());

  if (alt_derecha > alt_izquierda)
    return alt_derecha++;
  else
    return alt_izquierda++;
}

template <class Clave>
bool ABB<Clave>::Buscar(const Clave &x)
{
  return Buscar_rama(this->get_raiz(), x);
}

template <class Clave>
bool ABB<Clave>::Buscar_rama(NodoB<Clave> *nodo, Clave x)
{
  if (nodo == nullptr)
    return false;

  else if (x == nodo->get_dato())
    return true;

  else if (x < nodo->get_dato())
    Buscar_rama(nodo->get_izq(), x);
  Buscar_rama(nodo->get_dcho(), x);
}

template <class Clave>
bool ABB<Clave>::Insertar(const Clave &x)
{
  if (Buscar(x))
    return false;
    else {  if (this->get_raiz() == nullptr)
  {
    NodoB<Clave> *nodo = new NodoB<Clave>(x);
    this->set_raiz(nodo);
    return true;
  }
  insertar_rama(this->get_raiz(), x);}

}

template <class Clave>
void ABB<Clave>::insertar_rama(NodoB<Clave> *&nodo, Clave x)
{
  if (nodo == nullptr)
    nodo = new NodoB<Clave>(x);

  else if (x < nodo->get_dato())
    insertar_rama(nodo->get_izq(), x);

  else
    insertar_rama(nodo->get_dcho(), x);
}

template <class Clave>
void ABB<Clave>::eliminar(Clave x)
{
  eliminar_rama(this->get_raiz(), x);
}

template <class Clave>
void ABB<Clave>::eliminar_rama(NodoB<Clave> *&nodo, Clave x)
{
  if (nodo == nullptr)
    return;

  if (x < nodo->get_dato())
    eliminar_rama(nodo->get_izq(), x);

  else if (x > nodo->get_dato())
    eliminar_rama(nodo->get_dcho(), x);

  else
  {
    NodoB<Clave> *eliminado = nodo;

    if (nodo->get_dcho() == nullptr)
      nodo = nodo->get_izq();

    else if (nodo->get_izq() == nullptr)
      nodo = nodo->get_dcho();

    else
      sustituir(eliminado, nodo->get_izq());

    delete (eliminado);
  }
}

template <class Clave>
void ABB<Clave>::sustituir(NodoB<Clave> *&eliminado, NodoB<Clave> *&sustituto)
{
  if (sustituto->get_dcho() != nullptr)
    sustituir(eliminado, sustituto->get_dcho());

  else
  {

    eliminado->set_dato(sustituto->get_dato());
    eliminado = sustituto;

    sustituto = sustituto->get_izq();
  }
}

template <class Clave>
void ABB<Clave>::inorden(NodoB<Clave> *nodo)
{
  if (nodo == nullptr)
    return;

  inorden(nodo->get_izq());
  std::cout << "[";
  nodo->get_dato().write();
  std::cout << "]";
  inorden(nodo->get_dcho());
}

template <class Clave>
void ABB<Clave>::preorden(NodoB<Clave> *nodo)
{
  if (nodo == nullptr)
    return;

  std::cout << "[";
  nodo->get_dato().write();
  std::cout << "]";
  preorden(nodo->get_izq());
  preorden(nodo->get_dcho());
}

template <class Clave>
void ABB<Clave>::postorden(NodoB<Clave> *nodo)
{
  if (nodo == nullptr)
    return;

  postorden(nodo->get_izq());
  postorden(nodo->get_dcho());
  std::cout << "[";
  nodo->get_dato().write();
  std::cout << "]";
}

template <class Clave>
void ABB<Clave>::niveles(NodoB<Clave> *nodo)
{
  std::deque<std::pair<NodoB<Clave> *, int>> Q;
  NodoB<Clave> *aux;
  int nivel = 0, nivel_actual = 0;

  Q.push_back(std::pair<NodoB<Clave> *, int>(nodo, 0));

  std::cout << "\nNivel 0: ";

  while (!Q.empty())
  {
    aux = (Q.front()).first;
    nivel = (Q.front()).second;
    Q.pop_front();

    if (nivel > nivel_actual)
    {
      nivel_actual = nivel;
      std::cout << "\nNivel " << nivel_actual << ": ";
    }

    std::cout << aux;
    if (aux != nullptr)
    {
      Q.push_back(std::pair<NodoB<Clave> *, int>(aux->get_izq(), nivel + 1));
      Q.push_back(std::pair<NodoB<Clave> *, int>(aux->get_dcho(), nivel + 1));
    }
  }
}

template <class Clave>
void ABB<Clave>::write(/*int recorrido*/)
{
  /*if (recorrido == 1)
    preorden(this->get_raiz());
  else if (recorrido == 2)
    inorden(this->get_raiz());
  else if (recorrido == 3)
    postorden(this->get_raiz());
  else*/
  niveles(this->get_raiz());
}
#endif