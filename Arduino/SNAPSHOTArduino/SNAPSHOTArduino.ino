#include <DHT.h>
#include <DHT_U.h>

//LIBRERIA PARA EL SENSOR DE HUMEDAD Y TEMPERATURA
#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11

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
    } 

  // CONTROL DEL PRIMER LED
  estadoBoton1 = digitalRead(pulsador1);
    if (estadoBoton1 == HIGH) {
        if(digitalRead(LED1) == HIGH){
          Serial.println("L01F");
          digitalWrite(LED1,LOW);
          delay(360);
          }else{
            digitalWrite(LED1,HIGH);
            Serial.println("L01T");
            delay(360);
            }      
    }
    // CONTROL DEL SEGUNDO LED
      estadoBoton2 = digitalRead(pulsador2);
    if (estadoBoton2 == HIGH) {
        if(digitalRead(LED2) == HIGH){
          Serial.println("L02F");
          digitalWrite(LED2,LOW);
          delay(360);
          }else{
            Serial.println("L02T");
            digitalWrite(LED2,HIGH);
            delay(360);
            }      
    }
    // CONTROL DEL TERCER LED
      estadoBoton3 = digitalRead(pulsador3);
    if (estadoBoton3 == HIGH) {
        if(digitalRead(LED3) == HIGH){
          Serial.println("L03F");
          digitalWrite(LED3,LOW);
          delay(360);
          }else{
            Serial.println("L03T");
            digitalWrite(LED3,HIGH);
            delay(360);
            }      
    }
// CONTROL RGB
     estadobotonRgb = digitalRead(PULSADORRGB);
  if (estadobotonRgb == HIGH){
      delay(360);
    contadorRgb = contadorRgb + 1 ;
    if (contadorRgb >= 7){
      contadorRgb = 0;
      }
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
   //30000 lo ideal
  if (presa > 999999){
     Serial.print("Humedad : ");
   Serial.println(h);
   Serial.print("Temperatura : ");
   Serial.println(t);
   presa = 0;
  }
  presa = presa + 1;
 
}
