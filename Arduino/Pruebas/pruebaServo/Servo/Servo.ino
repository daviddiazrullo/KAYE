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
int pulsador =26; 
int estadoBoton=0;
boolean estado = false;
void setup() {
  pinMode (pulsador,INPUT);    //configurado de entrada
  myservo.attach(52);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  estadoBoton = digitalRead(pulsador);

  if(estadoBoton == HIGH && estado == false){
      for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
    // waits 15ms for the servo to reach the position
    estado = true; 
      }  
    }
    else if (estadoBoton == HIGH && estado == true){
    for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
    estado = false;// waits 15ms for the servo to reach the position
  }
  }
  delay(360);
  


}
