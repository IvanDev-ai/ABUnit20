#ifndef REPORTE_H
#define REPORTE_H

#include <iostream>
#include <string>
#include <vector>

class Reporte {
private:
    int id;
    std::string titulo;
    std::string contenido;

public:
    // Constructor
    Reporte(int id, std::string titulo, std::string contenido);
    int getId() const {
        return id;
    }
    // Metodos
    static void generarReportes(std::vector<Reporte> reportes, Reporte reporte);
    static void consultarReportes(std::vector<Reporte> reportes, int idReporte);
    void mostrarInformacion() const;
};

#endif 
