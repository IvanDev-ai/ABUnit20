#include "HistorialClinico.h"

HistorialClinico::HistorialClinico()
{
}

void HistorialClinico::agregarRegistro(std::string diagnostico, std::string tratamiento) {
    registros.insert(std::make_pair(diagnostico, tratamiento));
}

void HistorialClinico::mostrarHistorial() const {
    if (registros.empty()) {
        std::cout << "El historial medico esta vacio." << std::endl;
    }
    else {
        std::cout << "Historial medico:" << std::endl;
        for (const auto& registro : registros) {
            std::cout << registro.first << ": " << registro.second << std::endl;
        }
    }
}
