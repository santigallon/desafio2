#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <array>

using namespace std;

// Clase Combustible
class Combustible {
private:
    string categoria;
    double precio;
    double cantidad;

public:
    Combustible(string categoria, double precio, double cantidad)
        : categoria(categoria), precio(precio), cantidad(cantidad) {}

    string getCategoria() const { return categoria; }
    double getPrecio() const { return precio; }
    double getCantidad() const { return cantidad; }

    void setCantidad(double cantidad) { this->cantidad = cantidad; }
    void setPrecio(double precio) { this->precio = precio; }
};

// Clase TanqueSuministro
class TanqueSuministro {
private:
    std::array<Combustible*, 3> combustibles;

public:
    TanqueSuministro()
        : combustibles{ new Combustible("Regular", 0, 0),
                       new Combustible("Premium", 0, 0),
                       new Combustible("EcoExtra", 0, 0)} {}

    ~TanqueSuministro() {
        for (auto& combustible : combustibles) {
            delete combustible;
        }
    }

    Combustible* getCombustible(size_t indice) {
        if (indice < combustibles.size()) {
            return combustibles[indice];
        } else {
            throw std::out_of_range("Índice fuera de rango");
        }
    }

    void setCapacidad(size_t indice, double capacidad) {
        if (indice < combustibles.size()) {
            combustibles[indice]->setCantidad(capacidad);
        } else {
            throw std::out_of_range("Índice fuera de rango");
        }
    }

    void setPrecio(size_t indice, double precio) {
        if (indice < combustibles.size()) {
            combustibles[indice]->setPrecio(precio);
        } else {
            throw std::out_of_range("Índice fuera de rango");
        }
    }
};

// Clase Surtidor
class Surtidor {
private:
    string codigo;
    string modelo;
    bool activo;
    TanqueSuministro* tanqueSuministro;
    struct Transaccion {
        string fecha;
        double cantidad;
        string categoriaCombustible;
        string metodoPago;
        string numeroDocumentoCliente;
    } transacciones[100];
    int indiceTransacciones;

public:
    Surtidor(string codigo, string modelo)
        : codigo(codigo), modelo(modelo), activo(true),
        tanqueSuministro(nullptr), indiceTransacciones(0) {}

    ~Surtidor() {
        delete tanqueSuministro;
    }

    string getCodigo() const { return codigo; }
    string getModelo() const { return modelo; }
    bool getActivo() const { return activo; }

    void setActivo(bool activo) { this->activo = activo; }
    void agregarTransaccion(Transaccion transaccion) {
        this->transacciones[indiceTransacciones++] = transaccion;
    }

    Transaccion* getTransacciones() { return transacciones; }
};

// Clase EstacionServicio
class EstacionServicio {
private:
    string nombre;
    string codigo;
    string gerente;
    string region;
    string ubicacion;
    TanqueSuministro tanqueSuministro;
    Surtidor* surtidores[12];
    int indiceSurtidores;

public:
    EstacionServicio(string nombre, string codigo, string gerente, string region, string ubicacion)
        : nombre(nombre), codigo(codigo), gerente(gerente), region(region),
        ubicacion(ubicacion), indiceSurtidores(0) {}

    ~EstacionServicio() {
        for (int i = 0; i < indiceSurtidores; i++) {
            delete surtidores[i];
        }
    }

    string getNombre() const { return nombre; }
    string getCodigo() const { return codigo; }
    string getGerente() const { return gerente; }
    string getRegion() const { return region; }
    string getUbicacion() const { return ubicacion; }

    void agregarSurtidor(Surtidor* surtidor) {
        if (indiceSurtidores < 12) {
            surtidores[indiceSurtidores++] = surtidor;
        } else {
            throw std::out_of_range("No se pueden agregar más surtidores");
        }
    }

    Surtidor** getSurtidores() { return surtidores; }
};

// Clase RedNacional
class RedNacional {
private:
    EstacionServicio* estacionesServicio[100];
    int indiceEstaciones;

public:
    RedNacional() : indiceEstaciones(0) {}

    ~RedNacional() {
        for (int i = 0; i < indiceEstaciones; i++) {
            delete estacionesServicio[i];
        }
    }

    void agregarEstacionServicio(EstacionServicio* estacion) {
        if (indiceEstaciones < 100) {
            estacionesServicio[indiceEstaciones++] = estacion;
        } else {
            throw std::out_of_range("No se pueden agregar más estaciones");
        }
    }

    EstacionServicio** getEstacionesServicio() { return estacionesServicio; }
};

int main() {
    // Crear objetos
    RedNacional* redNacional = new RedNacional();

    // Menú
    int opcion;
    do {
        cout << "Menú" << endl;
        cout << "1. Gestión de la red" << endl;
        cout << "2. Gestión de estaciones de servicio" << endl;
        cout << "3. Sistema nacional de verificación de fugas" << endl;
        cout << "4. Simulación de ventas" << endl;
        cout << "5. Salir" << endl;
        cin >> opcion;

        switch (opcion) {
        case 1: {
            // Gestión de la red
            int opcionRed;
            do {
                cout << "Menú Gestión de la red" << endl;
                cout << "1. Agregar estaciones de servicio" << endl;
                cout << "2. Eliminar una E/S de la red nacional" << endl;
                cout << "3. Calcular el monto total de las ventas en cada E/S del país" << endl;
                cout << "4. Fijar los precios del combustible para toda la red" << endl;
                cout << "5. Regresar" << endl;
                cin >> opcionRed;

                switch (opcionRed) {
                case 1: {
                    // Agregar estaciones de servicio
                    string nombre, codigo, gerente, region, ubicacion;
                    cout << "Ingrese el nombre de la estación: ";
                    cin >> nombre;
                    cout << "Ingrese el código de la estación: ";
                    cin >> codigo;
                    cout << "Ingrese el gerente de la estación: ";
                    cin >> gerente;
                    cout << "Ingrese la región de la estación: ";
                    cin >> region;
                    cout << "Ingrese la ubicación de la estación: ";
                    cin >> ubicacion;

                    EstacionServicio* estacion = new EstacionServicio(nombre, codigo, gerente, region, ubicacion);
                    redNacional->agregarEstacionServicio(estacion);
                    break;
                }
                    // ...
                }
            } while (opcionRed != 5);
            break;
        }
            // ...
        }
    } while (opcion != 5);

    delete redNacional;
    return 0;
}
