#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>


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
    string nombreArchivoModificado = "archivo_modificado.txt";

    // Vector para almacenar las líneas del programa
    vector<string> programa;

    int opcion;
    bool programaIniciado = false;

    do {
        
        cout << "----- MENU -----" << endl;
        cout << "1. Verificar archivo TXT" << endl;
        cout << "2. Iniciar programa" << endl;
        cout << "3. Mostrar detalle y tiempo de ejecucion" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                if (ifstream(nombreArchivoOriginal)) {
                    cout << "Existe un archivo TXT." << endl;
                } else {
                    cout << "El archivo TXT no existe." << endl;
                }
              cout << "Presione cualquier tecla para continuar...";
              cin.ignore();
              cin.get();
                break;
            case 2:
              
                if (!programaIniciado) {
                  
                    // Leer el archivo y agregar asteriscos a cada línea
                    leerArchivo(programa, nombreArchivoOriginal);
                    // Ejecutar el programa y registrar el log
                    ejecutarPrograma(programa, nombreArchivoLog);
                    // Escribir el programa modificado en otro archivo
                    escribirArchivo(programa, nombreArchivoModificado);
                    programaIniciado = true;
                } else {
                    cout << "El programa ya ha sido iniciado." << endl;
                }
              cout << "El programa ya ha sido ejecutado." << endl;
              cout << "Presione cualquier tecla para continuar...";
              cin.ignore();
              cin.get();
                break;
            case 3:
                if (programaIniciado) {
                    ifstream logFile(nombreArchivoLog);
                    if (logFile.is_open()) {
                        string line;
                        while (getline(logFile, line)) {
                            cout << line << endl;
                        }
                        logFile.close();
                    } else {
                        cerr << "Error al abrir el archivo de log: " << nombreArchivoLog << endl;
                    }
                } else {
                    cout << "Primero debes iniciar el programa." << endl;
                }
              cout << "Presione cualquier tecla para continuar...";
              cin.ignore();
              cin.get();
              
                break;
            case 4:
                cout << "Saliendo del programa, Muchas gracias." << endl;
                break;
            default:
                cout << "Opción inválida. Por favor ingrese una opción válida." << endl;
                break;
        }
    } while (opcion != 4);

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

    auto startTotal = steady_clock::now();

    while (posicion < programa.size()) {
        logFile << "p" << proceso << endl;

        while (posicion < programa.size()) {
            auto start = steady_clock::now();

            if (programa[posicion].find("definir uno como usuario") != string::npos) {
                logFile << "Interrupción detectada en la línea " << posicion << endl;
                modoMonitor(programa, posicion, logFile);
                logFile << "Volviendo al modo usuario..." << endl;
                modoUsuario(programa, posicion, logFile);
                ++posicion; // Mover a la siguiente línea después de manejar la interrupción
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
                ++posicion; // Mover a la siguiente línea después de manejar 'write'
                continue;
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

    auto endTotal = steady_clock::now();
    auto durationTotal = duration_cast<seconds>(endTotal - startTotal).count();
    logFile << "Tiempo total de ejecución del programa: " << durationTotal << " segundos" << endl;
    
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

// No necesitamos guardar la posición actual del programa,
// ya que se maneja adecuadamente fuera de esta función
}
