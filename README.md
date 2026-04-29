# PIA_PAC
Suite con herramienta de analisis estatico y analisis de red. Proyecto final de Programacion Avanzada para Ciberseguridad
# SecureWatch: Sistema de Auditoría e Integridad

## Información Académica
* **Institución:** Universidad Autónoma de Nuevo León 
* **Facultad:** Facultad de CIencias Fisico Matematicas 
* **Materia:** Programación avanzada para ciberseguridad
* **Catedrática:** Dra. Perla Marlene Viera González
* **Equipo:** Equipo 3

## Integrantes
* Jair Gonzalo Cortés Romero
* Estefani Jazmín Meléndez Magallanes


## Descripción del Proyecto
SecureWatch es una herramienta integral diseñada para el monitoreo de seguridad en sistemas operativos Linux. El proyecto combina técnicas de análisis estático de binarios con monitoreo de tráfico en red para ofrecer una solución robusta de auditoría.

## Módulos del Sistema
1. **Análisis de Integridad (Bajo Nivel):** Implementado en C++, este módulo realiza un análisis estático de archivos binarios. Utiliza técnicas de ingeniería inversa básica para leer el contenido byte a byte y generar un checksum, permitiendo detectar cualquier alteración o inyección de código no autorizada.
2. **Sistema de Auditoría y Logs:** Generación automática de un archivo de registro (`security_audit.log`) que almacena detalladamente cada acción realizada por el usuario y los eventos detectados por el sistema.
3. **Monitoreo de Red (Sniffer):** Módulo encargado del análisis de tráfico de red en tiempo real, identificando paquetes y flujos de datos sospechosos.

## Configuración del Entorno
Para el correcto funcionamiento de los módulos de seguridad, se recomienda el siguiente entorno:
* **SO:** Ubuntu / Kali Linux.
* **Red:** Configuración de Red Interna (Host-only) para aislamiento de pruebas.
* **Lenguajes:** C++ (Compilador G++) 

## Colaboración y Control de Versiones
Este repositorio utiliza un flujo de trabajo profesional basado en **Forks** y **Pull Requests**. Cada integración de código es revisada y auditada antes de incorporarse a la rama principal, garantizando la integridad del código fuente.
