# Sistema de Gestión Hospitalaria

## Descripción
Este proyecto es un sistema de gestión hospitalaria diseñado para facilitar la administración de pacientes, médicos y citas médicas. Permite almacenar, buscar y ordenar registros en archivos CSV, asegurando escalabilidad y eficiencia para manejar grandes volúmenes de datos.

## Características principales
- Gestión de pacientes, médicos y citas.
- Operaciones de búsqueda y ordenación optimizadas.
- Copias de seguridad automáticas de los archivos de datos.
- Soporte para manejo de errores como datos faltantes o formatos incorrectos.
- Diseño modular aplicando principios SOLID y técnicas de código limpio.

## Requisitos del sistema
- **Lenguaje**: C++20 o superior.
- **Herramienta de construcción**: CMake (versión 3.8 o superior).
- **Compilador**: GCC, Clang o MSVC con soporte para C++20.

## Estructura del proyecto
├── Paciente.cpp <br>
├── Paciente.h<br>
├── HistorialClinico.cpp <br>
├── HistorialClinico.h <br>
├── Medico.cpp <br>
├── Medico.h <br>
├── Cita.cpp<br>
├── Cita.h<br>
├── SistemaHospital.cpp <br>
├── SistemaHospital.h <br>
├── ABUnit20.cpp <br>
├── ABUnit20.h <br>
├── pacientes.csv <br>
├── medicos.csv <br>
├── citas.csv <br>
├── CMakeLists.txt <br>
└── README.md<br>

## Instalación
1. Clona el repositorio:
   ```bash
   git clone https://github.com/usuario/sistema-gestion-hospital.git
   cd sistema-gestion-hospital
   ```
2. Crea un directorio para la compilación:
   ```bash
   mkdir build
   cd build
   ```
3. Configura el proyecto con CMake:
   ```bash
   cmake ..
   ```
4.Compila el proyecto:
   ```bash
   cmake --build .
   ```
5.Ejecuta el programa:
   ```bash
   ./ABUnit20
   ```
## Uso
- **Primer inicio**: Si no existen los archivos pacientes.csv, medicos.csv o citas.csv, el sistema creará una base de datos inicial con datos vacíos.
- **Gestión de datos**:
-- Agregar pacientes, médicos y citas.
-- Realizar búsquedas y ordenar datos.
- **Copias de seguridad**: El sistema genera copias automáticas de los archivos CSV para prevenir pérdida de datos.
  
## Archivos principales
- **Paciente.cpp** y **Paciente.h**: Manejo de datos relacionados con pacientes.
- **HistorialClinico.cpp** y **HistorialClinico.h**: Gestión del historial clínico de los pacientes.
- **Medico.cpp** y **Medico.h**: Gestión de datos de los médicos.
- **Cita.cpp** y **Cita.h**: Administración de citas médicas.
- **SistemaHospital.cpp** y **SistemaHospital.h**: Lógica principal del sistema.
- **ABUnit20.cpp** y **ABUnit20.h**: Archivo principal del programa y punto de entrada.
  
## Ejemplo de ejecución

Al ejecutar el sistema, se mostrará un menú interactivo para gestionar pacientes, médicos y citas. Puedes realizar búsquedas, ordenar datos o generar copias de seguridad.

## Licencia
Este proyecto está bajo la licencia MIT. Consulta el archivo LICENSE para más detalles.










