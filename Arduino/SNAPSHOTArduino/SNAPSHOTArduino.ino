//LIBRERIA PARA EL SENSOR DE HUMEDAD Y TEMPERATURA
#include <DHT.h>
#include <DHT_U.h>
#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11

//LIBRERIA PARA LOS SERVOS
#include <Servo.h>
//CONTROL DE LAS LUCES
   
int LED1 = 30; //LED SALON
int LED2 = 31; //LED COCINA
int LED3 = 32; //LED HABITACION
int pulsador1 = 27; // PULSADOR SALON
int pulsador2 = 28; // PULSADOR COCINA
int pulsador3 = 29; // PULSADOR HABITACION 

int estadoBoton1 = 0;
int estadoBoton2 = 0;
int estadoBoton3 = 0;

// CONTROL LUZ RGB
int LED_R = 33; 
int LED_G = 34;
int LED_B = 35;

int PULSADORRGB = 26;

int contadorRgb = 0;
int estadobotonRgb;
String mensaje;
// CONTROL DE TEMPERATURA Y HUMEDAD
const int DHTPin = 36; // SENSOR DE TEMPERATURA Y HUMEDAD
DHT dht(DHTPin, DHTTYPE);
int presa = 0;
//CONTROL DE SERVOS 
Servo puertaPrincipal;  // create servo object to control a servo
int pos = 0;   
int pulsador = 40; 
int estadoBoton=0;
int tiempo = 0 ;
boolean estado = false;

void setup () { 
Serial.begin(9600);

////CONTROL DE LAS LUCES
  pinMode (LED1, OUTPUT);       //configurado como salida
  pinMode (LED2, OUTPUT);       //configurado como salida
  pinMode (LED3, OUTPUT);       //configurado como salida
  
  pinMode (pulsador1,INPUT);    //configurado de entrada
  pinMode (pulsador2, INPUT);   //configurado de entrada
  pinMode (pulsador3, INPUT);   //pulsador configurado como entrada
  
// CONTROL LUZ RGB
  pinMode(LED_R,OUTPUT);
  pinMode(LED_G,OUTPUT);
  pinMode(LED_B,OUTPUT);

  pinMode(PULSADORRGB, INPUT);

 // SENSOR DE TEMPERATURA Y HUMEDAD
  dht.begin(); 

 // CONTROL DE LOS SERVOS
   pinMode (pulsador,INPUT);    //configurado de entrada
    puertaPrincipal.attach(37);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  // PARTE PARA CONTROLAR EL LED CON LA RASPBERRY

  if(Serial.available()){
    String estado = Serial.readString();
    if (estado == "L01T"){
          digitalWrite(LED1,HIGH);
      }else if (estado == "L01F"){
        digitalWrite(LED1,LOW);
        }
     if (estado =="L02T"){
          digitalWrite(LED2,HIGH);
        }else if (estado =="L02F"){
          digitalWrite(LED2,LOW);
            }
      if (estado =="L03T"){
           digitalWrite(LED3,HIGH);
         }else if (estado == "L03F") {
          digitalWrite(LED3,LOW);
        }
       if (estado == "LR00") {
          digitalWrite(LED_R, LOW);
          digitalWrite(LED_G, LOW);
          digitalWrite(LED_B, LOW);
          contadorRgb = 6;
        }
       if (estado == "LR0R") {
          digitalWrite(LED_R, HIGH);
          digitalWrite(LED_G, LOW);
          digitalWrite(LED_B, LOW);
          contadorRgb = 0;
        }
       if (estado == "LR0G") {
        digitalWrite(LED_R, LOW);
        digitalWrite(LED_G, HIGH);
        digitalWrite(LED_B, LOW);
        contadorRgb = 1;
        }
       if (estado == "LR0B") {
        digitalWrite(LED_R, LOW);
        digitalWrite(LED_G, LOW);
        digitalWrite(LED_B, HIGH);
        contadorRgb = 2;
        }
       if (estado == "LR0Y") {
        digitalWrite(LED_R, HIGH);
        digitalWrite(LED_G, HIGH);
        digitalWrite(LED_B, LOW);
        contadorRgb = 3;
        }
       if (estado == "LR0P") {
        digitalWrite(LED_R, HIGH);
        digitalWrite(LED_G, LOW);
        digitalWrite(LED_B, HIGH);
        contadorRgb = 4;
        }               
       if (estado == "LR0C") {
        digitalWrite(LED_R, LOW);
        digitalWrite(LED_G, HIGH);
        digitalWrite(LED_B, HIGH);
        contadorRgb = 5;
        }
       if (estado == "P001T"){
        int envio = 0;
        PuertaPrincipalAbrirADerecha(envio);
      }else if (estado == "P001F"){
        int envio = 0;
        PuertaPrincipalCerrarDerecha(envio);
        }   
    } 

  // CONTROL DEL PRIMER LED
  estadoBoton1 = digitalRead(pulsador1);
    if (estadoBoton1 == HIGH) {
          String texto = "L01";
          ControlLuzLed(LED1 , texto);        
    }
    // CONTROL DEL SEGUNDO LED
      estadoBoton2 = digitalRead(pulsador2);
    if (estadoBoton2 == HIGH) {
          String texto = "L02";
          ControlLuzLed(LED2 , texto);
    }
    // CONTROL DEL TERCER LED
      estadoBoton3 = digitalRead(pulsador3);
    if (estadoBoton3 == HIGH) {
    String texto = "L03";
    ControlLuzLed(LED3 , texto);
    }
// CONTROL RGB
     estadobotonRgb = digitalRead(PULSADORRGB);
  if (estadobotonRgb == HIGH){
      delay(360);
    contadorRgb = contadorRgb + 1 ;
    if (contadorRgb >= 7){
      contadorRgb = 0;
      }
      ControlLuzRgb(contadorRgb);     
  }
 
   //30000 lo ideal
  if (presa > 999999){
    Temperatura(presa);
  }
  presa = presa + 1;
 
//CONTROL PUERTA PRINCIPAL 
 estadoBoton = digitalRead(pulsador);
 int envio = 1;
  if (estado == true){
          tiempo++;
    }
  if(estadoBoton == HIGH && estado == false){
     PuertaPrincipalAbrirADerecha(envio);  
    }
    else if (estadoBoton == HIGH && estado == true){
    envio = 1;
    PuertaPrincipalCerrarDerecha(envio);

  }else if (tiempo >= 15 ){
    envio = 1;
    PuertaPrincipalCerrarDerecha(envio);
    tiempo = 0; 
    }
  delay(360);
}
 //METODO PARA EL CONTROL DE LA PUERTA PRINCIPAL

 void PuertaPrincipalAbrirADerecha(int envio){
   if (estado != true ){
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            puertaPrincipal.write(pos);              // tell servo to go to position in variable 'pos'
            delay(15);
            // waits 15ms for the servo to reach the position
            estado = true;
      }
      if (envio == 1){
        Serial.println("P001T");
        }
    }
   
  }
  void PuertaPrincipalCerrarDerecha(int envio){
       if (estado != false ){
          for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
              puertaPrincipal.write(pos);              // tell servo to go to position in variable 'pos'
              delay(15);
              estado = false;// waits 15ms for the servo to reach the position
              tiempo = 0; 
    }
      if (envio == 1){
          Serial.println("P001F");
        }
    }

    }

 //METODO PARA CONTROL EL SENSOR DE TEMPERATURA
void Temperatura(int presa){
   //CONTROL SENSOR HUMEDAD Y TEMPERATURATURA
    //ESPERAMOS 5 SEGUNDOS PARA LA TOMA DE TEMPERATURA Y HUMEDAD
   //delay(1000);

   // Reading temperature or humidity takes about 250 milliseconds!
   float h = dht.readHumidity();
   float t = dht.readTemperature();
 
   if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
   }
   Serial.print("Humedad : ");
   Serial.println(h);
   Serial.print("Temperatura : ");
   Serial.println(t);
   presa = 0;
  }
  
//METODO PARA CONTROL LA LUZ RGB

void ControlLuzRgb(int contadorRgb){
    switch (contadorRgb) {
            case 0:
            //ROJO
              digitalWrite(LED_R, HIGH);
              digitalWrite(LED_G, LOW);
              digitalWrite(LED_B, LOW);
              mensaje = "LR0R";
              Serial.println(mensaje);
              break;
            case 1:
            //VERDE
              digitalWrite(LED_R, LOW);
              digitalWrite(LED_G, HIGH);
              digitalWrite(LED_B, LOW);
              mensaje ="LR0G";
              Serial.println(mensaje);              
              break;
            case 2:
            //AZUL
              digitalWrite(LED_R, LOW);
              digitalWrite(LED_G, LOW);
              digitalWrite(LED_B, HIGH);
              mensaje = "LR0B";
              Serial.println(mensaje);
              break;
            case 3:
            //AMARILLO
              digitalWrite(LED_R, HIGH);
              digitalWrite(LED_G, HIGH);
              digitalWrite(LED_B, LOW);
              mensaje ="LR0Y";
              Serial.println(mensaje);
              break;
            case 4:
            //MORADO
              digitalWrite(LED_R, HIGH);
              digitalWrite(LED_G, LOW);
              digitalWrite(LED_B, HIGH);
              mensaje = "LR0P";
              Serial.println(mensaje);
              break;
            case 5:
            //CELESTE
              digitalWrite(LED_R, LOW);
              digitalWrite(LED_G, HIGH);
              digitalWrite(LED_B, HIGH);
              mensaje ="LR0C";
              Serial.println(mensaje);
              break;
            case 6:
            //APAGADO
              digitalWrite(LED_R, LOW);
              digitalWrite(LED_G, LOW);
              digitalWrite(LED_B, LOW);
              mensaje ="LR00";
              Serial.println(mensaje);
              break;
            default:
              digitalWrite(LED_R, LOW);
              digitalWrite(LED_G, LOW);
              digitalWrite(LED_B, LOW);
              mensaje ="LR00";
              Serial.println(mensaje);    
              break;
          }
  }
  //METODO PARA EL CONTROL DE LUCES LEDS
void ControlLuzLed(int LED , String texto ){
   if(digitalRead(LED) == HIGH){
          Serial.println(texto+"F");
          digitalWrite(LED,LOW);
          delay(360);
          }else{
            Serial.println(texto+"T" );
            digitalWrite(LED,HIGH);
            delay(360);
          }
  }
