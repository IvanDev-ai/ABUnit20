# CMakeLists.txt : CMake project for ABUnit20, include source and define
# project specific logic here.
#
project ("ABUnit20")

# Define sources
set(SOURCES
    "ABUnit20.cpp"
    "ABUnit20.h"
    "Paciente.cpp"
    "Paciente.h"
    "HistorialClinico.cpp"
    "HistorialClinico.h"
    "Medico.cpp"
    "Medico.h"
    "Cita.h"
    "Cita.cpp"
    "SistemaHospital.cpp"
    "SistemaHospital.h"
)

# Add source to this project's executable.
add_executable (ABUnit20 ${SOURCES})

# Set C++ standard for the project if the CMake version is greater than 3.12
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ABUnit20 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
