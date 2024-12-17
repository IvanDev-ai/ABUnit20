#ifndef SISTEMAHOSPITAL_H
#define SISTEMAHOSPITAL_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Paciente.h"
#include "Medico.h"
#include "Cita.h"
#include "HistorialClinico.h"
#include "Reporte.h"
class SistemaHospital {
private:
    std::vector<Paciente> pacientes;
    std::vector<Medico> medicos;
    std::vector<Cita> citas;
    std::vector<Reporte> reportes;
public:
    SistemaHospital();

    // Métodos 

    //void guardarDatosEnArchivo();
    //void realizarCopiaBBDD();
    void crearBaseDeDatos();
    void crearMenu();
    void ejecutarSistema();

};

#endif
