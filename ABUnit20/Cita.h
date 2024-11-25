#ifndef CITA_H
#define CITA_H

#include <iostream>
#include <string>
#include "Paciente.h"
#include "Medico.h"
class Cita {
private:
    Paciente paciente;
    Medico medico;
    std::string fecha;
    std::string prioridad;

public:
    Cita(Paciente paciente, Medico medico, const std::string& fecha, const std::string& prioridad);

    static void consultarCita(const Cita& cita);
    void mostrarInformacion() const;
};

#endif 
