#ifndef SISTEMAHOSPITAL_H
#define SISTEMAHOSPITAL_H

#include <iostream>
#include <string>
#include <vector>
#include "Paciente.h"
#include "Medico.h"
#include "Cita.h"
#include "HistorialClinico.h"

class SistemaHospital {
private:
    std::vector<Paciente> pacientes;
    std::vector<Medico> medicos;
    std::vector<Cita> citas;

public:
    SistemaHospital();

    // Métodos 
    void crearBaseDeDatos();
    void crearMenu();
    void ejecutarSistema();

    void agregarPaciente();
    void eliminarPaciente();
    void consultarPaciente();

    void listarMedicosPorEspecialidad();
    void consultarMedico();

    void programarCita();
    void cancelarCita();
    void modificarCita();
    void consultarCita();

    void generarReportes();
    void consultarReportes();
    void guardarDatosEnArchivo();
    void realizarCopiaBBDD();

};

#endif
