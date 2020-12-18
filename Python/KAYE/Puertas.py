import serial
from time import sleep
from firebase_admin import db


REF_SALON = 'SALON'
REF_PUERTAS_SALON = 'PUERTAS'
REF_PUERTA_PRINCIPAL = 'Puerta-principal'

arduino = serial.Serial('/dev/ttyUSB0', 9600)


class puertas:
    def Control_puerta(self,comando):
        self.REF_SALON = db.reference(REF_SALON)
        self.REF_PUERTAS_SALON = self.REF_SALON.child(REF_PUERTAS_SALON)
        self.REF_PUERTA_PRINCIPAL = self.REF_PUERTAS_SALON.child(REF_PUERTA_PRINCIPAL)
        if comando == 'P001T':
            self.REF_PUERTA_PRINCIPAL.set("true")
            comando = ""
            #print("Cerrando puerta principal")
        elif comando == 'P001F':
            self.REF_PUERTA_PRINCIPAL.set("false")
            comando = ""
            #print("Abriendo puerta principal")

    def controlPuertas(self):
        self.REF_SALON = db.reference(REF_SALON)
        self.REF_PUERTAS_SALON = self.REF_SALON.child(REF_PUERTAS_SALON)
        self.REF_PUERTA_PRINCIPAL = self.REF_PUERTAS_SALON.child(REF_PUERTA_PRINCIPAL)
        print("Metodo Puertas")
        E5, i = [], 0
        puertas = ["Puerta-principal"]
        estado_anterior5 = self.REF_PUERTA_PRINCIPAL.get()
        self.puertaControlGPIO(estado_anterior5, "Puerta-principal")

        E5.append(estado_anterior5)

        while True:
            estado_actual5 = self.REF_PUERTA_PRINCIPAL.get()

            E5.append(estado_actual5)

            if E5[i] != E5[-1]:
                ref = "Puerta-principal"
                self.puertaControlGPIO(estado_actual5, ref)
            del E5[0]
            i = i + i
            sleep(0.4)


    def puertaControlGPIO(self, estado, refe):
        if refe == "Puerta-principal":
            if estado:
                print('Puerta principal abierta')
                arduino.write("P001T")
            else:
                print('uerta principal cerrada')
                arduino.write('P001F')
