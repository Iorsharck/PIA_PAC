# PIA_PAC.
**SecureWatch: Sistema de Auditoría e Integridad**

## Información Académica
* **Institución:** Universidad Autónoma de Nuevo León 
* **Facultad:** Facultad de CIencias Fisico Matematicas 
* **Materia:** Programación avanzada para ciberseguridad
* **Catedrática:** Dra. Perla Marlene Viera González
* **Equipo:** Equipo 3

## Integrantes
* Jair Gonzalo Cortés Romero
* Estefani Jazmín Meléndez Magallanes




# Objetivo
El objetivo de este programa es proveer una serie de herramientas unidas para que sea facil diagnosticar y analizar el trafico de la red asi como la integridad de un archivo, usando las buenas practias siendo esto una suite con herramienta de analisis estatico y analisis de red. Esta suite tambien tiene como objetivo operar en los sitemas operativos de Windows y Linux (se recomienda usar Kali)

## Descripción del Proyecto
SecureWatch es una herramienta integral diseñada para el monitoreo de seguridad en sistemas operativos Linux. El proyecto combina técnicas de análisis estático de binarios con monitoreo de tráfico en red para ofrecer una solución robusta de auditoría.

## Dependencias
Windows: Ncap
Linux: Libcap++

## Compilación (con simbolos)
g++ -std=c++17 -g
main.cpp
analizador.cpp
NetworkMonitor.cpp
-o SecureWatch.exe
-I/usr/local/include/pcapplusplus
-lPcap++
-lPacket++
-lCommon++
-lpcap

## Ejecución
Linux: sudo ./SecureWatch.exe
Windows: ejecutar como administrador el .exe

## Reporte final 
*Enlace*

