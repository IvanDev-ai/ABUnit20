#ifndef MEDICO_H
#define MEDICO_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class Medico {
private:
    std::string nombre;
    int id;
    std::string especialidad;
    bool disponibilidad;

public:
    Medico(std::string nombre, int id, std::string especialidad, bool disponibilidad);

    int getId() const {
        return id;
    }
    std::string getNombre() const {
        return nombre;
    }
    std::string getEspecialidad() const {
        return especialidad;
    }
    bool getDisponibilidad() const {
        return disponibilidad;
    }

    static std::vector<Medico> leerMedicosDesdeCSV(const std::string& nombreArchivo);
    static void escribirMedicosEnCSV(const std::string& nombreArchivo, const std::vector<Medico>& medicos);

    static void asignarEspecialidad(int idMedico, const std::string& nuevaEspecialidad);
    static void cambiarDisponibilidad(int idMedico, bool nuevaDisponibilidad);
    static void listarMedicosPorEspecialidad(const std::string& especialidad);
    static void consultarMedico(int idMedico);
    void mostrarInformacion() const;
};

#endif 
