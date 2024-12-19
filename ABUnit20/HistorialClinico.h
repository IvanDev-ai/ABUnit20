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
    bool enfermedadCronica;

public:
    HistorialClinico(std::string diagnostico, std::string tratamiento, bool enfermedadCronica);
    std::string getDiagnostico() const {
        return diagnostico;
    }
    std::string getTratamiento() const {
        return tratamiento;
    }
    bool getEnfermedadCronica() const {
        return enfermedadCronica;
    }
    std::string mostrarInformacion() const;
};

#endif 
