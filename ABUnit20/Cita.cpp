#include "Cita.h"

Cita::Cita(int id, Paciente paciente, Medico medico, const std::string& fecha, const std::string& prioridad)
    : id(id),paciente(paciente), medico(medico), fecha(fecha), prioridad(prioridad) {
}


void Cita::programarCita(std::vector<Cita>& citas, Cita cita)
{
    citas.push_back(cita);
}

void Cita::cancelarCita(std::vector<Cita>& citas, int idCita)
{
    for (auto it = citas.begin(); it != citas.end(); ++it) {
        if (it->getId() == idCita) {
            citas.erase(it);
            return;
        }
    }
    std::cout << "Cita no encontrada." << std::endl;
}

void Cita::modificarCita(std::vector<Cita>& citas, int idCita, std::vector<Paciente>& pacientes, std::vector<Medico>& medicos)
{
    auto it = std::find_if(citas.begin(), citas.end(), [idCita](const Cita& cita) {
        return cita.getId() == idCita;
        });

    if (it != citas.end()) {
        int opcion;
        std::cout << "¿Que deseas modificar?\n";
        std::cout << "1. Paciente\n";
        std::cout << "2. Medico\n";
        std::cout << "3. Fecha\n";
        std::cout << "4. Prioridad\n";
        std::cout << "Elige una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1: {
            int nuevoIdPaciente;
            std::cout << "Introduce el nuevo ID del paciente: ";
            std::cin >> nuevoIdPaciente;
            auto pacienteIt = std::find_if(pacientes.begin(), pacientes.end(), [nuevoIdPaciente](const Paciente& paciente) {
                return paciente.getId() == nuevoIdPaciente;
                });
            if (pacienteIt != pacientes.end()) {
                it->paciente = *pacienteIt;
            }
            else {
                std::cout << "Paciente no encontrado." << std::endl;
            }
            break;
        }
        case 2: {
            int nuevoIdMedico;
            std::cout << "Introduce el nuevo ID del medico: ";
            std::cin >> nuevoIdMedico;
            auto medicoIt = std::find_if(medicos.begin(), medicos.end(), [nuevoIdMedico](const Medico& medico) {
                return medico.getId() == nuevoIdMedico;
                });
            if (medicoIt != medicos.end()) {
                it->medico = *medicoIt;
            }
            else {
                std::cout << "Medico no encontrado." << std::endl;
            }
            break;
        }
        case 3: {
            std::cout << "Introduce la nueva fecha de la cita (formato: YYYY-MM-DD HH:MM): ";
            std::cin.ignore(); 
            std::getline(std::cin, it->fecha);  
            break;
        }
        case 4: {
            std::cout << "Introduce la nueva prioridad (e.g., baja, urgente): ";
            std::cin.ignore();  
            std::getline(std::cin, it->prioridad); 
            break;
        }
        default:
            std::cout << "Opcion no valida." << std::endl;
        }

        std::cout << "Cita modificada correctamente." << std::endl;
    }
    else {
        std::cout << "Cita no encontrada." << std::endl;
    }
}

void Cita::consultarCita(std::vector<Cita> citas, int idCita)
{
    for (const auto& cita : citas) {
        if (cita.getId() == idCita) {
            cita.mostrarInformacion();
            return;
        }
    }
    std::cout << "Cita no encontrada." << std::endl;
}

void Cita::mostrarInformacion() const {
    std::cout << " Id: " << id <<  std::endl;
    std::cout << " Paciente: " << std::endl;
    paciente.mostrarInformacion();
    std::cout << "Medico: " << std::endl;
    medico.mostrarInformacion();
    std::cout << "Fecha y Hora: " << fecha << std::endl;
    std::cout << "Prioridad: " << prioridad << std::endl;
}
