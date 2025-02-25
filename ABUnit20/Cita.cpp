#include "Cita.h"

Cita::Cita(int id, Paciente paciente, Medico medico, const std::string& fecha, const std::string& prioridad)
    : id(id), paciente(paciente), medico(medico), fecha(fecha), prioridad(prioridad) {
}

// Buscar un paciente por nombre
Paciente buscarPaciente(const std::string nombrePaciente) {
    std::vector<Paciente> pacientes = Paciente::leerPacientesDesdeCSV("pacientes.csv");

    for (auto& paciente : pacientes) {
        if (paciente.getNombre() == nombrePaciente) {
            return paciente;
        }
    }

    throw std::runtime_error("Paciente no encontrado");
}

// Buscar un m�dico por nombre
Medico buscarMedico(const std::string nombreMedico) {
    std::vector<Medico> medicos = Medico::leerMedicosDesdeCSV("medicos.csv");

    for (auto& medico : medicos) {
        if (medico.getNombre() == nombreMedico) {
            return medico;
        }
    }

    throw std::runtime_error("M�dico no encontrado");
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

    // Verificar si el ID de la cita ya existe
    for (const auto& c : citas) {
        if (c.getId() == cita.getId()) {
            std::cout << "Error: Ya existe una cita con el mismo ID.\n";
            return;
        }
    }

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
    std::vector<Paciente> pacientes = Paciente::leerPacientesDesdeCSV("pacientes.csv");
    std::vector<Medico> medicos = Medico::leerMedicosDesdeCSV("medicos.csv");

    auto it = std::find_if(citas.begin(), citas.end(), [idCita](const Cita& cita) {
        return cita.getId() == idCita;
        });

    if (it != citas.end()) {
        int opcion;
        std::cout << "�Qu� deseas modificar?\n";
        std::cout << "1. Paciente\n";
        std::cout << "2. Medico\n";
        std::cout << "3. Fecha\n";
        std::cout << "4. Prioridad\n";
        std::cout << "Elige una opci�n: ";
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
            std::cout << "Opci�n no v�lida." << std::endl;
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

void Cita::cambiarNombrePaciente(const std::string& nuevoNombre) {
    paciente.setNombre(nuevoNombre);

    std::vector<Cita> citas = leerCitasDesdeCSV("citas.csv");

    for (auto& cita : citas) {
        if (cita.getId() == id) {
            cita.paciente.setNombre(nuevoNombre);  
            break;
        }
    }

    escribirCitasEnCSV("citas.csv", citas);
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