red_nacional.h

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


red_nacional.cpp

#include "red_nacional.h"

RedNacional::RedNacional() : cantidadEstaciones(0) {}

RedNacional::~RedNacional() {
    for (int i = 0; i < cantidadEstaciones; i++) {
        delete estaciones[i];
    }
}

void RedNacional::agregarEstacion(const string& codigo, const string& nombre) {
    EstacionServicio* estacion = new EstacionServicio();
    estacion->codigo = codigo;
    estacion->nombre = nombre;
    estacion->cantidadSurtidores = 0;
    estaciones.push_back(estacion);
    cantidadEstaciones++;
}

void RedNacional::eliminarEstacion(const string& codigo) {
    for (int i = 0; i < cantidadEstaciones; i++) {
        if (estaciones[i]->codigo == codigo) {
            delete estaciones[i];
            estaciones.erase(estaciones.begin() + i);
            cantidadEstaciones--;
            return;
        }
    }
}

void RedNacional::agregarSurtidor(const string& codigoEstacion, const string& codigoSurtidor, const string& modelo) {
    for (int i = 0; i < cantidadEstaciones; i++) {
        if (estaciones[i]->codigo == codigoEstacion) {
            Surtidor* surtidor = new Surtidor();
            surtidor->codigo = codigoSurtidor;
            surtidor->modelo = modelo;
            surtidor->estado = true;
            estaciones[i]->surtidores.push_back(surtidor);
            estaciones[i]->cantidadSurtidores++;
            return;
        }
    }
}

void RedNacional::eliminarSurtidor(const string& codigoEstacion, const string& codigoSurtidor) {
    for (int i = 0; i < cantidadEstaciones; i++) {
        if (estaciones[i]->codigo == codigoEstacion) {
            for (int j = 0; j < estaciones[i]->cantidadSurtidores; j++) {
                if (estaciones[i]->surtidores[j]->codigo == codigoSurtidor) {
                    delete estaciones[i]->surtidores[j];
                    estaciones[i]->surtidores.erase(estaciones[i]->surtidores.begin() + j);
                    estaciones[i]->cantidadSurtidores--;
                    return;
                }
            }
        }
    }
}

void RedNacional::activarSurtidor(const string& codigoEstacion, const string& codigoSurtidor) {
    for (int i = 0; i < cantidadEstaciones; i++) {
        if (estaciones[i]->codigo == codigoEstacion) {
            for (int j = 0; j < estaciones[i]->cantidad

[16/10 3:15 p. m.] Meta AI: Aquí continúa el código:

void RedNacional::activarSurtidor(const string& codigoEstacion, const string& codigoSurtidor) {
for (int i = 0; i < cantidadEstaciones; i++) {
if (estaciones[i]->codigo == codigoEstacion) {
for (int j = 0; j < estaciones[i]->cantidadSurtidores; j++) {
if (estaciones[i]->surtidores[j]->codigo == codigoSurtidor) {
estaciones[i]->surtidores[j]->estado = true;
return;
}
}
}
}
}

void RedNacional::desactivarSurtidor(const string& codigoEstacion, const string& codigoSurtidor) {
for (int i = 0; i < cantidadEstaciones; i++) {
if (estaciones[i]->codigo == codigoEstacion) {
for (int j = 0; j < estaciones[i]->cantidadSurtidores; j++) {
if (estaciones[i]->surtidores[j]->codigo == codigoSurtidor) {
estaciones[i]->surtidores[j]->estado = false;
return;
}
}
}
}
}

void RedNacional::consultarHistoricoTransacciones(const string& codigoEstacion, const string& codigoSurtidor) {
for (int i = 0; i < cantidadEstaciones; i++) {
if (estaciones[i]->codigo == codigoEstacion) {
for (int j = 0; j < estaciones[i]->cantidadSurtidores; j++) {
if (estaciones[i]->surtidores[j]->codigo == codigoSurtidor) {
cout << "Historico de transacciones:" << endl;
for (int k = 0; k < estaciones[i]->surtidores[j]->transacciones.size(); k++) {
cout << "Transaccion " << k + 1 << ":" << endl;
cout << "Tipo: " << estaciones[i]->surtidores[j]->transacciones[k].tipo << endl;
cout << "Cantidad: " << estaciones[i]->surtidores[j]->transacciones[k].cantidad << endl;
cout << endl;
}
return;
}
}
}
}
}

void RedNacional::reportarLitrosVendidosPorCategoria(const string& codigoEstacion, const string& codigoSurtidor) {
for (int i = 0; i < cantidadEstaciones; i++) {
if (estaciones[i]->codigo == codigoEstacion) {
for (int j = 0; j < estaciones[i]->cantidadSurtidores; j++) {
if (estaciones[i]->surtidores[j]->codigo == codigoSurtidor) {
int litrosRegular = 0, litrosPremium = 0, litrosEcoExtra = 0;
for (int k = 0; k < estaciones[i]->surtidores[j]->transacciones.size(); k++) {
switch (estaciones[i]->surtidores[j]->transacciones[k].tipo) {
case 0:
litrosRegular += estaciones[i]->surtidores[j]->transacciones[k].cantidad;
break;
case 1:
litrosPremium += estaciones[i]->surtidores[j]->transacciones[k].cantidad;
break;
case 2:
litrosEcoExtra += estaciones[i]->surtidores[j]->transacciones[k].cantidad;
break;
}
}
cout << "Litros vendidos por categoria:" << endl;
cout << "Regular: " << litrosRegular << endl;
cout << "Premium: " << litrosPremium << endl;
cout << "EcoExtra: " << litrosEcoExtra << endl;
return;
}
}
}
}
}

void RedNacional::simularVenta(const string& codigoEstacion, const string& codigoSurtidor, int tipoCombustible, int cantidad) {
for (int i = 0; i < cantidadEstaciones; i++) {
if (estaciones[i]->codigo == codigoEstacion) {
for (int j = 0; j < estaciones[i]->cantidadSurtidores; j++) {
if (estaciones[i]->surtidores[j]->codigo == codigoSurtidor) {
if (estaciones[i]->surtidores[j]->estado) {
Transaccion transaccion;
transaccion.tipo = tipoCombustible;
transaccion.cantidad = cantidad;
estaciones[i]->surtidores[j]->transacciones.push_back(transaccion);
cout << "Venta simulada con exito." << endl;
} else {
cout << "Surtidor desactivado." << endl;
[16/10 3:16 p. m.] Meta AI: Aquí continúa el código:


} else {
cout << "Surtidor desactivado." << endl;
}
return;
}
}
}
}
}

void RedNacional::guardarDatosJSON(const string& archivo) {
Json::Value datos;
datos["estaciones"] = Json::arrayValue;
for (int i = 0; i < cantidadEstaciones; i++) {
Json::Value estacion;
estacion["codigo"] = estaciones[i]->codigo;
estacion["nombre"] = estaciones[i]->nombre;
estacion["surtidores"] = Json::arrayValue;
for (int j = 0; j < estaciones[i]->cantidadSurtidores; j++) {
Json::Value surtidor;
surtidor["codigo"] = estaciones[i]->surtidores[j]->codigo;
surtidor["modelo"] = estaciones[i]->surtidores[j]->modelo;
surtidor["estado"] = estaciones[i]->surtidores[j]->estado;
surtidor["transacciones"] = Json::arrayValue;
for (int k = 0; k < estaciones[i]->surtidores[j]->transacciones.size(); k++) {
Json::Value transaccion;
transaccion["tipo"] = estaciones[i]->surtidores[j]->transacciones[k].tipo;
transaccion["cantidad"] = estaciones[i]->surtidores[j]->transacciones[k].cantidad;
surtidor["transacciones"].append(transaccion);
}
estacion["surtidores"].append(surtidor);
}
datos["estaciones"].append(estacion);
}

ofstream salida(archivo);
salida << datos.toStyledString();
salida.close();
}

void RedNacional::cargarDatosJSON(const string& archivo) {
ifstream entrada(archivo);
Json::Value datos;
entrada >> datos;
entrada.close();

cantidadEstaciones = 0;
estaciones.clear();

for (int i = 0; i < datos["estaciones"].size(); i++) {
EstacionServicio* estacion = new EstacionServicio();
estacion->codigo = datos["estaciones"][i]["codigo"].asString();
estacion->nombre = datos["estaciones"][i]["nombre"].asString();
estacion->cantidadSurtidores = 0;
estaciones.push_back(estacion);
cantidadEstaciones++;

for (int j = 0; j < datos["estaciones"][i]["surtidores"].size(); j++) {
Surtidor* surtidor = new Surtidor();
surtidor->codigo = datos["estaciones"][i]["surtidores"][j]["codigo"].asString();
surtidor->modelo = datos["estaciones"][i]["surtidores"][j]["modelo"].asString();
surtidor->estado = datos["estaciones"][i]["surtidores"][j]["estado"].asBool();
surtidor->transacciones.clear();

for (int k = 0; k < datos["estaciones"][i]["surtidores"][j]["transacciones"].size(); k++) {
Transaccion transaccion;
transaccion.tipo = datos["estaciones"][i]["surtidores"][j]["transacciones"][k]["tipo"].asInt();
transaccion.cantidad = datos["estaciones"][i]["surtidores"][j]["transacciones"][k]["cantidad"].asInt();
surtidor->transacciones.push_back(transaccion);
}

estacion->surtidores.push_back(surtidor);
estacion->cantidadSurtidores++;
}
}
}


main.cpp


#include "red_nacional.h"

int main() {
RedNacional red;

while (true) {
cout << "Menu" << endl;
cout << "1. Agregar estacion" << endl;
cout << "2. Eliminar estacion" << endl;
cout << "3. Agregar surtidor" << endl;
cout << "4. Eliminar surtidor" << endl;
cout << "5. Activar surtidor" << endl;
cout << "6. Desactivar surtidor" << endl;
cout << "7. Consultar historico de transacciones" << endl;
cout << "8. Reportar litros vendidos por categoria" << endl;
cout << "9. Simular venta" << endl;
cout << "10. Guardar datos en JSON" << endl;
cout << "11. Cargar datos desde JSON" << endl;
cout << "12. Salir" << endl;

int opcion;
cin >> opcion;

switch (opcion) {
case 1: {
string codigo, nombre;
cout << "Ingrese codigo de la estacion: ";
cin >> codigo;
cout << "Ingrese nombre de la estacion: ";
cin >> nombre;
red.agregarEstacion(codigo, nombre);
break;
}
case 2: {
string codigo;
cout << "Ingrese codigo de la estacion: ";
cin >> codigo;
red.eliminarEstacion(codigo);
break

    Aquí continúa el código:

                              case 2: {
    string codigo;
    cout << "Ingrese codigo de la estacion: ";
    cin >> codigo;
    red.eliminarEstacion(codigo);
    break;
}

case 3: {
    string codigoEstacion, codigoSurtidor, modelo;
    cout << "Ingrese codigo de la estacion: ";
    cin >> codigoEstacion;
    cout << "Ingrese codigo del surtidor: ";
    cin >> codigoSurtidor;
    cout << "Ingrese modelo del surtidor: ";
    cin >> modelo;
    red.agregarSurtidor(codigoEstacion, codigoSurtidor, modelo);
    break;
}

case 4: {
    string codigoEstacion, codigoSurtidor;
    cout << "Ingrese codigo de la estacion: ";
    cin >> codigoEstacion;
    cout << "Ingrese codigo del surtidor: ";
    cin >> codigoSurtidor;
    red.eliminarSurtidor(codigoEstacion, codigoSurtidor);
    break;
}

case 5: {
    string codigoEstacion, codigoSurtidor;
    cout << "Ingrese codigo de la estacion: ";
    cin >> codigoEstacion;
    cout << "Ingrese codigo del surtidor: ";
    cin >> codigoSurtidor;
    red.activarSurtidor(codigoEstacion, codigoSurtidor);
    break;
}

case 6: {
    string codigoEstacion, codigoSurtidor;
    cout << "Ingrese codigo de la estacion: ";
    cin >> codigoEstacion;
    cout << "Ingrese codigo del surtidor: ";
    cin >> codigoSurtidor;
    red.desactivarSurtidor(codigoEstacion, codigoSurtidor);
    break;
}

case 7: {
    string codigoEstacion, codigoSurtidor;
    cout << "Ingrese codigo de la estacion: ";
    cin >> codigoEstacion;
    cout << "Ingrese codigo del surtidor: ";
    cin >> codigoSurtidor;
    red.consultarHistoricoTransacciones(codigoEstacion, codigoSurtidor);
    break;
}

case 8: {
    string codigoEstacion, codigoSurtidor;
    cout << "Ingrese codigo de la estacion: ";
    cin >> codigoEstacion;
    cout << "Ingrese codigo del surtidor: ";
    cin >> codigoSurtidor;
    red.reportarLitrosVendidosPorCategoria(codigoEstacion, codigoSurtidor);
    break;
}

case 9: {
    string codigoEstacion, codigoSurtidor;
    int tipoCombustible, cantidad;
    cout << "Ingrese codigo de la estacion: ";
    cin >> codigoEstacion;
    cout << "Ingrese codigo del surtidor: ";
    cin >> codigoSurtidor;
    cout << "Ingrese tipo de combustible (0: Regular, 1: Premium, 2: EcoExtra): ";
    cin >> tipoCombustible;
    cout << "Ingrese cantidad de combustible: ";
    cin >> cantidad;
    red.simularVenta(codigoEstacion, codigoSurtidor, tipoCombustible, cantidad);
    break;
}

case 10: {
    string archivo;
    cout << "Ingrese nombre del archivo JSON: ";
    cin >> archivo;
    red.guardarDatosJSON(archivo);
    break;
}

case 11: {
    string archivo;
    cout << "Ingrese nombre del archivo JSON: ";
    cin >> archivo;
    red.cargarDatosJSON(archivo);
    break;
}

case 12: {
    return 0;
}

default: {
    cout << "Opcion invalida. Intente nuevamente." << endl;
}
}
}
}
