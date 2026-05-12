#include <iostream>
#include "analizador.hpp" // Esto conecta el main con el modulo

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
        
        // Validacion para que el menu no se rompa si metes una letra
        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "[!] Por favor, elige una opcion valida.\n";
            continue;
        }

        if (opcion == 1) {
            analizarArchivo(); // Llama a la funcion que esta en analizador.cpp
        } else if (opcion == 2) {
            std::cout << "\n[i] Modulo de Jair: Esperando integracion...\n";
        } else if (opcion == 3) {
            std::cout << "\nSaliendo del programa...\n";
        } else {
            std::cout << "\n[!] Opcion no valida.\n";
        }
    }
    return 0;
}