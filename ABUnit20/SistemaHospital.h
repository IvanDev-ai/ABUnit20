#ifndef SISTEMAHOSPITAL_H
#define SISTEMAHOSPITAL_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <ctime>
#include <iomanip>
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

    void realizarCopiaCSV(const std::string& nombreArchivo);
    void realizarCopiaBBDD();
    void crearBaseDeDatos();
    void crearMenu();
    void ejecutarSistema();

};

#endif
