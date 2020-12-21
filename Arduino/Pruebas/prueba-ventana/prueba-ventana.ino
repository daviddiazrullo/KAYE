#include <Servo.h>
int boton = 43;
int pos = 0;
Servo prueba;
void setup() {
  // put your setup code here, to run once:
 //PUERTA PRINCIPAL
   pinMode (boton,INPUT);    //configurado de entrada
    prueba.attach(44); 
}

void loop() {
  int estadoBotonHabitacion = digitalRead(boton);

  if(estadoBotonHabitacion == HIGH ){
                delay(15);

     for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            prueba.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);
            // waits 15ms for the servo to reach the position
            //estadoPuerta = true;
      }
      }
  // put your main code here, to run repeatedly:

}
