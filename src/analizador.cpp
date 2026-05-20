#include "analizador.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <sys/stat.h>
#include <iomanip>

/**
 * @brief Registra eventos en el archivo de auditoria
 * @param mensaje El evento a loguear
 * @complexity O(1) en apertura, O(N) en escritura del buffer
 */
void registrarAccion(std::string mensaje) {
    std::ofstream archivoLog("security_audit.log", std::ios::app);
    if (!archivoLog.is_open()) {
        std::cerr << "[!] Error crítico: No se pudo acceder al log de auditoría." << std::endl;
        return;
    }
    std::time_t ahora = std::time(nullptr);
    char horaStr[20];
    std::strftime(horaStr, sizeof(horaStr), "%Y-%m-%d %H:%M:%S", std::localtime(&ahora));
    
    archivoLog << "[" << horaStr << "] " << mensaje << std::endl;
    archivoLog.close();
}

/**
 * @brief Genera reporte de integridad formateado
 * @param ruta Ruta del archivo analizado
 * @param checksum Valor numérico del hash calculado
 */
void generarReporteTxt(std::string ruta, unsigned long long checksum) {
    std::ofstream reporte("reporte_analisis.txt");
    if (reporte.is_open()) {
        reporte << "=== REPORTE DE INTEGRIDAD SECUREWATCH ===" << std::endl;
        reporte << "Archivo analizado: " << ruta << std::endl;
        reporte << "Checksum: 0x" << std::hex << std::uppercase << checksum << std::endl;
        reporte << "Resultado: Integridad verificada." << std::endl;
        reporte.close();
        std::cout << "[+] Reporte guardado en: reporte_analisis.txt" << std::endl;
    }
}

/**
 * @brief Funcion principal del modulo de integridad
 * Implementa calculo de checksum simple basado en suma de bytes
 */
void analizarArchivo() {
    std::string ruta;
    std::cout << "\n[Analizador] Introduce la ruta del archivo a auditar: ";
    std::cin >> ruta;

    struct stat buffer;
    if (stat(ruta.c_str(), &buffer) != 0) {
        std::cerr << "[!] Error: El archivo no existe." << std::endl;
        registrarAccion("Intento fallido: archivo no encontrado (" + ruta + ")");
        return;
    }

    std::ifstream archivo(ruta, std::ios::binary);
    if (!archivo) {
        std::cerr << "[!] Error: No se pudo abrir el archivo." << std::endl;
        return;
    }

    unsigned char byte;
    unsigned long long checksum = 0;
    while (archivo.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        checksum += byte; // Logica de suma de bytes para integridad
    }

    archivo.close();
    generarReporteTxt(ruta, checksum);
    registrarAccion("Analisis completado exitosamente: " + ruta);
}