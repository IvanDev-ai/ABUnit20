// ABUnit20.cpp : Defines the entry point for the application.
//

#include "ABUnit20.h"
#include "Paciente.h"
#include "HistorialClinico.h"

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
    
    Paciente::consultarPaciente(paciente1);
    Paciente::consultarPaciente(paciente2);
    Paciente::consultarPaciente(paciente3);
	return 0;
}
