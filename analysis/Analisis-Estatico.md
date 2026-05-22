# Exportaciones completas
En este caso las exportaiones del programa no son muy importantes, ninguna en extremo preocupante como lo serian InjectDLL, o que analiza si es una maquina virtual. Y por motivos evidentes la exportacion de redes como lo son "IPv4Address",,"IPv4Layer" aunque ninguno de estos es algo demasiado sospechoso debido a que no tiene un "SendData" al internet. Tambien se vio las funciones en Guidra y no se encontra nada proucpante


# Strings
Se detectaron algunos strings, pese que no son de mucha utilidad en este especifico casoo, se pyuede notar que  los dos primeros son de un print, y el ultimo es la ejecuciion de uun comando interno de la libreria de red si hacemos educated guess, sin embargo tiene demasiado para ponerlo mas allla de lo que muestra el comando  
"-----END"  
"-----BEGINN  
"ascii   command -v nmcli >/dev/null 2>&1 || { echo 'nmcli not installed'"...  


# Capturas

[Captura al analisar lo exportado de Ghuidra](AnalisisGhidra.png)  
[Captura al analisar los strings en Radaware2](AnalisisRadaware2.png)
