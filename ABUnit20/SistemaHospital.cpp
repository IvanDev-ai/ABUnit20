#include "SistemaHospital.h"

SistemaHospital::SistemaHospital() {
    crearBaseDeDatos();
}

void SistemaHospital::crearBaseDeDatos() {
    HistorialClinico historial1;
    historial1.agregarRegistro("Resfriado", "Descanso y liquidos");

    HistorialClinico historial2;
    historial2.agregarRegistro("Gripe", "Antivirales");

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

    Reporte reporte1(1, "Reporte A", "Contenido del Reporte A");
    Reporte reporte2(2, "Reporte B", "Contenido del Reporte B");
    reportes = { reporte1, reporte2 };
}

void SistemaHospital::crearMenu() {
    int opcion;

    do {
        std::cout << "\n--- MENU ---" << std::endl;
        std::cout << "1. Visitas el Hospital como Paciente" << std::endl;
        std::cout << "2. Trabajas en el Hospital como Medico" << std::endl;
        std::cout << "3. Gestion del Hospital" << std::endl;
        std::cout << "4. Salir" << std::endl;

        std::cout << "Seleccione una opción: ";
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
                Paciente::consultarPaciente(pacientes, idPaciente);
                break;
            }
            case 3: {
                int idMedico;
                std::cout << "Ingrese ID de tu medico: ";
                std::cin >> idMedico;
                Medico::consultarMedico(medicos, idMedico);
                break;
            }
            case 4: {
                int idCita;
                std::cout << "Ingrese ID de la cita: ";
                std::cin >> idCita;
                Cita::consultarCita(citas, idCita);
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
            std::cout << "Seleccione una opcion: ";
            std::cin >> opcionMedico;

            switch (opcionMedico) {
            case 1: {  // Gestion de Pacientes
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
                    HistorialClinico historial;
                    Paciente nuevoPaciente(nombre, id, fechaIngreso, historial);
                    Paciente::agregarPaciente(pacientes, nuevoPaciente);
                    pacientes.push_back(nuevoPaciente);
                    break;
                }
                case 2: {
                    int idPaciente;
                    std::cout << "Ingrese ID del paciente: ";
                    std::cin >> idPaciente;
                    Paciente::eliminarPaciente(pacientes, idPaciente);
                    break;
                }
                case 3: {
                    int idPaciente;
                    std::cout << "Ingrese ID del paciente: ";
                    std::cin >> idPaciente;
                    Paciente::consultarPaciente(pacientes, idPaciente);
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
                        std::string diagnostico, tratamiento;
                        std::cout << "Ingrese diagnostico: ";
                        std::getline(std::cin, diagnostico);
                        std::cout << "Ingrese tratamiento: ";
                        std::getline(std::cin, tratamiento);
                        paciente->getHistorial().agregarRegistro(diagnostico, tratamiento); 
                        std::cout << "Registro agregado correctamente." << std::endl;
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
            case 2: {  // Gestion de Medicos
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
                            medico.asignarEspecialidad(especialidad);
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
                            medico.cambiarDisponibilidad(disponibilidad);
                            break;
                        }
                    }
                    break;
                }
                case 3: {
                    int idMedico;
                    std::cout << "Ingrese ID del medico: ";
                    std::cin >> idMedico;
                    Medico::consultarMedico(medicos, idMedico);
                    break;
                }
                case 4: {
                    std::string especialidad;
                    std::cout << "Ingrese especialidad: ";
                    std::cin.ignore();
                    std::getline(std::cin, especialidad);
                    Medico::listarMedicosPorEspecialidad(medicos, especialidad);
                    break;
                }
                default:
                    std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
                    break;
                }
                break;
            }
            case 3: {  // Gestion de Citas
                int opcionCita;
                std::cout << "\n--- GESTION DE CITAS ---" << std::endl;
                std::cout << "1. Programar cita" << std::endl;
                std::cout << "2. Cancelar cita" << std::endl;
                std::cout << "3. Modificar cita" << std::endl;
                std::cout << "4. Consultar cita" << std::endl;
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
                        Cita::programarCita(citas, nuevaCita);
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
                    Cita::cancelarCita(citas, idCita);
                    break;
                }
                case 3: {
                    int idCita;
                    std::cout << "Ingrese ID de la cita: ";
                    std::cin >> idCita;
                    Cita::modificarCita(citas, idCita, pacientes, medicos);
                    break;
                }
                case 4: {
                    int idCita;
                    std::cout << "Ingrese ID de la cita: ";
                    std::cin >> idCita;
                    Cita::consultarCita(citas, idCita);
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
            int idReporte;
            std::cout << "Ingrese ID del reporte: ";
            std::cin >> idReporte;
            Reporte::consultarReportes(reportes, idReporte);
            break;
        }
        case 4:
            std::cout << "Saliendo del programa..." << std::endl;
            break;
        default:
            std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
            break;
        }
    } while (opcion != 4);
}

void SistemaHospital::ejecutarSistema() {
    crearBaseDeDatos();
    crearMenu();
}
