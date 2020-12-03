
import sys
from time import sleep
import serial
import signal

from threading import Thread
import firebase_admin
from firebase_admin import credentials
from firebase_admin import db


PAHT_CRED = '/home/pi/iot/basedatosdomotica-firebase-adminsdk-j7hjo-1add7ac3dc.json'
URL_DB = 'https://basedatosdomotica.firebaseio.com/'
REF_HOME = 'LivingRoom'
REF_LUCES = 'Luces'
REF_LUZ1 = 'luz1'
arduino = serial.Serial('/dev/ttyUSB0', 9600)

class IOT():

    def __init__(self):
        cred = credentials.Certificate(PAHT_CRED)
        firebase_admin.initialize_app(cred, {
            'databaseURL': URL_DB
        })

        self.refHome = db.reference(REF_HOME)

        # self.estructuraInicialDB() # solo ejecutar la primera vez

        self.refLuces = self.refHome.child(REF_LUCES)
        self.refLuz1 = self.refLuces.child(REF_LUZ1)

    def estructuraInicialDB(self):
        self.refHome.set({
            "Luces" : {
                "luz1" :True
            }
        })

    def ledControlGPIO(self, estado):

        if estado:

            print('LED ON')
            arduino.write('t')

        else:

            print('LED OFF')
            arduino.write('f')


    def lucesStart(self):


        E, i = [], 0


        estado_anterior = self.refLuz1.get()

        self.ledControlGPIO(estado_anterior)


        E.append(estado_anterior)


        while True:

            estado_actual = self.refLuz1.get()

            E.append(estado_actual)


            if E[i] != E[-1]:

                self.ledControlGPIO(estado_actual)


            del E[0]

            i = i + i

            sleep(0.4)

    def leerArduino(self):

        while True:
            if(arduino.in_waiting >0):
                line = ser.readline()
                print(line)



print ('START !')
iot = IOT()

subproceso_led = Thread(target=iot.lucesStart)
subproceso_led.daemon = True
subproceso_led.start()

subproceso_leerArduino = Thread(target=iot.leerArduino)
subproceso_leerArduino.daemon = True
subproceso_leerArduino.start()

signal.pause()
hola tio
