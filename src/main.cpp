#include "../include/nodoB.h"
#include "../include/cola.h"
#include "../include/ABE.h"
#include "../include/ABB.h"
#include <iostream>

using namespace std;

int main(void)
{
  int opcion = 0;
  int clave = 0;
  Arbol<int> *ab;
  cout << "\33[1;32mIMPLEMENTACIÓN DE ÁRBOLES BINARIOS \033[0m" << endl;
  cout << "\33[1;34m\tElija una arbo: " << endl;
  cout << "\33[1;34m\t\t[0]  Salir\033[0m" << endl;
  cout << "\33[1;34m\t\t[1] Arbol equilibrado \033[0m" << endl;
  cout << "\33[1;34m\t\t[2]  Arbol binario\033[0m" << endl;
  cin >> opcion;
  switch (opcion)
  {
  case 0:
    return 0;
  case 1:
    ab = new ArbolB<int>;
    do
    {
      cout << "\33[1;32mOPCIONES DEL ARBOL SELECCIONADO \033[0m" << endl;

      cout << "\33[1;34m\t\t[0]  Salir\033[0m" << endl;
      cout << "\33[1;34m\t\t[1]  Insertar Clave\033[0m" << endl;
      cout << "\33[1;34m\t\t[2]  Buscar Clave\033[0m" << endl;
      cout << "\33[1;34m\t\t[3]  indorden Clave\033[0m" << endl;
      cout << "\33[1;34m\tRespuesta: \033[0m";
      cin >> opcion;
      switch (opcion)
      {
      case 0:
        cout << "\33[1;32m\t\tSaliendo del programa\033[0m" << endl;
        break;
      case 1:
        cout << "\33[1;33m\t\tIntroduzca la clave a insertar: \033[0m";
        cin >> clave;
        if (!ab->Insertar(clave))
          cout << "la clave ya esta en el arbol" << endl;

        cout << "\33[1;33m\t\tMostrando el árbol vacío: \033[0m" << endl;
        ab->write();
        cout << endl;
        break;

      case 2:
        cout << "\33[1;33m\t\tIntroduzca la clave a buscar: \033[0m";
        cin >> clave;
        if (ab->Buscar(clave))
          cout << "se encuentra en el arbol" << endl;
        else
          cout << "no se encuetra" << endl;
        break;
      case 3:
        cout << endl;
        ab->inOrden();
        cout << endl;
        break;
      default:
        cout << "\33[1;31m\t\tNo es un valor correcto (0, 1, 2 o 3)\033[0m" << endl;
        break;
      }
    } while (opcion != 0);
  case 2:
    ab = new ABB<int>;
    do
    {
      cout << "\33[1;32mOPCIONES DEL ARBOL SELECCIONADO \033[0m" << endl;

      cout << "\33[1;34m\t\t[0]  Salir\033[0m" << endl;
      cout << "\33[1;34m\t\t[1]  Insertar Clave\033[0m" << endl;
      cout << "\33[1;34m\t\t[2]  Buscar Clave\033[0m" << endl;
      cout << "\33[1;34m\t\t[3]  eliminar Clave\033[0m" << endl;
      cout << "\33[1;34m\t\t[3]  indorden Clave\033[0m" << endl;
      
      cout << "\33[1;34m\tRespuesta: \033[0m";
      cin >> opcion;
      switch (opcion)
      {
      case 0:
        cout << "\33[1;32m\t\tSaliendo del programa\033[0m" << endl;
        break;
      case 1:
        cout << "\33[1;33m\t\tIntroduzca la clave a insertar: \033[0m";
        cin >> clave;
        if (!ab->Insertar(clave))
          cout << "la clave ya esta en el arbol" << endl;

        cout << "\33[1;33m\t\tMostrando el árbol vacío: \033[0m" << endl;
        ab->write();
        cout << endl;
        break;

      case 2:
        cout << "\33[1;33m\t\tIntroduzca la clave a buscar: \033[0m";
        cin >> clave;
        if (ab->Buscar(clave))
          cout << "se encuentra en el arbol" << endl;
        else
          cout << "no se encuetra" << endl;
        break;
        case 3:
        cout << endl;
                cin >> clave;

        ab->eliminar(clave);
                ab->write();

        cout << endl;
        break;
      case 4:
        cout << endl;
        ab->inOrden();
        cout << endl;
        break;
      default:
        cout << "\33[1;31m\t\tNo es un valor correcto (0, 1, 2 o 3)\033[0m" << endl;
        break;
      }
    } while (opcion != 0);
  default:
    cout << "\33[1;31m\t\tNo es un valor correcto (0, 1, 2 o 3)\033[0m" << endl;
    break;
  }

  }
