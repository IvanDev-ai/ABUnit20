#include "SistemaHospital.h"


SistemaHospital::SistemaHospital() {}

void SistemaHospital::crearBaseDeDatos() {
    HistorialClinico historial1;
    historial1.agregarRegistro("Resfriado", "Descanso y liquidos");

    HistorialClinico historial2;
    historial2.agregarRegistro("Gripe", "Antivirales");


    Paciente paciente1("Ana Garcia", 1001, "2024-11-20", historial1);
    Paciente paciente2("Carlos Lopez", 1002, "2024-11-21", historial2);
    Paciente paciente3("Elena Martinez", 1003, "2024-11-22", historial1);
    std::vector<Paciente> pacientes = { paciente1, paciente2, paciente3 };

    Paciente::consultarPaciente(paciente1);
    Paciente::consultarPaciente(paciente2);
    Paciente::consultarPaciente(paciente3);

    Medico medico1("Dr. Juan Perez", 101, "Cardiologia", true);
    Medico medico2("Dra. Ana Gomez", 102, "Pediatria", false);
    Medico medico3("Dr. Carlos Sanchez", 103, "Traumatologia", true);
    std::vector<Medico> medicos = { medico1, medico2, medico3 };

    Medico::consultarMedico(medico1);

    Cita cita1(paciente1, medico1, "2023-11-26 10:00", "Urgente");
    Cita cita2(paciente2, medico2, "2023-11-27 15:00", "Normal");
    std::vector<Cita> citas = { cita1, cita2 };

    Cita::consultarCita(cita1);
}

static void agregarPaciente(Paciente paciente, std::vector<Paciente> pacientes) {
    pacientes.push_back(paciente);
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
            
            break;
        }
        case 2: {
           
            break;
        }
        case 3: {
            break;
        }
        case 4:
            std::cout << "Saliendo del programa..." << std::endl;
            break;
        default:
            std::cout << "Opción no válida. Intente de nuevo." << std::endl;
            break;
        }
    } while (opcion != 4);
}

void SistemaHospital::ejecutarSistema() {
    crearBaseDeDatos();
    crearMenu();
}
