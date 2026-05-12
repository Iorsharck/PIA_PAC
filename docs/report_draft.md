# Reporte Técnico - Avance II

## 1. Descripción del Módulo (Analizador de Integridad)
Se implementó un módulo de auditoría y validación de integridad en C++. Este componente es responsable de asegurar que los archivos críticos del sistema no hayan sido alterados por terceros o software malicioso.

## 2. Implementación Técnica
* **Cálculo de Checksum:** El sistema lee los archivos en modo binario mediante `std::ifstream` y calcula una suma de verificación para validar el estado del archivo.
* **Manejo de Errores:** Se integró la biblioteca `sys/stat.h` para verificar la existencia y permisos de los archivos antes de procesarlos, evitando fallos en tiempo de ejecución.
* **Bitácora de Auditoría:** Todas las acciones se registran automáticamente en un archivo `security_audit.log` con estampado de tiempo (timestamp).

## 3. Resultados y Evidencia
Durante las pruebas, el módulo generó con éxito reportes en formato `.txt` (`reporte_analisis.txt`), mostrando el valor hexadecimal del checksum calculado. Esto permite una rápida auditoría por parte del administrador del sistema.

## 4. Próximos Pasos (Fase III)
* Integración del módulo de monitoreo de red.
* Implementación de técnicas de análisis dinámico.
* Fortalecimiento de la seguridad de los archivos de log.
