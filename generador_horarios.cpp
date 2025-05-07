#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <limits>

// Clase para representar una actividad en el horario
class Actividad {
private:
    std::string nombre;
    int dia;           // 1-7 (Lunes-Domingo)
    int horaInicio;    // 0-23
    int minutoInicio;  // 0-59
    int horaFin;
    int minutoFin;
    std::string ubicacion;

public:
    // Constructor
    Actividad(std::string n, int d, int hI, int mI, int hF, int mF, std::string u)
        : nombre(n), dia(d), horaInicio(hI), minutoInicio(mI), 
          horaFin(hF), minutoFin(mF), ubicacion(u) {}

    // Getters
    std::string getNombre() const { return nombre; }
    int getDia() const { return dia; }
    int getHoraInicio() const { return horaInicio; }
    int getMinutoInicio() const { return minutoInicio; }
    int getHoraFin() const { return horaFin; }
    int getMinutoFin() const { return minutoFin; }
    std::string getUbicacion() const { return ubicacion; }

    // Método para verificar si hay conflicto con otra actividad
    bool conflictoCon(const Actividad& otra) const {
        if (dia != otra.dia) return false;

        // Convertir horas a minutos para facilitar la comparación
        int inicioA = horaInicio * 60 + minutoInicio;
        int finA = horaFin * 60 + minutoFin;
        int inicioB = otra.horaInicio * 60 + otra.minutoInicio;
        int finB = otra.horaFin * 60 + otra.minutoFin;

        // Hay conflicto si el inicio o fin de una actividad está dentro del rango de otra
        return (inicioA < finB && inicioB < finA);
    }

    // Método para obtener una representación en string de la actividad
    std::string toString() const {
        std::stringstream ss;
        ss << nombre << "," << dia << "," << horaInicio << "," << minutoInicio << ","
           << horaFin << "," << minutoFin << "," << ubicacion;
        return ss.str();
    }

    // Método para mostrar la actividad de forma legible
    void mostrar() const {
        static const std::string diasSemana[] = {"", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo"};
        std::cout << "- " << nombre << " (" << diasSemana[dia] << " " 
                  << std::setfill('0') << std::setw(2) << horaInicio << ":" 
                  << std::setw(2) << minutoInicio << " - "
                  << std::setw(2) << horaFin << ":" 
                  << std::setw(2) << minutoFin << ") en " << ubicacion << std::endl;
    }
};

// Clase para gestionar el horario completo
class Horario {
private:
    std::vector<Actividad> actividades;
    std::string nombre;

public:
    // Constructor
    Horario(std::string n = "Mi Horario") : nombre(n) {}

    // Método para añadir una actividad
    bool agregarActividad(const Actividad& nuevaActividad) {
        // Verificar si hay conflictos
        for (const auto& actividad : actividades) {
            if (actividad.conflictoCon(nuevaActividad)) {
                std::cout << "Error: Conflicto de horario detectado." << std::endl;
                std::cout << "La nueva actividad: ";
                nuevaActividad.mostrar();
                std::cout << "Conflicta con: ";
                actividad.mostrar();
                return false;
            }
        }

        // Si no hay conflictos, añadir la actividad
        actividades.push_back(nuevaActividad);
        return true;
    }

    // Método para mostrar todo el horario
    void mostrarHorario() const {
        if (actividades.empty()) {
            std::cout << "El horario está vacío." << std::endl;
            return;
        }

        std::cout << "\n=== " << nombre << " ===" << std::endl;
        
        for (int dia = 1; dia <= 7; dia++) {
            static const std::string diasSemana[] = {"", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo"};
            std::cout << "\n" << diasSemana[dia] << ":" << std::endl;
            
            bool hayActividades = false;
            std::vector<Actividad> actividadesDia;
            
            for (const auto& actividad : actividades) {
                if (actividad.getDia() == dia) {
                    actividadesDia.push_back(actividad);
                    hayActividades = true;
                }
            }
            
            if (!hayActividades) {
                std::cout << "  No hay actividades." << std::endl;
            } else {
                // Ordenar por hora de inicio
                std::sort(actividadesDia.begin(), actividadesDia.end(), 
                    [](const Actividad& a, const Actividad& b) {
                        int inicioA = a.getHoraInicio() * 60 + a.getMinutoInicio();
                        int inicioB = b.getHoraInicio() * 60 + b.getMinutoInicio();
                        return inicioA < inicioB;
                    });
                
                for (const auto& actividad : actividadesDia) {
                    std::cout << "  ";
                    actividad.mostrar();
                }
            }
        }
    }

    // Método para eliminar una actividad por nombre
    bool eliminarActividad(const std::string& nombre) {
        auto it = std::find_if(actividades.begin(), actividades.end(),
                              [&nombre](const Actividad& a) { return a.getNombre() == nombre; });
        
        if (it != actividades.end()) {
            actividades.erase(it);
            std::cout << "Actividad '" << nombre << "' eliminada correctamente." << std::endl;
            return true;
        }
        
        std::cout << "No se encontró ninguna actividad con el nombre '" << nombre << "'." << std::endl;
        return false;
    }

    // Método para mostrar actividades de un día específico
    void mostrarDia(int dia) const {
        static const std::string diasSemana[] = {"", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo"};
        
        if (dia < 1 || dia > 7) {
            std::cout << "Día inválido. Debe ser un número entre 1 (Lunes) y 7 (Domingo)." << std::endl;
            return;
        }
        
        std::cout << "\nActividades para el " << diasSemana[dia] << ":" << std::endl;
        
        bool hayActividades = false;
        std::vector<Actividad> actividadesDia;
        
        for (const auto& actividad : actividades) {
            if (actividad.getDia() == dia) {
                actividadesDia.push_back(actividad);
                hayActividades = true;
            }
        }
        
        if (!hayActividades) {
            std::cout << "  No hay actividades para este día." << std::endl;
            return;
        }
        
        // Ordenar por hora de inicio
        std::sort(actividadesDia.begin(), actividadesDia.end(), 
            [](const Actividad& a, const Actividad& b) {
                int inicioA = a.getHoraInicio() * 60 + a.getMinutoInicio();
                int inicioB = b.getHoraInicio() * 60 + b.getMinutoInicio();
                return inicioA < inicioB;
            });
        
        for (const auto& actividad : actividadesDia) {
            std::cout << "  ";
            actividad.mostrar();
        }
    }

    // Método para guardar el horario en un archivo
    bool guardarEnArchivo(const std::string& nombreArchivo) const {
        std::ofstream archivo(nombreArchivo);
        
        if (!archivo.is_open()) {
            std::cout << "Error: No se pudo abrir el archivo para escritura." << std::endl;
            return false;
        }
        
        archivo << nombre << std::endl;
        
        for (const auto& actividad : actividades) {
            archivo << actividad.toString() << std::endl;
        }
        
        archivo.close();
        std::cout << "Horario guardado correctamente en '" << nombreArchivo << "'." << std::endl;
        return true;
    }

    // Método para cargar el horario desde un archivo
    bool cargarDesdeArchivo(const std::string& nombreArchivo) {
        std::ifstream archivo(nombreArchivo);
        
        if (!archivo.is_open()) {
            std::cout << "Error: No se pudo abrir el archivo para lectura." << std::endl;
            return false;
        }
        
        actividades.clear();  // Limpiar las actividades actuales
        
        // Leer el nombre del horario
        std::getline(archivo, nombre);
        
        std::string linea;
        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string nombre, ubicacion, valor;
            int dia, horaInicio, minutoInicio, horaFin, minutoFin;
            
            // Leer los campos separados por comas
            std::getline(ss, nombre, ',');
            std::getline(ss, valor, ','); dia = std::stoi(valor);
            std::getline(ss, valor, ','); horaInicio = std::stoi(valor);
            std::getline(ss, valor, ','); minutoInicio = std::stoi(valor);
            std::getline(ss, valor, ','); horaFin = std::stoi(valor);
            std::getline(ss, valor, ','); minutoFin = std::stoi(valor);
            std::getline(ss, ubicacion);
            
            Actividad actividad(nombre, dia, horaInicio, minutoInicio, horaFin, minutoFin, ubicacion);
            actividades.push_back(actividad);
        }
        
        archivo.close();
        std::cout << "Horario cargado correctamente desde '" << nombreArchivo << "'." << std::endl;
        return true;
    }

    // Método para cambiar el nombre del horario
    void cambiarNombre(const std::string& nuevoNombre) {
        nombre = nuevoNombre;
        std::cout << "Nombre del horario cambiado a: " << nombre << std::endl;
    }

    // Método para buscar huecos libres en un día específico
    void buscarHuecosLibres(int dia) const {
        static const std::string diasSemana[] = {"", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado", "Domingo"};
        
        if (dia < 1 || dia > 7) {
            std::cout << "Día inválido. Debe ser un número entre 1 (Lunes) y 7 (Domingo)." << std::endl;
            return;
        }
        
        std::vector<Actividad> actividadesDia;
        for (const auto& actividad : actividades) {
            if (actividad.getDia() == dia) {
                actividadesDia.push_back(actividad);
            }
        }
        
        // Ordenar por hora de inicio
        std::sort(actividadesDia.begin(), actividadesDia.end(), 
            [](const Actividad& a, const Actividad& b) {
                int inicioA = a.getHoraInicio() * 60 + a.getMinutoInicio();
                int inicioB = b.getHoraInicio() * 60 + b.getMinutoInicio();
                return inicioA < inicioB;
            });
        
        std::cout << "\nHuecos libres para el " << diasSemana[dia] << ":" << std::endl;
        
        if (actividadesDia.empty()) {
            std::cout << "  Todo el día está libre." << std::endl;
            return;
        }
        
        // Horario típico diurno (8:00 - 22:00)
        int inicioJornada = 8 * 60;  // 8:00 AM
        int finJornada = 22 * 60;    // 10:00 PM
        
        // Hueco al inicio del día
        if (actividadesDia[0].getHoraInicio() * 60 + actividadesDia[0].getMinutoInicio() > inicioJornada) {
            std::cout << "  " << formatoHora(inicioJornada) << " - " 
                      << formatoHora(actividadesDia[0].getHoraInicio() * 60 + actividadesDia[0].getMinutoInicio()) 
                      << std::endl;
        }
        
        // Huecos entre actividades
        for (size_t i = 0; i < actividadesDia.size() - 1; i++) {
            int finActual = actividadesDia[i].getHoraFin() * 60 + actividadesDia[i].getMinutoFin();
            int inicioSiguiente = actividadesDia[i+1].getHoraInicio() * 60 + actividadesDia[i+1].getMinutoInicio();
            
            if (inicioSiguiente > finActual) {
                std::cout << "  " << formatoHora(finActual) << " - " << formatoHora(inicioSiguiente) << std::endl;
            }
        }
        
        // Hueco al final del día
        int finUltima = actividadesDia.back().getHoraFin() * 60 + actividadesDia.back().getMinutoFin();
        if (finUltima < finJornada) {
            std::cout << "  " << formatoHora(finUltima) << " - " << formatoHora(finJornada) << std::endl;
        }
    }

private:
    // Método auxiliar para formatear la hora (convertir minutos a formato HH:MM)
    static std::string formatoHora(int minutos) {
        int horas = minutos / 60;
        int mins = minutos % 60;
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(2) << horas << ":" 
           << std::setfill('0') << std::setw(2) << mins;
        return ss.str();
    }
};

// Función principal que implementa el menú interactivo
int main() {
    Horario miHorario;
    std::string nombreArchivo = "horario.txt";
    
    // Intentar cargar el horario desde el archivo al inicio
    std::ifstream testFile(nombreArchivo);
    if (testFile.good()) {
        testFile.close();
        miHorario.cargarDesdeArchivo(nombreArchivo);
    }
    
    int opcion;
    do {
        std::cout << "\n=== GENERADOR DE HORARIOS ===" << std::endl;
        std::cout << "1. Agregar actividad" << std::endl;
        std::cout << "2. Eliminar actividad" << std::endl;
        std::cout << "3. Mostrar horario completo" << std::endl;
        std::cout << "4. Mostrar actividades de un día" << std::endl;
        std::cout << "5. Buscar huecos libres en un día" << std::endl;
        std::cout << "6. Guardar horario" << std::endl;
        std::cout << "7. Cargar horario" << std::endl;
        std::cout << "8. Cambiar nombre del horario" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        
        // Limpiar el buffer de entrada
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (opcion) {
            case 1: {
                std::string nombre, ubicacion;
                int dia, horaInicio, minutoInicio, horaFin, minutoFin;
                
                std::cout << "Nombre de la actividad: ";
                std::getline(std::cin, nombre);
                
                std::cout << "Día de la semana (1=Lunes, 2=Martes, ..., 7=Domingo): ";
                std::cin >> dia;
                
                std::cout << "Hora de inicio (0-23): ";
                std::cin >> horaInicio;
                
                std::cout << "Minuto de inicio (0-59): ";
                std::cin >> minutoInicio;
                
                std::cout << "Hora de fin (0-23): ";
                std::cin >> horaFin;
                
                std::cout << "Minuto de fin (0-59): ";
                std::cin >> minutoFin;
                
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                std::cout << "Ubicación: ";
                std::getline(std::cin, ubicacion);
                
                if (dia < 1 || dia > 7 || horaInicio < 0 || horaInicio > 23 || 
                    minutoInicio < 0 || minutoInicio > 59 || horaFin < 0 || horaFin > 23 || 
                    minutoFin < 0 || minutoFin > 59) {
                    std::cout << "Error: Valores fuera de rango." << std::endl;
                    break;
                }
                
                if (horaInicio > horaFin || (horaInicio == horaFin && minutoInicio >= minutoFin)) {
                    std::cout << "Error: La hora de fin debe ser posterior a la hora de inicio." << std::endl;
                    break;
                }
                
                Actividad nuevaActividad(nombre, dia, horaInicio, minutoInicio, horaFin, minutoFin, ubicacion);
                miHorario.agregarActividad(nuevaActividad);
                break;
            }
            case 2: {
                std::string nombre;
                std::cout << "Nombre de la actividad a eliminar: ";
                std::getline(std::cin, nombre);
                miHorario.eliminarActividad(nombre);
                break;
            }
            case 3: {
                miHorario.mostrarHorario();
                break;
            }
            case 4: {
                int dia;
                std::cout << "Día de la semana (1=Lunes, 2=Martes, ..., 7=Domingo): ";
                std::cin >> dia;
                miHorario.mostrarDia(dia);
                break;
            }
            case 5: {
                int dia;
                std::cout << "Día de la semana (1=Lunes, 2=Martes, ..., 7=Domingo): ";
                std::cin >> dia;
                miHorario.buscarHuecosLibres(dia);
                break;
            }
            case 6: {
                std::string archivo;
                std::cout << "Nombre del archivo (deje en blanco para usar '" << nombreArchivo << "'): ";
                std::getline(std::cin, archivo);
                if (archivo.empty()) {
                    archivo = nombreArchivo;
                }
                miHorario.guardarEnArchivo(archivo);
                break;
            }
            case 7: {
                std::string archivo;
                std::cout << "Nombre del archivo (deje en blanco para usar '" << nombreArchivo << "'): ";
                std::getline(std::cin, archivo);
                if (archivo.empty()) {
                    archivo = nombreArchivo;
                }
                miHorario.cargarDesdeArchivo(archivo);
                break;
            }
            case 8: {
                std::string nombre;
                std::cout << "Nuevo nombre para el horario: ";
                std::getline(std::cin, nombre);
                miHorario.cambiarNombre(nombre);
                break;
            }
            case 0:
                std::cout << "¡Hasta pronto!" << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        }
        
    } while (opcion != 0);
    
    return 0;
}