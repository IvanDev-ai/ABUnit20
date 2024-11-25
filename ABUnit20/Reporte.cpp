#include "Reporte.h"

Reporte::Reporte(int id, std::string titulo, std::string contenido)
    : id(id), titulo(titulo), contenido(contenido){
}

void Reporte::generarReportes(std::vector<Reporte>& reportes, Reporte reporte)
{
    reportes.push_back(reporte);
    std::cout << "Reporte generado correctamente." << std::endl;
}

void Reporte::consultarReportes(std::vector<Reporte> reportes, int idReporte)
{
    auto it = std::find_if(reportes.begin(), reportes.end(), [idReporte](const Reporte& reporte) {
        return reporte.getId() == idReporte;
        });

    if (it != reportes.end()) {
        it->mostrarInformacion();
    }
    else {
        std::cout << "Reporte no encontrado." << std::endl;
    }
}

void Reporte::mostrarInformacion() const
{
    std::cout << "ID: " << id << std::endl;
    std::cout << "Titulo: " << titulo << std::endl;
    std::cout << "Contenido: " << contenido << std::endl;
}




