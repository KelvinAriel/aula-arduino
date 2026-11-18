#include <Servo.h>
const int pinPir = 2;
const int ledVerde = 3;
const int ledAmarillo = 4;
const int ledRojo = 5;
const int pinServo = 6;
const int pinBuzzer = 8;
const int pinTrig = 9;
const int pinEcho = 10;
Servo tapa;
float medirDistancia();
void mostrarNivel(int verde, int amarillo, int rojo);
void setup() {
  pinMode(pinPir, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);
  pinMode(ledRojo, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  tapa.attach(pinServo);
  tapa.write(0);
  Serial.begin(9600);
}
void loop() {
  float distancia = medirDistancia();
  int presencia = digitalRead(pinPir);
  bool lecturaValida = distancia >= 0.0;
  bool lleno = false;
  const char* nivel = "ERROR";
  if (!lecturaValida) {
    mostrarNivel(LOW, LOW, LOW);
    tone(pinBuzzer, 300);
    tapa.write(0);
    Serial.print("SIN LECTURA VALIDA");
  } else {
    if (distancia <= 10.0) {
      lleno = true;
      nivel = "LLENO";
      mostrarNivel(LOW, LOW, HIGH);
      tone(pinBuzzer, 1000);
    } else if (distancia <= 25.0) {
      nivel = "MEDIO";
      mostrarNivel(LOW, HIGH, LOW);
      noTone(pinBuzzer);
    } else {
      nivel = "DISPONIBLE";
      mostrarNivel(HIGH, LOW, LOW);
      noTone(pinBuzzer);
    }
    if (presencia == HIGH && !lleno) {
      tapa.write(90);
    } else {
      tapa.write(0);
    }
    Serial.print("Distancia: ");
    Serial.print(distancia, 1);
    Serial.print(" cm | Nivel: ");
    Serial.print(nivel);
  }
  Serial.print(" | Presencia: ");
  Serial.print(presencia);
  Serial.print(" | Tapa: ");
  if (lecturaValida && presencia == HIGH && !lleno) {
    Serial.println("ABIERTA");
  } else {
    Serial.println("CERRADA");
  }
  delay(300);
}
float medirDistancia() {
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  unsigned long duracion = pulseIn(pinEcho, HIGH, 30000);
  if (duracion == 0) {
    return -1.0;
  }
  return duracion * 0.0343 / 2.0;
}
void mostrarNivel(int verde, int amarillo, int rojo) {
  digitalWrite(ledVerde, verde);
  digitalWrite(ledAmarillo, amarillo);
  digitalWrite(ledRojo, rojo);
}
