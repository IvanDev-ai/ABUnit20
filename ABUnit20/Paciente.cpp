#include "Paciente.h"

Paciente::Paciente(static std::string nombre, int id, std::string fechaIngreso, HistorialClinico historial)
    : nombre(nombre), id(id), fechaIngreso(fechaIngreso), historial(historial) {
}

void Paciente::modificarDatos(const std::string& nuevoNombre, const std::string& nuevaFechaIngreso) {
    nombre = nuevoNombre;
    fechaIngreso = nuevaFechaIngreso;
}

void Paciente::agregarPaciente(std::vector<Paciente> pacientes, Paciente paciente) {
    pacientes.push_back(paciente);
}

void Paciente::eliminarPaciente(std::vector<Paciente> pacientes, int idPaciente)
{
    for (auto it = pacientes.begin(); it != pacientes.end(); ++it) {
        if (it->getId() == idPaciente) {
            pacientes.erase(it);
            std::cout << "Paciente con ID " << idPaciente << " eliminado correctamente." << std::endl;
            return;
        }
    }

    std::cout << "Paciente con ID " << idPaciente << " no encontrado." << std::endl;
}

void Paciente::consultarPaciente(std::vector<Paciente> pacientes, int idPaciente)
{
    for (const auto& paciente : pacientes) {
        if (paciente.getId() == idPaciente) {
            paciente.mostrarInformacion();
            return;
        }
    }

    std::cout << "Paciente con ID " << idPaciente << " no encontrado." << std::endl;
}

void Paciente::mostrarInformacion() const {
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Fecha de Ingreso: " << fechaIngreso << std::endl;
    historial.mostrarHistorial();
}
