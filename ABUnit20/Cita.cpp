#include "Cita.h"

Cita::Cita(Paciente paciente, Medico medico, const std::string& fecha, const std::string& prioridad)
    : paciente(paciente), medico(medico), fecha(fecha), prioridad(prioridad) {
}

void Cita::consultarCita(const Cita& cita) {
    cita.mostrarInformacion();
}

void Cita::mostrarInformacion() const {
    std::cout << " Paciente: " << std::endl;
    paciente.mostrarInformacion();
    std::cout << "Medico: " << std::endl;
    medico.mostrarInformacion();
    std::cout << "Fecha y Hora: " << fecha << std::endl;
    std::cout << "Prioridad: " << prioridad << std::endl;
}
