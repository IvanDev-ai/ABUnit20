#include "Medico.h"

Medico::Medico(std::string nombre, int id, std::string especialidad, bool disponibilidad)
    : nombre(nombre), id(id), especialidad(especialidad), disponibilidad(disponibilidad) {
}

void Medico::asignarEspecialidad(const std::string& nuevaEspecialidad) {
    especialidad = nuevaEspecialidad;
}

void Medico::cambiarDisponibilidad(bool nuevaDisponibilidad) {
    disponibilidad = nuevaDisponibilidad;
}



void Medico::mostrarInformacion() const {
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Especialidad: " << especialidad << std::endl;
    std::cout << "Disponibilidad: " << (disponibilidad ? "Disponible" : "No disponible") << std::endl;
}
