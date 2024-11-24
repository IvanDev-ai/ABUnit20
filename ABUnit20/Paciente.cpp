#include "Paciente.h"

Paciente::Paciente(std::string nombre, int id, std::string fechaIngreso, HistorialClinico historial)
    : nombre(nombre), id(id), fechaIngreso(fechaIngreso), historial(historial) {
}

void Paciente::modificarDatos(const std::string& nuevoNombre, const std::string& nuevaFechaIngreso) {
    nombre = nuevoNombre;
    fechaIngreso = nuevaFechaIngreso;
}

void Paciente::consultarPaciente(const Paciente& paciente) {
    paciente.mostrarInformacion();
}

void Paciente::mostrarInformacion() const {
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Fecha de Ingreso: " << fechaIngreso << std::endl;
    historial.mostrarHistorial();
}
