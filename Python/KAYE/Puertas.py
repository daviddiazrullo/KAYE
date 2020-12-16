from firebase_admin import db


REF_SALON = 'SALON'
REF_PUERTAS_SALON = 'PUERTAS'
REF_PUERTA_PRINCIPAL = 'Puerta-principal'

class puertas:
    def Control_puerta (self,comando):
        self.refSalon = db.reference(REF_SALON)
        self.REF_PUERTAS_SALON = self.refSalon.child(REF_CLIMATIZACION)
        self.REF_PUERTA_PRINCIPAL = self.refClimatizacion.child(REF_TEMPERATURA)
        if comando == 'P001T'|| comando == 'P001F':
            # BUG NO VA A HACER NADA
            self.REF_PUERTA_PRINCIPAL.set(comando)
            comando = ""
