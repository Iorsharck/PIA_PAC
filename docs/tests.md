# Comandos
## Compilacion
### Con simbolos
g++ -std=c++17 -g  \             
main.cpp \
analizador.cpp \
NetworkMonitor.cpp \
-o SecureWatchConSimbolos.exe \
-I/usr/local/include/pcapplusplus \
-lPcap++ \
-lPacket++ \
-lCommon++ \
-lpcap

### Sin simbolos
g++ -std=c++17 -O2  \            
main.cpp \
analizador.cpp \
NetworkMonitor.cpp \
-o SecureWatchSinSimbolos.exe \
-I/usr/local/include/pcapplusplus \
-lPcap++ \
-lPacket++ \
-lCommon++ \
-lpcap


### Ejecucion
sudo ./SecureWatchSinSimbolos.exe 
sudo ./SecureWatchConSimbolos.exe 


## Resultado
Posibles resultados de la ejecucion del codigo  

### Salida de texto:
- Logs *Aanalisiis de red*

### Archivos:
- network_report.txt *Analisis de red*
- reporte_analisis.txt *Aanalisis de archivo*
- security_audit.log *Analisis de archivo*
  
## Evidencias
[Ejecucion de SecureWatch con Simbolos el analisis de red](EvidenciaEjecucion1.png)
[Ejecucion de SecureWatch sin Simbolos el analisis de interidad de archivo]EvidenciaEjecucion2.png)


