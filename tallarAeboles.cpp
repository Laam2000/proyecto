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
};

// Crear un nuevo nodo
Nodo* crearNodo(char nombre[], int anio, char genero[], float dinero) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    strcpy(nuevo->nombre, nombre);
    nuevo->año = anio;
    strcpy(nuevo->genero, genero);
    nuevo->dinero = dinero;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

// Insertar nodo
void insertarNodo(Nodo*& arbol, char nombre[], int año, char genero[], float dinero) {
    if (arbol == NULL) {
        arbol = crearNodo(nombre, año, genero, dinero);
    } else {
        if (año < arbol->año) {
            insertarNodo(arbol->izq, nombre, año, genero, dinero);
        } else if (año == arbol->año) {
            insertarNodo(arbol->izq, nombre, año, genero, dinero); // regla especial
        } else {
            insertarNodo(arbol->der, nombre, año, genero, dinero);
        }
    }
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

int main() {
    Nodo* arbol = NULL;
    int opcion;
    char nombre[100], genero[20];
    int anio;
    float dinero;

    do {
        cout << "\n--- Menú ---\n";
        cout << "1. Insertar película\n";
        cout << "2. Mostrar en Inorden\n";
        cout << "3. Mostrar en Preorden\n";
        cout << "4. Mostrar en Posorden\n";
        cout << "5. Buscar película por nombre\n";
        cout << "6. Mostrar películas por género\n";
        cout << "7. Mostrar 3 fracasos taquilleros\n";
        cout << "8. Salir\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore(); // Limpia el buffer de entrada

        switch (opcion) {
            case 1:
                cout << "Nombre: ";
                cin.getline(nombre, 100);
                cout << "Año: ";
                cin >> anio;
                cin.ignore();
                cout << "Género: ";
                cin.getline(genero, 20);
                cout << "Dinero recaudado (millones): ";
                cin >> dinero;
                insertarNodo(arbol, nombre, anio, genero, dinero);
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
           /*case 6:
                cout << "Género a mostrar: ";
                cin.ignore();
                cin.getline(genero, 20);
                mostrarPorGenero(arbol, genero);
                break;*/ 
            case 7: {
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
            case 8:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción no válida.\n";
        }

    } while (opcion != 8);

    return 0;
}
