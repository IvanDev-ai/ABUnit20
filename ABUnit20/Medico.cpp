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

void Medico::listarMedicosPorEspecialidad(std::vector<Medico> medicos, std::string especialidad)
{
    bool encontrado = false;

    for (const auto& medico : medicos) {
        if (medico.getEspecialidad() == especialidad) {
            medico.mostrarInformacion();
            encontrado = true;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron medicos con la especialidad: " << especialidad << std::endl;
    }
}

void Medico::consultarMedico(std::vector<Medico> medicos, int idMedico)
{
    for (const auto& medico : medicos) {
        if (medico.getId() == idMedico) {
            medico.mostrarInformacion();
            return;  
        }
    }

    std::cout << "Medico con ID " << idMedico << " no encontrado." << std::endl;
}



void Medico::mostrarInformacion() const {
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Especialidad: " << especialidad << std::endl;
    std::cout << "Disponibilidad: " << (disponibilidad ? "Disponible" : "No disponible") << std::endl;
}
