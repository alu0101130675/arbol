#pragma once
#include <nodoB.h>
using namespace std;

#ifndef NODO
#define NODO

template <class Clave>
class NodoAVL: public NodoB<Clave>
{
private:
    int bal;

public:
NodoAVL<Clave> *& derecho()
{
    return reinterpret_cast<NodoAVL<Clave> *&>(this->get_dcho());
}
NodoAVL<Clave> *& izquierdo()
{
    return reinterpret_cast<NodoAVL<Clave> *&>(this->get_izq());
}
NodoAVL(Clave dato_){
      bal=0;
      this->set_dato(dato_);
      this->set_izq();
      this->set_dcho();
}
   /* NodoAVL(Clave dato_, NodoAVL<Clave> *iz = nullptr, NodoAVL<Clave> *der = nullptr)
    {
      bal=0;
      this->set_dato(dato_);
      NodoB::izq()=nullptr
      NodoB::dcho()=nullptr
    }*/
    ~NodoAVL() {}
    int get_bal() { return bal; }
    void set_bal(int bal_) { bal = bal_; }
};
#endif