int IN3 = 4;      // IN3 a pin digital 7
int IN4 = 3;      // IN4 a pin digital 8
int ENB = A0;      // ENA a pin digital 9
int Boton= 6 ;
int Fcarrera = 5 ;

void setup() {
  Serial.begin(9600);

  // put your setup code here, to run once:
  pinMode(IN3, OUTPUT);   // IN3 como salida
  pinMode(IN4, OUTPUT);   // IN4 como salida
  pinMode(ENB, OUTPUT);   // ENB como salida
  pinMode(Boton, INPUT);   // boton como entrada
  pinMode(Fcarrera, INPUT);   // boton como entrada

}

void loop() {
      //Retroceder();

  // put your main code here, to run repeatedly:
   int botonFinalDeCarrera = digitalRead(Fcarrera); 
  int estadoboton = digitalRead(Boton);
  if(estadoboton == HIGH && botonFinalDeCarrera == HIGH){
    Serial.println("Boton pulsado");
    Avance();
    delay(3700);
    Stop();
    Serial.print("Parado");
    delay(3600);

  }   
      if (botonFinalDeCarrera == HIGH ){
      Stop();
    
    }else{
      Retroceder();
      Serial.print("Para atras");

      }
}
void Stop(){
  analogWrite(ENB, 0);  // velocidad mediante PWM en ENB
  digitalWrite(IN3, LOW); // IN3 a cero logico
  digitalWrite(IN4, LOW);  // IN4 a uno logico
  }
void Avance(){  // funcion para avance de motor A

  analogWrite(ENB, 255);  // velocidad mediante PWM en ENB
  digitalWrite(IN3, LOW); // IN3 a cero logico
  digitalWrite(IN4, HIGH);  // IN4 a uno logico
}

void Retroceder(){  // funcion para avance de motor A

  analogWrite(ENB, 255);  // velocidad mediante PWM en ENB
  digitalWrite(IN3, HIGH); // IN3 a cero logico
  digitalWrite(IN4, LOW);  // IN4 a uno logico
}
