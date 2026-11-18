#include <Servo.h>
Servo puerta;
const int pinPIR = 2;
const int pinBoton = 3;
const int ledVerde = 4;
const int ledRojo = 5;
const int pinBuzzer = 8;
const int pinServo = 9;
void setup() {
  pinMode(pinPIR, INPUT);
  pinMode(pinBoton, INPUT_PULLUP);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  puerta.attach(pinServo);
  puerta.write(0);
  Serial.begin(9600);
}
void loop() {
  int presencia = digitalRead(pinPIR);
  int autorizacion = digitalRead(pinBoton);
  if (presencia == HIGH && autorizacion == LOW) {
    puerta.write(90);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledRojo, LOW);
    tone(pinBuzzer, 1500);
    Serial.println("ACCESO PERMITIDO");
  } else if (presencia == HIGH) {
    puerta.write(0);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledRojo, HIGH);
    tone(pinBuzzer, 400);
    Serial.println("ACCESO PENDIENTE");
  } else {
    puerta.write(0);
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledRojo, LOW);
    noTone(pinBuzzer);
    Serial.println("SISTEMA EN ESPERA");
  }
  delay(200);
}
