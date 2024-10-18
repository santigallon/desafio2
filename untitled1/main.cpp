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
        : combustibles{
            new Combustible("Regular", 0, 0),
            new Combustible("Premium", 0, 0),
            new Combustible("EcoExtra", 0, 0)
        } {}
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
        : codigo(codigo), modelo(modelo), activo(true), tanqueSuministro(nullptr), indiceTransacciones(0) {}
    ~Surtidor() { delete tanqueSuministro; }
    string getCodigo() const { return codigo; }
    string getModelo() const { return modelo; }
    bool getActivo() const { return activo; }
    void setActivo(bool activo) { this->activo = activo; }
    void agregarTransaccion(double cantidad, string categoriaCombustible) {
        Transaccion transaccion;
        transaccion.cantidad = cantidad;
        transaccion.categoriaCombustible = categoriaCombustible;
        transacciones[indiceTransacciones++] = transaccion;
    }
    Transaccion* getTransacciones() { return transacciones; }
    void setTanqueSuministro(TanqueSuministro* tanqueSuministro) {
        this->tanqueSuministro = tanqueSuministro;
    }
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
        : nombre(nombre), codigo(codigo), gerente(gerente), region(region), ubicacion(ubicacion), indiceSurtidores(0) {}
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
void eliminarSurtidor(string codigoSurtidor) {
    for (int i = 0; i < indiceSurtidores; i++) {
        if (surtidores[i]->getCodigo() == codigoSurtidor) {
            delete surtidores[i];
            for (int j = i; j < indiceSurtidores - 1; j++) {
                surtidores[j] = surtidores[j + 1];
            }
            indiceSurtidores--;
            break;
        }
    }
}
Surtidor** getSurtidores() { return surtidores; }
int getIndiceSurtidores() { return indiceSurtidores; }
TanqueSuministro* getTanqueSuministro() { return &tanqueSuministro; }
};

// Clase RedNacional
class RedNacional {
private:
    EstacionServicio** estacionesServicio;
    int indiceEstaciones;
    int maxEstaciones;
public:
    RedNacional(int maxEstaciones)
        :maxEstaciones(maxEstaciones),
        indiceEstaciones(0),
        estacionesServicio(new EstacionServicio*[maxEstaciones]) {}
    ~RedNacional() {
        for (int i = 0; i < indiceEstaciones; i++) {
            delete estacionesServicio[i];
        }
        delete[] estacionesServicio;
    }
    void agregarEstacionServicio(EstacionServicio* estacion) {
        if (indiceEstaciones < maxEstaciones) {
            estacionesServicio[indiceEstaciones++] = estacion;
        } else {
            throw std::out_of_range("No se pueden agregar más estaciones");
        }
    }
    void eliminarEstacionServicio(string codigoEstacion) {
        for (int i = 0; i < indiceEstaciones; i++) {
            if (estacionesServicio[i]->getCodigo() == codigoEstacion) {
                delete estacionesServicio[i];
                for (int j = i; j < indiceEstaciones - 1; j++) {
                    estacionesServicio[j] = estacionesServicio[j + 1];
                }
                indiceEstaciones--;
                break;
            }
        }
    }
    EstacionServicio** getEstacionesServicio() {
        return estacionesServicio;
    }
    int getIndiceEstaciones() {
        return indiceEstaciones;
    }
};

// Menú principal
void mostrarMenu() {
cout << "Menú principal" << endl;
cout << "1. Agregar estación de servicio" << endl;
cout << "2. Eliminar estación de servicio" << endl;
cout << "3. Agregar surtidor a estación de servicio" << endl;
cout << "4. Eliminar surtidor de estación de servicio" << endl;
cout << "5. Consultar información de estación de servicio" << endl;
cout << "6. Consultar información de surtidor" << endl;
cout << "7. Realizar venta de combustible" << endl;
cout << "8. Salir" << endl;
}

int main() {
RedNacional redNacional(100);
int opcion;
do {
mostrarMenu();
cin >> opcion;
switch (opcion) {
case 1: {
// Agregar estación de servicio
string nombre, codigo, gerente, region, ubicacion;
cout << "Ingrese nombre de la estación: ";
cin >> nombre;
cout << "Ingrese código de la estación: ";
cin >> codigo;
cout << "Ingrese gerente de la estación: ";
cin >> gerente;
cout << "Ingrese región de la estación: ";
cin >> region;
cout << "Ingrese ubicación de la estación: ";
cin >> ubicacion;
EstacionServicio* estacion = new EstacionServicio(nombre, codigo, gerente, region, ubicacion);
redNacional.agregarEstacionServicio(estacion);
break;
}
case 2: {
// Eliminar estación de servicio
string codigoEstacion;
cout << "Ingrese código de la estación: ";
cin >> codigoEstacion;
redNacional.eliminarEstacionServicio(codigoEstacion);
break;
}

case 3: {
// Agregar surtidor a estación de servicio
string codigoEstacion, codigoSurtidor, modelo;
cout << "Ingrese código de la estación: ";
cin >> codigoEstacion;
cout << "Ingrese código del surtidor: ";
cin >> codigoSurtidor;
cout << "Ingrese modelo del surtidor: ";
cin >> modelo;
EstacionServicio* estacion = nullptr;
for (int i = 0; i < redNacional.getIndiceEstaciones(); i++) {
if (redNacional.getEstacionesServicio()[i]->getCodigo() == codigoEstacion) {
estacion = redNacional.getEstacionesServicio()[i];
break;
}
}
if (estacion) {
Surtidor* surtidor = new Surtidor(codigoSurtidor, modelo);
estacion->agregarSurtidor(surtidor);
} else {
cout << "Estación no encontrada." << endl;
}
break;
}
case 4: {
// Eliminar surtidor de estación de servicio
string codigoEstacion, codigoSurtidor;
cout << "Ingrese código de la estación: ";
cin >> codigoEstacion;
cout << "Ingrese código del surtidor: ";
cin >> codigoSurtidor;
EstacionServicio* estacion = nullptr;
for (int i = 0; i < redNacional.getIndiceEstaciones(); i++) {
if (redNacional.getEstacionesServicio()[i]->getCodigo() == codigoEstacion) {
estacion = redNacional.getEstacionesServicio()[i];
break;
}
}
if (estacion) {
estacion->eliminarSurtidor(codigoSurtidor);
} else {
cout << "Estación no encontrada." << endl;
}
break;
}
case 5: {
// Consultar información de estación de servicio
string codigoEstacion;
cout << "Ingrese código de la estación: ";
cin >> codigoEstacion;
EstacionServicio* estacion = nullptr;
for (int i = 0; i < redNacional.getIndiceEstaciones(); i++) {
if (redNacional.getEstacionesServicio()[i]->getCodigo() == codigoEstacion) {
estacion = redNacional.getEstacionesServicio()[i];
break;
}
}
if (estacion) {
cout << "Nombre: " << estacion->getNombre() << endl;
cout << "Código: " << estacion->getCodigo() << endl;
cout << "Gerente: " << estacion->getGerente() << endl;
cout << "Región: " << estacion->getRegion() << endl;
cout << "Ubicación: " << estacion->getUbicacion() << endl;
} else {
cout << "Estación no encontrada." << endl;
}
break;
}
case 6: {
// Consultar información de surtidor
string codigoEstacion, codigoSurtidor;
cout << "Ingrese código de la estación: ";
cin >> codigoEstacion;
cout << "Ingrese código del surtidor: ";
cin >> codigoSurtidor;
EstacionServicio* estacion = nullptr;
for (int i = 0; i < redNacional.getIndiceEstaciones(); i++) {
if (redNacional.getEstacionesServicio()[i]->getCodigo() == codigoEstacion) {
estacion = redNacional.getEstacionesServicio()[i];
break;
}
}
if (estacion) {
Surtidor* surtidor = nullptr;
for (int i = 0; i < estacion->getIndiceSurtidores(); i++) {
if (estacion->getSurtidores()[i]->getCodigo() == codigoSurtidor) {
surtidor = estacion->getSurtidores()[i];
break;
}
}
if (surtidor) {
cout << "Código: " << surtidor->getCodigo() << endl;
cout << "Modelo: " << surtidor->getModelo() << endl;
} else {
cout << "Surtidor no encontrado." << endl;
}
} else {
cout << "Estación no encontrada." << endl;
}
break;
}

case 7: {
// Realizar venta de combustible
string codigoEstacion, codigoSurtidor;
cout << "Ingrese código de la estación: ";
cin >> codigoEstacion;
cout << "Ingrese código del surtidor: ";
cin >> codigoSurtidor;
EstacionServicio* estacion = nullptr;
for (int i = 0; i < redNacional.getIndiceEstaciones(); i++) {
if (redNacional.getEstacionesServicio()[i]->getCodigo() == codigoEstacion) {
estacion = redNacional.getEstacionesServicio()[i];
break;
}
}
if (estacion) {
Surtidor* surtidor = nullptr;
for (int i = 0; i < estacion->getIndiceSurtidores(); i++) {
if (estacion->getSurtidores()[i]->getCodigo() == codigoSurtidor) {
surtidor = estacion->getSurtidores()[i];
break;
}
}
if (surtidor) {
double cantidad;
string categoriaCombustible;
cout << "Ingrese cantidad de combustible: ";
cin >> cantidad;
cout << "Ingrese categoría de combustible: ";
cin >> categoriaCombustible;
surtidor->agregarTransaccion(cantidad, categoriaCombustible);
} else {
cout << "Surtidor no encontrado." << endl;
}
} else {
cout << "Estación no encontrada." << endl;
}
break;
}
case 8: {
cout << "Saliendo del programa." << endl;
break;
}
default: {
cout << "Opción inválida. Por favor, ingrese una opción válida." << endl;
break;
}
}
} while (opcion != 8);
return 0;
}
