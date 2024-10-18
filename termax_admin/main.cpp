#include <iostream>
#include <string>

using namespace std;

class EstacionServicio {
private:
    string nombre;
    string codigo;
    string gerente;
    string region;
    string ubicacion;
    int capacidadTanque;
    int cantidadSurtidores;

public:
    EstacionServicio() {} //construcctor por defecto
    EstacionServicio(string nombre, string codigo, string gerente, string region, string ubicacion) {
        this->nombre = nombre;
        this->codigo = codigo;
        this->gerente = gerente;
        this->region = region;
        this->ubicacion = ubicacion;
        capacidadTanque = 0;
        cantidadSurtidores = 0;
    }

    // Getters y setters
    string getNombre() { return nombre; }
    string getCodigo() { return codigo; }
    string getGerente() { return gerente; }
    string getRegion() { return region; }
    string getUbicacion() { return ubicacion; }
    int getCapacidadTanque() { return capacidadTanque; }
    int getCantidadSurtidores() { return cantidadSurtidores; }

    // Métodos
    void agregarSurtidor(Surtidor surtidor){
        surtidor[cantidadSurtidores] = surtidor;
        cantidadSurtidores++;
    }

    void eliminarSurtidor(int indice) {
        if (indice >= 0 && indice < cantidadSurtidores){
            for (int i = indice; i < cantidadSurtidores - 1; i++)
                surtidores[i] = surtidores[i+1];
        }
        cantidadSurtidores--;
    }
};
class Surtidor {
private:
    int codigo;
    string modelo;
    bool estado;

public:
    Surtidor() {}
    Surtidor(int codigo, string modelo) {
        this->codigo = codigo;
        this->modelo = modelo;
        estado = false;
    }

    // Getters y setters
    int getCodigo() { return codigo; }
    string getModelo() { return modelo; }
    bool getEstado() { return estado; }

    // Métodos
    void registrarTransacciones(Transaccion transaccion){
        transacciones[cantidadTransacciones]= transaccion;
        cantidadTransacciones++;
    }
    void activar() { estado = true; }
    void desactivar() { estado = false; }
};
class Transaccion {
private:
    string fecha;
    string hora;
    int cantidad;
    string categoria;
    string metodoPago;

public:
    Transaccion () {}
    Transaccion(string fecha, string hora, int cantidad, string categoria, string metodoPago) {
        this->fecha = fecha;
        this->hora = hora;
        this->cantidad = cantidad;
        this->categoria = categoria;
        this->metodoPago = metodoPago;
    }

    // Getters y setters
    string getFecha() { return fecha; }
    string getHora() { return hora; }
    int getCantidad() { return cantidad; }
    string getCategoria() { return categoria; }
    string getMetodoPago() { return metodoPago; }
};
class TanqueSuministro {
private:
    int capacidad;
    string categoria;

public:
    TanqueSuministro() {}
    TanqueSuministro(int capacidad, string categoria) {
        this->capacidad = capacidad;
        this->categoria = categoria;
    }

    // Getters y setters
    int getCapacidad() { return capacidad; }
    string getCategoria() { return categoria; }

    // Métodos
    void actualizarDisponibilidad(int cantidad) {
        capacidad -= cantidad;
    }
};
class RedNacionalEstacionesServicio {
private:
    EstacionServicio* estacionesServicio;
    int cantidadEstaciones;

public:
    RedNacionalEstacionesServicio() {
        estacionesServicio = new EstacionServicio[100];
        cantidadEstaciones = 0;
    }

    // Getters y setters
    EstacionServicio* getEstacionesServicio() { return estacionesServicio; }
    int getCantidadEstaciones() { return cantidadEstaciones; }

    // Métodos
    void agregarEstacionServicio(EstacionServicio estacion) {
        estacionesServicio[cantidadEstaciones] = estacion;
        cantidadEstaciones++;
    }
    void eliminarEstacionServicio(int indice){
        if (indice >= 0 && indice < cantidadEstaciones){
            for (int i = indice; i< cantidadEstaciones - 1 ; i++){
                estacionesServicio[i] = estacionesServicio[i+1];
            }
            cantidadEstaciones--;
        }
    }
    float calcularMontoTotalVentas() {
        float montoTotal = 0;
        for (int i = 0; i < cantidadEstaciones; i++) {
            for (int j = 0; j < estacionesServicio[i].getCantidadSurtidores(); j++) {
                for (int k = 0; k < estacionesServicio[i].getSurtidor(j).getCantidadTransacciones(); k++) {
                    montoTotal += estacionesServicio[i].getSurtidor(j).getTransaccion(k).getCantidad() * estacionesServicio[i].getSurtidor(j).getTransaccion(k).getPrecio();
                }
            }
        }
        return montoTotal;
    }
};
