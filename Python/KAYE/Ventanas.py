import serial
from time import sleep
from firebase_admin import db

REF_HABITACION = 'HABITACION'
REF_VENTANAS_HABITACION = 'VENTANAS'
REF_VENTANA_HABITACION = 'Ventana-habitacion'

arduino = serial.Serial('/dev/ttyUSB0', 115200)



class ventanas:
    CODIGO_ENVIO = 0
    def Control_ventana(self,comando):
        #REFERENCIAS A LA PUERTA DE LA HABITACION
        self.REF_HABITACION = db.reference(REF_HABITACION)
        self.REF_VENTANAS_HABITACION = self.REF_HABITACION.child(REF_VENTANAS_HABITACION)
        self.REF_VENTANA_HABITACION = self.REF_VENTANAS_HABITACION.child(REF_VENTANA_HABITACION)

        if comando == 'V001T':
            self.REF_VENTANA_HABITACION.set("true")
            comando = ""
        elif comando == 'V001F':
            self.REF_VENTANA_HABITACION.set("false")
            comando = ""
        global CODIGO_ENVIO = "1"

        print("Arduino salida")
        print(CODIGO_ENVIO)


    def controlVentanas(self):
        print("Firebase Entrada")
        global CODIGO_ENVIO
        print(CODIGO_ENVIO)
        global CODIGO_ENVIO
        if  CODIGO_ENVIO == 0:
            #REFERENCIAS A LA PUERTA DE LA HABITACION
            self.REF_HABITACION = db.reference(REF_HABITACION)
            self.REF_VENTANAS_HABITACION = self.REF_HABITACION.child(REF_VENTANAS_HABITACION)
            self.REF_VENTANA_HABITACION = self.REF_VENTANAS_HABITACION.child(REF_VENTANA_HABITACION)

            print("Metodo Ventanas")
            E, i = [], 0

            estado_anterior = self.REF_VENTANA_HABITACION.get()

            E.append(estado_anterior)

            while True:
                estado_actual = self.REF_VENTANA_HABITACION.get()
                E.append(estado_actual)
                if E[i] != E[-1]:
                    if estado_actual :
                        print('Ventana habitacion abierta')
                        arduino.write("V001T")
                    else:
                        print('Ventana habitacion cerrada')
                        arduino.write("V001F")
                del E[0]
                i = i + i
                sleep(0.4)
            else:
                global CODIGO_ENVIO = 0;

                print("Firebase Salida")
                global CODIGO_ENVIO
                print(CODIGO_ENVIO)
        print("Firebase Salida")
        print(CODIGO_ENVIO)
