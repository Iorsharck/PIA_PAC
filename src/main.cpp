#include <iostream>
#include <limits>

/*
    Modulo de integridad
*/
#include "analizador.hpp"

/*
    Modulo de red
*/
#include "NetworkMonitor.hpp"

int main()
{
    int opcion = 0;

    while (opcion != 3)
    {
        std::cout << "\n================================";
        std::cout << "\n    MENU SECUREWATCH - PIA      ";
        std::cout << "\n================================";

        std::cout << "\n1. Analizar Integridad (Estefani)";
        std::cout << "\n2. Modulo de Red (Jair)";
        std::cout << "\n3. Salir";

        std::cout << "\nOpcion: ";

        /*
            Validacion input
        */

        if (!(std::cin >> opcion))
        {
            std::cin.clear();

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            std::cout
                << "[!] Por favor, elige una opcion valida.\n";

            continue;
        }

        /*
            OPCION 1
        */

        if (opcion == 1)
        {
            analizarArchivo();
        }

        /*
            OPCION 2
        */

        else if (opcion == 2)
        {
            std::cout
                << "\n[i] Iniciando modulo de monitoreo de red...\n";

            /*
                Llamada al modulo de red
            */

            NetMon::NetworkMonitor::run();
        }

        /*
            OPCION 3
        */

        else if (opcion == 3)
        {
            std::cout
                << "\nSaliendo del programa...\n";
        }

        /*
            OPCION INVALIDA
        */

        else
        {
            std::cout
                << "\n[!] Opcion no valida.\n";
        }
    }

    return 0;
}
