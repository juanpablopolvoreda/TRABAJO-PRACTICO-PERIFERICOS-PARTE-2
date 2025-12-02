const int PIN_Boton1 = 2;
const int PIN_Boton2 = 3;
const int PIN_LED1 = 12;
const int PIN_LED2 = 13;
int estadoLed1 = 0;
int estadoLed2 = 0;


unsigned long tiempoAnteriorBtn1 = 0;
unsigned long tiempoAnteriorBtn2 = 0;
unsigned long tiempoAnteriorEnvio = 0;


const long intervaloRebote = 200; //antirrebote de los pulsadores
const long intervaloEnvio = 50;   

void setup() {
  Serial.begin(9600);

  
  pinMode(PIN_Boton1, INPUT);
  pinMode(PIN_Boton2, INPUT);
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
}

void loop() {
  
  unsigned long tiempoActual = millis();

  // Lee los botones:
  int lecturaBtn1 = digitalRead(PIN_Boton1); 
  int lecturaBtn2 = digitalRead(PIN_Boton2);

  if (lecturaBtn1 == HIGH) {
    
    if (tiempoActual - tiempoAnteriorBtn1 > intervaloRebote) {
      estadoLed1 = !estadoLed1;         
      tiempoAnteriorBtn1 = tiempoActual; 
    }
  } 

  
  if (lecturaBtn2 == HIGH) {
    if (tiempoActual - tiempoAnteriorBtn2 > intervaloRebote) {
      estadoLed2 = !estadoLed2;
      tiempoAnteriorBtn2 = tiempoActual; 
    }
  } 
   
  // Lee los comandos de processing:
  if (Serial.available() > 0) {
    char orden = Serial.read();

    if (orden == 'A') estadoLed1 = !estadoLed1;
    if (orden == 'B') estadoLed2 = !estadoLed2;
  }

  
  digitalWrite(PIN_LED1, estadoLed1);
  digitalWrite(PIN_LED2, estadoLed2);

  // Envia datos a processing
  if (tiempoActual - tiempoAnteriorEnvio > intervaloEnvio) {
  Serial.print(lecturaBtn1);
    Serial.print(",");
    Serial.print(lecturaBtn2);
    Serial.print(",");
    Serial.print(estadoLed1);
    Serial.print(",");
    Serial.println(estadoLed2); 
    
    tiempoAnteriorEnvio = tiempoActual; 
  }
  
}