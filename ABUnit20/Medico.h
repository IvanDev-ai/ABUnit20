#ifndef MEDICO_H
#define MEDICO_H

#include <iostream>
#include <string>
#include <vector>

class Medico {
private:
    std::string nombre;
    int id;
    std::string especialidad;
    bool disponibilidad;

public:
    Medico(std::string nombre, int id, std::string especialidad, bool disponibilidad);
    std::string getEspecialidad() const {
        return especialidad;
    }
    int getId() const {
        return id;
    }
    std::string getNombre() const {
        return nombre;
    }
    bool getDisponibilidad() const {
        return disponibilidad;
    }
    void asignarEspecialidad(const std::string& nuevaEspecialidad);
    void cambiarDisponibilidad(bool nuevaDisponibilidad);
    static void listarMedicosPorEspecialidad(std::vector<Medico> medicos, std::string especialidad);
    static void consultarMedico(std::vector<Medico> medicos, int idMedico);
    void mostrarInformacion() const;
};

#endif 
