import serial
from time import sleep
from firebase_admin import db


REF_SALON = 'SALON'
REF_PUERTAS_SALON = 'PUERTAS'
REF_PUERTA_PRINCIPAL = 'Puerta-principal'

REF_HABITACION = 'HABITACION'
REF_PUERTAS_HABITACION = 'PUERTAS'
REF_PUERTA_HABITACION = 'Puerta-habitacion'

REF_COCINA = 'COCINA'
REF_PUERTAS_COCINA = 'PUERTAS'
REF_PUERTA_COCINA = 'Puerta-cocina'

arduino = serial.Serial('/dev/ttyUSB0', 9600)


class puertas:
    def Control_puerta(self,comando):
        self.REF_SALON = db.reference(REF_SALON)
        self.REF_PUERTAS_SALON = self.REF_SALON.child(REF_PUERTAS_SALON)
        self.REF_PUERTA_PRINCIPAL = self.REF_PUERTAS_SALON.child(REF_PUERTA_PRINCIPAL)
        #REFERENCIAS A LA PUERTA DE LA HABITACION
        self.REF_HABITACION = db.reference(REF_HABITACION)
        self.REF_PUERTAS_HABITACION = self.REF_HABITACION.child(REF_PUERTAS_HABITACION)
        self.REF_PUERTA_HABITACION = self.REF_PUERTAS_HABITACION.child(REF_PUERTA_HABITACION)
        #REFERENCIAS A LA PUERTA DE LA COCINA
        self.REF_COCINA = db.reference(REF_COCINA)
        self.REF_PUERTAS_COCINA = self.REF_COCINA.child(REF_PUERTAS_COCINA)
        self.REF_PUERTA_COCINA = self.REF_PUERTAS_COCINA.child(REF_PUERTA_COCINA)
        if comando == 'P001T':
            self.REF_PUERTA_PRINCIPAL.set("true")
            comando = ""
            #print("Cerrando puerta principal")
        elif comando == 'P001F':
            self.REF_PUERTA_PRINCIPAL.set("false")
            comando = ""
            #print("Abriendo puerta principal")
        if comando == 'P002T':
            self.REF_PUERTA_HABITACION.set("true")
            comando = ""
        elif comando == 'P002F':
            self.REF_PUERTA_HABITACION.set("false")
            comando = ""
        if comando == 'P003T':
            self.REF_PUERTA_COCINA.set("true")
            comando = ""
        elif comando == 'P003F':
            self.REF_PUERTA_COCINA.set("false")
            comando = ""

    def controlPuertas(self):
        self.REF_SALON = db.reference(REF_SALON)
        self.REF_PUERTAS_SALON = self.REF_SALON.child(REF_PUERTAS_SALON)
        self.REF_PUERTA_PRINCIPAL = self.REF_PUERTAS_SALON.child(REF_PUERTA_PRINCIPAL)
        #REFERENCIAS A LA PUERTA DE LA HABITACION
        self.REF_HABITACION = db.reference(REF_HABITACION)
        self.REF_PUERTAS_HABITACION = self.REF_HABITACION.child(REF_PUERTAS_HABITACION)
        self.REF_PUERTA_HABITACION = self.REF_PUERTAS_HABITACION.child(REF_PUERTA_HABITACION)
        #REFERENCIAS A LA PUERTA DE LA COCINA
        self.REF_COCINA = db.reference(REF_COCINA)
        self.REF_PUERTAS_COCINA = self.REF_COCINA.child(REF_PUERTAS_COCINA)
        self.REF_PUERTA_COCINA = self.REF_PUERTAS_COCINA.child(REF_PUERTA_COCINA)
        print("Metodo Puertas")
        E, i = [], 0
        E1, i = [], 0
        E2, i = [], 0

        puertas = ["Puerta-principal","Puerta-habitacion","Puerta-cocina"]
        estado_anterior = self.REF_PUERTA_PRINCIPAL.get()
        estado_anterior1 = self.REF_PUERTA_HABITACION.get()
        estado_anterior2 = self.REF_PUERTA_COCINA.get()


        self.puertaControlGPIO(estado_anterior, "Puerta-principal")
        self.puertaControlGPIO(estado_anterior1, "Puerta-habitacion")
        self.puertaControlGPIO(estado_anterior2, "Puerta-cocina")


        E.append(estado_anterior)
        E1.append(estado_anterior1)
        E2.append(estado_anterior2)

        while True:
            estado_actual = self.REF_PUERTA_PRINCIPAL.get()
            estado_actual1 = self.REF_PUERTA_HABITACION.get()
            estado_actual2 = self.REF_PUERTA_COCINA.get()

            E.append(estado_actual)
            E1.append(estado_actual1)
            E2.append(estado_actual2)


            if E[i] != E[-1]:
                ref = "Puerta-principal"
                self.puertaControlGPIO(estado_actual, ref)
            del E[0]
            i = i + i
            sleep(0.4)

            if E1[i] != E1[-1]:
                ref = "Puerta-habitacion"
                self.puertaControlGPIO(estado_actual1, ref)
            del E1[0]
            i = i + i
            sleep(0.4)

            if E2[i] != E2[-1]:
                ref = "Puerta-cocina"
                self.puertaControlGPIO(estado_actual2, ref)
            del E2[0]
            i = i + i
            sleep(0.4)


    def puertaControlGPIO(self, estado, refe):
        if refe == "Puerta-principal":
            if estado:
                print('Puerta principal abierta')
                arduino.write("P001T")
            else:
                print('Puerta principal cerrada')
                arduino.write('P001F')
        if refe == "Puerta-habitacion":
            if estado:
                print('Puerta habitacion abierta')
                arduino.write("P002T")
            else:
                print('Puerta habitacion cerrada')
                arduino.write('P002F')
        if refe == "Puerta-cocina":
            if estado:
                print('Puerta cocina abierta')
                arduino.write("P003T")
            else:
                print('Puerta cocina cerrada')
                arduino.write('P003F')
