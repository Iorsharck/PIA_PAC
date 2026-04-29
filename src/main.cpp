#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sys/stat.h> 

// modulo de auditoria logs
void registrarAccion(std::string mensaje) {
    std::ofstream archivoLog("security_audit.log", std::ios::app);
    if (archivoLog.is_open()) {
        std::time_t ahora = std::time(nullptr);
        char horaStr[20];
        std::strftime(horaStr, sizeof(horaStr), "%Y-%m-%d %H:%M:%S", std::localtime(&ahora));
        archivoLog << "[" << horaStr << "] " << mensaje << std::endl;
        archivoLog.close();
    }
}

// modulo de bajo nivel
void analizarArchivo() {
    std::string ruta;
    std::cout << "\n[Analizador] Ingresa el nombre del archivo (ej: main.cpp): ";
    std::cin >> ruta;
    
    struct stat buffer;
    if (stat(ruta.c_str(), &buffer) != 0) {
        std::cout << "[!] Error: El archivo no existe." << std::endl;
        return;
    }
    
    std::ifstream archivo(ruta, std::ios::binary);
    if (archivo) {
        char byte;
        unsigned long long checksum = 0;
        while (archivo.get(byte)) checksum += static_cast<unsigned char>(byte);
        std::cout << ">>> Checksum de integridad: " << std::hex << checksum << std::dec << std::endl;
        registrarAccion("Analisis completado para: " + ruta);
    }
}

// 3. EL "MAIN" 
int main() {
    int opcion = 0;
    while (opcion != 3) {
        std::cout << "\n================================";
        std::cout << "\n    MENU SECUREWATCH - PIA      ";
        std::cout << "\n================================";
        std::cout << "\n1. Analizar Integridad (Estefani)";
        std::cout << "\n2. Modulo de Red (Jair)";
        std::cout << "\n3. Salir";
        std::cout << "\nOpcion: ";
        
        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        if (opcion == 1) {
            analizarArchivo();
        } else if (opcion == 2) {
            std::cout << "\n[i] Modulo pendiente de integrar de jeico ...\n";
        }
    }
    return 0;
}
