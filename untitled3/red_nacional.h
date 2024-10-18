#ifndef RED_NACIONAL_H
#define RED_NACIONAL_H

#endif // RED_NACIONAL_H
#ifndef RED_NACIONAL_H
#define RED_NACIONAL_H

#include <iostream>
#include <fstream>
#include <json/json.h>
#include <vector>

using namespace std;

struct EstacionServicio;
struct Surtidor;
struct TanqueCentral;
struct Transaccion;

class RedNacional {
public:
    RedNacional();
    ~RedNacional();

    void agregarEstacion(const string& codigo, const string& nombre);
    void eliminarEstacion(const string& codigo);
    void agregarSurtidor(const string& codigoEstacion, const string& codigoSurtidor, const string& modelo);
    void eliminarSurtidor(const string& codigoEstacion, const string& codigoSurtidor);
    void activarSurtidor(const string& codigoEstacion, const string& codigoSurtidor);
    void desactivarSurtidor(const string& codigoEstacion, const string& codigoSurtidor);
    void consultarHistoricoTransacciones(const string& codigoEstacion, const string& codigoSurtidor);
    void reportarLitrosVendidosPorCategoria(const string& codigoEstacion, const string& codigoSurtidor);
    void simularVenta(const string& codigoEstacion, const string& codigoSurtidor, int tipoCombustible, int cantidad);
    void guardarDatosJSON(const string& archivo);
    void cargarDatosJSON(const string& archivo);

private:
    vector<EstacionServicio*> estaciones;
    int cantidadEstaciones;
};

struct EstacionServicio {
    string codigo;
    string nombre;
    vector<Surtidor*> surtidores;
    int cantidadSurtidores;
};

struct Surtidor {
    string codigo;
    string modelo;
    bool estado;
    vector<Transaccion> transacciones;
};

struct TanqueCentral {
    int capacidad;
    int cantidadDisponible;
};

struct Transaccion {
    int tipo;
    int cantidad;
};

#endif // RED_NACIONAL_H
