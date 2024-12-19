#include "SistemaHospital.h"
namespace fs = std::filesystem;
#ifdef _WIN32
#define localtime_safe localtime_s
#else
#define localtime_safe localtime_r
#endif
SistemaHospital::SistemaHospital() {
    crearBaseDeDatos();
}
void SistemaHospital::crearBaseDeDatos() {
    HistorialClinico registro1("Resfriado", "Descanso y liquidos", true);
    HistorialClinico registro2("Gripe", "Antivirales", false);
    std::vector<HistorialClinico> historial1;
    std::vector<HistorialClinico> historial2;
    historial1.push_back(registro1);
    historial2.push_back(registro2);

    Paciente paciente1("Ana Garcia", 1001, "2024-11-20", historial1);
    Paciente paciente2("Carlos Lopez", 1002, "2024-11-21", historial2);
    Paciente paciente3("Elena Martinez", 1003, "2024-11-22", historial1);
    pacientes = { paciente1, paciente2, paciente3 };

    Medico medico1("Dr. Juan Perez", 101, "Cardiologia", true);
    Medico medico2("Dra. Ana Gomez", 102, "Pediatria", false);
    Medico medico3("Dr. Carlos Sanchez", 103, "Traumatologia", true);
    medicos = { medico1, medico2, medico3 };

    Cita cita1(11, paciente1, medico1, "2023-11-26 10:00", "Urgente");
    Cita cita2(12, paciente2, medico2, "2023-11-27 15:00", "Normal");
    citas = { cita1, cita2 };

    // Archivo CSV para Pacientes
    std::ofstream archivoPacientes("pacientes.csv");
    archivoPacientes << "Nombre,ID,FechaIngreso,HistorialClinico\n";
    for (const auto& paciente : pacientes) {
        archivoPacientes << paciente.getNombre() << ","
            << paciente.getId() << ","
            << paciente.getFechaIngreso() << ",";
        for (const auto& historial : paciente.getHistorial()) {
            archivoPacientes << historial.getDiagnostico() << ": " << historial.getTratamiento() << "; " << (historial.getEnfermedadCronica() ? "Enfermedad Cronica" : "Enfermedad Normal");
        }
        archivoPacientes << "\n";
    }
    archivoPacientes.close();

    // Archivo CSV para Medicos
    std::ofstream archivoMedicos("medicos.csv");
    archivoMedicos << "ID,Nombre,Especialidad,Disponible\n";
    for (const auto& medico : medicos) {
        archivoMedicos << medico.getId() << ","
            << medico.getNombre() << ","
            << medico.getEspecialidad() << ","
            << (medico.getDisponibilidad() ? "Si" : "No") << "\n";
    }
    archivoMedicos.close();

    // Archivo CSV para Citas
    std::ofstream archivoCitas("citas.csv");
    archivoCitas << "ID,Paciente,Medico,FechaHora,Prioridad\n";
    for (const auto& cita : citas) {
        archivoCitas << cita.getId() << ","
            << cita.getPaciente().getNombre() << ","
            << cita.getMedico().getNombre() << ","
            << cita.getFecha() << ","
            << cita.getPrioridad() << "\n";
    }
    archivoCitas.close();

}

void SistemaHospital::crearMenu() {
    int opcion;

    do {
        std::cout << "\n--- MENU ---" << std::endl;
        std::cout << "1. Visitas el Hospital como Paciente" << std::endl;
        std::cout << "2. Trabajas en el Hospital como Medico" << std::endl;
        std::cout << "3. Gestion del Hospital" << std::endl;
        std::cout << "4. Salir" << std::endl;

        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1: {
            int opcionPaciente;
            std::cout << "\n--- MENU PACIENTE ---" << std::endl;
            std::cout << "1. Modificar datos" << std::endl;
            std::cout << "2. Consultar tus datos de paciente" << std::endl;
            std::cout << "3. Consultar disponibilidad de tu medico" << std::endl;
            std::cout << "4. Consultar cita" << std::endl;
            std::cout << "Seleccione una opcion: ";
            std::cin >> opcionPaciente;

            switch (opcionPaciente) {
            case 1: {
                int idPaciente;
                std::string nuevoNombre, nuevaFechaIngreso;
                std::cout << "Ingrese tu ID: ";
                std::cin >> idPaciente;
                std::cin.ignore();
                std::cout << "Ingrese nuevo nombre: ";
                std::getline(std::cin, nuevoNombre);
                std::cout << "Ingrese nueva fecha de ingreso (YYYY-MM-DD): ";
                std::getline(std::cin, nuevaFechaIngreso);
                for (auto& paciente : pacientes) {
                    if (paciente.getId() == idPaciente) {
                        paciente.modificarDatos(nuevoNombre, nuevaFechaIngreso);
                        break;
                    }
                }
                break;
            }
            case 2: {
                int idPaciente;
                std::cout << "Ingrese tu ID: ";
                std::cin >> idPaciente;
                Paciente::consultarPaciente(idPaciente);
                break;
            }
            case 3: {
                int idMedico;
                std::cout << "Ingrese ID de tu medico: ";
                std::cin >> idMedico;
                Medico::consultarMedico(idMedico);
                break;
            }
            case 4: {
                int idCita;
                std::cout << "Ingrese ID de la cita: ";
                std::cin >> idCita;
                Cita::consultarCita(idCita);
                break;
            }
            default:
                std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
                break;
            }
            break;
        }
        case 2: {
            int opcionMedico;
            std::cout << "\n--- MENU MEDICO ---" << std::endl;
            std::cout << "1. Gestion de Pacientes" << std::endl;
            std::cout << "2. Gestion de Medicos" << std::endl;
            std::cout << "3. Gestion de Citas" << std::endl;
            std::cout << "4. Gestion de Reportes" << std::endl;
            std::cout << "Seleccione una opcion: ";
            std::cin >> opcionMedico;

            switch (opcionMedico) {
            case 1: {
                int opcionPaciente;
                std::cout << "\n--- GESTION DE PACIENTES ---" << std::endl;
                std::cout << "1. Agregar paciente" << std::endl;
                std::cout << "2. Eliminar paciente" << std::endl;
                std::cout << "3. Consultar paciente" << std::endl;
                std::cout << "4. Agregar registro al historial clinico" << std::endl;
                std::cout << "Seleccione una opcion: ";
                std::cin >> opcionPaciente;

                switch (opcionPaciente) {
                case 1: {
                    std::string nombre, fechaIngreso;
                    int id;
                    std::cout << "Ingrese nombre del paciente: ";
                    std::cin.ignore();
                    std::getline(std::cin, nombre);
                    std::cout << "Ingrese ID del paciente: ";
                    std::cin >> id;
                    std::cin.ignore();
                    std::cout << "Ingrese fecha de ingreso (YYYY-MM-DD): ";
                    std::getline(std::cin, fechaIngreso);
                    std::vector<HistorialClinico> historial;
                    Paciente nuevoPaciente(nombre, id, fechaIngreso, historial);
                    Paciente::agregarPaciente(nuevoPaciente);
                    break;
                }
                case 2: {
                    int idPaciente;
                    std::cout << "Ingrese ID del paciente: ";
                    std::cin >> idPaciente;
                    Paciente::eliminarPaciente(idPaciente);
                    break;
                }
                case 3: {
                    int idPaciente;
                    std::cout << "Ingrese ID del paciente: ";
                    std::cin >> idPaciente;
                    Paciente::consultarPaciente(idPaciente);
                    break;
                }
                case 4: {
                    int idPaciente;
                    std::cout << "Ingrese ID del paciente: ";
                    std::cin >> idPaciente;
                    std::cin.ignore();

                    auto paciente = std::find_if(pacientes.begin(), pacientes.end(), [idPaciente](const Paciente& p) {
                        return p.getId() == idPaciente;
                        });

                    if (paciente != pacientes.end()) {
                        std::string diagnostico, tratamiento, enfermedadCronicaStr;
                        std::cout << "Ingrese diagnostico: ";
                        std::getline(std::cin, diagnostico);
                        std::cout << "Ingrese tratamiento: ";
                        std::getline(std::cin, tratamiento);
                        std::cout << "Es una enfermedad Cronica? (solo responder Si o No): ";
                        std::getline(std::cin, enfermedadCronicaStr);
                        bool enfermedadCronica = (enfermedadCronicaStr == "Si");
                        paciente->agregarRegistroHistorial(idPaciente, diagnostico, tratamiento, enfermedadCronica);
                    }
                    else {
                        std::cout << "Paciente no encontrado." << std::endl;
                    }
                    break;
                }
                default:
                    std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
                    break;
                }
                break;
            }
            case 2: {
                int opcionMedico;
                std::cout << "\n--- GESTION DE MEDICOS ---" << std::endl;
                std::cout << "1. Asignar especialidad de medico" << std::endl;
                std::cout << "2. Cambiar disponibilidad de medico" << std::endl;
                std::cout << "3. Consultar medico" << std::endl;
                std::cout << "4. Listar medicos por especialidad" << std::endl;
                std::cout << "Seleccione una opcion: ";
                std::cin >> opcionMedico;

                switch (opcionMedico) {
                case 1: {
                    int idMedico;
                    std::string especialidad;
                    std::cout << "Ingrese ID del medico: ";
                    std::cin >> idMedico;
                    std::cin.ignore();
                    std::cout << "Ingrese especialidad del medico: ";
                    std::getline(std::cin, especialidad);
                    for (auto& medico : medicos) {
                        if (medico.getId() == idMedico) {
                            medico.asignarEspecialidad(idMedico, especialidad);
                            break;
                        }
                    }
                    break;
                }
                case 2: {
                    int idMedico;
                    bool disponibilidad;
                    std::cout << "Ingrese ID del medico: ";
                    std::cin >> idMedico;
                    std::cout << "Ingrese disponibilidad del medico (1 para disponible, 0 para no disponible): ";
                    std::cin >> disponibilidad;
                    for (auto& medico : medicos) {
                        if (medico.getId() == idMedico) {
                            medico.cambiarDisponibilidad(idMedico, disponibilidad);
                            break;
                        }
                    }
                    break;
                }
                case 3: {
                    int idMedico;
                    std::cout << "Ingrese ID del medico: ";
                    std::cin >> idMedico;
                    Medico::consultarMedico(idMedico);
                    break;
                }
                case 4: {
                    std::string especialidad;
                    std::cout << "Ingrese especialidad: ";
                    std::cin.ignore();
                    std::getline(std::cin, especialidad);
                    Medico::listarMedicosPorEspecialidad(especialidad);
                    break;
                }
                default:
                    std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
                    break;
                }
                break;
            }
            case 3: {
                int opcionCita;
                std::cout << "\n--- GESTION DE CITAS ---" << std::endl;
                std::cout << "1. Programar cita" << std::endl;
                std::cout << "2. Cancelar cita" << std::endl;
                std::cout << "3. Modificar cita" << std::endl;
                std::cout << "4. Consultar cita" << std::endl;
                std::cout << "5. Ordenar citas por Urgencia" << std::endl;
                std::cout << "Seleccione una opcion: ";
                std::cin >> opcionCita;

                switch (opcionCita) {
                case 1: {
                    int idCita, idPaciente, idMedico;
                    std::string fecha, prioridad;
                    std::cout << "Ingrese ID de la cita: ";
                    std::cin >> idCita;
                    std::cout << "Ingrese ID del paciente: ";
                    std::cin >> idPaciente;
                    std::cout << "Ingrese ID del medico: ";
                    std::cin >> idMedico;
                    std::cin.ignore();
                    std::cout << "Ingrese fecha de la cita (YYYY-MM-DD HH:MM): ";
                    std::getline(std::cin, fecha);
                    std::cout << "Ingrese prioridad de la cita (e.g., baja, urgente): ";
                    std::getline(std::cin, prioridad);
                    auto paciente = std::find_if(pacientes.begin(), pacientes.end(), [idPaciente](const Paciente& p) { return p.getId() == idPaciente; });
                    auto medico = std::find_if(medicos.begin(), medicos.end(), [idMedico](const Medico& m) { return m.getId() == idMedico; });
                    if (paciente != pacientes.end() && medico != medicos.end()) {
                        Cita nuevaCita(idCita, *paciente, *medico, fecha, prioridad);
                        Cita::programarCita(nuevaCita);
                    }
                    else {
                        std::cout << "Paciente o Medico no encontrado." << std::endl;
                    }
                    break;
                }
                case 2: {
                    int idCita;
                    std::cout << "Ingrese ID de la cita: ";
                    std::cin >> idCita;
                    Cita::cancelarCita(idCita);
                    break;
                }
                case 3: {
                    int idCita;
                    std::cout << "Ingrese ID de la cita: ";
                    std::cin >> idCita;
                    Cita::modificarCita(idCita);
                    break;
                }
                case 4: {
                    int idCita;
                    std::cout << "Ingrese ID de la cita: ";
                    std::cin >> idCita;
                    Cita::consultarCita(idCita);
                    break;
                }
                case 5: {
                    std::string urgencia;
                    std::cout << "Ingrese el tipo de urgencia: ";
                    std::cin >> urgencia;
                    Cita::listarCitasPorUrgencia(urgencia);
                    break;
                }
                default:
                    std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
                    break;
                }
                break;
            }
            case 4: {
                int opcionReporte;
                std::cout << "\n--- GESTION DE REPORTES ---" << std::endl;
                std::cout << "1. Listar Pacientes por fecha de ingreso" << std::endl;
                std::cout << "2. Listar Citas pendientes por medico o especialidad" << std::endl;
                std::cout << "3. Listar Pacientes con Enfermedades Cronicas" << std::endl;
                std::cout << "Seleccione una opcion: ";
                std::cin >> opcionReporte;

                switch (opcionReporte) {
                case 1: {
                    std::string fecha1, fecha2;
                    std::cout << "Ingrese Fecha de inicio: ";
                    std::cin >> fecha1;
                    std::cin.ignore();
                    std::cout << "Ingrese Fecha de fin: ";
                    std::cin >> fecha2;
                    Paciente::listarPacientesPorRangoDeFechas(fecha1, fecha2);
                    break;
                }
                case 2: {
                    int subopcion;
                    std::cout << "Listar citas pendientes por:\n";
                    std::cout << "1. Medico\n";
                    std::cout << "2. Especialidad\n";
                    std::cout << "Seleccione una opcion: ";
                    std::cin >> subopcion;

                    std::string criterio;
                    if (subopcion == 1) {
                        std::cout << "Ingrese el nombre del medico: ";
                        std::cin.ignore();
                        std::getline(std::cin, criterio);
                        Cita::listarCitasPendientes(criterio, false);
                    }
                    else if (subopcion == 2) {
                        std::cout << "Ingrese la especialidad: ";
                        std::cin.ignore();
                        std::getline(std::cin, criterio);
                        Cita::listarCitasPendientes(criterio, true);
                    }
                    else {
                        std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
                    }
                    break;
                }
                case 3: {
                    std::cout << "Listando pacientes con enfermedades crónicas..." << std::endl;
                    Paciente::listarPacientesConEnfermedadesCronicas();
                    break;
                }
                default:
                    std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
                    break;
                }
                break;
            }
            default:
                std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
                break;
            }
            break;
        }

        case 3: {
            int opcionGestion;
            std::cout << "\n--- GESTION DE HOSPITAL ---" << std::endl;
            std::cout << "1. Copia de 1 archivo" << std::endl;
            std::cout << "2. BackUp completo" << std::endl;
            std::cout << "Seleccione una opcion: ";
            std::cin >> opcionGestion;
            switch (opcionGestion) {
            case 1: {
                int archivoOpcion;
                std::cout << "\n--- SELECCIONAR ARCHIVO ---" << std::endl;
                std::cout << "1. Pacientes\n";
                std::cout << "2. Medicos\n";
                std::cout << "3. Citas\n";
                std::cout << "Seleccione un archivo para hacer la copia: ";
                std::cin >> archivoOpcion;
                std::string nombreArchivo;

                switch (archivoOpcion) {
                case 1:
                    nombreArchivo = "pacientes.csv";
                    break;
                case 2:
                    nombreArchivo = "medicos.csv";
                    break;
                case 3:
                    nombreArchivo = "citas.csv";
                    break;
                default:
                    std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
                    break;
                }

                if (!nombreArchivo.empty()) {
                    realizarCopiaCSV(nombreArchivo);
                }
                break;
                break;
            }
            case 2: {
                realizarCopiaBBDD();
                break;
            }
            default:
                std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
                break;
            }
            break;
        }
        case 4: {
            std::cout << "Saliendo del programa..." << std::endl;
            break;
        }

        default:
            std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
            break;
        }
    } while (opcion != 4);
}



void SistemaHospital::realizarCopiaCSV(const std::string& nombreArchivo) {
    try {
        fs::path archivoOriginal = nombreArchivo;
        if (fs::exists(archivoOriginal)) {
            std::time_t t = std::time(nullptr);
            std::tm tm;
            localtime_safe(&tm, &t);

            std::ostringstream oss;
            oss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
            std::string timestamp = oss.str();

            fs::path archivoCopia = archivoOriginal.stem().string() + "_" + timestamp + archivoOriginal.extension().string();
            fs::copy_file(archivoOriginal, archivoCopia);
            std::cout << "Copia de seguridad de " << nombreArchivo << " creada como " << archivoCopia << std::endl;
        }
        else {
            std::cerr << "El archivo " << nombreArchivo << " no existe." << std::endl;
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Error al realizar la copia de seguridad: " << e.what() << std::endl;
    }
}
void SistemaHospital::realizarCopiaBBDD() {
    try {
        std::time_t t = std::time(nullptr);
        std::tm tm;
        localtime_safe(&tm, &t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
        std::string timestamp = oss.str();

        fs::path directorioCopia = "Backup_" + timestamp;
        fs::create_directory(directorioCopia);

        std::vector<std::string> archivos = { "pacientes.csv", "citas.csv", "medicos.csv" };
        for (const auto& archivo : archivos) {
            fs::path archivoOriginal = archivo;
            if (fs::exists(archivoOriginal)) {
                fs::path archivoCopia = directorioCopia / archivoOriginal.filename();
                fs::copy_file(archivoOriginal, archivoCopia);
                std::cout << "Copia de seguridad de " << archivo << " creada en " << archivoCopia << std::endl;
            }
            else {
                std::cerr << "El archivo " << archivo << " no existe." << std::endl;
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Error al realizar la copia de seguridad: " << e.what() << std::endl;
    }
}


void SistemaHospital::ejecutarSistema() {
    crearBaseDeDatos();
    crearMenu();
}
