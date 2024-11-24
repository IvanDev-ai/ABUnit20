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

    // Métodos
    void asignarEspecialidad(const std::string& nuevaEspecialidad);
    void cambiarDisponibilidad(bool nuevaDisponibilidad);
    static void listarMedicosPorEspecialidad(const std::vector<Medico>& medicos, const std::string& especialidad);
    static void consultarMedico(const Medico& medico);
    void mostrarInformacion() const;
};

#endif // MEDICO_H
