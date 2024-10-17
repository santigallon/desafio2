using namespace std;
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

    int getIndiceSurtidor() {return indiceSurtidores;}

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

    int getIndiceEstaciones() {return indiceEstaciones;}

    void setIndiceEstaciones(int indice) {indiceEstaciones=indice;}

    void agregarEstacionServicio(EstacionServicio* estacion) {
        if (indiceEstaciones < 100) {
            estacionesServicio[indiceEstaciones++] = estacion;
        } else {
            throw std::out_of_range("No se pueden agregar más estaciones");
        }
    }

    EstacionServicio** getEstacionesServicio() { return estacionesServicio; }

    ~RedNacional() {
        for (int i = 0; i < indiceEstaciones; i++) {
            delete estacionesServicio[i];
        }
    }
};


int main() {
    // Crear objetos
    RedNacional redNacional;
    EstacionServicio estacion("Estación 1", "E-001", "Gerente 1", "Región 1", "Ubicación 1");
    Surtidor surtidor("S-001", "Modelo 1");
    TanqueSuministro tanqueSuministro;

    // Agregar surtidor a estación
    estacion.agregarSurtidor(&surtidor);

    // Agregar estación a red nacional
    redNacional.agregarEstacionServicio(&estacion);

    // Menú
    int opcion = 0;
    while (opcion != 5){
        cout << "Menú" << endl;
        cout << "1. Gestión de la red" << endl;
        cout << "2. Gestión de estaciones de servicio" << endl;
        cout << "3. Sistema nacional de verificación de fugas" << endl;
        cout << "4. Simulación de ventas" << endl;
        cout << "5. Salir" << endl;
        cout << opcion << endl;
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
                    redNacional.agregarEstacionServicio(estacion);
                    break;
                }
                case 2: {
                    // Eliminar una E/S de la red nacional
                    string codigo;
                    cout << "Ingrese el código de la estación a eliminar: ";
                    cin >> codigo;

                    for (int i = 0; i < redNacional.getIndiceEstaciones(); i++) {
                        if (redNacional.getEstacionesServicio()[i]->getCodigo() == codigo) {
                            delete redNacional.getEstacionesServicio()[i];
                            redNacional.getEstacionesServicio()[i] = nullptr;
                            redNacional.setIndiceEstaciones(redNacional.getIndiceEstaciones() - 1);
                            break;
                        }
                    }
                    break;
                }
                case 3: {
                    // Calcular el monto total de las ventas en cada E/S del país
                    double totalVentas = 0;
                    for (int i = 0; i < redNacional.getIndiceEstaciones(); i++) {
                        EstacionServicio* estacion = redNacional.getEstacionesServicio()[i];
                        for (int j = 0; j < estacion->getIndiceSurtidores(); j++) {
                            Surtidor* surtidor = estacion->getSurtidores()[j];
                            for (int k = 0; k < 100; k++) {
                                Transaccion transaccion = surtidor->getTransacciones()[k];
                                totalVentas += transaccion.cantidad * surtidor->getTanqueSuministro()->getCombustible(0)->getPrecio();
                            }
                        }
                    }
                    cout << "Monto total de ventas: " << totalVentas << endl;
                    break;
                }
                case 4: {
                    // Fijar los precios del combustible para toda la red
                    double precioRegular, precioPremium, precioEcoExtra;
                    cout << "Ingrese el precio del combustible Regular: ";
                    cin >> precioRegular;
                    cout << "Ingrese el precio del combustible Premium: ";
                    cin >> precioPremium;
                    cout << "Ingrese el precio del combustible EcoExtra: ";
                    cin >> precioEcoExtra;

                    for (int i = 0; i < redNacional.getIndiceEstaciones(); i++) {
                        EstacionServicio* estacion = redNacional.getEstacionesServicio()[i];
                        for (int j = 0; j < estacion->getIndiceSurtidores(); j++) {
                            Surtidor* surtidor = estacion->getSurtidores()[j];
                            surtidor->getTanqueSuministro()->setPrecio(0, precioRegular);
                            surtidor->getTanqueSuministro()->setPrecio(1, precioPremium);
                            surtidor->getTanqueSuministro()->setPrecio(2, precioEcoExtra);
                        }
                    }
                    break;
                }
                } while (opcionRed != 5);
                break;
            }
        case 2: {
            // Gestión de estaciones de servicio
            int opcionEstacion;
            do {
                cout << "Menú Gestión de estaciones de servicio" << endl;
                cout << "1. Agregar/eliminar un surtidor a una E/S" << endl;
                cout << "2. Activar/desactivar un surtidor de una E/S" << endl;
                cout << "3. Consultar el histórico de transacciones de cada surtidor de la E/S" << endl;
                cout << "4. Reportar la cantidad de litros vendida según cada categoría de combustible" << endl;
                cout << "5. Simular una venta de combustible" << endl;
                cout << "6. Asignar la capacidad del tanque de suministro" << endl;
                cout << "7. Regresar" << endl;
                cin >> opcionEstacion;

                switch (opcionEstacion) {
                case 1: {
                    // Agregar/eliminar un surtidor a una E/S
                    string codigoEstacion;
                    cout << "Ingrese el código de la estación: ";
                    cin >> codigoEstacion;

                    EstacionServicio* estacion = nullptr;
                    for (int i = 0; i < redNacional.getIndiceEstaciones(); i++) {
                        if (redNacional.getEstacionesServicio()[i]->getCodigo() == codigoEstacion) {
                            estacion = redNacional.getEstacionesServicio()[i];
                            break;
                        }
                    }

                    if (estacion != nullptr) {
                        string modeloSurtidor;
                        cout << "Ingrese el modelo del surtidor: ";
                        cin >> modeloSurtidor;

                        Surtidor* surtidor = new Surtidor(codigoEstacion + "-" + modeloSurtidor, modeloSurtidor);
                        estacion->agregarSurtidor(surtidor);
                    } else {
                        cout << "Estación no encontrada" << endl;
                    }
                    break;
                }
                case 2: {
                    // Activar/desactivar un surtidor de una E/S
                    string codigoEstacion, modeloSurtidor;
                    cout << "Ingrese el código de la estación: ";
                    cin >> codigoEstacion;
                    cout << "Ingrese el modelo del surtidor: ";
                    cin >> modeloSurtidor;

                    EstacionServicio* estacion = nullptr;
                    for (int i = 0; i < redNacional.getIndiceEstaciones(); i++) {
                        if (redNacional.getEstacionesServicio()[i]->getCodigo() == codigoEstacion) {
                            estacion = redNacional.getEstacionesServicio()[i];
                            break;
                        }
                    }

                    if (estacion != nullptr) {
                        Surtidor* surtidor = nullptr;
                        for (int j = 0; j < estacion->getIndiceSurtidores(); j++) {
                            if (estacion->getSurtidores()[j]->getModelo() == modeloSurtidor) {
                                surtidor = estacion->getSurtidores()[j];
                                break;
                            }
                        }

                        if (surtidor != nullptr) {
                            surtidor->setActivo(!surtidor->getActivo());
                            cout << "Surtidor " << (surtidor->getActivo() ? "activado" : "desactivado") << endl;
                        } else {
                            cout << "Surtidor no encontrado" << endl;
                        }
                    } else {
                        cout << "Estación no encontrada" << endl;
                    }
                    break;
                }
                case 3: {
                    // Consultar el histórico de transacciones de cada surtidor de la E/S
                    string codigoEstacion;
                    cout << "Ingrese el código de la estación: ";
                    cin >> codigoEstacion;

                    EstacionServicio* estacion = nullptr;
                    for (int i = 0; i < redNacional.getIndiceEstaciones(); i++) {
                        if (redNacional.getEstacionesServicio()[i]->getCodigo() == codigoEstacion) {
                            estacion = redNacional.getEstacionesServicio()[i];
                            break;
                        }
                    }

                    if (estacion != nullptr) {
                        for (int j = 0; j < estacion->getIndiceSurtidores(); j++) {
                            Surtidor* surtidor = estacion->getSurtidores()[j];
                            cout << "Surtidor " << surtidor->getModelo() << endl;
                            for (int k = 0; k < 100; k++) {
                                Transaccion transaccion = surtidor->getTransacciones()[k];
                                if (transaccion.fecha != "") {
                                    cout << "Fecha: " << transaccion.fecha << endl;
                                    cout << "Cantidad: " << transaccion.cantidad << endl;
                                    cout << "Categoría combustible: " << transaccion.categoriaCombustible << endl;
                                    cout << "Método pago: " << transaccion.metodoPago << endl;
                                    cout << "Número documento cliente: " << transaccion.numeroDocumentoCliente << endl;
                                }
                            }
                        }
                    } else {
                        cout << "Estación no encontrada" << endl;
                    }
                    break;
                }
                case 4: {
                    // Reportar la cantidad de litros vendida según cada categoría de combustible
                    string codigoEstacion;
                    cout << "Ingrese el código de la estación: ";
                    cin >> codigoEstacion;

                    EstacionServicio* estacion = nullptr;
                    for (int i = 0; i < redNacional.getIndiceEstaciones(); i++) {
                        if (redNacional.getEstacionesServicio()[i]->getCodigo() == codigoEstacion) {
                            estacion = redNacional.getEstacionesServicio()[i];
                            break;
                        }
                    }

                    if (estacion != nullptr) {
                        double litrosVendidos[3] = {0, 0, 0};
                        string categoriasCombustible[] = {"Regular", "Premium", "EcoExtra"};

                        for (int j = 0; j < estacion->getIndiceSurtidores(); j++) {
                            Surtidor* surtidor = estacion->getSurtidores()[j];
                            for (int k = 0; k < 100; k++) {
                                Transaccion transaccion = surtidor->getTransacciones()[k];
                                if (transaccion.fecha != "") {
                                    int indiceCategoria = -1;
                                    for (int l = 0; l < 3; l++) {
                                        if (categoriasCombustible[l] == transaccion.categoriaCombustible) {
                                            indiceCategoria = l;
                                            break;
                                        }
                                    }

                                    if (indiceCategoria != -1) {
                                        litrosVendidos[indiceCategoria] += transaccion.cantidad;
                                    }
                                }
                            }
                        }

                        for (int l = 0; l < 3; l++) {
                            cout << "Litros vendidos de " << categoriasCombustible[l] << ": " << litrosVendidos[l] << endl;
                        }
                    } else {
                        cout << "Estación no encontrada" << endl;
                    }
                    break;
                }
                case 5: {
                    // Simular una venta de combustible
                    string codigoEstacion, modeloSurtidor;
                    cout << "Ingrese el código de la estación: ";
                    cin >> codigoEstacion;
                    cout << "Ingrese el modelo del surtidor: ";
                    cin >> modeloSurtidor;

                    EstacionServicio* estacion = nullptr;
                    for (int i = 0; i < redNacional.getIndiceEstaciones(); i++) {
                        if (redNacional.getEstacionesServicio()[i]->getCodigo() == codigoEstacion) {
                            estacion = redNacional.getEstacionesServicio()[i];
                            break;
                        }
                    }

                    if (estacion != nullptr) {
                        Surtidor* surtidor = nullptr;
                        for (int j = 0; j < estacion->getIndiceSurtidores(); j++) {
                            if (estacion->getSurtidores()[j]->getModelo() == modeloSurtidor) {
                                surtidor = estacion->getSurtidores()[j];
                                break;
                            }
                        }

                        if (surtidor != nullptr) {
                            double cantidad;
                            string categoriaCombustible, metodoPago, numeroDocumentoCliente;
                            cout << "Ingrese la cantidad de combustible: ";
                            cin >> cantidad;
                            cout << "Ingrese la categoría del combustible: ";
                            cin >> categoriaCombustible;
                            cout << "Ingrese el método de pago: ";
                            cin >> metodoPago;
                            cout << "Ingrese el número de documento del cliente: ";
                            cin >> numeroDocumentoCliente;

                            Transaccion transaccion;
                            transaccion.fecha = "2024-10-14";
                            transaccion.cantidad = cantidad;
                            transaccion.categoriaCombustible = categoriaCombustible;
                            transaccion.metodoPago = metodoPago;
                            transaccion.numeroDocumentoCliente = numeroDocumentoCliente;

                            surtidor->agregarTransaccion(transaccion);
                            cout << "Venta registrada con éxito" << endl;
                        } else {
                            cout << "Surtidor no encontrado" << endl;
                        }
                    } else {
                        cout << "Estación no encontrada" << endl;
                    }
                    break;
                }
                case 6: {
                    // Asignar la capacidad del tanque de suministro
                    string codigoEstacion, modeloSurtidor;
                    cout << "Ingrese el código de la estación: ";
                    cin >> codigoEstacion;
                    cout << "Ingrese el modelo del surtidor: ";
                    cin >> modeloSurtidor;

                    EstacionServicio* estacion = nullptr;
                    for (int i = 0; i < redNacional.getIndiceEstaciones(); i++) {
                        if (redNacional.getEstacionesServicio()[i]->getCodigo() == codigoEstacion) {
                            estacion = redNacional.getEstacionesServicio()[i];
                            break;
                        }
                    }

                    if (estacion != nullptr) {
                        Surtidor* surtidor = nullptr;
                        for (int j = 0; j < estacion->getIndiceSurtidores(); j++) {
                            if (estacion->getSurtidores()[j]->getModelo() == modeloSurtidor) {
                                surtidor = estacion->getSurtidores()[j];
                                break;
                            }
                        }

                        if (surtidor != nullptr) {
                            double capacidadRegular, capacidadPremium, capacidadEcoExtra;
                            cout << "Ingrese la capacidad del tanque de combustible Regular: ";
                            cin >> capacidadRegular;
                            cout << "Ingrese la capacidad del tanque de combustible Premium: ";
                            cin >> capacidadPremium;
                            cout << "Ingrese la capacidad del tanque de combustible EcoExtra: ";
                            cin >> capacidadEcoExtra;

                            surtidor->getTanqueSuministro()->setCapacidad(0, capacidadRegular);
                            surtidor->getTanqueSuministro()->setCapacidad(1, capacidadPremium);
                            surtidor->getTanqueSuministro()->setCapacidad(2, capacidadEcoExtra);
                            cout << "Capacidad del tanque actualizada con éxito" << endl;
                        } else {
                            cout << "Surtidor no encontrado" << endl;
                        }
                    } else {
                        cout << "Estación no encontrada" << endl;
                    }
                    break;
                }
                } while (opcionEstacion != 7);
                break;
            }
        case 3: {
            // Sistema nacional de verificación de fugas
            string codigoEstacion;
            cout << "Ingrese el código de la estación: ";
            cin >> codigoEstacion;

            EstacionServicio* estacion = nullptr;
            for (int i = 0; i < redNacional.getIndiceEstaciones(); i++) {
                if (redNacional.getEstacionesServicio()[i]->getCodigo() == codigoEstacion) {
                    estacion = redNacional.getEstacionesServicio()[i];
                    break;
                }
            }

            if (estacion != nullptr) {
                // Verificar fugas en la estación
                bool hayFugas = false;
                for (int j = 0; j < estacion->getIndiceSurtidores(); j++) {
                    Surtidor* surtidor = estacion->getSurtidores()[j];
                    // Verificar fugas en el surtidor
                    if (surtidor->getTanqueSuministro()->getCapacidad(0) < 0 ||
                        surtidor->getTanqueSuministro()->getCapacidad(1) < 0 ||
                        surtidor->getTanqueSuministro()->getCapacidad(2) < 0) {
                        hayFugas = true;
                        break;
                    }
                }

                if (hayFugas) {
                    cout << "Se detectaron fugas en la estación" << endl;
                } else {
                    cout << "No se detectaron fugas en la estación" << endl;
                }
            } else {
                cout << "Estación no encontrada" << endl;
            }
            break;
        }
        case 4: {
            // Simulación de ventas
            string codigoEstacion;
            cout << "Ingrese el código de la estación: ";
            cin >> codigoEstacion;

            EstacionServicio* estacion = nullptr;
            for (int i = 0; i < redNacional.getIndiceEstaciones(); i++) {
                if (redNacional.getEstacionesServicio()[i]->getCodigo() == codigoEstacion) {
                    estacion = redNacional.getEstacionesServicio()[i];
                    break;
                }
            }

            if (estacion != nullptr) {
                // Simular ventas en la estación
                double totalVentas = 0;
                for (int j = 0; j < estacion->getIndiceSurtidores(); j++) {
                    Surtidor* surtidor = estacion->getSurtidores()[j];
                    // Simular ventas en el surtidor
                    for (int k = 0; k < 100; k++) {
                        Transaccion transaccion;
                        transaccion.fecha = "2024-10-14";
                        transaccion.cantidad = 10 + (rand() % 50);
                        transaccion.categoriaCombustible = "Regular";
                        transaccion.metodoPago = "Efectivo";
                        transaccion.numeroDocumentoCliente = "123456789";

                        surtidor->agregarTransaccion(transaccion);
                        totalVentas += transaccion.cantidad * surtidor->getTanqueSuministro()->getPrecio(0);
                    }
                }

                cout << "Total de ventas simuladas: " << totalVentas << endl;
            } else {
                cout << "Estación no encontrada" << endl;
            }
            break;
        }
        case 5: {
            cout << "Saliendo del programa..." << endl;
            return 0;
        }
        }
        } while (opcion != 5);

            return 0;
        }
    }
};

