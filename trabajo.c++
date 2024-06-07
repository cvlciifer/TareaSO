//Integrantes: Jose Malca





/*
Este programa en C++ ejecuta un programa almacenado en un archivo de texto y registra la ejecución y eventos relevantes en un archivo de log.

Funciones principales:
- leerArchivo(): Lee el contenido del archivo de entrada y almacena cada línea en un vector.
- escribirArchivo(): Escribe el programa modificado en un archivo de salida.
- ejecutarPrograma(): Ejecuta el programa leyendo línea por línea, simulando la ejecución de instrucciones y registrando eventos en el archivo de log.
- modoUsuario(): Simula el modo de operación del usuario.
- modoMonitor(): Simula el modo de operación del monitor.

El programa detecta interrupciones y cambios de modo, como la palabra 'write', y simula la ejecución de rutinas asociadas a través de los modos de usuario y monitor.

El archivo de log registra la ejecución de cada línea, el tiempo de ejecución, las interrupciones detectadas y los cambios de modo.

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

// Declaración de funciones
void leerArchivo(vector<string>& programa, const string& nombreArchivo);
void escribirArchivo(const vector<string>& programa, const string& nombreArchivo);
void modoMonitor(vector<string>& programa, int& posicion, ofstream& logFile);
void modoUsuario(vector<string>& programa, int& posicion, ofstream& logFile);
void ejecutarPrograma(vector<string>& programa, const string& logFileName);

int main() {
    // Nombre del archivo de texto original
    string nombreArchivoOriginal = "archivo.txt";
    string nombreArchivoLog = "log.txt";

    // Vector para almacenar las líneas del programa
    vector<string> programa;

    // Leer el archivo y agregar asteriscos a cada línea
    leerArchivo(programa, nombreArchivoOriginal);

    // Ejecutar el programa y registrar el log
    ejecutarPrograma(programa, nombreArchivoLog);

    return 0;
}

// Función para leer el archivo y agregar asteriscos a cada línea
void leerArchivo(vector<string>& programa, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) {
            programa.push_back(linea); // Agregar línea al programa
        }
        archivo.close();
    } else {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
    }
}

// Función para escribir el programa modificado en otro archivo
void escribirArchivo(const vector<string>& programa, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        for (const string& linea : programa) {
            archivo << linea << endl; // Escribir cada línea en el archivo de salida
        }
        archivo.close();
    } else {
        cerr << "Error al abrir el archivo de salida: " << nombreArchivo << endl;
    }
}

// Función para ejecutar el programa
void ejecutarPrograma(vector<string>& programa, const string& logFileName) {
    ofstream logFile(logFileName);

    if (!logFile.is_open()) {
        cerr << "Error al abrir el archivo de log: " << logFileName << endl;
        return;
    }

    int posicion = 0; // Posición actual del programa
    int proceso = 1;

    while (posicion < programa.size()) {
        logFile << "p" << proceso << endl;

        while (posicion < programa.size()) {
            auto start = steady_clock::now();
            
            if (programa[posicion].find("definir uno como usuario") != string::npos) {
                logFile << "Interrupción detectada en la línea " << posicion << endl;
                modoMonitor(programa, posicion, logFile);
                logFile << "Volviendo al modo usuario..." << endl;
                modoUsuario(programa, posicion, logFile);
                continue;
            }

            logFile << "Ejecutando línea " << posicion << ": " << programa[posicion] << endl;
            this_thread::sleep_for(seconds(1)); // Simular tiempo de ejecución de 1 segundo
            auto end = steady_clock::now();
            auto duration = duration_cast<seconds>(end - start).count();
            logFile << "Tiempo de ejecución: " << duration << " segundos" << endl;

            programa[posicion] += "*"; // Agregar asterisco a la línea ejecutada

            if (programa[posicion].find("write") != string::npos) {
                logFile << "Encontrada la palabra 'write' en la línea " << posicion << endl;
                modoMonitor(programa, posicion, logFile); // Cambiar al modo monitor
                logFile << "Volviendo al modo usuario..." << endl;
                modoUsuario(programa, posicion, logFile); // Volver al modo usuario
            }

            if (programa[posicion].find("fin del proceso") != string::npos) {
                logFile << "Encontrada la palabra 'fin del proceso' en la línea " << posicion << endl;
                ++posicion; // Avanzar a la siguiente línea para continuar el siguiente proceso
                break;
            }

            ++posicion; // Avanzar a la siguiente línea
        }

        proceso++;
    }

    // Marcar el final del programa
    logFile << "El programa ha finalizado." << endl;
    programa.push_back("FIN DEL PROGRAMA");

    logFile.close();
}

// Función para el modo usuario
void modoUsuario(vector<string>& programa, int& posicion, ofstream& logFile) {
    logFile << "Modo usuario activado." << endl;
    // Supongamos que hacemos algo específico en el modo usuario
}

// Función para el modo monitor
void modoMonitor(vector<string>& programa, int& posicion, ofstream& logFile) {
    // Simulamos la ejecución de la rutina asociada a la interrupción
    logFile << "Ejecutando rutina de espera (standby) en modo monitor..." << endl;
    this_thread::sleep_for(seconds(1)); // Simular tiempo de espera de 1 segundo

    // Guardar la posición actual del programa
    // para retomar la ejecución después del modo usuario
    int posicionGuardada = posicion;

    // Supongamos que aquí se ejecuta la rutina de espera

    // Cambiar al modo usuario
    posicion = posicionGuardada;

    // Mostrar el cambio de vuelta al modo usuario
    logFile << "Volviendo al modo usuario..." << endl;
}
