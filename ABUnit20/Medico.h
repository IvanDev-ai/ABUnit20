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
    // Constructor
    Medico(std::string nombre, int id, std::string especialidad, bool disponibilidad);

    // Metodos
    void asignarEspecialidad(const std::string& nuevaEspecialidad);
    void cambiarDisponibilidad(bool nuevaDisponibilidad);
    void mostrarInformacion() const;
};

#endif 
