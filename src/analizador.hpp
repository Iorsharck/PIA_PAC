#ifndef ANALIZADOR_HPP
#define ANALIZADOR_HPP

#include <string>

// Prototipos de las funciones de mi módulo (Estefani)
// Esto le dice al compilador qué funciones existen antes de usarlas
void registrarAccion(std::string mensaje);
void analizarArchivo();
void generarReporteTxt(std::string ruta, unsigned long long checksum);

#endif