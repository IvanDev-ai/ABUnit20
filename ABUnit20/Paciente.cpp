#include "Paciente.h"

Paciente::Paciente(std::string nombre, int id, std::string fechaIngreso, std::vector<HistorialClinico> historial)
    : nombre(nombre), id(id), fechaIngreso(fechaIngreso), historial(historial) {
}

std::vector<Paciente> Paciente::leerPacientesDesdeCSV(const std::string& nombreArchivo)
{
    std::vector<Paciente> pacientes;
    std::ifstream archivo(nombreArchivo);
    std::string linea, nombre, fechaIngreso, historialClinicoStr;
    int id;

    if (archivo.is_open()) {
        
        std::getline(archivo, linea);

        
        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::getline(ss, nombre, ',');

            ss >> id;
            ss.ignore(1, ',');  

            std::getline(ss, fechaIngreso, ',');

            
            std::replace(fechaIngreso.begin(), fechaIngreso.end(), ',', '-');

            std::getline(ss, historialClinicoStr);

            
            std::vector<HistorialClinico> historial;
            std::stringstream historialStream(historialClinicoStr);
            std::string registro;

            while (std::getline(historialStream, registro, ';')) {
                if (registro.empty()) {
                    continue;
                }
                size_t pos = registro.find(": ");
                if (pos != std::string::npos) {
                    std::string enfermedad = registro.substr(0, pos);
                    std::string tratamiento = registro.substr(pos + 2);
                    historial.push_back(HistorialClinico(enfermedad, tratamiento));
                }
            }

          
            Paciente paciente(nombre, id, fechaIngreso, historial);
            pacientes.push_back(paciente);
        }
        archivo.close();
    }
    else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
    }
    return pacientes;
}


void Paciente::escribirPacientesEnCSV(const std::string& nombreArchivo, const std::vector<Paciente>& pacientes)
{
    std::ofstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        
        archivo << "Nombre,ID,FechaIngreso,HistorialClinico\n";

      
        for (const auto& paciente : pacientes) {
            
            std::string historialStr;
            for (const auto& registro : paciente.getHistorial()) {
                if (!historialStr.empty()) {
                    historialStr += "; ";  
                }
                historialStr += registro.getDiagnostico() + ": " + registro.getTratamiento();
            }

            
            archivo << paciente.getNombre() << ","
                << paciente.getId() << ","
                << paciente.getFechaIngreso() << ","
                << historialStr << "\n";
        }

        archivo.close();
    }
    else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
    }
}


void Paciente::modificarDatos(const std::string& nuevoNombre, const std::string& nuevaFechaIngreso) {
    std::vector<Paciente> pacientes = leerPacientesDesdeCSV("pacientes.csv");

    for (auto& paciente : pacientes) {
        if (paciente.getId() == id) {
            paciente.nombre = nuevoNombre;
            paciente.fechaIngreso = nuevaFechaIngreso;
            break;
        }
    }

    escribirPacientesEnCSV("pacientes.csv", pacientes);
}

void Paciente::agregarPaciente(Paciente paciente) {
    std::vector<Paciente> pacientes = leerPacientesDesdeCSV("pacientes.csv");
    pacientes.push_back(paciente);
    escribirPacientesEnCSV("pacientes.csv", pacientes);
}

void Paciente::eliminarPaciente(int idPaciente) {
    std::vector<Paciente> pacientes = leerPacientesDesdeCSV("pacientes.csv");

    for (auto it = pacientes.begin(); it != pacientes.end(); ++it) {
        if (it->getId() == idPaciente) {
            pacientes.erase(it);
            std::cout << "Paciente con ID " << idPaciente << " eliminado correctamente." << std::endl;
            escribirPacientesEnCSV("pacientes.csv", pacientes);
            return;
        }
    }

    std::cout << "Paciente con ID " << idPaciente << " no encontrado." << std::endl;
}

void Paciente::consultarPaciente(int idPaciente) {
    std::vector<Paciente> pacientes = leerPacientesDesdeCSV("pacientes.csv");

    for (const auto& paciente : pacientes) {
        if (paciente.getId() == idPaciente) {
            paciente.mostrarInformacion();
            return;
        }
    }

    std::cout << "Paciente con ID " << idPaciente << " no encontrado." << std::endl;
}

void Paciente::agregarRegistroHistorial(int idPaciente, const std::string& diagnostico, const std::string& tratamiento)
{

    
    HistorialClinico registro(diagnostico, tratamiento);

  
    historial.push_back(registro);

    
    std::vector<Paciente> pacientes = leerPacientesDesdeCSV("pacientes.csv");

    
    for (auto& paciente : pacientes) {
        if (idPaciente == id) {
            paciente.historial = historial;
            break;
        }
    }

    
    escribirPacientesEnCSV("pacientes.csv", pacientes);
}



void Paciente::mostrarInformacion() const {
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Fecha de Ingreso: " << fechaIngreso << std::endl;
    for (int i = 0; i < historial.size(); i++)
        std::cout << historial[i].mostrarInformacion() << " ";
}
