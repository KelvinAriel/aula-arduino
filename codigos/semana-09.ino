#include <Servo.h>

// Objeto que permite controlar el servomotor
Servo puerta;

// Pines utilizados en el circuito
const int pinPIR = 4;
const int pinServo = 9;

// Variable para guardar el estado del sensor PIR
int estadoPIR = LOW;

void setup() {
  pinMode(pinPIR, INPUT);       // D4 recibe la señal digital del PIR
  puerta.attach(pinServo);     // La señal del servo está conectada a D9
  puerta.write(0);             // La puerta inicia cerrada
}

void loop() {
  estadoPIR = digitalRead(pinPIR);

  if (estadoPIR == HIGH) {
    puerta.write(90);          // Abre la puerta a 90 grados
    delay(3000);               // Permanece abierta durante 3 segundos
    puerta.write(0);           // Regresa a la posición cerrada
  } else {
    puerta.write(0);           // Sin movimiento, permanece cerrada
  }
}
