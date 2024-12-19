#include "Cita.h"

Cita::Cita(int id, Paciente paciente, Medico medico, const std::string& fecha, const std::string& prioridad)
    : id(id), paciente(paciente), medico(medico), fecha(fecha), prioridad(prioridad) {
}

std::vector<Paciente> leerPacientesDesdeCSV(const std::string& nombreArchivo)
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
                    std::string enfermedadCronicaStr = registro.substr(pos + 3);
                    bool enfermedadCronica = (enfermedadCronicaStr == "true");
                    historial.push_back(HistorialClinico(enfermedad, tratamiento, enfermedadCronica));
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

std::vector<Medico> leerMedicosDesdeCSV(const std::string& nombreArchivo) {
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

// Buscar un paciente por nombre
Paciente buscarPaciente(const std::string nombrePaciente) {
    std::vector<Paciente> pacientes = leerPacientesDesdeCSV("pacientes.csv");

    for (auto& paciente : pacientes) {
        if (paciente.getNombre() == nombrePaciente) {
            return paciente;
        }
    }

    throw std::runtime_error("Paciente no encontrado");
}

// Buscar un médico por nombre
Medico buscarMedico(const std::string nombreMedico) {
    std::vector<Medico> medicos = leerMedicosDesdeCSV("medicos.csv");

    for (auto& medico : medicos) {
        if (medico.getNombre() == nombreMedico) {
            return medico;
        }
    }

    throw std::runtime_error("Médico no encontrado");
}
std::vector<Cita> Cita::leerCitasDesdeCSV(const std::string& nombreArchivo) {
    std::vector<Cita> citas;
    std::ifstream archivo(nombreArchivo);
    std::string linea, nombrePaciente, nombreMedico, fecha, prioridad;
    int id;

    if (archivo.is_open()) {
        std::getline(archivo, linea);

        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);


            ss >> id;
            ss.ignore(1, ',');
            std::getline(ss, nombrePaciente, ',');
            std::getline(ss, nombreMedico, ',');
            std::getline(ss, fecha, ',');
            std::getline(ss, prioridad);


            Paciente paciente = buscarPaciente(nombrePaciente);
            Medico medico = buscarMedico(nombreMedico);


            Cita nuevaCita(id, paciente, medico, fecha, prioridad);
            citas.push_back(nuevaCita);
        }
        archivo.close();
    }
    else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
    }

    return citas;
}

void Cita::escribirCitasEnCSV(const std::string& nombreArchivo, const std::vector<Cita>& citas) {
    std::ofstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        archivo << "ID,Paciente,Medico,FechaHora,Prioridad\n";

        for (const auto& cita : citas) {
            archivo << cita.getId() << ","
                << cita.getPaciente().getNombre() << ","
                << cita.getMedico().getNombre() << ","
                << cita.getFecha() << ","
                << cita.getPrioridad() << "\n";
        }
        archivo.close();
    }
    else {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
    }
}

void Cita::programarCita(const Cita& cita) {
    std::vector<Cita> citas = leerCitasDesdeCSV("citas.csv");
    citas.push_back(cita);
    escribirCitasEnCSV("citas.csv", citas);
}

void Cita::cancelarCita(int idCita) {
    std::vector<Cita> citas = leerCitasDesdeCSV("citas.csv");
    auto it = std::remove_if(citas.begin(), citas.end(), [idCita](const Cita& cita) {
        return cita.getId() == idCita;
        });

    if (it != citas.end()) {
        citas.erase(it, citas.end());
        escribirCitasEnCSV("citas.csv", citas);
    }
    else {
        std::cout << "Cita no encontrada." << std::endl;
    }
}

void Cita::modificarCita(int idCita) {
    std::vector<Cita> citas = leerCitasDesdeCSV("citas.csv");
    std::vector<Paciente> pacientes = leerPacientesDesdeCSV("pacientes.csv");
    std::vector<Medico> medicos = leerMedicosDesdeCSV("medicos.csv");

    auto it = std::find_if(citas.begin(), citas.end(), [idCita](const Cita& cita) {
        return cita.getId() == idCita;
        });

    if (it != citas.end()) {
        int opcion;
        std::cout << "¿Qué deseas modificar?\n";
        std::cout << "1. Paciente\n";
        std::cout << "2. Medico\n";
        std::cout << "3. Fecha\n";
        std::cout << "4. Prioridad\n";
        std::cout << "Elige una opción: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1: {
            std::string nuevoNombrePaciente;
            std::cout << "Introduce el nuevo nombre del paciente (Tiene que existir en pacientes.csv primero): ";
            std::cin.ignore();
            std::getline(std::cin, nuevoNombrePaciente);
            Paciente nuevoPaciente = buscarPaciente(nuevoNombrePaciente);
            if (nuevoPaciente.getId() != -1) {
                it->paciente = nuevoPaciente;
            }
            else {
                std::cout << "Paciente no encontrado." << std::endl;
            }
            break;
        }
        case 2: {
            std::string nuevoNombreMedico;
            std::cout << "Introduce el nuevo nombre del medico (Tiene que existir en medicos.csv primero): ";
            std::cin.ignore();
            std::getline(std::cin, nuevoNombreMedico);
            Medico nuevoMedico = buscarMedico(nuevoNombreMedico);
            if (nuevoMedico.getId() != -1) {
                it->medico = nuevoMedico;
            }
            else {
                std::cout << "Medico no encontrado." << std::endl;
            }
            break;
        }
        case 3: {
            std::cout << "Introduce la nueva fecha de la cita (formato: YYYY-MM-DD HH:MM): ";
            std::cin.ignore();
            std::getline(std::cin, it->fecha);
            break;
        }
        case 4: {
            std::cout << "Introduce la nueva prioridad (e.g., baja, urgente): ";
            std::cin.ignore();
            std::getline(std::cin, it->prioridad);
            break;
        }
        default:
            std::cout << "Opción no válida." << std::endl;
        }

        escribirCitasEnCSV("citas.csv", citas);
        std::cout << "Cita modificada correctamente." << std::endl;
    }
    else {
        std::cout << "Cita no encontrada." << std::endl;
    }
}


void Cita::consultarCita(int idCita) {
    std::vector<Cita> citas = leerCitasDesdeCSV("citas.csv");
    auto it = std::find_if(citas.begin(), citas.end(), [idCita](const Cita& cita) {
        return cita.getId() == idCita;
        });

    if (it != citas.end()) {
        it->mostrarInformacion();
    }
    else {
        std::cout << "Cita no encontrada." << std::endl;
    }
}

void Cita::listarCitasPendientes(const std::string& criterio, bool esEspecialidad) {
    std::vector<Cita> citas = leerCitasDesdeCSV("citas.csv");
    std::vector<Cita> citasPendientes;

    for (const auto& cita : citas) {
        if (esEspecialidad) {
            if (cita.getMedico().getEspecialidad() == criterio) {
                citasPendientes.push_back(cita);
            }
        }
        else {
            if (cita.getMedico().getNombre() == criterio) {
                citasPendientes.push_back(cita);
            }
        }
    }

    if (citasPendientes.empty()) {
        if (esEspecialidad) {
            std::cout << "No se encontraron citas pendientes para la especialidad: " << criterio << std::endl;
        }
        else {
            std::cout << "No se encontraron citas pendientes para el medico: " << criterio << std::endl;
        }
    }
    else {
        std::sort(citasPendientes.begin(), citasPendientes.end(), [](const Cita& a, const Cita& b) {
            return a.getFecha() > b.getFecha();
            });

        for (const auto& cita : citasPendientes) {
            cita.mostrarInformacion();
            std::cout << std::endl;
        }
    }
}

void Cita::listarCitasPorUrgencia(const std::string& urgencia) {
    std::vector<Cita> citas = leerCitasDesdeCSV("citas.csv");
    std::vector<Cita> citasFiltradas;

    for (const auto& cita : citas) {
        if (cita.getPrioridad() == urgencia) {
            citasFiltradas.push_back(cita);
        }
    }

    if (citasFiltradas.empty()) {
        std::cout << "No se encontraron citas con la urgencia: " << urgencia << std::endl;
        return;
    }

    for (const auto& cita : citasFiltradas) {
        cita.mostrarInformacion();
        std::cout << std::endl;
    }
}



void Cita::mostrarInformacion() const {
    std::cout << "ID: " << id << std::endl;
    std::cout << "Paciente: " << std::endl;
    paciente.mostrarInformacion();
    std::cout << "Medico: " << std::endl;
    medico.mostrarInformacion();
    std::cout << "Fecha y Hora: " << fecha << std::endl;
    std::cout << "Prioridad: " << prioridad << std::endl;
}
