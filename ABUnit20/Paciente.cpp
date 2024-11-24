#include "Paciente.h"

Paciente::Paciente(std::string nombre, int id, std::string fechaIngreso, HistorialClinico historial)
    : nombre(nombre), id(id), fechaIngreso(fechaIngreso), historial(historial) {
}

void Paciente::modificarDatos(const std::string& nuevoNombre, const std::string& nuevaFechaIngreso) {
    nombre = nuevoNombre;
    fechaIngreso = nuevaFechaIngreso;
}

void Paciente::eliminarPaciente() const {
    std::cout << "Paciente eliminado." << std::endl;
}

void Paciente::agregarPaciente(Paciente& paciente) {
    // Lógica para agregar paciente (esto es solo un placeholder)
    std::cout << "Paciente agregado: " << paciente.nombre << std::endl;
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
