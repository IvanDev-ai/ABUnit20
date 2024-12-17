#ifndef PACIENTE_H
#define PACIENTE_H

#include <iostream>
#include <string>
#include "HistorialClinico.h"
#include <vector>

class Paciente {
private:
    std::string nombre;
    int id;
    std::string fechaIngreso;
    std::vector<HistorialClinico> historial;
public:
    Paciente(std::string nombre, int id, std::string fechaIngreso, std::vector<HistorialClinico> historial);

    int getId() const {
        return id;
    }
    std::string getNombre() const {
        return nombre;
    }
    std::string getfechaIngreso() const {
        return fechaIngreso;
    }
    std::vector<HistorialClinico> getHistorial() const {
        return historial;
    }
    void modificarDatos(const std::string& nuevoNombre, const std::string& nuevaFechaIngreso);
    static void agregarPaciente(std::vector<Paciente>& pacientes, Paciente paciente);
    static void eliminarPaciente(std::vector<Paciente>& pacientes, int idPaciente);
    static void consultarPaciente(std::vector<Paciente> pacientes, int idPaciente);
    void agregarRegistroHistorial(std::string& diagnostico, std::string& tratamiento);

    void mostrarInformacion() const;
};

#endif 
