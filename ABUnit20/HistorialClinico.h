#ifndef HISTORIALCLINICO_H
#define HISTORIALCLINICO_H

#include <iostream>
#include <map>
#include <string>

class HistorialClinico {

private:
    std::map<std::string, std::string> registros;

public:
    HistorialClinico();
    void agregarRegistro(std::string diagnostico, std::string tratamiento);
    void mostrarHistorial() const;
};

#endif 
