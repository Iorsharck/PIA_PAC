# Arquitectura
En materia de la arquitectura del codigo, todo se conectara por el menu, el main tendrá el menu para que se ejecuten y llamen todos los moduios, es más comodo asi para implementar en este menu y el main en general buenas practicas ya sean de errores, permisos, e incluso logs. Y de ahi hay dos modulos que se conectaran con el main, que es donde se crearan los procecsos para generar el analisis

# Modulos 
## Main
Es básicamente el menú principal que conecta todos los módulos. Lo importante aquí es que implementamos una función de logs que escribe todo lo que el usuario hace en el archivo security_audit.log. Así cumplimos con la parte de que el proyecto sea benigno y fácil de seguir cuando lo estemos analizando en ejecución.
## Modulo "Analisis de seguridad"
Aquí nos enfocamos en la seguridad de los archivos. El programa abre los ejecutables y lee su contenido binario de forma manual para sacar un checksum, con esto podemos comprobar la integridad de los datos y ver si el archivo es el original o si fue inyectado con algo.
## Modulo "Analisis de red"
En este programa sniffea el trafico el trafico de la red, y analisa si hay un patron malicioso en la red, dandote al final recomendaciones sobre comandos o cosas que podrías hacer para accabar con este posible ataque, se tiene planeado que recomiende bloquear ciertas IPs, o poner ciertas reglas de firewall.

# Dependencias
Las dependencias por ahbora en lo que se lleva este proyecto son los siguientes:
- *Llenar esto mientras se programa*
