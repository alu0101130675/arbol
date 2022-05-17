#include <iostream>

using namespace std;

#ifndef Nodo_B
#define Nodo_B

template <class Clave>
class NodoB {
  private:
    Clave dato;
    NodoB* izq;
    NodoB* dcho;
  public:
    NodoB();
    NodoB(Clave, NodoB *izq = nullptr, NodoB *dcho = nullptr);

    NodoB<Clave>* &get_izq() { return izq; };
    NodoB<Clave>* &get_dcho() { return dcho; };
    Clave& get_dato() { return dato; };
    void set_dato(Clave date) { dato=date; };
    void write();
    
};

template <class Clave>
NodoB<Clave>::NodoB() :
  dato(NULL),
  izq(nullptr),
  dcho(nullptr)
{}

template <class Clave>
NodoB<Clave>::NodoB(Clave dato, NodoB *izq, NodoB *dcho) :
  dato(dato),
  izq(izq),
  dcho(dcho)
{}

template <class Clave>
void NodoB<Clave>::write() {
  if(this != NULL)
    cout << "[" << dato << "]";
  else
    cout << "[.]";
}
template <class Clave>
std::ostream& operator<<(std::ostream& os, NodoB<Clave> *nodo) {
  if(nodo != NULL)
    os << "[" <<   nodo->get_dato() << "]";
  else
    os << "[.]";
    return os;
  }

#endif
