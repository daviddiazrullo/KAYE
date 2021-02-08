import Firebase
import Luces
import Arduino
import Puertas
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

subproceso_leerArduinoNano = threading.Thread(target=Arduino.leerArduinoNano)
subproceso_leerArduinoNano.daemon = True

subproceso_luces = threading.Thread(target=Luces.Luces().controlluces)
subproceso_luces.daemon = True

subproceso_puertas = threading.Thread(target=Puertas.puertas().controlPuertas)
subproceso_luces.daemon = True

subproceso_luces.start()

subproceso_leerArduino.start()

subproceso_leerArduinoNano.start()

subproceso_puertas.start()


signal.pause()
