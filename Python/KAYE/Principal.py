import Firebase
import Luces
import Arduino
import threading


import signal


print("Comienza la Aplicacion")
#Inicio la conexion con la base de datos
iniciar = Firebase.IOT().iniciar()

#Luces.Luces().controlluces()
#Arduino.leerArduino()
#Creo hilos para poder ejecutar todas las partes a la vez
subproceso_leerArduino = threading.Thread(target=Arduino.leerArduino)
subproceso_leerArduino.daemon = True

subproceso_luces = threading.Thread(target=Luces.Luces().controlluces)
subproceso_luces.daemon = True

subproceso_luces.start()

subproceso_leerArduino.start()

signal.pause()

