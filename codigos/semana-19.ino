#include <Servo.h>
const int pinTrig = 9;
const int pinEcho = 10;
const int ledVerde = 3;
const int ledAmarillo = 4;
const int ledRojo = 5;
const int pinServo = 6;
Servo indicador;
float medirDistancia() {
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  unsigned long duracion = pulseIn(pinEcho, HIGH, 30000);
  if (duracion == 0) return -1.0;
  return duracion * 0.0343 / 2.0;
}
void mostrarEstado(int verde, int amarillo, int rojo, int angulo) {
  digitalWrite(ledVerde, verde);
  digitalWrite(ledAmarillo, amarillo);
  digitalWrite(ledRojo, rojo);
  indicador.write(angulo);
}
void setup() {
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  indicador.attach(pinServo);
  Serial.begin(9600);
}
void loop() {
  float distancia = medirDistancia();
  if (distancia < 0) {
    mostrarEstado(LOW, LOW, LOW, 90);
    Serial.println("Lectura no valida");
  } else if (distancia <= 30) {
    mostrarEstado(LOW, LOW, HIGH, 180);
    Serial.println("Zona cercana");
  } else if (distancia <= 100) {
    mostrarEstado(LOW, HIGH, LOW, 90);
    Serial.println("Zona media");
  } else {
    mostrarEstado(HIGH, LOW, LOW, 0);
    Serial.println("Zona lejana");
  }
  delay(300);
}
