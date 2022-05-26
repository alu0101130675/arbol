#pragma once
#include <deque>
#include "../include/nodoAVL.h"
#include "../include/ABB.h"

template <class Clave>
class AVL : public ABB<Clave>
{
private:
    // Operaciones iniciales
    void podar(NodoAVL<Clave> *&nodo);

    // Tamano y altura
    const int size_rama(NodoAVL<Clave> *nodo);
    const int altura_nodo(NodoAVL<Clave> *nodo);

    // Busqueda
   // NodoAVL<Clave> *buscar_rama(NodoAVL<Clave> *nodo, Clave x);

    // Insertar
    void insertar_bal(NodoAVL<Clave> *&nodo, NodoAVL<Clave> *nuevo, bool &crece);
    void insertar_re_bal_izquierda(NodoAVL<Clave> *&nodo, bool &crece);
    void insertar_re_bal_derecha(NodoAVL<Clave> *&nodo, bool &crece);

    // Eliminar
    void eliminar_rama(NodoAVL<Clave> *&nodo, Clave x, bool &decrece);
    void eliminar_re_bal_izquierda(NodoAVL<Clave> *&nodo, bool &decrece);
    void eliminar_re_bal_derecha(NodoAVL<Clave> *&nodo, bool &decrece);

    // Recorridos
    void preorden(NodoAVL<Clave> *nodo);
    void inorden(NodoAVL<Clave> *nodo);
    void postorden(NodoAVL<Clave> *nodo);
    void niveles(NodoAVL<Clave> *nodo);
    NodoAVL<Clave> *&raiz();

public:
    AVL();
    ~AVL();
    bool hoja(NodoAVL<Clave> *nodo);
    bool vacio(NodoAVL<Clave> *nodo);

    // Tamano y altura
    const int size();
    const int altura();

    // Busqueda
    //NodoAVL<Clave> *buscar(Clave x);

    // Rotaciones
    void rotacion_II(NodoAVL<Clave> *&nodo);
    void rotacion_DD(NodoAVL<Clave> *&nodo);
    void rotacion_ID(NodoAVL<Clave> *&nodo);
    void rotacion_DI(NodoAVL<Clave> *&nodo);

    // Insertar
    bool Insertar(const Clave &x);

    // Eliminar
    bool eliminar(Clave x);

    // Sustituir
    void sustituir(NodoAVL<Clave> *&eliminado, NodoAVL<Clave> *&sustituto, bool &decrece);

    // Recorridos
    void write();
};
template <class Clave>
NodoAVL<Clave> *&AVL<Clave>::raiz()
{
    return reinterpret_cast<NodoAVL<Clave> *&>(this->get_raiz());
}
template <class Clave>
AVL<Clave>::AVL()
{
    raiz() = nullptr;
}

template <class Clave>
AVL<Clave>::~AVL()
{
    podar(raiz());
}

template <class Clave>
void AVL<Clave>::podar(NodoAVL<Clave> *&nodo)
{
    if (nodo == nullptr)
        return;

    podar(nodo->izquierdo());
    podar(nodo->derecho());
    delete nodo;
    nodo = nullptr;
}

template <class Clave>
bool AVL<Clave>::hoja(NodoAVL<Clave> *nodo)
{
    return (!nodo->derecha && !nodo->izquierda);
}

template <class Clave>
bool AVL<Clave>::vacio(NodoAVL<Clave> *nodo)
{
    return (nodo == nullptr);
}

template <class Clave>
const int AVL<Clave>::size()
{
    return size_rama(raiz());
}

template <class Clave>
const int AVL<Clave>::size_rama(NodoAVL<Clave> *nodo)
{
    if (nodo == nullptr)
        return 0;

    return (1 + size_rama(nodo->izquierdo()) + size_rama(nodo->derecho()));
}

template <class Clave>
const int AVL<Clave>::altura()
{
    return altura_nodo(raiz());
}

template <class Clave>
const int AVL<Clave>::altura_nodo(NodoAVL<Clave> *nodo)
{
    if (nodo == nullptr)
        return 0;

    int alt_izquierda = altura_nodo(nodo->izquierdo());
    int alt_derecha = altura_nodo(nodo->derecho());

    if (alt_derecha > alt_izquierda)
        return alt_derecha++;
    else
        return alt_izquierda++;
}
/*
template <class Clave>
NodoAVL<Clave> *AVL<Clave>::buscar(Clave x)
{
    return buscar_rama(raiz(), x);
}

template <class Clave>
NodoAVL<Clave> *AVL<Clave>::buscar_rama(NodoAVL<Clave> *nodo, Clave x)
{
    if (nodo == nullptr)
        return nullptr;

    if (x == nodo->get_dato())
        return nodo;

    if (x < nodo->get_dato())
        return buscar_rama(nodo->izquierdo(), x);

    return buscar_rama(nodo->derecho(), x);
}
*/
template <class Clave>
void AVL<Clave>::rotacion_II(NodoAVL<Clave> *&nodo)
{
    NodoAVL<Clave> *nodo1 = nodo->izquierdo();
    nodo->izquierdo() = nodo1->derecho();
    nodo1->derecho() = nodo;

    if (nodo1->get_bal() == 1)
    {
        nodo->set_bal(0);
        nodo1->set_bal(0);
    }
    else
    {
        nodo->set_bal(1);
        nodo1->set_bal(-1);
    }

    nodo = nodo1;
}

template <class Clave>
void AVL<Clave>::rotacion_DD(NodoAVL<Clave> *&nodo)
{
    NodoAVL<Clave> *nodo1 = nodo->derecho();
    nodo->derecho() = nodo1->izquierdo();
    nodo1->izquierdo() = nodo;

    if (nodo1->get_bal() == -1)
    {
        nodo->set_bal(0);
        nodo1->set_bal(0);
    }
    else
    {
        nodo->set_bal(-1);
        nodo1->set_bal(1);
    }

    nodo = nodo1;
}

template <class Clave>
void AVL<Clave>::rotacion_ID(NodoAVL<Clave> *&nodo)
{
    NodoAVL<Clave> *nodo1 = nodo->izquierdo();
    NodoAVL<Clave> *nodo2 = nodo1->derecho();

    nodo->izquierdo() = nodo2->derecho();
    nodo2->derecho() = nodo;
    nodo1->derecho() = nodo2->izquierdo();
    nodo2->izquierdo() = nodo1;

    if (nodo2->get_bal() == -1)
        nodo1->set_bal(1);
    else
        nodo1->set_bal(0);

    if (nodo2->get_bal() == 1)
        nodo->set_bal(-1);
    else
        nodo->set_bal(0);

    nodo2->set_bal(0);
    nodo = nodo2;
}

template <class Clave>
void AVL<Clave>::rotacion_DI(NodoAVL<Clave> *&nodo)
{
    NodoAVL<Clave> *nodo1 = nodo->derecho();
    NodoAVL<Clave> *nodo2 = nodo1->izquierdo();

    nodo->derecho() = nodo2->izquierdo();
    nodo2->izquierdo() = nodo;
    nodo1->izquierdo() = nodo2->derecho();
    nodo2->derecho() = nodo1;

    if (nodo2->get_bal() == 1)
        nodo1->set_bal(-1);
    else
        nodo1->set_bal(0);

    if (nodo2->get_bal() == -1)
        nodo->set_bal(1);
    else
        nodo->set_bal(0);

    nodo2->set_bal(0);
    nodo = nodo2;
}

template <class Clave>
bool AVL<Clave>::Insertar(const Clave &x)
{
    if (this->Buscar(x))
        return false;
    else
    {
        NodoAVL<Clave> *nuevo = new NodoAVL<Clave>(x);
        bool crece = false;
        insertar_bal(raiz(), nuevo, crece);
        return crece;
    }
}

template <class Clave>
void AVL<Clave>::insertar_bal(NodoAVL<Clave> *&nodo, NodoAVL<Clave> *nuevo, bool &crece)
{
    if (nodo == nullptr)
    {
        nodo = nuevo;
        crece = true;
    }
    else if (nuevo->get_dato() < nodo->get_dato())
    {
        insertar_bal(nodo->izquierdo(), nuevo, crece);
        if (crece)
            insertar_re_bal_izquierda(nodo, crece);
    }
    else
    {
        insertar_bal(nodo->derecho(), nuevo, crece);
        if (crece)
            insertar_re_bal_derecha(nodo, crece);
    }
}

template <class Clave>
void AVL<Clave>::insertar_re_bal_izquierda(NodoAVL<Clave> *&nodo, bool &crece)
{
    NodoAVL<Clave> *nodo1;
    switch (nodo->get_bal())
    {
    case -1:
        nodo->set_bal(0);
        crece = false;
        break;

    case 0:
        nodo->set_bal(1);
        break;
    case 1:
        nodo1 = nodo->izquierdo();
        if (nodo1->get_bal() == 1)
        {
            std::cout << "rotacion II en " << nodo->get_dato() << std::endl;

            rotacion_II(nodo);
        }
        else
        {
            std::cout << "rotacion ID en " << nodo->get_dato() << std::endl;

            rotacion_ID(nodo);
        }
        crece = false;
        break;
    }
}

template <class Clave>
void AVL<Clave>::insertar_re_bal_derecha(NodoAVL<Clave> *&nodo, bool &crece)
{
    NodoAVL<Clave> *nodo1;
    switch (nodo->get_bal())
    {
    case 1:
        nodo->set_bal(0);
        crece = false;
        break;
    case 0:
        nodo->set_bal(-1);
        break;
    case -1:
        nodo1 = nodo->derecho();
        if (nodo1->get_bal() == -1)
        {
            std::cout << "rotacion DD en " << nodo->get_dato() << std::endl;

            rotacion_DD(nodo);
        }
        else
        {
            std::cout << "rotacion DI en " << nodo->get_dato() << std::endl;

            rotacion_DI(nodo);
        }
        crece = false;
        break;
    }
}

template <class Clave>
bool AVL<Clave>::eliminar(Clave x)
{
    bool decrece = false;
    eliminar_rama(raiz(), x, decrece);
}

template <class Clave>
void AVL<Clave>::eliminar_rama(NodoAVL<Clave> *&nodo, Clave x, bool &decrece)
{
    if (nodo == nullptr)
        return;
    if (x < nodo->get_dato())
    {
        eliminar_rama(nodo->izquierdo(), x, decrece);
        if (decrece)
            eliminar_re_bal_izquierda(nodo, decrece);
    }
    else if (x > nodo->get_dato())
    {
        eliminar_rama(nodo->derecho(), x, decrece);
        if (decrece)
            eliminar_re_bal_derecha(nodo, decrece);
    }
    else
    {
        NodoAVL<Clave> *eliminado = nodo;
        if (nodo->izquierdo() == nullptr)
        {
            nodo = nodo->derecho();
            decrece = true;
        }
        else if (nodo->derecho() == nullptr)
        {
            nodo = nodo->izquierdo();
            decrece = true;
        }
        else
        {
            sustituir(eliminado, nodo->izquierdo(), decrece);
            if (decrece)
                eliminar_re_bal_izquierda(nodo, decrece);
        }

        delete eliminado;
    }
}

template <class Clave>
void AVL<Clave>::eliminar_re_bal_izquierda(NodoAVL<Clave> *&nodo, bool &decrece)
{
    NodoAVL<Clave> *nodo1;
    switch (nodo->get_bal())
    {
    case -1:
        nodo1 = nodo->derecho();
        if (nodo1->get_bal() > 0)
            rotacion_DI(nodo);
        else
        {
            if (nodo1->get_bal() == 0)
                decrece = false;
            rotacion_DD(nodo);
        }
        break;

    case 0:
        nodo->set_bal(-1);
        decrece = false;
        break;
    case 1:
        nodo->set_bal(0);
        break;
    }
}

template <class Clave>
void AVL<Clave>::eliminar_re_bal_derecha(NodoAVL<Clave> *&nodo, bool &decrece)
{
    NodoAVL<Clave> *nodo1;
    switch (nodo->get_bal())
    {
    case 1:
        nodo1 = nodo->izquierdo();
        if (nodo->get_bal() < 0)
            rotacion_ID(nodo);
        else
        {
            if (nodo1->get_bal() == 0)
                decrece = false;
            rotacion_II(nodo);
        }
        break;

    case 0:
        nodo->set_bal(1);
        decrece = false;
        break;

    case -1:
        nodo->set_bal(0);
        break;
    }
}

template <class Clave>
void AVL<Clave>::sustituir(NodoAVL<Clave> *&eliminado, NodoAVL<Clave> *&sustituto, bool &decrece)
{
    if (sustituto->derecho() != nullptr)
    {
        sustituir(eliminado, sustituto->derecho(), decrece);
        if (decrece)
            eliminar_re_bal_derecha(sustituto, decrece);
    }
    else
    {
        eliminado->set_dato(sustituto->get_dato());
        eliminado = sustituto;
        sustituto = sustituto->izquierdo();
        decrece = true;
    }
}

template <class Clave>
void AVL<Clave>::inorden(NodoAVL<Clave> *nodo)
{
    if (nodo == nullptr)
        return;

    inorden(nodo->izquierdo());
    std::cout << "[";
    nodo->get_dato().write();
    std::cout << "]";
    inorden(nodo->derecho());
}

template <class Clave>
void AVL<Clave>::preorden(NodoAVL<Clave> *nodo)
{
    if (nodo == nullptr)
        return;

    std::cout << "[";
    nodo->get_dato().write();
    std::cout << "]";
    preorden(nodo->izquierdo());
    preorden(nodo->derecho());
}

template <class Clave>
void AVL<Clave>::postorden(NodoAVL<Clave> *nodo)
{
    if (nodo == nullptr)
        return;

    postorden(nodo->izquierdo());
    postorden(nodo->derecho());
    std::cout << "[";
    nodo->get_dato().write();
    std::cout << "]";
}

template <class Clave>
void AVL<Clave>::niveles(NodoAVL<Clave> *nodo)
{
    std::deque<std::pair<NodoAVL<Clave> *, int>> Q;
    NodoAVL<Clave> *aux;
    int nivel = 0, nivel_actual = 0;

    Q.push_back(std::pair<NodoAVL<Clave> *, int>(nodo, 0));

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

        cout << aux;
        if (aux != nullptr)
        {
            Q.push_back(std::pair<NodoAVL<Clave> *, int>(aux->izquierdo(), nivel + 1));
            Q.push_back(std::pair<NodoAVL<Clave> *, int>(aux->derecho(), nivel + 1));
        }
    }
}

template <class Clave>
void AVL<Clave>::write()
{
    niveles(raiz());
}