import processing.serial.*;

Serial miPuerto;
String datosRecibidos = "";


int estadoE1 = 0;
int estadoE2 = 0;
int estadoL1 = 0;
int estadoL2 = 0;

void setup() {
  size(400, 300);

  printArray(Serial.list());
  String puertoNombre = Serial.list()[2]; 
  miPuerto = new Serial(this, puertoNombre, 9600);
  
  // Leemos hasta encontrar un salto de línea 
  miPuerto.bufferUntil('\n'); 
  textSize(20);
  textAlign(CENTER, CENTER);
}

void draw() {
  background(255); 
  
 
  fill(200); rect(50, 50, 120, 40); fill(0); text("Entradas", 110, 70);
  fill(255, 200, 200); rect(50, 150, 120, 40); fill(0); text("Salidas", 110, 170);

 
  if (estadoE1 == 1) fill(0, 255, 0); else fill(255);
  rect(200, 50, 50, 50); 
  fill(0); text("E1", 225, 75);

  if (estadoE2 == 1) fill(0, 255, 0); else fill(255);
  rect(300, 50, 50, 50); 
  fill(0); text("E2", 325, 75);


  if (estadoL1 == 1) fill(255, 0, 0); else fill(255);
  ellipse(225, 175, 50, 50);
  fill(0); text("L1", 225, 175);

  if (estadoL2 == 1) fill(255, 0, 0); else fill(255);
  ellipse(325, 175, 50, 50);
  fill(0); text("L2", 325, 175);
}

//EVENTO DE MOUSE
void mousePressed() {
 
 
  if (mouseX > 200 && mouseX < 250 && mouseY > 50 && mouseY < 100) {
    miPuerto.write('A'); 
  }
  
    
  if (mouseX > 300 && mouseX < 350 && mouseY > 50 && mouseY < 100) {
    miPuerto.write('B'); 
  }
  
}


void serialEvent(Serial p) {
  datosRecibidos = p.readString();
  datosRecibidos = trim(datosRecibidos); 
  
  
  int[] valores = int(split(datosRecibidos, ','));
  
  
  if (valores.length == 4) {
    estadoE1 = valores[0];
    estadoE2 = valores[1];
    estadoL1 = valores[2];
    estadoL2 = valores[3];
  }
}
