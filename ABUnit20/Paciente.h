#ifndef PACIENTE_H
#define PACIENTE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "HistorialClinico.h"

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

    std::string getFechaIngreso() const {
        return fechaIngreso;
    }

    std::vector<HistorialClinico> getHistorial() const {
        return historial;
    }

    static std::vector<Paciente> leerPacientesDesdeCSV(const std::string& nombreArchivo);
    static void escribirPacientesEnCSV(const std::string& nombreArchivo, const std::vector<Paciente>& pacientes);
    void modificarDatos(const std::string& nuevoNombre, const std::string& nuevaFechaIngreso);
    static void agregarPaciente(Paciente paciente);
    static void eliminarPaciente(int idPaciente);
    static void consultarPaciente(int idPaciente);
    void agregarRegistroHistorial(int idPaciente, const std::string& diagnostico, const std::string& tratamiento);

    void mostrarInformacion() const;
};

#endif
