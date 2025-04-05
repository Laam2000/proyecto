//parcial c++
//luis alber mosquera angulo
#include <iostream>
#include <cstring>
#include <cstdlib>  // Para malloc y free

using namespace std;

struct jugador {
    int id;
    char nombre[50];
    int edad;
    char genero;
    char deporte[50];
    jugador *sig;
};
jugador* historial = NULL;
jugador *cab = NULL;

bool idExiste(int id) {
    jugador* aux = cab;
    while (aux != NULL) {
        if (aux->id == id) {
            return true; // El ID ya está registrado
        }
        aux = aux->sig;
    }
    return false; // ID disponible
}


void agregarJugador() {
    jugador *nuevo = (jugador*) malloc(sizeof(jugador));
    if (!nuevo) {
        cout << "Error al asignar memoria." << endl;
        return;
    }

    int id;
    do {
        cout << "Ingrese el ID del jugador: ";
        cin >> id;
        cin.ignore();

        if (idExiste(id)) {
            cout << "Error: El ID ya está registrado. Intente con otro.\n";
        }
    } while (idExiste(id)); // Sigue pidiendo hasta que se ingrese un ID único

    nuevo->id = id;

    cout << "Ingrese el nombre del jugador: ";
    cin.getline(nuevo->nombre, 50);

    cout << "Ingrese la edad del jugador: ";
    cin >> nuevo->edad;
   if (nuevo->edad< 15){
        cout << "  La edad del jugador  no puede ser menor a 15 años.\n";
        free(nuevo); // Liberar memoria si la edad es inválida
        return ;
   }
    cin.ignore();

    cout << "Ingrese el género del jugador ( F ) para femenino y (M) para masculino: ";
    cin>>(nuevo->genero );
    cout << "Ingrese el deporte del jugador: ";
    cin.getline(nuevo->deporte, 50);

    nuevo->sig = NULL;

    if (cab == NULL) {
        cab = nuevo;
    } else {
        jugador *aux = cab;
        while (aux->sig != NULL)
            aux = aux->sig;
        aux->sig = nuevo;
    }

    cout << " Jugador registrado exitosamente.\n";
    cout << "--------------------------\n" << endl;
}


void mostrarJugadores() {
    cout << "\n\t\t\t Lista de jugadores \n\n";
    int i = 1;
    for (jugador *aux = cab; aux != NULL; aux = aux->sig) {
        cout << i++ << ". ID: " << aux->id
             << " | Nombre: " << aux->nombre
             << " | Edad: " << aux->edad
             << " | Genero: " << aux->genero
             << " | Deporte: " << aux->deporte << endl;
    }
}

int contarJugadoresEspera() {
    cout << "\n\t\t\t jugadores en espera  \n\n";
    int contador = 0;
    for (jugador *aux = cab; aux != NULL; aux = aux->sig) {
        contador++;
        cout<<"ID: " << aux->id
            << " | Nombre: " << aux->nombre
            << " | Edad: " << aux->edad
            << " | Genero: " << aux->genero
            << " | Deporte: " << aux->deporte << endl;
    }
    return contador;
}


void permitirParticipacion() {
    cout << "\n\t\t\t participacion de  jugadores \n\n";
    if (cab == NULL) {
        cout << "No hay jugadores en espera." << endl;
        return;
    }

    jugador* actual = cab;
    cout << "\nJugador que participa ahora:\n";
    cout << "ID: " << actual->id
         << " | Nombre: " << actual->nombre
         << " | Edad: " << actual->edad
         << " | Genero: " << actual->genero
         << " | Deporte: " << actual->deporte << endl;

    cab = cab->sig; // Avanza el inicio de la lista

    // Guardar en historial
    actual->sig = historial;
    historial = actual;

    cout << "Jugador movido al historial de participación." << endl;
}

void mostrarHistorial() {
    cout << "\n\t\t\t historial de los  jugadores \n\n";
    if (historial == NULL) {
        cout << "No hay historial de participantes." << endl;
        return;
    }

    cout << "\nHistorial de jugadores que han participado:\n";
    for (jugador *aux = historial; aux != NULL; aux = aux->sig) {
        cout << "ID: " << aux->id
             << " | Nombre: " << aux->nombre
             << " | Edad: " << aux->edad
             << " | Genero: " << aux->genero
             << " | Deporte: " << aux->deporte << endl;
    }
}

void deshacerParticipacion() {
    if (historial == NULL) {
        cout << "No hay participaciones para deshacer." << endl;
        return;
    }

    // Sacamos el último jugador del historial
    jugador* ultimo = historial;
    historial = historial->sig; // Avanzamos en el historial

    // Restauramos al inicio de la lista de espera
    ultimo->sig = cab;
    cab = ultimo;

    cout << "Última participación deshecha. Jugador devuelto a la lista de espera.\n";
}






int main() {
    int opcion;
    do {
        cout << "\nMenu de opciones:" << endl;
        cout << "1. Agregar jugador" << endl;
        cout << "2. Mostrar jugadores" << endl;
        cout << "3. Contar jugadores en espera" << endl;
        cout << "4. Permitir participación del siguiente jugador" << endl;
        cout << "5. Mostrar historial de participantes" << endl;
        cout << "6. dechaser participacion de jugador " << endl;
        cout << "7. Salir" << endl;
        cout << "--------------------------\n" << endl;        
        
        
        cout << "Ingrese su opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                agregarJugador();
                break;
            case 2:
                mostrarJugadores();
                break;
            case 3:
                contarJugadoresEspera();
                break;
            case 4:
                permitirParticipacion();
                break;
            case 5:
                mostrarHistorial();
                break;
            case 6:
                deshacerParticipacion();
                break;
            case 7:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
                break;
        }
        cout << "--------------------------\n" << endl;        
        
    } while (opcion != 7);

    return 0;
}
