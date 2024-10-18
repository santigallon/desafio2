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

void RedNacional::reportarLitros
