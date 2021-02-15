// 46 47 ventanas
// 45 boton
#include <Servo.h>

////////////////////////////////////////////////////////////
int botonventana = 45;
int pos1 = 90;
Servo VIzquierda;
Servo VDerecha;
Servo ventanaHabitacion[2] = { VIzquierda, VDerecha };


void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode (botonventana, INPUT);
  ventanaHabitacion[0].attach(46);
  ventanaHabitacion[1].attach(47);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void AbrirVentana() {
  for (pos1 = 90; pos1 <= 180; pos1 += 1) { // Aumenta la posicion en grados desde 0 a 90
    ventanaHabitacion[0].write(pos1);              // Coloca el primer servo en la posicion actual
    ventanaHabitacion[1].write(180 - pos1);        // Coloca el segundo servo en la posicion opuesta
    delay(25);                       // Detiene el avance 15ms para dar tiempo al servo a moverse
  }
}
void CerrarVentana() {
  for (pos1 = 180; pos1 >= 90; pos1 -= 1) { // Disminuye la posicion en grados de 90 a 0
    ventanaHabitacion[0].write(pos1);              // Coloca el primer servo en la posicion actual     Serial.println("Primero");
    ventanaHabitacion[1].write(180 - pos1);       // Coloca el segundo servo en la posicion opuesta
    delay(25);                       // Detiene el avance 15ms para dar tiempo al servo a moverse
  }
}
