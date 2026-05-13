Compilado en Linux:

# Comandos
## Con simbolos
g++ -std=c++17 -g \
main.cpp \
analizador.cpp \
NetworkMonitor.cpp \
-o SecureWatch_Debug \
-I/usr/local/include/pcapplusplus \
-lPcap++ \
-lPacket++ \
-lCommon++ \
-lpcap
## Sin simbvolos
g++ -std=c++17 -O2 \
main.cpp \
analizador.cpp \
NetworkMonitor.cpp \
-o SecureWatch \
-I/usr/local/include/pcapplusplus \
-lPcap++ \
-lPacket++ \
-lCommon++ \
-lpcap

# Ejecuion
sudo ./SecureWatch

Capturas son ejecuccion1 y ejecucion 2


