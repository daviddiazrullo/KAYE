import serial
import Firebase
import Confort
import Puertas

arduino = serial.Serial('/dev/ttyUSB0', 9600)


def leerArduino():
    print("Arduino escuchando")
    comando = ' '
    while True:
        if (arduino.in_waiting > 0):
            line = arduino.readline()
            #IMPRIME EL MENSAJE QUE ENVIA ARDUINO
            #print(line.strip())
            comando = line.strip()
            if comando == 'L01T':
                Firebase.IOT().ControlArduino(comando)
            elif comando == 'L01F':
                Firebase.IOT().ControlArduino(comando)
            if comando == 'L02T':
                Firebase.IOT().ControlArduino(comando)
                comando = ""
            elif comando == 'L02F':
                Firebase.IOT().ControlArduino(comando)
            if comando == 'L03T':
                Firebase.IOT().ControlArduino(comando)
                comando = ""
            elif comando == 'L03F':
                Firebase.IOT().ControlArduino(comando)
            if comando == 'LR00':
                Firebase.IOT().ControlArduino(comando)
                comando = ""
            if comando == 'LR0R':
                Firebase.IOT().ControlArduino(comando)
                comando = ""
            if comando == 'LR0G':
                Firebase.IOT().ControlArduino(comando)
                comando = ""
            if comando == 'LR0B':
                Firebase.IOT().ControlArduino(comando)
                comando = ""
            if comando == 'LR0Y':
                Firebase.IOT().ControlArduino(comando)
                comando = ""
            if comando == 'LR0P':
                Firebase.IOT().ControlArduino(comando)
                comando = ""
            if comando == 'LR0C':
                Firebase.IOT().ControlArduino(comando)
                comando = ""
            if comando == 'P001T':
                Firebase.IOT().Control_puerta(comando)
                comando = ""
            if comando == 'P001F':
                Firebase.IOT().Control_puerta(comando)
                comando = ""
            else:
                Confort.confort().controlHumedadTemperatura(comando)
