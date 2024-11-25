#include "HistorialClinico.h"

HistorialClinico::HistorialClinico(std::string diagnostico, std::string tratamiento) : diagnostico(diagnostico), tratamiento(tratamiento) {
}

std::string HistorialClinico::mostrarInformacion() const
{
    std::ostringstream oss;
    oss << "Diagnostico: " << diagnostico << "\nTratamiento: " << tratamiento << std::endl;
    return oss.str();
}


