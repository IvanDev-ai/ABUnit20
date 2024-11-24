#ifndef PACIENTE_H
#define PACIENTE_H

#include <iostream>
#include <string>
#include "HistorialClinico.h"

class Paciente {
private:
    std::string nombre;
    int id;
    std::string fechaIngreso;
    HistorialClinico historial;
public:
    Paciente(std::string nombre, int id, std::string fechaIngreso, HistorialClinico historial);

    void modificarDatos(const std::string& nuevoNombre, const std::string& nuevaFechaIngreso);
    void eliminarPaciente() const;

    static void agregarPaciente(Paciente& paciente);
    static void consultarPaciente(const Paciente& paciente);

    void mostrarInformacion() const;
};

#endif // PACIENTE_H
