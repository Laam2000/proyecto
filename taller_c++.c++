// luis alber mosquera angulo

#include <iostream>
#include <cstring>   
using namespace std; 


struct producto {
    int codigo;      
    char nombre[50];
    int cantidad;    
    int precio;      
};

struct nodo {
    producto producto;  
    nodo* siguiente;  
};

void registrarProducto(nodo** cabeza) {
    nodo* nuevoNodo = (nodo*)malloc(sizeof(nodo)); // Se reserva memoria para un nuevo nodo

    // Verificación de memoria asignada correctamente
    if (nuevoNodo == NULL) {
        cout << "Error: No se pudo asignar memoria." << endl;
        return;
    }

    
    cout << "Ingrese el código del producto: ";
    cin >> nuevoNodo->producto.codigo;

    // Validación: el código no puede ser negativo
    if (nuevoNodo->producto.codigo < 0) {
        cout << "El código no puede ser negativo." << endl;
        free(nuevoNodo); // Liberar memoria si el código es inválido
        return;
    }

    cin.ignore(); // Limpiar buffer de entrada para evitar problemas al leer cadenas

    cout << "Ingrese el nombre del producto: ";
    cin.getline(nuevoNodo->producto.nombre, 50);

    cout << "Ingrese la cantidad del producto: ";
    cin >> nuevoNodo->producto.cantidad;

    cout << "Ingrese el precio del producto: ";
    cin >> nuevoNodo->producto.precio;

    // Inicializar el puntero del nodo a NULL
    nuevoNodo->siguiente = NULL;

    // Si la lista está vacía, el nuevo nodo será la cabeza
    if (*cabeza == NULL) {
        *cabeza = nuevoNodo;
    } else {
        // Si la lista tiene elementos, se recorre hasta el último nodo
        nodo* temp = *cabeza;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        // Se enlaza el nuevo nodo al final de la lista 
        temp->siguiente = nuevoNodo;
    }

    cout << "El producto ha sido registrado con éxito." << endl;
    cout << "--------------------------\n";         
}

// Función para vender productos
void venderInventario(nodo* cabeza) {
    if (cabeza == NULL) {
        cout << "El inventario está vacío.\n";
        return;
    }

    int codigo, cantidadVender;
    cout << "Ingrese el código del producto a vender: ";
    cin >> codigo;

    nodo* temp = cabeza;

    // Se busca el producto por su código
    while (temp != NULL) {
        if (temp->producto.codigo == codigo) {
            cout << "Cantidad disponible: " << temp->producto.cantidad << endl;
            cout << "Ingrese la cantidad a vender: ";
            cin >> cantidadVender;

            // Verificar si hay suficiente cantidad para vender
            if (cantidadVender > temp->producto.cantidad) {
                cout << "Error: No hay suficientes unidades disponibles.\n";
            } else {
                temp->producto.cantidad -= cantidadVender;
                cout << "Venta realizada. Nueva cantidad: " << temp->producto.cantidad << endl;
            }
            return;
        }
        temp = temp->siguiente; // Avanzar al siguiente nodo
    }
    cout << "Producto no encontrado.\n";
    cout << "--------------------------\n"; 
}


void calcularCostoTotal(nodo* cabeza) {
    if (cabeza == NULL) {
        cout << "El inventario está vacío.\n";
        return;
    }

    int costoTotal = 0;
    nodo* temp = cabeza;

    while (temp != NULL) {
        costoTotal += temp->producto.cantidad * temp->producto.precio;
        temp = temp->siguiente;
    }

    cout << "Costo total del inventario: $" << costoTotal << endl;
}


void eliminarProducto(nodo** cabeza) {
    if (*cabeza == NULL) {
        cout << "El inventario está vacío.\n";
        return;
    }

    int codigo;
    cout << "Ingrese el código del producto a eliminar: ";
    cin >> codigo;

    nodo* temp = *cabeza;
    nodo* prev = NULL;

    // Si el nodo a eliminar es el primero de la lista
    if (temp != NULL && temp->producto.codigo == codigo) {
        *cabeza = temp->siguiente;
        free(temp);
        cout << "Producto eliminado exitosamente.\n";
        return;
    }

    // Buscar el nodo a eliminar
    while (temp != NULL && temp->producto.codigo != codigo) {
        prev = temp;
        temp = temp->siguiente;
    }

    if (temp == NULL) {
        cout << "Producto no encontrado.\n";
        return;
    }

    prev->siguiente = temp->siguiente; // Saltar el nodo eliminado
    free(temp);
    cout << "Producto eliminado exitosamente.\n";
}

void mostrarProductos(nodo* cabeza) {
    if (cabeza == NULL) {
        cout << "El inventario está vacío.\n";
        return;
    }

    cout << "Lista de productos:\n";
    nodo* temp = cabeza;

    while (temp != NULL) {
        cout << "Código: " << temp->producto.codigo << endl;
        cout << "Nombre: " << temp->producto.nombre << endl;
        cout << "Cantidad: " << temp->producto.cantidad << endl;
        cout << "Precio: $" << temp->producto.precio << endl;
        cout << "--------------------------\n";
        temp = temp->siguiente;
    }
}


void actualizarProducto(nodo* cabeza) {
    if (cabeza == NULL) {
        cout << "El inventario está vacío.\n";
        return;
    }

    int codigo;
    cout << "Ingrese el código del producto a actualizar: ";
    cin >> codigo;

    nodo* temp = cabeza;

    while (temp != NULL) {
        if (temp->producto.codigo == codigo) {
            cout << "Ingrese el nuevo nombre del producto: ";
            cin.ignore();
            cin.getline(temp->producto.nombre, 50);

            cout << "Ingrese la nueva cantidad del producto: ";
            cin >> temp->producto.cantidad;

            cout << "Ingrese el nuevo precio del producto: ";
            cin >> temp->producto.precio;

            cout << "Producto actualizado exitosamente.\n";
            return;
        }
        temp = temp->siguiente;
    }

    cout << "Producto no encontrado.";
    cout << "--------------------------\n";
}


int main() {
    nodo* cabeza = NULL;
    int opcion;

    do {
        cout << "Menu principal\n";
        cout << "1. Registrar producto\n";
        cout << "2. Vender inventario\n";
        cout << "3. Calcular costo total\n";
        cout << "4. Eliminar producto\n";
        cout << "5. Mostrar productos\n";
        cout << "6. Actualizar productos\n";
        cout << "7. Salir\n";
        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: registrarProducto(&cabeza); break;
            case 2: venderInventario(cabeza); break;
            case 3: calcularCostoTotal(cabeza); break;
            case 4: eliminarProducto(&cabeza); break;
            case 5: mostrarProductos(cabeza); break;
            case 6: actualizarProducto(cabeza); break;
            case 7: cout << "Saliendo del programa...\n"; break;
            default: cout << "Opción no válida. Intente nuevamente.\n";
        }
    } while (opcion != 7);

    return 0;
}