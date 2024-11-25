#ifndef CITA_H
#define CITA_H

#include <iostream>
#include <string>
#include "Paciente.h"
#include "Medico.h"
class Cita {
private:
    int id;
    Paciente paciente;
    Medico medico;
    std::string fecha;
    std::string prioridad;

public:
    Cita(int id, Paciente paciente, Medico medico, const std::string& fecha, const std::string& prioridad);

    int getId() const {
        return id;
    }

    static void consultarCita(const Cita& cita);
    static void programarCita(std::vector<Cita> citas, Cita cita);
    static void cancelarCita(std::vector<Cita> citas, int idCita);
    static void modificarCita(std::vector<Cita>& citas, int idCita, std::vector<Paciente>& pacientes, std::vector<Medico>& medicos);
    static void consultarCita(std::vector<Cita> citas, int idCita);
    void mostrarInformacion() const;
};

#endif 
