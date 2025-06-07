#include <iostream>
#include <cstring>  //   strcmp
using namespace std;

struct Nodo {
    char nombre[100];
    int año;
    char genero[20];
    float dinero;
    Nodo* izq;
    Nodo* der;
    Nodo *padre;
};

// Crear un nuevo nodo
Nodo* crearNodo(char nombre[], int año, char genero[], float dinero, Nodo* padre) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    strcpy(nuevo->nombre, nombre);
    nuevo->año = año;
    strcpy(nuevo->genero, genero);
    nuevo->dinero = dinero;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    nuevo->padre = padre;
    nuevo-> altura = 1; // inicializa la altura del nodo hoja
    return nuevo;
}
// Función para obtener la altura de un nodo
int getAltura(nodo* nodo){
    return nodo ? nodo->altura : 0;
}

 int getBalane(Nodo* nodo) {
    if (!nodo) return 0;
    return alturaHoja(nodo->izq) - alturaHoja(nodo->der);
 }
void actualizarAltura(Nodo* nodo) {
    if (nodo) {
        nodo->altura = 1 + max(alturaHoja(nodo->izq), altura(nodo->der));
    }
}
// Función para rotar a la derecha
Nodo* rotarDerecha(Nodo* y) {
    Nodo* x = y->izq;
    Nodo* T2 = x->der;

    // Realizar rotación
    x->der = y;
    y->izq = T2;

    // Actualizar alturas
    actualizarAltura(y);
    actualizarAltura(x);

    return x; // Nueva raíz
}
// Función para rotar a la izquierda
Nodo* rotarIzquierda(Nodo* x) {
    Nodo* y = x->der;
    Nodo* T2 = y->izq;

    // Realizar rotación
    y->izq = x;
    x->der = T2;

    // Actualizar alturas
    actualizarAltura(x);
    actualizarAltura(y);

    return y; // Nueva raíz
}
// Insertar nodo
Nodo* insertarAVL(Nodo* nodo, char nombre[], int año, char genero[], float dinero, Nodo* padre) {
    if (nodo == NULL) {
        return crearNodo(nombre, año, genero, dinero, padre);
    }

    if (año < nodo->año) {
        nodo->izq = insertarAVL(nodo->izq, nombre, año, genero, dinero, nodo);
    } else if (año > nodo->año) {
        nodo->der = insertarAVL(nodo->der, nombre, año, genero, dinero, nodo);
    } else {
        cout << "El año ingresado ya existe: " << año << endl;
        return nodo;
    }

    actualizarAltura(nodo);
    int balance =  getBalane(nodo);

    // Casos de desbalance
    if (balance > 1 && año < nodo->izq->año)
        return rotarDerecha(nodo);

    if (balance < -1 && año > nodo->der->año)
        return rotarIzquierda(nodo);

    if (balance > 1 && año > nodo->izq->año) {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }

    if (balance < -1 && año < nodo->der->año) {
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

   return nodo;
}
        
    


// Recorridos
void inorden(Nodo* arbol) {
    if (arbol != NULL) {
        inorden(arbol->izq);
        cout << "Nombre: " << arbol->nombre << ", Año: " << arbol->año
             << ", Género: " << arbol->genero << ", Dinero: $" << arbol->dinero << "M" << endl;
        inorden(arbol->der);
    }
}

void preorden(Nodo* arbol) {
    if (arbol != NULL) {
        cout << "Nombre: " << arbol->nombre << ", Año: " << arbol->año
             << ", Género: " << arbol->genero << ", Dinero: $" << arbol->dinero << "M" << endl;
        preorden(arbol->izq);
        preorden(arbol->der);
    }
}

void posorden(Nodo* arbol) {
    if (arbol != NULL) {
        posorden(arbol->izq);
        posorden(arbol->der);
        cout << "Nombre: " << arbol->nombre << ", Año: " << arbol->año
             << ", Género: " << arbol->genero << ", Dinero: $" << arbol->dinero << "M" << endl;
    }
}

//Buscar película por nombre
void buscarPorNombre(Nodo* arbol, const char* nombre) {
    if (arbol == NULL) return ;

    if (strcmp(arbol->nombre, nombre) != 0) {
        cout << "Película encontrada:\n";
        cout << "Nombre: " << arbol->nombre << ", Año: " << arbol->año
             << ", Género: " << arbol->genero << ", Dinero: $" << arbol->dinero << "M" << endl;
    }
    buscarPorNombre(arbol->izq, nombre);
    buscarPorNombre(arbol->der, nombre);
}

/* Mostrar películas por género
void mostrarPorGenero(Nodo* arbol, const char* genero) {
    if (arbol != NULL) {
        mostrarPorGenero(arbol->izq, genero);
        if (strcmp(arbol->genero, genero) == 0) {
            cout << "Nombre: " << arbol->nombre << ", Año: " << arbol->año
                 << ", Dinero: $" << arbol->dinero << "M" << endl;
        }
        mostrarPorGenero(arbol->der, genero);
    }
}*/

// Mostrar 3 fracasos taquilleros
void mostrarFracasos(Nodo* arbol, Nodo* fracasos[], int& count) {
    if (arbol == NULL) return;

    mostrarFracasos(arbol->izq, fracasos, count);

    if (count < 3) {
        fracasos[count++] = arbol;
    } else {
        int maxIndex = 0;
        for (int i = 1; i < 3; i++) {
            if (fracasos[i]->dinero > fracasos[maxIndex]->dinero) {
                maxIndex = i;
            }
        }
        if (arbol->dinero < fracasos[maxIndex]->dinero) {
            fracasos[maxIndex] = arbol;
        }
    }

    mostrarFracasos(arbol->der, fracasos, count);
}
//eliminar un nodo del arbol
 void eliminarNodoPorNombre(Nodo*& raiz, const char* nombre) {
    if (raiz == NULL) return;

    if (strcmp(raiz->nombre, nombre) == 0) {
        // Caso 1: Nodo sin hijos
        if (raiz->izq == NULL && raiz->der == NULL) {
            free(raiz);
            raiz = NULL;
            return;
        }
        // Caso 2: Nodo con un hijo
        else if (raiz->izq == NULL || raiz->der == NULL) {
            Nodo* hijo = (raiz->izq != NULL) ? raiz->izq : raiz->der;
            hijo->padre = raiz->padre;
            free(raiz);
            raiz = hijo;
            return;
        }
        // Caso 3: Nodo con dos hijos
        else {
            Nodo* sucesor = raiz->der;
            while (sucesor->izq != NULL) {
                sucesor = sucesor->izq;
            }
            strcpy(raiz->nombre, sucesor->nombre);
            raiz->año = sucesor->año;
            strcpy(raiz->genero, sucesor->genero);
            raiz->dinero = sucesor->dinero;
            eliminarNodoPorNombre(raiz->der, sucesor->nombre);
        }
    } else {
        eliminarNodoPorNombre(raiz->izq, nombre);
        eliminarNodoPorNombre(raiz->der, nombre);
    }
}
// Función principal          
int main() {
    Nodo* arbol = NULL;
    int opcion;
    char nombre[100], genero[20];
    int año;
    float dinero;

    do {
        cout << "\n--- Menú ---\n";
        cout << "1. Insertar película\n";
        cout << "2. Mostrar en Inorden\n";
        cout << "3. Mostrar en Preorden\n";
        cout << "4. Mostrar en Posorden\n";
        cout << "5. Buscar película por nombre\n";
       cout << "6. Mostrar 3 fracasos taquilleros\n";
        cout << "7.eliminar pelicula \n";
        cout << "8. Salir\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore(); // Limpia el buffer de entrada

        switch (opcion) {
            case 1:
                cout << "Nombre: ";
                cin.getline(nombre, 100);
                cout << "Año: ";
                cin >>  año;
                cin.ignore();
                cout << "Género: ";
                cin.getline(genero, 20);
                cout << "Dinero recaudado (millones): ";
                cin >> dinero;
                 insertarAVL(arbol, nombre, año, genero, dinero, NULL);
                break;
            case 2:
                cout << "\nRecorrido Inorden:\n";
                inorden(arbol);
                break;
            case 3:
                cout << "\nRecorrido Preorden:\n";
                preorden(arbol);
                break;
            case 4:
                cout << "\nRecorrido Posorden:\n";
                posorden(arbol);
                break;
            case 5:
                cout << "Nombre de la película a buscar: ";
                cin.ignore();
                cin.getline(nombre, 100);
                buscarPorNombre(arbol, nombre);
                break;
         
            case 6: {
                Nodo* fracasos[3] = {NULL, NULL, NULL};
                int count = 0;
                mostrarFracasos(arbol, fracasos, count);
                cout << "\n3 Fracasos taquilleros:\n";
                for (int i = 0; i < count; i++) {
                    if (fracasos[i]) {
                        cout << "Nombre: " << fracasos[i]->nombre
                             << ", Dinero: $" << fracasos[i]->dinero << "M" << endl;
                    }
                }
                break;
            } 
            case 7:
                cout << "Nombre de la película a eliminar: ";
                cin.ignore();
                cin.getline(nombre, 100);
                eliminarNodoPorNombre(arbol, nombre);
                if (arbol == NULL) {
                    cout << "Película no encontrada.\n";

                    break;
                }
                cout << "Película eliminada.\n";
            case 8:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida.\n";
        }

    } while (opcion != 9);

    return 0;
}
