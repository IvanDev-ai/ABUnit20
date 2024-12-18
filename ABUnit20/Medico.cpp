#include "Medico.h"

Medico::Medico(std::string nombre, int id, std::string especialidad, bool disponibilidad)
    : nombre(nombre), id(id), especialidad(especialidad), disponibilidad(disponibilidad) {
}

std::vector<Medico> Medico::leerMedicosDesdeCSV(const std::string& nombreArchivo) {
    std::vector<Medico> medicos;
    std::ifstream archivo(nombreArchivo);
    std::string linea, nombre, especialidad, disponibilidadStr;
    int id;
    bool disponibilidad;

    if (archivo.is_open()) {
        std::getline(archivo, linea);

        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            ss >> id;
            ss.ignore(1, ',');
            std::getline(ss, nombre, ',');
            std::getline(ss, especialidad, ',');
            std::getline(ss, disponibilidadStr);

            disponibilidad = (disponibilidadStr == "Si");

            Medico medico(nombre, id, especialidad, disponibilidad);
            medicos.push_back(medico);
        }
        archivo.close();
    }
    else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
    }
    return medicos;
}

void Medico::escribirMedicosEnCSV(const std::string& nombreArchivo, const std::vector<Medico>& medicos) {
    std::ofstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        archivo << "ID,Nombre,Especialidad,Disponible\n";

        for (const auto& medico : medicos) {
            archivo << medico.getId() << ","
                << medico.getNombre() << ","
                << medico.getEspecialidad() << ","
                << (medico.getDisponibilidad() ? "Si" : "No") << "\n";
        }
        archivo.close();
    }
    else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
    }
}

void Medico::asignarEspecialidad(int idMedico, const std::string& nuevaEspecialidad) {
    std::vector<Medico> medicos = leerMedicosDesdeCSV("medicos.csv");

    for (auto& medico : medicos) {
        if (medico.getId() == idMedico) {
            medico.especialidad = nuevaEspecialidad;
            break;
        }
    }

    escribirMedicosEnCSV("medicos.csv", medicos);
}

void Medico::cambiarDisponibilidad(int idMedico, bool nuevaDisponibilidad) {
    std::vector<Medico> medicos = leerMedicosDesdeCSV("medicos.csv");

    for (auto& medico : medicos) {
        if (medico.getId() == idMedico) {
            medico.disponibilidad = nuevaDisponibilidad;
            break;
        }
    }

    escribirMedicosEnCSV("medicos.csv", medicos);
}

void Medico::listarMedicosPorEspecialidad(const std::string& especialidad) {
    std::vector<Medico> medicos = leerMedicosDesdeCSV("medicos.csv");
    bool encontrado = false;

    for (const auto& medico : medicos) {
        if (medico.getEspecialidad() == especialidad) {
            medico.mostrarInformacion();
            encontrado = true;
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron médicos con la especialidad: " << especialidad << std::endl;
    }
}

void Medico::consultarMedico(int idMedico) {
    std::vector<Medico> medicos = leerMedicosDesdeCSV("medicos.csv");

    for (const auto& medico : medicos) {
        if (medico.getId() == idMedico) {
            medico.mostrarInformacion();
            return;
        }
    }

    std::cout << "Medico con ID " << idMedico << " no encontrado." << std::endl;
}



void Medico::mostrarInformacion() const {
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Especialidad: " << especialidad << std::endl;
    std::cout << "Disponibilidad: " << (disponibilidad ? "Disponible" : "No disponible") << std::endl;
}
