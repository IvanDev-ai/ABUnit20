#ifndef HISTORIALCLINICO_H
#define HISTORIALCLINICO_H

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
class HistorialClinico {

private:
    std::string diagnostico;
    std::string tratamiento;


public:
    HistorialClinico(std::string diagnostico, std::string tratamiento);
    std::string getDiagnostico() const {
        return diagnostico;
    }
    std::string getTratamiento() const {
        return tratamiento;
    }
    std::string mostrarInformacion() const;
};

#endif 
