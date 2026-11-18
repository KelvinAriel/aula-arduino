#include <Servo.h>
const int pinTrig = 9;
const int pinEcho = 10;
const int pinServo = 6;
const int ledVerde = 3;
const int ledRojo = 4;
const int buzzer = 8;
Servo barrera;
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
void cerrarBarrera() {
  barrera.write(0);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledRojo, HIGH);
}
void abrirBarrera() {
  barrera.write(90);
  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledRojo, LOW);
}
void setup() {
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(buzzer, OUTPUT);
  barrera.attach(pinServo);
  cerrarBarrera();
  Serial.begin(9600);
}
void loop() {
  float distancia = medirDistancia();
  if (distancia < 0) {
    cerrarBarrera();
    tone(buzzer, 300);
    Serial.println("ERROR DE LECTURA");
  } else if (distancia <= 20) {
    abrirBarrera();
    tone(buzzer, 1200, 120);
    Serial.println("OBJETO DETECTADO - BARRERA ABIERTA");
  } else {
    cerrarBarrera();
    noTone(buzzer);
    Serial.println("BARRERA CERRADA");
  }
  delay(300);
}
