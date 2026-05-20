#include <iostream>
#include <limits>
#include "analizador.hpp"
#include "NetworkMonitor.hpp"

/**
 * @brief Punto de entrada principal del sistema.
 * Gestiona el menú de opciones del PIA integrando el módulo de 
 * integridad y el módulo de monitoreo de red.
 */
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

        // Validacion para que el menu no se rompa si el usuario ingresa caracteres
        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\n[!] Por favor, elige una opcion valida.\n";
            continue;
        }

        if (opcion == 1) {
            analizarArchivo(); // Llama a la funcion que esta en analizador.cpp
        } 
        else if (opcion == 2) {
            std::cout << "\n[i] Iniciando modulo de monitoreo de red...\n";
            NetMon::NetworkMonitor::run();
        } 
        else if (opcion == 3) {
            std::cout << "\nSaliendo del programa...\n";
        } 
        else {
            std::cout << "\n[!] Opcion no valida.\n";
        }
    }

    return 0;
}
