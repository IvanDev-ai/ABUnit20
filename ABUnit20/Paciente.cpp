#include "Paciente.h"

Paciente::Paciente( std::string nombre, int id, std::string fechaIngreso, std::vector<HistorialClinico> historial)
    : nombre(nombre), id(id), fechaIngreso(fechaIngreso), historial(historial) {
}

std::vector<Paciente> Paciente::leerPacientesDesdeCSV(const std::string& nombreArchivo) {
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

            size_t enfermedadPos = historialClinicoStr.find(";"); 
            if (enfermedadPos != std::string::npos) {
                std::string tratamiento = historialClinicoStr.substr(0, enfermedadPos); 
                std::string enfermedadCronicaStr = historialClinicoStr.substr(enfermedadPos + 2); 


                bool enfermedadCronica = (enfermedadCronicaStr == "Enfermedad Cronica"); 

                size_t pos = tratamiento.find(": ");
                if (pos != std::string::npos) {
                    std::string diagnostico = tratamiento.substr(0, pos);  
                    std::string tratamientoStr = tratamiento.substr(pos + 2); 

                    historial.push_back(HistorialClinico(diagnostico, tratamientoStr, enfermedadCronica));  
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


void Paciente::escribirPacientesEnCSV(const std::string& nombreArchivo, const std::vector<Paciente>& pacientes) {
    std::ofstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        archivo << "Nombre,ID,FechaIngreso,HistorialClinico\n";

        for (const auto& paciente : pacientes) {
            std::string historialClinicoStr;

            for (const auto& registro : paciente.getHistorial()) {
                if (!historialClinicoStr.empty()) {
                    historialClinicoStr += "; ";  
                }

                historialClinicoStr += registro.getDiagnostico() + ": " + registro.getTratamiento() +
                    (registro.getEnfermedadCronica() ? "; Enfermedad Cronica" : "; Enfermedad Normal");
            }

            archivo << paciente.getNombre() << ","
                << paciente.getId() << ","
                << paciente.getFechaIngreso() << ","
                << historialClinicoStr << "\n";
        }

        archivo.close();
    }
    else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
    }
}

// "YYYY-MM-DD" a "YYYYMMDD"
std::string actualizarFecha(const std::string& fecha) {
    std::string comparableFecha = fecha;
    comparableFecha.erase(std::remove(comparableFecha.begin(), comparableFecha.end(), '-'), comparableFecha.end());
    return comparableFecha;
}


void Paciente::listarPacientesPorRangoDeFechas(const std::string& fechaInicio, const std::string& fechaFin) {
    std::vector<Paciente> pacientes = Paciente::leerPacientesDesdeCSV("pacientes.csv");
    std::vector<Paciente> pacientesEnRango;
    std::string fechaInicioComparable = actualizarFecha(fechaInicio);
    std::string fechaFinComparable = actualizarFecha(fechaFin);

    for (const auto& paciente : pacientes) {
        std::string fechaIngresoComparable = actualizarFecha(paciente.getFechaIngreso());
        if (fechaIngresoComparable >= fechaInicioComparable && fechaIngresoComparable <= fechaFinComparable) {
            pacientesEnRango.push_back(paciente);
        }
    }

    std::sort(pacientesEnRango.begin(), pacientesEnRango.end(), [](const Paciente& a, const Paciente& b) {
        return actualizarFecha(a.getFechaIngreso()) > actualizarFecha(b.getFechaIngreso());
        });

    for (const auto& paciente : pacientesEnRango) {
        paciente.mostrarInformacion();
        std::cout << std::endl;
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

    // Verificar si el ID del paciente ya existe
    for (const auto& p : pacientes) {
        if (p.getId() == paciente.getId()) {
            std::cout << "Error: Ya existe un paciente con el mismo ID.\n";
            return;
        }
    }
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

void Paciente::agregarRegistroHistorial(int idPaciente, const std::string& diagnostico, const std::string& tratamiento, bool& enfermedadCronica)
{

    HistorialClinico registro(diagnostico, tratamiento, enfermedadCronica);

    std::vector<Paciente> pacientes = leerPacientesDesdeCSV("pacientes.csv");

    for (auto& paciente : pacientes) {
        if (idPaciente == paciente.id) {
            paciente.historial.push_back(registro);
            break;
        }
    }

    escribirPacientesEnCSV("pacientes.csv", pacientes);
}

void Paciente::listarPacientesConEnfermedadesCronicas() {
    std::vector<Paciente> pacientes = leerPacientesDesdeCSV("pacientes.csv");
    bool found = false; 

    for (const auto& paciente : pacientes) {
        for (const auto& registro : paciente.getHistorial()) {
            if (registro.getEnfermedadCronica()) { 
                paciente.mostrarInformacion();  
                found = true; 
                break;  
            }
        }
    }

    if (!found) {
        std::cout << "No se encontraron pacientes con enfermedades crónicas." << std::endl;
    }
}

void Paciente::mostrarInformacion() const {
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Fecha de Ingreso: " << fechaIngreso << std::endl;
    for (int i = 0; i < historial.size(); i++)
        std::cout << historial[i].mostrarInformacion();
}
