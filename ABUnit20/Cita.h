#ifndef CITA_H
#define CITA_H

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
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
    Paciente getPaciente() const {
        return paciente;
    }
    Medico getMedico() const {
        return medico;
    }
    std::string getFecha() const {
        return fecha;
    }
    std::string getPrioridad() const {
        return prioridad;
    }
    static std::vector<Cita> leerCitasDesdeCSV(const std::string& nombreArchivo);
    static void escribirCitasEnCSV(const std::string& nombreArchivo, const std::vector<Cita>& citas);
    static void listarCitasPendientes(const std::string& criterio, bool esEspecialidad);
    static void programarCita(const Cita& cita);
    static void cancelarCita(int idCita);
    static void modificarCita(int idCita);
    static void consultarCita(int idCita);
    static void listarCitasPorUrgencia(const std::string& urgencia);
    void mostrarInformacion() const;
};

#endif
