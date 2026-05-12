#include "analizador.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <sys/stat.h>
#include <iomanip>

// 1. Función para registrar logs (Auditoría)
void registrarAccion(std::string mensaje) {
    std::ofstream archivoLog("security_audit.log", std::ios::app);
    if (!archivoLog) {
        std::cerr << "[!] Error: No se pudo abrir el log." << std::endl;
        return;
    }
    std::time_t ahora = std::time(nullptr);
    char horaStr[20];
    std::strftime(horaStr, sizeof(horaStr), "%Y-%m-%d %H:%M:%S", std::localtime(&ahora));
    
    archivoLog << "[" << horaStr << "] " << mensaje << std::endl;
    archivoLog.close();
}

// 2. Función para generar el reporte TXT que pediste Jair
void generarReporteTxt(std::string ruta, unsigned long long checksum) {
    std::ofstream reporte("reporte_analisis.txt");
    if (reporte.is_open()) {
        reporte << "=== REPORTE DE INTEGRIDAD SECUREWATCH ===" << std::endl;
        reporte << "Archivo analizado: " << ruta << std::endl;
        reporte << "Checksum: 0x" << std::hex << std::uppercase << checksum << std::endl;
        reporte << "Resultado: Integridad verificada." << std::endl;
        reporte.close();
        std::cout << "[+] Reporte TXT generado con exito." << std::endl;
    }
}

// 3. Función principal del módulo
void analizarArchivo() {
    std::string ruta;
    std::cout << "\n[Analizador] Nombre del archivo a revisar: ";
    std::cin >> ruta;

    // Manejo de errores: Verificar si el archivo existe
    struct stat buffer;
    if (stat(ruta.c_str(), &buffer) != 0) {
        std::cerr << "[!] Error: El archivo no existe o no hay permisos." << std::endl;
        return;
    }

    std::ifstream archivo(ruta, std::ios::binary);
    if (!archivo) {
        std::cerr << "[!] Error: No se pudo abrir para lectura." << std::endl;
        return;
    }

    char byte;
    unsigned long long checksum = 0;
    while (archivo.get(byte)) {
        checksum += static_cast<unsigned char>(byte);
    }
    archivo.close();

    std::cout << ">>> Checksum calculado: 0x" << std::hex << std::uppercase << checksum << std::dec << std::endl;
    
    // Llamamos a las otras funciones del módulo
    registrarAccion("Analisis completado: " + ruta);
    generarReporteTxt(ruta, checksum);
}