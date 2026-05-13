/*
    NetworkMonitor.hpp
    -------------------------------------------------------
    El main únicamente llamará run().
*/

#pragma once

#ifdef _WIN32
    #ifdef NETWORKMONITOR_EXPORTS
        #define NETWORKMONITOR_API __declspec(dllexport)
    #else
        #define NETWORKMONITOR_API __declspec(dllimport)
    #endif
#else
    #define NETWORKMONITOR_API
#endif

namespace NetMon
{
    class NETWORKMONITOR_API NetworkMonitor
    {
    public:
        /*
            TODO el flujo:
              - Enumerar interfaces
              - Menú selección
              - Captura
              - Análisis
              - Reporte
        */

        static void run();
    };
}
