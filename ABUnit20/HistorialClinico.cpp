#include "HistorialClinico.h"

HistorialClinico::HistorialClinico(std::string diagnostico, std::string tratamiento, bool enfermedadCronica) : diagnostico(diagnostico), tratamiento(tratamiento), enfermedadCronica(enfermedadCronica) {
}

std::string HistorialClinico::mostrarInformacion() const
{
    std::ostringstream oss;
    oss << "Diagnostico: " << diagnostico << "\nTratamiento: " << tratamiento << (enfermedadCronica ? "\nEnfermedad Cronica" : "\nEnfermedad Normal1") << std::endl;
    return oss.str();
}


