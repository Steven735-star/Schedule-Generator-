
# Generador de Horarios en C++

Este proyecto es una aplicación de consola en C++ que permite gestionar un horario semanal de actividades. Incluye funcionalidades para agregar, eliminar, mostrar y guardar actividades, así como detectar conflictos de tiempo y buscar huecos libres durante el día.

## Características

- Agregar actividades con nombre, día, horario y ubicación.
- Detección automática de conflictos entre actividades.
- Visualización del horario completo o por día.
- Eliminación de actividades por nombre.
- Guardado y carga del horario desde archivo (`horario.txt`).
- Cambio de nombre del horario.
- Búsqueda de huecos libres durante el día (entre 8:00 y 22:00).

## Estructura del Proyecto

- `Actividad`: Clase que representa una actividad individual.
- `Horario`: Clase que maneja un conjunto de actividades.
- `main()`: Función principal con un menú interactivo.

## Uso

### Compilación

Compila el código con `g++` u otro compilador C++ compatible:

```bash
g++ generador_horarios.cpp -o generador_horarios
./generador_horarios.exe
