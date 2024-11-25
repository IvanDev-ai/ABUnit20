// ABUnit20.cpp : Defines the entry point for the application.
//

#include "ABUnit20.h"
#include "Paciente.h"
#include "HistorialClinico.h"
#include "Medico.h"
#include "Cita.h"
using namespace std;

int main()
{
    
    HistorialClinico historial1;
    historial1.agregarRegistro("Resfriado", "Descanso y liquidos");

    HistorialClinico historial2;
    historial2.agregarRegistro("Gripe", "Antivirales");


    Paciente paciente1("Ana Garcia", 1001, "2024-11-20", historial1);
    Paciente paciente2("Carlos Lopez", 1002, "2024-11-21", historial2);
    Paciente paciente3("Elena Martinez", 1003, "2024-11-22", historial1);
    vector<Paciente> pacientes = { paciente1, paciente2, paciente3 };

    Paciente::consultarPaciente(paciente1);
    Paciente::consultarPaciente(paciente2);
    Paciente::consultarPaciente(paciente3);

    Medico medico1("Dr. Juan Perez", 101, "Cardiologia", true);
    Medico medico2("Dra. Ana Gómez", 102, "Pediatria", false);
    Medico medico3("Dr. Carlos Sanchez", 103, "Traumatologia", true);
    vector<Medico> medicos = { medico1, medico2, medico3 };

    Medico::consultarMedico(medico1);

    Cita cita1(paciente1, medico1, "2023-11-26 10:00", "Urgente");
    Cita cita2(paciente2, medico2, "2023-11-27 15:00", "Normal");
    vector<Cita> citas = { cita1, cita2};

    Cita::consultarCita(cita1);

	return 0;
}
