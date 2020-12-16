/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int pulsador = 40; 
int estadoBoton=0;
int tiempo = 0 ;
boolean estado = false;
void setup() {
  Serial.begin(9600);
  pinMode (pulsador,INPUT);    //configurado de entrada
  myservo.attach(37);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  estadoBoton = digitalRead(pulsador);
  Serial.println(estado);

  if (estado == true){
          tiempo++;
    }
  if(estadoBoton == HIGH && estado == false){
      Serial.println("pulsado");

      for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
    // waits 15ms for the servo to reach the position
    estado = true;
    
      }  
    }
    else if (estadoBoton == HIGH && estado == true){
      Serial.println("pulsado");
      for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);
      estado = false;// waits 15ms for the servo to reach the position
      tiempo = 0; 
    }
  }else if (tiempo >= 15 ){
        for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
            myservo.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);
            estado = false;// waits 15ms for the servo to reach the position
        }
    tiempo = 0; 

    }
  delay(360);
  


}
